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
void Simulation::RenderLit( const int windowWidth, const int windowHeight ) const
{
    frmr::Vec3f viewVector = activeCamera.GetViewVector();

    glRotatef( -activeCamera.GetRotation().GetX(), 1.0f, 0.0f, 0.0f );
    glRotatef( -activeCamera.GetRotation().GetY(), 0.0f, 1.0f, 0.0f );
    glTranslatef( -activeCamera.GetPosition().GetX(), -activeCamera.GetPosition().GetY(), -activeCamera.GetPosition().GetZ() );

	//unproject the four corners of the screen, then use them to build the view frustum
	int viewportParams[4];
	double modelViewParams[16];
	double projectionParams[16];

	glGetIntegerv( GL_VIEWPORT, viewportParams );
	glGetDoublev( GL_MODELVIEW_MATRIX, modelViewParams );
	glGetDoublev( GL_PROJECTION_MATRIX, projectionParams );

	vector<frmr::Vec3f> frustumVertices;
	double objX, objY, objZ;

	gluUnProject( 0.0, (double) windowHeight, 0.0, &modelViewParams[0], &projectionParams[0], &viewportParams[0], &objX, &objY, &objZ ); //top left
	frustumVertices.push_back( activeCamera.GetPosition() + ( frmr::Vec3f( (float) objX, (float) objY, (float) objZ ) - activeCamera.GetPosition() ) * 1000.0f );
	gluUnProject( 0.0, 0.0, 0.0, &modelViewParams[0], &projectionParams[0], &viewportParams[0], &objX, &objY, &objZ ); //bottom left
	frustumVertices.push_back( activeCamera.GetPosition() + ( frmr::Vec3f( (float) objX, (float) objY, (float) objZ ) - activeCamera.GetPosition() ) * 1000.0f );
	gluUnProject( (double) windowWidth, 0.0, 0.0, &modelViewParams[0], &projectionParams[0], &viewportParams[0], &objX, &objY, &objZ ); //bottom right
	frustumVertices.push_back( activeCamera.GetPosition() + ( frmr::Vec3f( (float) objX, (float) objY, (float) objZ ) - activeCamera.GetPosition() ) * 1000.0f );
	gluUnProject( (double) windowWidth, (double) windowHeight, 0.0, &modelViewParams[0], &projectionParams[0], &viewportParams[0], &objX, &objY, &objZ ); //top right
	frustumVertices.push_back( activeCamera.GetPosition() + ( frmr::Vec3f( (float) objX, (float) objY, (float) objZ ) - activeCamera.GetPosition() ) * 1000.0f );

    Frustum viewFrustum( activeCamera.GetPosition(), frustumVertices );

    staticGeometry.Render( activeCamera.GetCurrentZoneNum(), activeCamera.GetPosition(), viewFrustum );
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
    : activeCamera( "ActiveCamera", frmr::Vec3f( 0.0f, 0.0f, 10.0f ), frmr::Vec2f(), 2 ),
      staticGeometry( "X:/Produce/Wizmatch/dev/tools/Zone Compiler/bin/Debug/twocubes.wzz", assets )
{
    //staticLights.push_back( Light( frmr::Vec3f( 80.0f, 0.0f, 0.0f ), frmr::Vec3f( 12.0f, 12.0f, 12.0f ), 0 ) );
    //staticLights.push_back( Light( frmr::Vec3f( -80.0f, 0.0f, 0.0f ), frmr::Vec3f( 9.0f, 9.0f, 9.0f ), 0 ) );
}

Simulation::~Simulation()
{
}
