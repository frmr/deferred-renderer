#include "IcosphereGenerator.h"

GLuint IcosphereGenerator::GenerateIcosphereDisplayList( const int subdivisions )
{
    GLuint sphereList = glGenLists( 1 );
    glNewList( sphereList, GL_COMPILE );
        glBegin( GL_TRIANGLES );

        glEnd();
    glEndList();

    return sphereList;
}
