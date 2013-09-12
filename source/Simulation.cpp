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

Camera Simulation::GetCamera() const
{
    return activeCamera;
}

vector<Light> Simulation::GetStaticLights() const
{
    return staticLights;
}

void Simulation::RenderLit() const
{
    glRotatef( -activeCamera.GetRotation().GetX(), 1.0f, 0.0f, 0.0f );
    glRotatef( -activeCamera.GetRotation().GetY(), 0.0f, 1.0f, 0.0f );
    glTranslatef( -activeCamera.GetPosition().GetX(), -activeCamera.GetPosition().GetY(), -activeCamera.GetPosition().GetZ() );
    staticGeometry.Render();
}

bool Simulation::LoadMap( const string filename )
{
    return true;
}

void Simulation::UnloadCurrentMap()
{

}

void Simulation::Update( const int32_t elapsedTime, const float deltaTime, const InputState &inputs, const float mouseSensitivity )
{
    activeCamera.Update( inputs, mouseSensitivity, deltaTime );
}

Simulation::Simulation()
    : activeCamera( "ActiveCamera", frmr::Vec3f(), frmr::Vec2f() )
{
    //staticLights.push_back( Light( frmr::Vec3f( 80.0f, 0.0f, 0.0f ), frmr::Vec3f( 12.0f, 12.0f, 12.0f ) ) );
    staticLights.push_back( Light( frmr::Vec3f( -80.0f, 0.0f, 0.0f ), frmr::Vec3f( 9.0f, 9.0f, 9.0f ) ) );
}

Simulation::~Simulation()
{
}
