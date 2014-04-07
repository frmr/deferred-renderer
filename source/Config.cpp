#include "config.h"
#include "frmr/TextFile.h"
#include <stdlib.h>

int     EngineConfig::GetWindowWidth() const        { return windowWidth; }
int     EngineConfig::GetWindowHeight() const       { return windowHeight; }
int     EngineConfig::GetFullscreenWidth() const    { return fullscreenWidth; }
int     EngineConfig::GetFullscreenHeight() const   { return fullscreenHeight; }
int     EngineConfig::GetActiveWidth() const        { return ( fullscreen ) ? fullscreenWidth : windowWidth; }
int     EngineConfig::GetActiveHeight() const       { return ( fullscreen ) ? fullscreenHeight : windowHeight; }
bool    EngineConfig::GetFullscreen() const         { return fullscreen; }
float	EngineConfig::GetFOV() const                { return fov; }
float	EngineConfig::GetActiveVerticalFOV() const	{ return (float) GetActiveHeight() / (float) GetActiveWidth() * fov; }
bool    EngineConfig::GetFilterTextures() const     { return filterTextures; }
float   EngineConfig::GetMasterVolume() const       { return masterVolume; }
float   EngineConfig::GetEffectsVolume() const      { return effectsVolume; }
float   EngineConfig::GetMusicVolume() const        { return musicVolume; }
float   EngineConfig::GetMouseSensitivity() const   { return mouseSensitivity; }

EngineConfig::EngineConfig( const string &configFilename )
{
    //set defaults
    windowWidth = 800;
    windowHeight = 600;
    fullscreenWidth = 800;
    fullscreenHeight = 600;
    fullscreen = false;
    fov = 120.0f;
    filterTextures = false;
    masterVolume = 1.0f;
    effectsVolume = 1.0f;
    musicVolume = 1.0f;
    mouseSensitivity = 0.1f;

    frmr::TextFile configFile( configFilename );

    for ( auto lineIt : configFile.GetLines() )
    {
        if      ( lineIt[0] == "windowWidth" )      { windowWidth = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "windowHeight" )     { windowHeight = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "fullscreenWidth" )  { fullscreenWidth = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "fullscreenHeight" ) { fullscreenHeight = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "fullscreen" )       { fullscreen = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "fov" )              { fov = atof( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "fulterTextures" )   { filterTextures = atoi( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "masterVolume" )     { masterVolume = atof( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "effectsVolume" )    { effectsVolume = atof( lineIt[1].c_str() ) ; }
        else if ( lineIt[0] == "musicVolume" )      { musicVolume = atof( lineIt[1].c_str() ); }
        else if ( lineIt[0] == "mouseSensitivity" ) { mouseSensitivity = atof( lineIt[1].c_str() ); }
    }


}
