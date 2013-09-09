#ifndef LIGHT_H
#define LIGHT_H

#include "frmr_Vec3f.h"

class Light
{
private:
    static constexpr float  attenuation = 0.1f;
    static constexpr float  intensityLowerBound = 0.003f;
    frmr::Vec3f             position;
    frmr::Vec3f             color;
    float                   radius;

private:
    float CalculateRadius() const;

public:
    frmr::Vec3f GetPosition() const;
    frmr::Vec3f GetColor() const;
    float GetAttenuation() const;

public:
    Light( const frmr::Vec3f &position, const frmr::Vec3f &color );
};

#endif // LIGHT_H
