#include "Light.h"

float Light::CalculateRadius() const
{
    float largestColorComponent = ( color.GetX() > color.GetY() ) ? color.GetX() : color.GetY();
    largestColorComponent = ( largestColorComponent > color.GetZ() ) ? largestColorComponent : color.GetZ();

    //return largestColorComponent / intensityLowerBound * linearAttenuation;
    return 800.0f;
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

void Light::RenderShadowVolume() const
{
    glBindTexture( GL_TEXTURE_2D, 0 );
    staticShadowVolume.Render();
}

Light::Light( const frmr::Vec3f &position, const frmr::Vec3f &color, const float radius, const GLuint staticShadowVolumeDisplayList )
    : position( position ),
      color( color ),
      radius( radius ),
      staticShadowVolume( staticShadowVolumeDisplayList )
{
//    GLuint shadowList = glGenLists( 1 );
//    glNewList( shadowList, GL_COMPILE );
//        glBegin( GL_QUADS );
//            glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f );
//            glVertex3f( 90.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f );
//            glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 110.f, -50.0f, -50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f );
//            glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 110.0f, -50.0f, -50.0f );
//            glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, 50.0f );
//            glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f ); glVertex3f( 110.0f, -50.0f, -50.0f );
//        glEnd();
//    glEndList();
//
//    staticShadowVolume = Light::ShadowVolume( shadowList );
}
