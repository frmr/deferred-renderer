#ifndef FRMR_MATH_H
#define FRMR_MATH_H

#include "../frmr/Vec2f.h"
#include "../frmr/Vec3f.h"

namespace frmr
{
    int         Round( const float value );
    int         Round( const double value );

    float       VectorDot( const frmr::Vec2f &vecA, const frmr::Vec2f &vecB );
    float       VectorDot( const frmr::Vec3f &vecA, const frmr::Vec3f &vecB );

    frmr::Vec3f VectorCross( const frmr::Vec3f &vecA, const frmr::Vec3f &vecB );

    float       CalculateRotationFromCoords( const frmr::Vec3f &coord );
	frmr::Vec3f	CalculateVectorFromRotation( const float rotationX, const float rotationY ); //takes degrees

    float       NormaliseAngle( const float &angle );

    bool		LinePlaneIntersection( const frmr::Vec3f &planeNormal, const frmr::Vec3f &planeVertex, const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector, const bool limitToBounds, frmr::Vec3f &intersect );
    frmr::Vec3f LinePointIntersection( const frmr::Vec3f &pA, const frmr::Vec3f &pB, const frmr::Vec3f &px, const bool limitToBounds );
    frmr::Vec3f LineLineIntersection( const frmr::Vec3f &startA, const frmr::Vec3f &vecA, const frmr::Vec3f &startB, const frmr::Vec3f &vecB, const bool limitToBounds );
}

#endif
