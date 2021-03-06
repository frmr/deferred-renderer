#ifndef FRMR_TRIANGLE_H
#define FRMR_TRIANGLE_H

#include "../frmr/Vec3f.h"

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
        frmr::Vec3f vec12; //vector from vert1 to vert2

        frmr::Vec3f normal;

    private:
        frmr::Vec3f CalculateNormal() const;

    public:
        bool        Contains( const frmr::Vec3f &point, const bool closed ) const;
        bool		LineIntersection( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector, const bool lineBounds, const bool triangleBounds, frmr::Vec3f &intersect ) const;

        frmr::Vec3f GetVert0() const;
        frmr::Vec3f GetVert1() const;
        frmr::Vec3f GetVert2() const;

        frmr::Vec3f GetVec01() const;
        frmr::Vec3f GetVec02() const;
        frmr::Vec3f GetVec12() const;

        frmr::Vec3f GetNormal() const;

    public:
        Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2 );

        Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                  const frmr::Vec3f &vec01, const frmr::Vec3f &vec02, const frmr::Vec3f &vec12,
                  const frmr::Vec3f &normal );

        Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                  const frmr::Vec3f &normal );
    };
}

#endif // FRMR_TRIANGLE_H
