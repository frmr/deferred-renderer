#include "StaticGeometry.h"

vector<int16_t> Zone::Render() const
{
    vector<int16_t> visibleZones;
    visibleZones.push_back( 0 );
    return visibleZones;
}

void StaticGeometry::Render() const
{
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    //determine which zone the player is in
    //draw that zone
        //draw the geometry
        //draw the portals
        //
    for ( auto zoneIt : zones )
    {
        //glCallList( zoneIt. );
    }
}

StaticGeometry::StaticGeometry()
{
//    zone = glGenLists( 1 );
//    glNewList( zone, GL_COMPILE );
//        glBegin( GL_QUADS );
//            glNormal3f( 0.0f, 0.0f, 1.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( -100.0f, -100.0f, 100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( -100.0f, 100.0f, 100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, 100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( 100.0f, -100.0f, 100.0f );
//
//            glNormal3f( 1.0f, 0.0f, 0.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( 100.0f, -100.0f, 100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, 100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( 100.0f, -100.0f, -100.0f );
//
//            glNormal3f( -1.0f, 0.0f, 0.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( -100.0f, -100.0f, -100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( -100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( -100.0f, 100.0f, 100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( -100.0f, -100.0f, 100.0f );
//
//            glNormal3f( 0.0f, 0.0f, -1.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( 100.0f, -100.0f, -100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( -100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( -100.0f, -100.0f, -100.0f );
//
//            glNormal3f( 0.0f, 1.0f, 0.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( -100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( 100.0f, 100.0f, 100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( -100.0f, 100.0f, 100.0f );
//
//            glNormal3f( 0.0f, -1.0f, 0.0f );
//            glTexCoord2f( 0.0f, 0.0f );
//            glVertex3f( 100.0f, -100.0f, 100.0f );
//            glTexCoord2f( 0.0f, 1.0f );
//            glVertex3f( 100.0f, -100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 1.0f );
//            glVertex3f( -100.0f, -100.0f, -100.0f );
//            glTexCoord2f( 1.0f, 0.0f );
//            glVertex3f( -100.0f, -100.0f, 100.0f );
//        glEnd();
//    glEndList();
}

StaticGeometry::~StaticGeometry()
{
    //free display list
}
