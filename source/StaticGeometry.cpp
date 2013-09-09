#include "StaticGeometry.h"

void StaticGeometry::Render() const
{
    glColor3f( 1.0f, 1.0f, 1.0f );
    glCallList( zone );
}

StaticGeometry::StaticGeometry()
{
    zone = glGenLists( 1 );
    glNewList( zone, GL_COMPILE );
        glBegin( GL_QUADS );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( -100.0f, -100.0f, 100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( -100.0f, 100.0f, 100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, 100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( 100.0f, -100.0f, 100.0f );

            glNormal3f( 1.0f, 0.0f, 0.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( 100.0f, -100.0f, 100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, 100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, -100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( 100.0f, -100.0f, -100.0f );

            glNormal3f( -1.0f, 0.0f, 0.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( -100.0f, -100.0f, -100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( -100.0f, 100.0f, -100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( -100.0f, 100.0f, 100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( -100.0f, -100.0f, 100.0f );

            glNormal3f( 0.0f, 0.0f, -1.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( -100.0f, -100.0f, -100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( -100.0f, 100.0f, -100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, -100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( 100.0f, -100.0f, -100.0f );

            glNormal3f( 0.0f, 1.0f, 0.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( -100.0f, 100.0f, 100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, 100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( 100.0f, 100.0f, -100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( -100.0f, 100.0f, -100.0f );

            glNormal3f( 0.0f, -1.0f, 0.0f );
            glTexCoord2f( 0.0f, 0.0f );
            glVertex3f( 100.0f, -100.0f, 100.0f );
            glTexCoord2f( 0.0f, 1.0f );
            glVertex3f( 100.0f, -100.0f, -100.0f );
            glTexCoord2f( 1.0f, 1.0f );
            glVertex3f( -100.0f, -100.0f, -100.0f );
            glTexCoord2f( 1.0f, 0.0f );
            glVertex3f( -100.0f, -100.0f, 100.0f );
        glEnd();
    glEndList();
}

StaticGeometry::~StaticGeometry()
{
    //free display list
}
