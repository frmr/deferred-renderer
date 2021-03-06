#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

using std::string;

class EngineConfig
{
private:
    int     windowWidth;
    int     windowHeight;
    int     fullscreenWidth;
    int     fullscreenHeight;
    bool    fullscreen;
    float   fov;
    bool    filterTextures;
    float   masterVolume;
    float   effectsVolume;
    float   musicVolume;
    float   mouseMenuSensitivity;
    float	mouseGameSensitivity;

public:
    int     GetWindowWidth() const;
    int     GetWindowHeight() const;
    int     GetFullscreenWidth() const;
    int     GetFullscreenHeight() const;
    int     GetActiveWidth() const;
    int     GetActiveHeight() const;
    bool    GetFullscreen() const;
    float	GetFOV() const;
	float	GetActiveVerticalFOV() const;
    bool    GetFilterTextures() const;
    float   GetMasterVolume() const;
    float   GetEffectsVolume() const;
    float   GetMusicVolume() const;
    float   GetMouseMenuSensitivity() const;
    float   GetMouseGameSensitivity() const;

public:
    EngineConfig( const string &configFilename );
};

class InterfaceConfig
{

};

class InputConfig
{

};

#endif // CONFIG_H
