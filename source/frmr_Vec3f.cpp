#include "frmr_Vec3f.h"
#include <cmath>

bool frmr::Vec3f::IsValid() const
{
    return valid;
}

float frmr::Vec3f::Length()
{
	if (length == -1.0f)
	{
		length = sqrt( x * x + y * y + z * z );
	}
	return length;
}

float frmr::Vec3f::GetX() const
{
	return x;
}

float frmr::Vec3f::GetY() const
{
	return y;
}

float frmr::Vec3f::GetZ() const
{
	return z;
}

void frmr::Vec3f::Reset()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    length = 0.0f;
    valid = true;
}

void frmr::Vec3f::SetValid( const bool newValid )
{
    valid = newValid;
}

frmr::Vec3f frmr::Vec3f::Unit()
{
	Length();
	if ( length > 0.0001f )
    {
        x /= length;
        y /= length;
        z /= length;
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
	return Vec3f( x + rhs.x, y + rhs.y, z + rhs.z );
}

frmr::Vec3f frmr::Vec3f::operator- ( const Vec3f &rhs ) const
{
	return Vec3f( x - rhs.x, y - rhs.y, z - rhs.z );
}

frmr::Vec3f frmr::Vec3f::operator* ( const float &rhs ) const
{
	return Vec3f( x * rhs, y * rhs, z * rhs );
}

frmr::Vec3f frmr::Vec3f::operator/ ( const float &rhs ) const
{
	return Vec3f( x / rhs, y / rhs, z / rhs );
}

frmr::Vec3f& frmr::Vec3f::operator+= ( const Vec3f &rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	length = -1.0f;
	return *this;
}

frmr::Vec3f& frmr::Vec3f::operator-= ( const Vec3f &rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	length = -1.0f;
	return *this;
}

frmr::Vec3f& frmr::Vec3f::operator*= ( const float &rhs )
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	length = -1.0f;
	return *this;
}

frmr::Vec3f::Vec3f( const float x, const float y, const float z )
	: x( x ), y( y ), z( z ), length( -1.0f ), valid( true )
{
}

frmr::Vec3f::Vec3f()
	: x( 0.0f ), y( 0.0f ), z( 0.0f ), length( 0.0f ), valid( true )
{
}

frmr::Vec3f::~Vec3f()
{
}
