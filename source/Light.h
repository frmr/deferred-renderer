#ifndef LIGHT_H
#define LIGHT_H

#include "frmr_Vec3f.h"

class Light
{
private:
    static constexpr float  linearAttenuation = 0.3f;
    static constexpr float  quadraticAttenuation = 0.01f;
    static constexpr float  intensityLowerBound = 0.003f;
    frmr::Vec3f             position;
    frmr::Vec3f             color;
    float                   radius;

private:
    float CalculateRadius() const;

public:
    frmr::Vec3f GetColor() const;
    float       GetLinearAttenuation() const;
    frmr::Vec3f GetPosition() const;
    float       GetRadius() const;
    float       GetQuadraticAttenuation() const;

public:
    Light( const frmr::Vec3f &position, const frmr::Vec3f &color );
};

#endif // LIGHT_H
