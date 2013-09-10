#include "Light.h"

float Light::CalculateRadius() const
{
    float largestColorComponent = ( color.GetX() > color.GetY() ) ? color.GetX() : color.GetY();
    largestColorComponent = ( largestColorComponent > color.GetZ() ) ? largestColorComponent : color.GetZ();

    //return largestColorComponent / intensityLowerBound * linearAttenuation;
    return 10.0f;
}

frmr::Vec3f Light::GetPosition() const
{
    return position;
}

frmr::Vec3f Light::GetColor() const
{
    return color;
}

float Light::GetLinearAttenuation() const
{
    return linearAttenuation;
}

float Light::GetQuadraticAttenuation() const
{
    return quadraticAttenuation;
}

Light::Light( const frmr::Vec3f &position, const frmr::Vec3f &color )
    : position( position ),
      color( color ),
      radius( CalculateRadius() )
{

}
