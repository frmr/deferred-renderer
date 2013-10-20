#include <iostream>
#include <fstream>

#include "StaticGeometry.h"
#include "frmr_encode.h"
#include "frmr_Vec2f.h"
#include "frmr_Vec3f.h"

using std::cout;
using std::endl;

vector<int16_t> StaticGeometry::Zone::Render() const
{
    vector<int16_t> visibleZones;
    visibleZones.push_back( 0 );
    return visibleZones;
}

vector<StaticGeometry::Zone> StaticGeometry::LoadZoneFile( const string &zoneDataFilename ) const
{
    vector<StaticGeometry::Zone> loadedZones;
    string zoneString;

    std::ifstream zoneFile( zoneDataFilename );
    if ( zoneFile.is_open() )
    {
        while ( zoneFile.good() )
        {
            zoneString += zoneFile.get();
        }
        zoneFile.close();

        int i = 0;

        int16_t numOfZones = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
        i = 2;

        for ( int zoneIndex = 0; zoneIndex < numOfZones; zoneIndex++ )
        {
            int16_t zoneNum = frmr::DecodeINT32( zoneString.substr( i, 2 ) );
            i += 2;
            int32_t numOfTexTriangles = frmr::DecodeINT32( zoneString.substr( i, 4 ) );
            i += 4;

            GLuint zoneDisplayList = glGenLists(1);
            glNewList( zoneDisplayList, GL_COMPILE );

            for ( int texTriangleIndex = 0; texTriangleIndex < numOfTexTriangles; texTriangleIndex++ )
            {
                int16_t texNameLength = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;
                string texName = zoneString.substr( i, texNameLength );
                i += texNameLength;

                glBindTexture( GL_TEXTURE_2D,  );
                glBegin( GL_TRIANGLES );
                    glNormal3f( frmr::DecodeFloat( zoneString.substr( i+60, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+64, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+68, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+36, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+52, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+56, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+40, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+44, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+48, 4 ) ) );
                glEnd();

                i += 72;
            }
            glEndList();

            int16_t numOfPortals = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int portalIndex = 0; portalIndex < numOfPortals; portalIndex++ )
            {

            }
        }

    }
    else
    {
        cout << "StaticGeometry::LoadZoneFile() - Failed to open zone file: " << zoneDataFilename << endl;
    }
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

StaticGeometry::StaticGeometry( const string &zoneDataFilename )
    : zoneTree( frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 100.0f, 100.0f, 100.0f ) )
{
    zones = LoadZoneFile( zoneDataFilename );
}

StaticGeometry::StaticGeometry()
    : zoneTree( frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 100.0f, 100.0f, 100.0f ) )
{
    int16_t* coolData;
    coolData = new int16_t(31);
    cout << *coolData << endl;

    zoneTree = frmr::Octree<int16_t>( frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 100.0f, 100.0f, 100.0f ) );

    vector<int> coord;
    zoneTree.AddChild( coord, frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 0.0f, 0.0f, 0.0f ) );

    coord.push_back( 0 );

    zoneTree.AddChild( coord, frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( -50.0f, -50.0f, -50.0f ), coolData );

    int16_t* foundData = zoneTree.GetData( frmr::Vec3f( -75.0f, -75.0f, -75.0f ) );
    if ( foundData == nullptr )
    {
        cout << "Returned null pointer." << endl;
    }
    else
    {
        cout << *foundData << endl;
    }
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
