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

Camera Simulation::GetActiveCamera() const
{
    return activeCamera;
}

vector<Light> Simulation::GetStaticLights() const
{
    return staticGeometry.GetStaticLights();
}

ProjectionState Simulation::RenderLit( const int windowWidth, const int windowHeight ) const
{
	glPushMatrix();

		activeCamera.ApplyTransformation();
		ProjectionState cameraProjection;

		//unproject the four corners of the screen and use them to build the view frustum
		vector<frmr::Vec3f> frustumVertices;
		frustumVertices.reserve( 4 );
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( 0.0f, 			windowHeight, 	0.0f ) ) );	//top left
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( 0.0f, 			0.0f, 			0.0f ) ) );	//bottom left
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( windowWidth, 	0.0f, 			0.0f ) ) );	//bottom right
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( windowWidth, 	windowHeight, 	0.0f ) ) );	//top right

		Frustum viewFrustum( activeCamera.GetPosition(), frustumVertices );

		staticGeometry.Render( activeCamera.GetZoneNum(), activeCamera.GetPosition(), cameraProjection, viewFrustum );

    glPopMatrix();

    return cameraProjection;
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
    :	activeCamera( frmr::Vec3f(), frmr::Vec2f(), false, 0 ),
		spectator( "Spectator", frmr::Vec3f( 30.0f, 0.0f, 0.0f ), frmr::Vec2f(), 0 ),
		staticGeometry( "../maps/twocubes.wzz", assets )
{
    //staticLights.push_back( Light( frmr::Vec3f( 80.0f, 0.0f, 0.0f ), frmr::Vec3f( 12.0f, 12.0f, 12.0f ), 0 ) );
    //staticLights.push_back( Light( frmr::Vec3f( -80.0f, 0.0f, 0.0f ), frmr::Vec3f( 9.0f, 9.0f, 9.0f ), 0 ) );
}

Simulation::~Simulation()
{
}
