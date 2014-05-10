#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "frmr/frmrMath.h"



frmr::Vec3f	Camera::GetPosition() const
{
	return position;
}

frmr::Vec2f	Camera::GetRotation() const
{
	return rotation;
}

int16_t Camera::GetZoneNum() const
{
	return zoneNum;
}

Camera::Camera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum )
	:	position( position ),
		rotation( rotation ),
		zoneNum( zoneNum )
{
}
