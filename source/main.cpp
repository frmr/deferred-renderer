#include "windows.h"

#include "Config.h"
#include "InputState.h"
#include "RenderManager.h"
#include "Simulation.h"
#include "frmr_TimeManager.h"

void ModifyWindow( sf::RenderWindow* const window, const EngineConfig engineCfg )
{
    if ( engineCfg.GetFullscreen() )
    {
        window->create( sf::VideoMode( engineCfg.GetFullscreenWidth(), engineCfg.GetFullscreenHeight() ), "Wizmatch", sf::Style::Fullscreen, sf::ContextSettings( 24, 8 ) );
    }
    else
    {
        window->create( sf::VideoMode( engineCfg.GetWindowWidth(), engineCfg.GetWindowHeight() ), "Wizmatch", sf::Style::Default, sf::ContextSettings( 24, 8 ) );
    }
}

int main()
{
    EngineConfig    engineCfg( "engine.cfg" );

    sf::RenderWindow window;
    ModifyWindow( &window, engineCfg );
    window.setMouseCursorVisible( false );
    window.setFramerateLimit( 120 );

    bool isClient = true;
    bool isServer = false;

    frmr::TimeManager   timer;
    InputState          inputs;
    RenderManager       renderer ( engineCfg );
    Simulation          gameSim;

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

        gameSim.Update( timer.GetElapsedTime(), timer.GetDeltaTime(), inputs, engineCfg.GetMouseSensitivity() );

        renderer.Render( gameSim, engineCfg );
        window.display();

        timer.Stop();
    }
}
