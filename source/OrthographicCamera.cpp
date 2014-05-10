#ifndef ORTHOGONAL_CAMERA_H
#define ORTHOGONAL_CAMERA_H

#include "OrthographicCamera.h"

#include <SFML/OpenGL.hpp>

void OrthographicCamera::ApplyTransformation() const
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glRotatef( -rotation.GetX(), 1.0f, 0.0f, 0.0f );
	glRotatef( -rotation.GetY(), 0.0f, 1.0f, 0.0f );
	glTranslatef( -position.GetX(), -position.GetY(), -position.GetZ() );
}

OrthographicCamera::OrthographicCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int width, const int height )
	:	Camera( position, rotation, 0 ),
		width( (double) width ),
		height( (double) height )
{
}

OrthographicCamera::OrthographicCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum, const int width, const int height )
	:	Camera( position, rotation, zoneNum ),
		width( (double) width ),
		height( (double) height )
{
}

#endif // ORTHOGONAL_CAMERA_H
