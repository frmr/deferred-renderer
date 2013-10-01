#ifndef FRMR_TRIANGLE_H
#define FRMR_TRIANGLE_H

#include <SFML/OpenGL.hpp>

#include "frmr_Vec2f.h"
#include "frmr_Vec3f.h"

namespace frmr
{
    class Triangle
    {
    private:
        frmr::Vec3f vert0;
        frmr::Vec3f vert1;
        frmr::Vec3f vert2;

        frmr::Vec3f vec01; //vector from vert0 to vert1
        frmr::Vec3f vec02; //vector from vert0 to vert2

        frmr::Vec2f texCoord0;
        frmr::Vec2f texCoord1;
        frmr::Vec2f texCoord2;

        frmr::Vec3f normal;

        GLuint      displayList;

    private:
        frmr::Vec3f CalculateNormal() const;
        GLuint      CreateDisplayList() const;

    public:
        bool        ContainsPoint( const frmr::Vec3f &point ) const;

        frmr::Vec3f GetVert0() const;
        frmr::Vec3f GetVert1() const;
        frmr::Vec3f GetVert2() const;

        frmr::Vec3f GetVec01() const;
        frmr::Vec3f GetVec02() const;

        frmr::Vec3f GetNormal() const;

        void        Render() const;

    public:
        Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                  const frmr::Vec2f &texCoord0, const frmr::Vec2f &texCoord1, const frmr::Vec2f &texCoord2 );

        Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                  const frmr::Vec3f &vec01, const frmr::Vec3f &vec02,
                  const frmr::Vec2f &texCoord0, const frmr::Vec2f &texCoord1, const frmr::Vec2f &texCoord2,
                  const frmr::Vec3f &normal );
    };
}

#endif // FRMR_TRIANGLE_H
