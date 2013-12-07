#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <vector>
#include "frmr_Triangle.h"

class Frustum
{
private:
    vector<frmr::Triangle> faces;

public:
    bool                Contains( const frmr::Vec3f &point ) const;
    vector<frmr::Vec3f> GetIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const;

public:
    Frustum( const frmr::Vec3f &viewVector, const float fov, const frmr::Vec2f &lowerLeft, const frmr::Vec2f &viewportSize );
    Frustum( const frmr::Vec3f &viewVector, const float fov, const frmr::Vec2f &lowerLeft, const frmr::Vec2f &viewportSize, const float nearPlane, const float farPlane );
};

#endif // FRUSTUM_H
