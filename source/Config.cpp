#include "config.h"

int     EngineConfig::GetWindowWidth() const        { return windowWidth; }
int     EngineConfig::GetWindowHeight() const       { return windowHeight; }
int     EngineConfig::GetFullscreenWidth() const    { return fullscreenWidth; }
int     EngineConfig::GetFullscreenHeight() const   { return fullscreenHeight; }
int     EngineConfig::GetActiveWidth() const        { return ( fullscreen ) ? fullscreenWidth : windowWidth; }
int     EngineConfig::GetActiveHeight() const       { return ( fullscreen ) ? fullscreenHeight : windowHeight; }
bool    EngineConfig::GetFullscreen() const         { return fullscreen; }
int     EngineConfig::GetFOV() const                { return fov; }
float   EngineConfig::GetMasterVolume() const       { return masterVolume; }
float   EngineConfig::GetEffectsVolume() const      { return effectsVolume; }
float   EngineConfig::GetMusicVolume() const        { return musicVolume; }
float   EngineConfig::GetMouseSensitivity() const   { return mouseSensitivity; }

EngineConfig::EngineConfig( const string &configFilename )
{
    windowWidth = 1440;
    windowHeight = 900;
    fullscreenWidth = 1920;
    fullscreenHeight = 1080;
    fullscreen = true;
    fov = 120;
    masterVolume = 1.0f;
    effectsVolume = 1.0f;
    musicVolume = 1.0f;
    mouseSensitivity = 0.13f;
}
