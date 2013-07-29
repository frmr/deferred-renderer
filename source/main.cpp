#include "irrlicht.h"

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






    enum class AppStage
    {
        MAIN_MENU,
        IN_GAME,
        OPTIONS
    };

    AppStage stage = AppStage::IN_GAME;

    while ( device->run() )
    {
        driver->beginScene(true, true, 0);

        if ( stage == AppStage::MAIN_MENU )
        {

        }
        else if ( stage == AppStage::IN_GAME )
        {

        }
        else if ( stage == AppStage::OPTIONS )
        {

        }

        driver->endScene();
    }

    device->drop();
}
