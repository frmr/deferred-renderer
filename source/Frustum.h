#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <vector>
#include "frmr_Triangle.h"
#include "frmr_Vec2f.h"

using std::vector;

class Frustum
{
private:
	frmr::Vec3f				position;
	vector<frmr::Vec3f>		edgeVectors;
    vector<frmr::Triangle> 	faces;

public:
    bool                	Contains( const frmr::Vec3f &point ) const;
    vector<frmr::Vec3f> 	GetLineIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const;
    vector<frmr::Vec3f>		GetVisibleTrianglePoints( const frmr::Triangle &triangle ) const;
    vector<frmr::Triangle>	GetFaces() const;

public:
    Frustum( const frmr::Vec3f &cameraPosition, const frmr::Vec2f &cameraRotation, const float fovX, const float fovY, const float nearPlane, const float farPlane );
    Frustum( const frmr::Vec3f &cameraPosition, const vector<frmr::Vec3f> &vertices );
};

#endif // FRUSTUM_H
