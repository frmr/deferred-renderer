#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"
#include "Frustum.h"

class PerspectiveCamera : public Camera
{
private:
	int		verticalFov;
	float	fovRatio;

public:
	void 	ApplyTransformation() const;
	Frustum	GetFrustum() const;

public:
	PerspectiveCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum, const int verticalFov, const float fovRatio );
};

#endif // PERSPECTIVE_CAMERA_H
