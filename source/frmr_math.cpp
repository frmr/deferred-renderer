#include "frmr_math.h"

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

int frmr::Round( const float value )
{
    return (int) floor( value + 0.5f );
}

int frmr::Round( const double value )
{
    return (int) floor( value + 0.5 );
}

float frmr::VectorDot( const frmr::Vec2f &vect1, const frmr::Vec2f &vect2 )
{
    return vect1.GetX() * vect2.GetX() + vect1.GetY() * vect2.GetY();
}

float frmr::VectorDot( const frmr::Vec3f &vect1, const frmr::Vec3f &vect2 )
{
    return vect1.GetX() * vect2.GetX() + vect1.GetY() * vect2.GetY() + vect1.GetZ() * vect2.GetZ();
}

frmr::Vec3f frmr::VectorCross( const frmr::Vec3f &vect1, const frmr::Vec3f &vect2 )
{
    return frmr::Vec3f( vect1.GetY() * vect2.GetZ() - vect1.GetZ() * vect2.GetY(),
                        vect1.GetZ() * vect2.GetX() - vect1.GetX() * vect2.GetZ(),
                        vect1.GetX() * vect2.GetY() - vect1.GetY() * vect2.GetX() );
}

//TODO make this function return degrees instead of radians
float frmr::CalculateRotationFromCoords( const frmr::Vec3f &coord )
{
    if ( coord.GetX() >= 0.0f && coord.GetZ() >= 0.0f )
    {
        return asinf( coord.GetX() );
    }
    else if ( coord.GetX() >= 0.0f && coord.GetZ() < 0.0f )
    {
        return acosf( coord.GetZ() );
    }
    else if ( coord.GetX() < 0.0f && coord.GetZ() >= 0.0f )
    {
        return asinf( coord.GetX() );
    }
    else
    {
        return -acosf( coord.GetZ() );
    }
}

float frmr::NormaliseAngle( const float &angle )
{
    if ( angle >= 360.0f )
    {
        return angle - 360.0f;
    }
    else if ( angle < 0.0f )
    {
        return angle + 360.0f;
    }
    else
    {
        return angle;
    }
}

frmr::Vec3f frmr::LinePlaneIntersection(const frmr::Vec3f &planeNormal, const frmr::Vec3f &planeVertex, const frmr::Vec3f &lineStart, const frmr::Vec3f &lineDirection, const bool bidirectional ) //bidirectional refers to the line i.e. check in opposite direction?
{
    float parallelCheck = VectorDot( planeNormal, lineDirection );

    if ( parallelCheck == 0.0f )
    {
        return frmr::Vec3f();
    }
    else
    {
        float vectorMult = VectorDot( planeNormal, planeVertex - lineStart ) / parallelCheck;
        if ( vectorMult <= 0.0f && !bidirectional )
        {
            cout << "frmr::LinePlaneIntersection() - Line is not bidirectional." << endl;
            return frmr::Vec3f();
        }
        else
        {
            return lineStart + lineDirection * vectorMult;
        }
    }
}

frmr::Vec3f frmr::LinePointIntersection( const frmr::Vec3f &p1, const frmr::Vec3f &p2, const frmr::Vec3f &px, const bool limitToBounds )
{
    Vec3f lineVector = p2 - p1;

    float u = ( px.GetX() - p1.GetX() ) * lineVector.GetX() + ( px.GetY() - p1.GetY() ) * lineVector.GetY() + ( px.GetZ() - p1.GetZ() ) * lineVector.GetZ();
    float dist = lineVector.Length();
    u /= ( dist * dist );

    if ( !limitToBounds )
    {
        return p1 + lineVector * u;
    }
    else
    {
        //if point of intersection is not on the line
        if ( u < 0.0f || u > 1.0f )
        {
            //check which vertex is closest
            float p1Dist = ( p1 - px ).Length();
            float p2Dist = ( p2 - px ).Length();

            return ( p1Dist < p2Dist ) ? p1 : p2;
        }
        else
        {
            return p1 + lineVector * u;
        }
    }
}

frmr::Vec3f frmr::LineLineIntersection( const frmr::Vec3f &start1, const frmr::Vec3f &vec1, const frmr::Vec3f &start2, const frmr::Vec3f &vec2, const bool limitToBounds )
{
    float parallelCheck = vec1.GetY() * vec2.GetX() - vec1.GetX() * vec2.GetY();
    if ( parallelCheck == 0.0f )
    {
        return frmr::Vec3f();
    }
    else
    {
        float multiplier = ( vec1.GetY() * start1.GetX() - vec1.GetY() * start2.GetX() + vec1.GetX() * start2.GetY() - vec1.GetX() * start1.GetY() ) / parallelCheck;
        if ( limitToBounds && ( multiplier > 1.0f || multiplier < 0.0f ) )
        {
            return frmr::Vec3f();
        }
        else
        {
            return start2 + vec2 * multiplier;
        }
    }
}
