#include "irrlicht.h"
#include "Simulation.h"

int main()
{
    //setup irrlicht
    //IrrlichtDevice* device = createDevice( video::EDT_OPENGL, core::dimension2d<u32>(1920, 1080), 32, true, false, false, &receiver );
    irr::IrrlichtDevice* device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>( 1920, 1080 ), 32, true, false, false );

	if ( device == NULL )
	{
	    return 1; // could not create selected driver.
	}

	irr::video::IVideoDriver* driver = device->getVideoDriver();

    Simulation gameSim( device );

    AppStage stage = AppStage::IN_GAME;

    while ( device->run() )
    {
        driver->beginScene(true, true, 0);



        driver->endScene();
    }

    device->drop();
}
