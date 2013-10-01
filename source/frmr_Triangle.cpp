#include "frmr_Triangle.h"

#include "frmr_math.h"

frmr::Vec3f frmr::Triangle::CalculateNormal() const
{
    return frmr::VectorCross( vec01, vec02 ).Unit();
}

GLuint frmr::Triangle::CreateDisplayList() const
{
    GLuint listIndex = glGenLists( 1 );
    glNewList( listIndex, GL_COMPILE );
        glBegin( GL_TRIANGLES );
            glNormal3f( normal.GetX(), normal.GetY(), normal.GetZ() );
            glTexCoord2f( texCoord0.GetX(), texCoord0.GetY() );
            glVertex3f( vert0.GetX(), vert0.GetY(), vert0.GetZ() );
            glTexCoord2f( texCoord1.GetX(), texCoord1.GetY() );
            glVertex3f( vert1.GetX(), vert1.GetY(), vert1.GetZ() );
            glTexCoord2f( texCoord2.GetX(), texCoord2.GetY() );
            glVertex3f( vert2.GetX(), vert2.GetY(), vert2.GetZ() );
        glEnd();
    glEndList();

    return listIndex;
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

    return ( ( u > 0 ) && ( v > 0 ) && ( u + v < 1 ) ) ? true : false;
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

frmr::Vec3f frmr::Triangle::GetNormal() const
{
    return normal;
}

void frmr::Triangle::Render() const
{
    glCallList( displayList );
}

frmr::Triangle::Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                          const frmr::Vec2f &texCoord0, const frmr::Vec2f &texCoord1, const frmr::Vec2f &texCoord2 )
    : vert0( vert0 ),
      vert1( vert1 ),
      vert2( vert2 ),
      vec01( vert1 - vert0 ),
      vec02( vert2 - vert0 ),
      texCoord0( texCoord0 ),
      texCoord1( texCoord1 ),
      texCoord2( texCoord2 ),
      normal( CalculateNormal() ),
      displayList( CreateDisplayList() )
{
}

frmr::Triangle::Triangle( const frmr::Vec3f &vert0, const frmr::Vec3f &vert1, const frmr::Vec3f &vert2,
                          const frmr::Vec3f &vec01, const frmr::Vec3f &vec02,
                          const frmr::Vec2f &texCoord0, const frmr::Vec2f &texCoord1, const frmr::Vec2f &texCoord2,
                          const frmr::Vec3f &normal )
    : vert0( vert0 ),
      vert1( vert1 ),
      vert2( vert2 ),
      vec01( vec01 ),
      vec02( vec02 ),
      texCoord0( texCoord0 ),
      texCoord1( texCoord1 ),
      texCoord2( texCoord2 ),
      normal( normal ),
      displayList( CreateDisplayList() )
{

}
