#include "windows.h"

#include "InputState.h"
#include "RenderManager.h"
#include "Simulation.h"
#include "frmr_TimeManager.h"

int main()
{
    sf::RenderWindow window( sf::VideoMode( 1440, 900 ), "Wizmatch", sf::Style::Default, sf::ContextSettings( 24, 8 ) );

    bool isClient = true;
    bool isServer = false;

    frmr::TimeManager   timer;
    InputState          inputs;
    RenderManager       renderer;
    Simulation          gameSim;

    gameSim.ChangeMap( "arse" );


    bool running = true;

    while ( running )
    {
        timer.Start();

        inputs.Update( window );

        if ( inputs.GetExitHeld() )
        {
            running = false;
        }

        gameSim.Update( timer.GetElapsedTime(), timer.GetDeltaTime() );

        renderer.Render( gameSim );
        window.display();

        timer.Stop();
    }
}
