#ifndef CAMERA_H
#define CAMERA_H

#include "frmr/Vec2f.h"
#include "ProjectionState.h"

class Camera
{
private:
	frmr::Vec3f			position;
	frmr::Vec2f			rotation;
	float				fov;
	float				vfov;
	bool				orthographic;
	int16_t				zoneNum;

public:
	void			ApplyTransformation() const;
	frmr::Vec3f		GetPosition() const;
	frmr::Vec2f		GetRotation() const;
	bool			GetOrthographic() const;
	ProjectionState	GetProjectionState() const;
	int16_t			GetZoneNum() const;
	void			RefreshProjectionState();

public:
	Camera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const bool orthographic, const int16_t zoneNum );
};

#endif // CAMERA_H
