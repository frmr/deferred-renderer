#include "GLEW/glew.h"
#include <SFML/OpenGL.hpp>

#include "AssetManager.h"
#include "Config.h"
#include "InputState.h"
#include "RenderManager.h"
#include "Simulation.h"
#include "frmr/TimeManager.h"

void ModifyWindow( sf::RenderWindow* const window, const EngineConfig engineCfg )
{
    sf::Uint32 style = ( engineCfg.GetFullscreen() ) ? sf::Style::Fullscreen : sf::Style::Default;
    window->create( sf::VideoMode( engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() ), "Wizmatch", style, sf::ContextSettings( 24, 8 ) );
}

int main()
{
    EngineConfig    engineCfg( "../engine.cfg" );

    sf::RenderWindow window;
    ModifyWindow( &window, engineCfg );
    window.setMouseCursorVisible( false );
    window.setFramerateLimit( 120 );

    bool isClient = true;
    bool isServer = false;

    frmr::TimeManager   timer;
    InputState          inputs; //this should be done within the Client
    AssetManager        assets( "../data.txt", engineCfg.GetFilterTextures() );
    RenderManager       renderer( engineCfg );
    Simulation          gameSim( assets );

    gameSim.ChangeMap( "arse" );


    bool running = true;

    while ( running )
    {
        timer.Start();

        inputs.Update( window, engineCfg );

        if ( inputs.GetExitHeld() )
        {
            running = false;
        }

        gameSim.Update( timer.GetElapsedTime(), timer.GetDeltaTime(), inputs, engineCfg.GetMouseGameSensitivity() );

        renderer.Render( gameSim, engineCfg );
        //renderer.SimpleRender( gameSim, engineCfg );
        window.display();

        timer.Stop();
    }
}
