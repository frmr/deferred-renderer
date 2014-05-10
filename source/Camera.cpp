#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "frmr/frmrMath.h"

void Camera::ApplyTransformation() const
{
	//glLoadIdentity();
	glRotatef( -rotation.GetX(), 1.0f, 0.0f, 0.0f );
	glRotatef( -rotation.GetY(), 0.0f, 1.0f, 0.0f );
	glTranslatef( -position.GetX(), -position.GetY(), -position.GetZ() );
}

frmr::Vec3f	Camera::GetPosition() const
{
	return position;
}

frmr::Vec2f	Camera::GetRotation() const
{
	return rotation;
}

bool Camera::GetOrthographic() const
{
	return orthographic;
}

int16_t Camera::GetZoneNum() const
{
	return zoneNum;
}

Camera::Camera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const bool orthographic, const int16_t zoneNum )
	:	position( position ),
		rotation( rotation ),
		orthographic( orthographic ),
		zoneNum( zoneNum )
{
}
