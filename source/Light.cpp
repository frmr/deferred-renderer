#include "Light.h"

float Light::CalculateRadius() const
{
    float largestColorComponent = ( color.GetX() > color.GetY() ) ? color.GetX() : color.GetY();
    largestColorComponent = ( largestColorComponent > color.GetZ() ) ? largestColorComponent : color.GetZ();

    return largestColorComponent / intensityLowerBound * attenuation;
}

frmr::Vec3f Light::GetPosition() const
{
    return position;
}

frmr::Vec3f Light::GetColor() const
{
    return color;
}

float Light::GetAttenuation() const
{
    return attenuation;
}

Light::Light( const frmr::Vec3f &position, const frmr::Vec3f &color )
    : position( position ),
      color( color ),
      radius( CalculateRadius() )
{

}
