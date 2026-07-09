import argparse
import os
import struct
import subprocess
import sys


def read_exports(path):
    with open(path, "rb") as f:
        data = f.read()

    if data[:2] != b"MZ":
        sys.exit(f"error: not a PE file: {path}")

    e_lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    if data[e_lfanew:e_lfanew + 4] != b"PE\0\0":
        sys.exit(f"error: bad PE signature: {path}")

    coff = e_lfanew + 4
    num_sections = struct.unpack_from("<H", data, coff + 2)[0]
    size_opt = struct.unpack_from("<H", data, coff + 16)[0]
    opt = coff + 20

    magic = struct.unpack_from("<H", data, opt)[0]
    if magic == 0x20B:
        dir_off = opt + 112
    elif magic == 0x10B:
        dir_off = opt + 96
    else:
        sys.exit(f"error: unknown optional header magic {magic:#x}")

    exp_rva = struct.unpack_from("<I", data, dir_off)[0]
    if exp_rva == 0:
        sys.exit(f"error: no export table in {path}")

    sections = []
    sec_off = opt + size_opt
    for i in range(num_sections):
        base = sec_off + i * 40
        v_size, v_addr, raw_size, raw_ptr = struct.unpack_from("<IIII", data, base + 8)
        sections.append((v_addr, v_size, raw_size, raw_ptr))

    def rva_to_off(rva):
        for v_addr, v_size, raw_size, raw_ptr in sections:
            span = max(v_size, raw_size)
            if v_addr <= rva < v_addr + span:
                return rva - v_addr + raw_ptr
        sys.exit(f"error: RVA {rva:#x} outside all sections")

    exp = rva_to_off(exp_rva)
    num_names = struct.unpack_from("<I", data, exp + 24)[0]
    names_rva = struct.unpack_from("<I", data, exp + 32)[0]
    names_off = rva_to_off(names_rva)

    names = []
    for i in range(num_names):
        str_rva = struct.unpack_from("<I", data, names_off + i * 4)[0]
        str_off = rva_to_off(str_rva)
        end = data.index(b"\0", str_off)
        names.append(data[str_off:end].decode("ascii"))
    return names


def write_def(names, out_path):
    lines = ["EXPORTS"]
    for n in sorted(names):
        lines.append(f"    {n}=baselib_original.{n}")
    with open(out_path, "w", encoding="ascii", newline="\n") as f:
        f.write("\n".join(lines) + "\n")


def main():
    repo_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    default_def = os.path.join(repo_root, "src", "proxy", "baselib.def")

    ap = argparse.ArgumentParser(
        description="Generate src/proxy/baselib.def from a game's baselib.dll, then optionally build the proxy.")
    ap.add_argument("baselib", help="path to the game's original baselib.dll")
    ap.add_argument("--def-out", default=default_def,
                    help="output .def path (default: src/proxy/baselib.def)")
    ap.add_argument("--build", action="store_true",
                    help="after writing the .def, build the baselib_proxy target")
    ap.add_argument("--build-dir", default=os.path.join(repo_root, "build"),
                    help="CMake build dir to use with --build (default: build)")
    ap.add_argument("--config", default="Release", help="CMake config for --build (default: Release)")
    args = ap.parse_args()

    if not os.path.isfile(args.baselib):
        sys.exit(f"error: file not found: {args.baselib}")

    names = read_exports(args.baselib)
    if not names:
        sys.exit("error: no named exports found (ordinal-only baselib is not supported)")

    write_def(names, args.def_out)
    print(f"wrote {len(names)} forwards to {args.def_out}")

    if args.build:
        cmd = ["cmake", "--build", args.build_dir, "--config", args.config, "--target", "baselib_proxy"]
        print("running:", " ".join(cmd))
        raise SystemExit(subprocess.call(cmd))

    print("done. build baselib_proxy to produce baselib.dll (or re-run with --build).")


if __name__ == "__main__":
    main()
