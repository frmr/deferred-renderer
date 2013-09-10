#include "IcosphereGenerator.h"

vector<IcosphereGenerator::Triangle> IcosphereGenerator::icosahedron = IcosphereGenerator::DefineIcosahedron();

GLuint IcosphereGenerator::GenerateIcosphereDisplayList( const int subdivisions )
{
    vector<Triangle> undivided = icosahedron;
    vector<Triangle> divided;

    //subdivide icosahedron
    for ( int i = 0; i < subdivisions; i++ )
    {
        for ( auto triangleIt : undivided )
        {
            frmr::Vec3f v01 = ( ( triangleIt.v0 + triangleIt.v1 ) / 2.0f ).Unit();
            frmr::Vec3f v12 = ( ( triangleIt.v1 + triangleIt.v2 ) / 2.0f ).Unit();
            frmr::Vec3f v20 = ( ( triangleIt.v2 + triangleIt.v0 ) / 2.0f ).Unit();

            divided.push_back( Triangle( triangleIt.v0, v01, v20 ) );
            divided.push_back( Triangle( v01, triangleIt.v1, v12 ) );
            divided.push_back( Triangle( v01, v12, v20 ) );
            divided.push_back( Triangle( v20, v12, triangleIt.v2 ) );
        }

        undivided = divided;
        divided.clear();
    }

    //put subdivided icosahedron into a display list
    GLuint sphereList = glGenLists( 1 );
    glNewList( sphereList, GL_COMPILE );
        glBegin( GL_TRIANGLES );
            for ( auto triangleIt : undivided )
            {
                glVertex3f( triangleIt.v0.GetX(), triangleIt.v0.GetY(), triangleIt.v0.GetZ() );
                glVertex3f( triangleIt.v1.GetX(), triangleIt.v1.GetY(), triangleIt.v1.GetZ() );
                glVertex3f( triangleIt.v2.GetX(), triangleIt.v2.GetY(), triangleIt.v2.GetZ() );
            }
        glEnd();
    glEndList();

    return sphereList;
}

