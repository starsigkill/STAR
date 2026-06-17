#pragma once
#include "core/star_common.h"
#include "steam/isteammusic.h"

class StarSteamMusic : public ISteamMusic {
public:
    static StarSteamMusic& get();
    bool BIsEnabled() override;
    bool BIsPlaying() override;
    AudioPlayback_Status GetPlaybackStatus() override;
    void Play() override;
    void Pause() override;
    void PlayPrevious() override;
    void PlayNext() override;
    void SetVolume(float flVolume) override;
    float GetVolume() override;
private:
    StarSteamMusic() = default;
};
