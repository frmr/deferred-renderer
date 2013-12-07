#include "frmr_Vec2f.h"
#include "math.h"

float frmr::Vec2f::GetX() const
{
	return x;
}

float frmr::Vec2f::GetY() const
{
	return y;
}

bool frmr::Vec2f::IsValid() const
{
    return valid;
}

float frmr::Vec2f::Length()
{
	if ( length == -1.0f )
	{
		length = sqrt(x * x + y * y);
	}
	return length;
}

void frmr::Vec2f::Reset()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
	valid = true;
}

void frmr::Vec2f::SetValid( const bool newValid )
{
    valid = newValid;
}

frmr::Vec2f frmr::Vec2f::Unit()
{
	Length();
	if ( length > 0.0001f )
    {
        x /= length;
        y /= length;
        length = 1.0f;
    }
    else
    {
        Reset();
    }
	return *this;
}

frmr::Vec2f frmr::Vec2f::operator+ ( const Vec2f &rhs ) const
{
	return Vec2f( x + rhs.x, y + rhs.y );
}

frmr::Vec2f frmr::Vec2f::operator- ( const Vec2f &rhs ) const
{
	return Vec2f( x - rhs.x, y - rhs.y );
}

frmr::Vec2f frmr::Vec2f::operator* ( const float &rhs ) const
{
	return Vec2f( x * rhs, y * rhs );
}

frmr::Vec2f frmr::Vec2f::operator/ ( const float &rhs ) const
{
	return Vec2f( x / rhs, y / rhs );
}

frmr::Vec2f& frmr::Vec2f::operator+= ( const Vec2f &rhs )
{
	x += rhs.x;
	y += rhs.y;
	length = -1.0f;
	return *this;
}

frmr::Vec2f& frmr::Vec2f::operator-= ( const Vec2f &rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	length = -1.0f;
	return *this;
}

frmr::Vec2f& frmr::Vec2f::operator*= ( const float &rhs )
{
	x *= rhs;
	y *= rhs;
	length = -1.0f;
	return *this;
}

frmr::Vec2f::Vec2f( const float x, const float y )
	: x( x ), y( y ), length( -1.0f ), valid( true )
{
}

frmr::Vec2f::Vec2f()
	: x( 0.0f ), y( 0.0f ), length( 0.0f ), valid( true )
{
}

frmr::Vec2f::~Vec2f()
{
}
