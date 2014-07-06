#include "Light.h"

#include "frmr/Vec2f.h"

float Light::CalculateRadius() const
{
    float largestColorComponent = ( color.GetX() > color.GetY() ) ? color.GetX() : color.GetY();
    largestColorComponent = ( largestColorComponent > color.GetZ() ) ? largestColorComponent : color.GetZ();

    //return largestColorComponent / intensityLowerBound * linearAttenuation;
    return 5.0f;
}

bool Light::CastsShadows() const
{
	return castShadows;
}

frmr::Vec3f Light::GetColor() const
{
    return color;
}

float Light::GetLinearAttenuation() const
{
    return linearAttenuation;
}

frmr::Vec3f Light::GetPosition() const
{
    return position;
}

float Light::GetRadius() const
{
    return radius;
}

float Light::GetQuadraticAttenuation() const
{
    return quadraticAttenuation;
}

Light::Light( const frmr::Vec3f &position, const frmr::Vec3f &color, const float radius, const int16_t zoneNum, const bool castShadows )
    : position( position ),
      color( color ),
      radius( radius ),
      castShadows( castShadows ),
      zoneNum( zoneNum )
{
	if ( castShadows )
	{
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( 0.0f, 270.0f ), zoneNum, 90.0f, 1.0f ) );	//+X
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( 0.0f, 90.0f ), zoneNum, 90.0f, 1.0f ) );	//-X
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( 90.0f, 0.0f ), zoneNum, 90.0f, 1.0f ) );	//+Y
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( -90.0f, 0.0f ), zoneNum, 90.0f, 1.0f ) );	//-Y
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( 0.0f, 180.0f ), zoneNum, 90.0f, 1.0f ) );	//+Z
		cameras.push_back( PerspectiveCamera( position, frmr::Vec2f( 0.0f, 0.0f ), zoneNum, 90.0f, 1.0f ) );	//-Z
	}

	//TODO: Calculate visible zones immediately and save
}
