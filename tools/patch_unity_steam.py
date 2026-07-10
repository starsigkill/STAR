import glob
import os
import sys
import subprocess
import tempfile

CS_CODE = """
using System;
using System.IO;
using System.Reflection;

class Program {
    static string targetFolder;
    static void Main(string[] args) {
        if (args.Length < 1) {
            Console.WriteLine("Usage: patch [dll_path]");
            return;
        }
        string dllPath = args[0];
        targetFolder = Path.GetDirectoryName(Path.GetFullPath(dllPath));
        AppDomain.CurrentDomain.AssemblyResolve += ResolveEventHandler;
        try {
            byte[] bytes = File.ReadAllBytes(dllPath);
            Assembly asm = Assembly.Load(bytes);
            Type t = null;
            try {
                foreach (Type type in asm.GetTypes()) {
                    if (type.Name == "SteamManager") {
                        t = type;
                        break;
                    }
                }
            } catch (ReflectionTypeLoadException ex) {
                foreach (Type type in ex.Types) {
                    if (type != null && type.Name == "SteamManager") {
                        t = type;
                        break;
                    }
                }
            }
            if (t == null) {
                Console.WriteLine("SteamManager type not found.");
                return;
            }
            FieldInfo f = t.GetField("enable", BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
            if (f == null) {
                Console.WriteLine("'enable' field not found on SteamManager.");
                return;
            }
            int token = f.MetadataToken;
            Console.WriteLine("Found 'enable' field token: " + token.ToString("X"));
            byte[] tb = BitConverter.GetBytes(token);
            
            bool patched = false;
            for (int i = 0; i < bytes.Length - 9; i++) {
                if (bytes[i] == 0x02 &&
                    bytes[i+1] == 0x7B &&
                    bytes[i+2] == tb[0] &&
                    bytes[i+3] == tb[1] &&
                    bytes[i+4] == tb[2] &&
                    bytes[i+5] == tb[3] &&
                    bytes[i+6] == 0x2D &&
                    bytes[i+8] == 0x2A) {
                    
                    Console.WriteLine("Found pattern at offset: 0x" + i.ToString("X") + ". Patching...");
                    bytes[i] = 0x17;
                    bytes[i+1] = 0x2D;
                    bytes[i+2] = 0x01;
                    bytes[i+3] = 0x2A;
                    bytes[i+4] = 0x00;
                    bytes[i+5] = 0x00;
                    bytes[i+6] = 0x00;
                    bytes[i+7] = 0x00;
                    bytes[i+8] = 0x00;
                    patched = true;
                    break;
                }
            }
            if (patched) {
                File.Copy(dllPath, dllPath + ".bak", true);
                File.WriteAllBytes(dllPath, bytes);
                Console.WriteLine("DLL patched successfully!");
            } else {
                Console.WriteLine("Pattern not found in DLL.");
            }
        } catch (Exception ex) {
            Console.WriteLine("Error: " + ex.ToString());
        }
    }

    private static Assembly ResolveEventHandler(object sender, ResolveEventArgs args) {
        string name = new AssemblyName(args.Name).Name + ".dll";
        string path = Path.Combine(targetFolder, name);
        if (File.Exists(path)) {
            try {
                return Assembly.Load(File.ReadAllBytes(path));
            } catch {}
        }
        return null;
    }
}
"""

def main():
    if len(sys.argv) < 2:
        print("Usage: python patch_unity_steam.py [path_to_game_dir_or_dll]")
        sys.exit(1)

    target = sys.argv[1]
    dll_path = None

    if os.path.isdir(target):
        matches = glob.glob(os.path.join(target, "**", "Assembly-CSharp.dll"), recursive=True) \
            or glob.glob(os.path.join(target, "**", "*Assembly.dll"), recursive=True)
        dll_path = matches[0] if matches else None
    elif os.path.isfile(target):
        dll_path = target

    if not dll_path or not os.path.exists(dll_path):
        print("Error: Target DLL or directory not found.")
        sys.exit(1)

    csc_path = next((p for p in (
        r"C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe",
        r"C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe",
    ) if os.path.exists(p)), None)
    if not csc_path:
        print("Error: MSVC C# Compiler (csc.exe) not found on this system.")
        sys.exit(1)

    temp_dir = tempfile.gettempdir()
    cs_file = os.path.join(temp_dir, "temp_patcher.cs")
    exe_file = os.path.join(temp_dir, "temp_patcher.exe")

    try:
        with open(cs_file, "w", encoding="utf-8") as f:
            f.write(CS_CODE)

        cmd = [csc_path, f"/out:{exe_file}", cs_file]
        res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if res.returncode != 0:
            print("Error: Compilation of patcher helper failed.")
            print(res.stdout)
            print(res.stderr)
            sys.exit(1)

        res = subprocess.run([exe_file, dll_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        print(res.stdout)
        if res.returncode != 0:
            print(res.stderr)
            sys.exit(1)

    finally:
        if os.path.exists(cs_file):
            try: os.remove(cs_file)
            except: pass
        if os.path.exists(exe_file):
            try: os.remove(exe_file)
            except: pass

if __name__ == "__main__":
    main()
