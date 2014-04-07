#include "../frmr/Vec3f.h"
#include <cmath>

array<float, 3>	frmr::Vec3f::GetArray() const
{
	return point;
}

float frmr::Vec3f::GetAt( const size_t index ) const
{
	return point[index];
}

float frmr::Vec3f::GetX() const
{
	return point[0];
}

float frmr::Vec3f::GetY() const
{
	return point[1];
}

float frmr::Vec3f::GetZ() const
{
	return point[2];
}

float frmr::Vec3f::Length()
{
	if (length == -1.0f)
	{
		length = sqrt( point[0] * point[0] + point[1] * point[1] + point[2] * point[2] );
	}
	return length;
}

void frmr::Vec3f::Reset()
{
	Set( 0.0f, 0.0f, 0.0f );
    length = 0.0f;
}

void frmr::Vec3f::Set( const float x, const float y, const float z )
{
	point.at( 0 ) = x;
	point.at( 1 ) = y;
	point.at( 2 ) = z;
	length = -1.0f;
}

void frmr::Vec3f::SetAt( const size_t index, const float newValue )
{
	point.at( index ) = newValue;
}

void frmr::Vec3f::SetX( const float newX )
{
	point.at( 0 ) = newX;
}

void frmr::Vec3f::SetY( const float newY )
{
	point.at( 1 ) = newY;
}

void frmr::Vec3f::SetZ( const float newZ )
{
	point.at( 2 ) = newZ;
}

size_t frmr::Vec3f::Size() const
{
	return point.size();
}

frmr::Vec3f frmr::Vec3f::Unit()
{
	Length();
	if ( length > 0.001f )
    {
        point.at( 0 ) /= length;
        point.at( 1 ) /= length;
        point.at( 2 ) /= length;
        length = 1.0f;
    }
    else
    {
        Reset();
    }
	return *this;
}

frmr::Vec3f frmr::Vec3f::operator+ ( const Vec3f &rhs ) const
{
	return Vec3f( point[0] + rhs.GetX(), point[1] + rhs.GetY(), point[2] + rhs.GetZ() );
}

frmr::Vec3f frmr::Vec3f::operator- ( const Vec3f &rhs ) const
{
	return Vec3f( point[0] - rhs.GetX(), point[1] - rhs.GetY(), point[2] - rhs.GetZ() );
}

frmr::Vec3f frmr::Vec3f::operator* ( const float &rhs ) const
{
	return Vec3f( point[0] * rhs, point[1] * rhs, point[2] * rhs );
}

frmr::Vec3f frmr::Vec3f::operator/ ( const float &rhs ) const
{
	return Vec3f( point[0] / rhs, point[1] / rhs, point[2] / rhs );
}

frmr::Vec3f& frmr::Vec3f::operator+= ( const Vec3f &rhs )
{
	point.at( 0 ) += rhs.GetX();
	point.at( 1 ) += rhs.GetY();
	point.at( 2 ) += rhs.GetZ();
	length = -1.0f;
	return *this;
}

frmr::Vec3f& frmr::Vec3f::operator-= ( const Vec3f &rhs )
{
	point.at( 0 ) -= rhs.GetX();
	point.at( 1 ) -= rhs.GetY();
	point.at( 2 ) -= rhs.GetZ();
	length = -1.0f;
	return *this;
}

frmr::Vec3f& frmr::Vec3f::operator*= ( const float &rhs )
{
	point.at( 0 ) *= rhs;
	point.at( 1 ) *= rhs;
	point.at( 2 ) *= rhs;
	length = -1.0f;
	return *this;
}

frmr::Vec3f& frmr::Vec3f::operator/= ( const float &rhs )
{
	point.at( 0 ) /= rhs;
	point.at( 1 ) /= rhs;
	point.at( 2 ) /= rhs;
	length = -1.0f;
	return *this;
}

frmr::Vec3f::Vec3f( const float x, const float y, const float z )
	: point({{ x, y, z }}), length( -1.0f )
{
}

frmr::Vec3f::Vec3f( const float xyz )
	: point({{ xyz, xyz, xyz }}), length( -1.0f )
{
}

frmr::Vec3f::Vec3f()
	: point({{ 0.0f, 0.0f, 0.0f }}), length( 0.0f )
{
}

frmr::Vec3f::~Vec3f()
{
}