vector<IcosphereGenerator::Triangle> IcosphereGenerator::DefineIcosahedron()
{
    vector<IcosphereGenerator::Triangle> tempIcosahedron( 20, Triangle() );
    tempIcosahedron[0] = Triangle( frmr::Vec3f( 0.0f, 0.0f, 1.0f ), frmr::Vec3f( 0.27639f, 0.85064f, 0.44721f ), frmr::Vec3f( -0.72360f, 0.52572f, 0.44721f ) );
    tempIcosahedron[1] = Triangle( frmr::Vec3f( 0.0f, 0.0f, 1.0f ), frmr::Vec3f( -0.72360f, 0.52572f, 0.44721f ), frmr::Vec3f( -0.72360f, -0.52572f, 0.44721f ) );
    tempIcosahedron[2] = Triangle( frmr::Vec3f( 0.0f, 0.0f, 1.0f ), frmr::Vec3f( -0.72360f, -0.52572f, 0.44721f ), frmr::Vec3f( 0.27639f, -0.85064f, 0.44721f ) );
    tempIcosahedron[3] = Triangle( frmr::Vec3f( 0.0f, 0.0f, 1.0f ), frmr::Vec3f( 0.27639f, -0.85064f, 0.44721f ), frmr::Vec3f( 0.89442f, 0.0f, 0.44721f ) );
    tempIcosahedron[4] = Triangle( frmr::Vec3f( 0.0f, 0.0f, 1.0f ), frmr::Vec3f( 0.89442f,	0.0f, 0.44721f ), frmr::Vec3f( 0.27639f, 0.85064f, 0.44721f ) );
    tempIcosahedron[5] = Triangle( frmr::Vec3f( 0.89442f, 0.0f, 0.44721f ), frmr::Vec3f( 0.72360f, -0.52572f, -0.44721f ), frmr::Vec3f( 0.72360f, 0.52572f, -0.44721f ) );
    tempIcosahedron[6] = Triangle( frmr::Vec3f( 0.89442f, 0.0f, 0.44721f ), frmr::Vec3f( 0.72360f, 0.52572f, -0.44721f ), frmr::Vec3f( 0.27639f, 0.85064f, 0.44721f ) );
    tempIcosahedron[7] = Triangle( frmr::Vec3f( 0.72360f, 0.52572f, -0.44721f ), frmr::Vec3f( -0.27639f, 0.85064f, -0.44721f ), frmr::Vec3f( 0.27639f, 0.85064f, 0.44721f ) );
    tempIcosahedron[8] = Triangle( frmr::Vec3f( 0.27639f, 0.85064f, 0.44721f ), frmr::Vec3f( -0.27639f, 0.85064f, -0.44721f ), frmr::Vec3f( -0.7236f, 0.52572f, 0.44721f ) );
    tempIcosahedron[9] = Triangle( frmr::Vec3f( -0.27639f, 0.85064f, -0.44721f ), frmr::Vec3f( -0.89442f, 0.0f, -0.44721f ), frmr::Vec3f( -0.7236f, 0.52572f, 0.44721f ) );
    tempIcosahedron[10] = Triangle( frmr::Vec3f( -0.7236f, 0.52572f, 0.44721f ),  frmr::Vec3f( -0.89442f, 0.0f, -0.44721f ), frmr::Vec3f( -0.7236f, -0.52572f, 0.44721f ) );
    tempIcosahedron[11] = Triangle( frmr::Vec3f( -0.7236f, -0.52572f, 0.44721f ), frmr::Vec3f( -0.89442f, 0.0f, -0.44721f ), frmr::Vec3f( -0.27639f, -0.85064f, -0.44721f ) );
    tempIcosahedron[12] = Triangle( frmr::Vec3f( -0.7236f, -0.52572f, 0.44721f ), frmr::Vec3f( -0.27639f, -0.85064f, -0.44721f ), frmr::Vec3f( 0.27639f, -0.85064f, 0.44721f ) );
    tempIcosahedron[13] = Triangle( frmr::Vec3f( 0.27639f, -0.85064f, 0.44721f ), frmr::Vec3f( -0.27639f, -0.85064f, -0.44721f ), frmr::Vec3f( 0.7236f, -0.52572f, -0.44721 ) );
    tempIcosahedron[14] = Triangle( frmr::Vec3f( 0.27639f, -0.85064f, 0.44721f ), frmr::Vec3f( 0.7236f, -0.52572f, -0.44721f ), frmr::Vec3f( 0.89442f, 0.0f, 0.44721f ) );
    tempIcosahedron[15] = Triangle( frmr::Vec3f( 0.0f, 0.0f, -1.0f ), frmr::Vec3f( -0.27639f, -0.85064f, -0.44721f ), frmr::Vec3f( -0.89442f, 0.0f, -0.44721f ) );
    tempIcosahedron[16] = Triangle( frmr::Vec3f( 0.0f, 0.0f, -1.0f ), frmr::Vec3f( 0.7236f, -0.52572f, -0.44721f ), frmr::Vec3f( -0.27639f, -0.85064f, -0.44721f ) );
    tempIcosahedron[17] = Triangle( frmr::Vec3f( 0.0f, 0.0f, -1.0f ), frmr::Vec3f( 0.7236f, 0.52572f, -0.44721f ), frmr::Vec3f( 0.7236f, -0.52572f, -0.44721f ) );
    tempIcosahedron[18] = Triangle( frmr::Vec3f( 0.0f, 0.0f, -1.0f ), frmr::Vec3f( -0.27639f, 0.85064f, -0.44721f ), frmr::Vec3f( 0.7236f, 0.52572f, -0.44721f ) );
    tempIcosahedron[19] = Triangle( frmr::Vec3f( 0.0f, 0.0f, -1.0f ), frmr::Vec3f( -0.89442f, 0.0f, -0.44721f ), frmr::Vec3f( -0.27639f, 0.85064f, -0.44721f ) );

    return tempIcosahedron;
}

