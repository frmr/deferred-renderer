#include "Frustum.h"

#include "frmr_math.h"

bool Frustum::Contains( const frmr::Vec3f &point ) const
{
    for ( auto faceIt : faces )
    {
        //if point is on the wrong side of the face
        //  return false
    }
    return true;
}

vector<frmr::Vec3f> Frustum::GetIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const
{
    vector<frmr::Vec3f> intersections;

    for ( auto faceIt : faces )
    {
        //get point of intersection
        //check if point is within face
        //if so, add to intersections
    }

    return intersections;
}

Frustum::Frustum( const frmr::Vec3f &viewVector, const float fov, const frmr::Vec2f &lowerLeft, const frmr::Vec2f &viewportSize )
{
    //create four triangles

}

Frustum::Frustum( const frmr::Vec3f &viewVector, const float fov, const frmr::Vec2f &lowerLeft, const frmr::Vec2f &viewportSize, const float nearPlane, const float farPlane )
{
    //create 12 triangles
}
