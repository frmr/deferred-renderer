#ifndef FRMR_MATH_H
#define FRMR_MATH_H

//#include <

#include "frmr_Vec2f.h"
#include "frmr_Vec3f.h"

namespace frmr
{
    int         Round( const float value );
    int         Round( const double value );

    float       VectorDot( const frmr::Vec2f &vect1, const frmr::Vec2f &vect2 );
    float       VectorDot( const frmr::Vec3f &vect1, const frmr::Vec3f &vect2 );

    frmr::Vec3f VectorCross( const frmr::Vec3f &vect1, const frmr::Vec3f &vect2 );

    float       CalculateRotationFromCoords( const frmr::Vec3f &coord );

    float       NormaliseAngle( const float &angle );

    frmr::Vec3f LinePlaneIntersection( const frmr::Vec3f &planeNormal, const frmr::Vec3f &planeVertex, const frmr::Vec3f &lineStart, const frmr::Vec3f &lineDirection, const bool bidirectional );
    frmr::Vec3f LinePointIntersection( const frmr::Vec3f &p1, const frmr::Vec3f &p2, const frmr::Vec3f &px, const bool limitToBounds );
    frmr::Vec3f LineLineIntersection( const frmr::Vec3f &start1, const frmr::Vec3f &vec1, const frmr::Vec3f &start2, const frmr::Vec3f &vec2, const bool limitToBounds );
}

#endif
