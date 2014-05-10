#include <iostream>

#include "Frustum.h"
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

PerspectiveCamera Simulation::GetActiveCamera() const
{
    return activeCamera;
}

vector<Light> Simulation::GetStaticLights() const
{
    return staticGeometry.GetStaticLights();
}

ProjectionState Simulation::RenderLit( const int viewportWidth, const int viewportHeight ) const
{
	glPushMatrix();

		activeCamera.ApplyTransformation();
		ProjectionState cameraProjection;
		staticGeometry.Render( activeCamera.GetZoneNum(), cameraProjection, activeCamera.GetFrustum() );

    glPopMatrix();

    return cameraProjection;
}

void Simulation::RenderShadowCasters( const PerspectiveCamera &lightView ) const
{
	glPushMatrix();

		lightView.ApplyTransformation();
		ProjectionState cameraProjection;
		staticGeometry.Render( activeCamera.GetZoneNum(), cameraProjection, activeCamera.GetFrustum() );

	glPopMatrix();
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
    spectator.Update( inputs, mouseSensitivity, deltaTime );
    activeCamera = spectator.GetCamera();
}

Simulation::Simulation( const AssetManager &assets )
    :	activeCamera( frmr::Vec3f(), frmr::Vec2f(), 0, 1.0f, 1.0f ),
		spectator( "Spectator", frmr::Vec3f( 30.0f, 0.0f, 0.0f ), frmr::Vec2f(), 0 ),
		staticGeometry( "../maps/twocubes.wzz", assets )
{
    //staticLights.push_back( Light( frmr::Vec3f( 80.0f, 0.0f, 0.0f ), frmr::Vec3f( 12.0f, 12.0f, 12.0f ), 0 ) );
    //staticLights.push_back( Light( frmr::Vec3f( -80.0f, 0.0f, 0.0f ), frmr::Vec3f( 9.0f, 9.0f, 9.0f ), 0 ) );
}

Simulation::~Simulation()
{
}
