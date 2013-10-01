#include "Light.h"

float Light::CalculateRadius() const
{
    float largestColorComponent = ( color.GetX() > color.GetY() ) ? color.GetX() : color.GetY();
    largestColorComponent = ( largestColorComponent > color.GetZ() ) ? largestColorComponent : color.GetZ();

    //return largestColorComponent / intensityLowerBound * linearAttenuation;
    return 80.0f;
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

void Light::RenderShadowVolumes() const
{
    for ( auto shadowIt : staticShadowVolumes )
    {
        shadowIt.Render();
    }
}

Light::Light( const frmr::Vec3f &position, const frmr::Vec3f &color )
    : position( position ),
      color( color ),
      radius( CalculateRadius() )
{
    GLuint shadowList = glGenLists( 1 );
    glNewList( shadowList, GL_COMPILE );
        glBegin( GL_QUADS );
            glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f );
            glVertex3f( 90.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f );
            glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 110.f, -50.0f, -50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f );
            glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 110.0f, -50.0f, -50.0f );
            glVertex3f( 90.0f, -50.0f, 50.0f ); glVertex3f( 110.0f, -50.0f, 50.0f ); glVertex3f( 110.0f, 50.0f, 50.0f ); glVertex3f( 90.0f, 50.0f, 50.0f );
            glVertex3f( 90.0f, -50.0f, -50.0f ); glVertex3f( 90.0f, 50.0f, -50.0f ); glVertex3f( 110.0f, 50.0f, -50.0f ); glVertex3f( 110.0f, -50.0f, -50.0f );
        glEnd();
    glEndList();

    staticShadowVolumes.push_back( Light::ShadowVolume( shadowList ) );
}
