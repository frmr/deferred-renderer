#include "../frmr/frmrMath.h"

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

float frmr::VectorDot( const frmr::Vec2f &vecA, const frmr::Vec2f &vecB )
{
    return vecA.GetX() * vecB.GetX() + vecA.GetY() * vecB.GetY();
}

float frmr::VectorDot( const frmr::Vec3f &vecA, const frmr::Vec3f &vecB )
{
    return vecA.GetX() * vecB.GetX() + vecA.GetY() * vecB.GetY() + vecA.GetZ() * vecB.GetZ();
}

frmr::Vec3f frmr::VectorCross( const frmr::Vec3f &vecA, const frmr::Vec3f &vecB )
{
    return frmr::Vec3f( vecA.GetY() * vecB.GetZ() - vecA.GetZ() * vecB.GetY(),
                        vecA.GetZ() * vecB.GetX() - vecA.GetX() * vecB.GetZ(),
                        vecA.GetX() * vecB.GetY() - vecA.GetY() * vecB.GetX() );
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

frmr::Vec3f	frmr::CalculateVectorFromRotation( const float rotationX, const float rotationY ) //takes degrees
{
	return frmr::Vec3f( -sin( rotationY * 0.01745f ), tan( rotationX * 0.01745f ), -cos( rotationY * 0.01745f ) ).Unit();
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

bool frmr::LinePlaneIntersection( const frmr::Vec3f &planeNormal, const frmr::Vec3f &planeVertex, const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector, const bool limitToBounds, frmr::Vec3f &intersect )
{
    float parallelCheck = VectorDot( planeNormal, lineVector );

    if ( parallelCheck < 0.001f && parallelCheck > -0.001f )
    {
        return false;
    }
    else
    {
        float vectorMult = VectorDot( planeNormal, planeVertex - lineStart ) / parallelCheck;
        //if ( ( vectorMult < 0.0f || vectorMult > 1.0f ) && limitToBounds )
        if ( vectorMult < 0.0f  || ( vectorMult > 1.0f && limitToBounds ) )
        {
            return false;
        }
        else
        {
            intersect = lineStart + lineVector * vectorMult;
            return true;
        }
    }
}

frmr::Vec3f frmr::LinePointIntersection( const frmr::Vec3f &pA, const frmr::Vec3f &pB, const frmr::Vec3f &px, const bool limitToBounds )
{
    Vec3f lineVector = pB - pA;

    float u = ( px.GetX() - pA.GetX() ) * lineVector.GetX() + ( px.GetY() - pA.GetY() ) * lineVector.GetY() + ( px.GetZ() - pA.GetZ() ) * lineVector.GetZ();
    float dist = lineVector.Length();
    u /= ( dist * dist );

    if ( !limitToBounds )
    {
        return pA + lineVector * u;
    }
    else
    {
        //if point of intersection is not on the line
        if ( u < 0.0f || u > 1.0f )
        {
            //check which vertex is closest
            float pADist = ( pA - px ).Length();
            float pBDist = ( pB - px ).Length();

            return ( pADist < pBDist ) ? pA : pB;
        }
        else
        {
            return pA + lineVector * u;
        }
    }
}

frmr::Vec3f frmr::LineLineIntersection( const frmr::Vec3f &startA, const frmr::Vec3f &vecA, const frmr::Vec3f &startB, const frmr::Vec3f &vecB, const bool limitToBounds )
{
    float parallelCheck = vecA.GetY() * vecB.GetX() - vecA.GetX() * vecB.GetY();
    if ( parallelCheck == 0.0f )
    {
        return frmr::Vec3f();
    }
    else
    {
        float multiplier = ( vecA.GetY() * startA.GetX() - vecA.GetY() * startB.GetX() + vecA.GetX() * startB.GetY() - vecA.GetX() * startA.GetY() ) / parallelCheck;
        if ( limitToBounds && ( multiplier > 1.0f || multiplier < 0.0f ) )
        {
            return frmr::Vec3f();
        }
        else
        {
            return startB + vecB * multiplier;
        }
    }
}
