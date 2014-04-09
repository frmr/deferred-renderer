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

Camera Simulation::GetCamera() const
{
    return activeCamera;
}

vector<Light> Simulation::GetStaticLights() const
{
    return staticGeometry.GetStaticLights();
}

//void Simulation::RenderLit( const float fovX, const float fovY ) const
ProjectionState Simulation::RenderLit( const int windowWidth, const int windowHeight ) const
{
    frmr::Vec3f viewVector = activeCamera.GetViewVector();

	glPushMatrix();

		glRotatef( -activeCamera.GetRotation().GetX(), 1.0f, 0.0f, 0.0f );
		glRotatef( -activeCamera.GetRotation().GetY(), 0.0f, 1.0f, 0.0f );
		glTranslatef( -activeCamera.GetPosition().GetX(), -activeCamera.GetPosition().GetY(), -activeCamera.GetPosition().GetZ() );

		//unproject the four corners of the screen and use them to build the view frustum
		ProjectionState cameraProjection;

		vector<frmr::Vec3f> frustumVertices;
		frustumVertices.reserve( 4 );
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( 0.0f, 			windowHeight, 	0.998f ) ) );	//top left
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( 0.0f, 			0.0f, 			0.998f ) ) );	//bottom left
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( windowWidth, 	0.0f, 			0.998f ) ) );	//bottom right
		frustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( windowWidth, 	windowHeight, 	0.998f ) ) );	//top right

		Frustum viewFrustum( activeCamera.GetPosition(), frustumVertices );

		staticGeometry.Render( activeCamera.GetCurrentZoneNum(), activeCamera.GetPosition(), cameraProjection, viewFrustum );

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
    activeCamera.Update( inputs, mouseSensitivity, deltaTime );
}

Simulation::Simulation( const AssetManager &assets )
    : activeCamera( "ActiveCamera", frmr::Vec3f( 0.0f, 0.0f, 10.0f ), frmr::Vec3f(), 2 ),
      staticGeometry( "../maps/twocubes.wzz", assets )
{
    //staticLights.push_back( Light( frmr::Vec3f( 80.0f, 0.0f, 0.0f ), frmr::Vec3f( 12.0f, 12.0f, 12.0f ), 0 ) );
    //staticLights.push_back( Light( frmr::Vec3f( -80.0f, 0.0f, 0.0f ), frmr::Vec3f( 9.0f, 9.0f, 9.0f ), 0 ) );
}

Simulation::~Simulation()
{
}
