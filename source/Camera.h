#ifndef CAMERA_H
#define CAMERA_H

#include "frmr/Vec2f.h"
#include "frmr/Vec3f.h"

class Camera
{
protected:
	frmr::Vec3f		position;
	frmr::Vec2f		rotation;
	int16_t			zoneNum;

public:
	virtual void	ApplyTransformation() const = 0;
	frmr::Vec3f		GetPosition() const;
	frmr::Vec2f		GetRotation() const;
	int16_t			GetZoneNum() const;


public:
	Camera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum );
};

#endif // CAMERA_H
