#include <iostream>

#include "Simulation.h"

using std::cout;
using std::endl;

void Simulation::LoadBillboardAnimation( const string filename )
{

}

bool Simulation::ChangeMap( const string filename )
{
    UnloadCurrentMap();
    LoadMap( filename );
    return true;
}

void Simulation::RenderLit() const
{
    //sceneManager->drawAll();
}

bool Simulation::LoadMap( const string filename )
{
    return true;
}

void Simulation::UnloadCurrentMap()
{

}

void Simulation::Update( const uint32_t elapsedTime, const float deltaTime )
{
}

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}
