#include "../frmr/Triangle.h"
#include "../frmr/frmrMath.h"

frmr::Vec3f frmr::Triangle::CalculateNormal() const
{
    return frmr::VectorCross( vec01, vec02 ).Unit();
}

bool frmr::Triangle::ContainsPoint( const frmr::Vec3f &point ) const
{
    frmr::Vec3f pVec = point - vert0;
    float dot11 = VectorDot( vec01, vec01 );
    float dot12 = VectorDot( vec01, vec02 );
    float dot1p = VectorDot( vec01, pVec );
    float dot22 = VectorDot( vec02, vec02 );
    float dot2p = VectorDot( vec02, pVec );

    float invDenom = 1.0f / ( dot11 * dot22 - dot12 * dot12 );
    float u = ( dot22 * dot1p - dot12 * dot2p ) * invDenom;
    float v = ( dot11 * dot2p - dot12 * dot1p ) * invDenom;

    return ( ( u > 0.0f ) && ( v > 0.0f ) && ( u + v < 1.0f ) ) ? true : false;
}

frmr::Vec3f frmr::Triangle::GetVert0() const
{
    return vert0;
}

frmr::Vec3f frmr::Triangle::GetVert1() const
{
    return vert1;
}

frmr::Vec3f frmr::Triangle::GetVert2() const
{
    return vert2;
}

frmr::Vec3f frmr::Triangle::GetVec01() const
{
    return vec01;
}

frmr::Vec3f frmr::Triangle::GetVec02() const
{
    return vec02;
}

frmr::Vec3f frmr::Triangle::GetVec12() const
{
	return vec12;
}

frmr::Vec3f frmr::Triangle::GetNormal() const
{
    return normal;
}

frmr::Triangle::Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2 )
    : vert0( vert0 ),
      vert1( vert1 ),
      vert2( vert2 ),
      vec01( vert1 - vert0 ),
      vec02( vert2 - vert0 ),
      vec12( vert2 - vert1 ),
      normal( CalculateNormal() )
{
}

frmr::Triangle::Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                          const frmr::Vec3f &vec01, const frmr::Vec3f &vec02, const frmr::Vec3f &vec12,
                          const frmr::Vec3f &normal )
    : vert0( vert0 ),
      vert1( vert1 ),
      vert2( vert2 ),
      vec01( vec01 ),
      vec02( vec02 ),
      vec12( vec12 ),
      normal( normal )
{
}

frmr::Triangle::Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                          const frmr::Vec3f &normal )
    : vert0( vert0 ),
      vert1( vert1 ),
      vert2( vert2 ),
      vec01( vert1 - vert0 ),
      vec02( vert2 - vert0 ),
      vec12( vert2 - vert1 ),
      normal( normal )
{
}
