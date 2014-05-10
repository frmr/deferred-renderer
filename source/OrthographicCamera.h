#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "Camera.h"

class OrthographicCamera : public Camera
{
private:
	double	width;
	double	height;

public:
	void ApplyTransformation() const;

public:
	OrthographicCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int width, const int height );
	OrthographicCamera( const frmr::Vec3f &position, const frmr::Vec2f &rotation, const int16_t zoneNum, const int width, const int height );
};

#endif // ORTHOGRAPHIC_CAMERA_H
