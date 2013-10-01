#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/OpenGL.hpp>
#include <stdint.h>
#include <vector>

#include "frmr_Vec3f.h"

using std::vector;

class Light
{
private:
    class ShadowVolume
    {
    private:
        GLuint  displayList;
    public:
        void Render() const
        {
            glCallList( displayList );
        }
    public:
        ShadowVolume( const GLuint &displayList )
            : displayList( displayList )
        {
        }
        ~ShadowVolume()
        {
            glDeleteLists( displayList, 1 );
        }
    };

private:
    static constexpr float  linearAttenuation = 0.3f;
    static constexpr float  quadraticAttenuation = 0.01f;
    static constexpr float  intensityLowerBound = 0.003f;
    frmr::Vec3f             position;
    frmr::Vec3f             color;
    float                   radius;

    vector<ShadowVolume>    staticShadowVolumes;

private:
    float CalculateRadius() const;

public:
    frmr::Vec3f GetColor() const;
    float       GetLinearAttenuation() const;
    frmr::Vec3f GetPosition() const;
    float       GetRadius() const;
    float       GetQuadraticAttenuation() const;
    void        RenderShadowVolumes() const;

public:
    Light( const frmr::Vec3f &position, const frmr::Vec3f &color );
};

#endif // LIGHT_H
