#include "Simulation.h"

void Simulation::Update()
{
}

Simulation::Simulation( irr::IrrlichtDevice* const device )
{
    sceneManager = device->getSceneManager();
}

Simulation::~Simulation()
{
}
