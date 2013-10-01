#include "StaticGeometry.h"

#include <iostream>

using std::cout;
using std::endl;

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
    : zoneTree( frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 100.0f, 100.0f, 100.0f ) )
{
    vector<int> coord;
    zoneTree.AddChild( coord, frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 0.0f, 0.0f, 0.0f ) );

    coord.push_back( 0 );
    int* coolData;
    coolData = new int(31);
    cout << *coolData << endl;
    zoneTree.AddChild( coord, frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( -50.0f, -50.0f, -50.0f ), coolData );

    cout << *zoneTree.GetData( frmr::Vec3f( -75.0f, -75.0f, -75.0f ) ) << endl;
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
