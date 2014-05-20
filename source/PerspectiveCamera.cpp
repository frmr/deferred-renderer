#include "PerspectiveCamera.h"

#include <SFML/OpenGL.hpp>

void PerspectiveCamera::ApplyTransformation() const
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( (double) verticalFov, (double) fovRatio, 1.0, 5000.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glRotatef( -rotation.GetX(), 1.0f, 0.0f, 0.0f );
	glRotatef( -rotation.GetY(), 0.0f, 1.0f, 0.0f );
	glTranslatef( -position.GetX(), -position.GetY(), -position.GetZ() );
}

Frustum	PerspectiveCamera::GetFrustum() const
{
	return Frustum( position, rotation, verticalFov, fovRatio );
}

PerspectiveCamera::PerspectiveCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum, const int verticalFov, const float fovRatio )
	:	Camera( position, rotation, zoneNum ),
		verticalFov( verticalFov ),
		fovRatio( fovRatio )
{

}
