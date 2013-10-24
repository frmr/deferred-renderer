#include <iostream>
#include <fstream>

#include "StaticGeometry.h"
#include "frmr_encode.h"
#include "frmr_Vec2f.h"
#include "frmr_Vec3f.h"

using std::cout;
using std::endl;

void StaticGeometry::Portal::Render() const
{
    glBindTexture( GL_TEXTURE_2D, 0 );
    glCallList( displayList );
}

int16_t StaticGeometry::Portal::GetTargetZoneNum() const
{
    return targetZoneNum;
}

StaticGeometry::Portal::Portal( const GLuint displayList, const int16_t targetZoneNum )
    : displayList( displayList ), targetZoneNum( targetZoneNum )
{
}

StaticGeometry::Portal::~Portal()
{
    glDeleteLists( displayList, 1 );
}

void StaticGeometry::Zone::TexTriangleGroup::Render() const
{
    glBindTexture( GL_TEXTURE_2D, textureNum );
    glCallList( displayList );
}

StaticGeometry::Zone::TexTriangleGroup::TexTriangleGroup( const GLuint displayList, GLuint textureNum )
    : displayList( displayList ), textureNum( textureNum )
{
}

StaticGeometry::Zone::TexTriangleGroup::TexTriangleGroup::~TexTriangleGroup()
{
    glDeleteLists( displayList, 1 );
}

int16_t StaticGeometry::Zone::GetZoneNum() const
{
    return zoneNum;
}

vector<int16_t> StaticGeometry::Zone::Render() const
{
    vector<int16_t> visibleZones;
    visibleZones.push_back( 0 );
    return visibleZones;
}

StaticGeometry::Zone::Zone( const vector<TexTriangleGroup> &texTriangleGroups, const vector<frmr::Triangle> &collTriangles, const vector<Portal> &portals, const vector<Light> &lights )
    : texTriangleGroups( texTriangleGroups ),
      collTriangles( collTriangles ),
      portals( portals ),
      lights( lights )
{
}

vector<StaticGeometry::Zone> StaticGeometry::LoadZoneFile( const string &zoneDataFilename, const AssetManager &assets ) const
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

                //POLYGONS NEED TO BE ORDERED BY TEXTURE TO AVOID GLBINDTEXTURE

                glBindTexture( GL_TEXTURE_2D, assets.GetTexture( texName, AssetManager::SearchMode::PERMANENT ) ); //TODO change this to temporary
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

            vector<frmr::Triangle> collTriangles;

            int32_t numOfCollTriangles = frmr::DecodeINT32( zoneString.substr( i, 4 ) );
            i += 4;

            for ( int collTriangleIndex = 0; collTriangleIndex < numOfCollTriangles; collTriangleIndex++ )
            {
                collTriangles.push_back( frmr::Triangle( frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+36, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+40, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+44, 4 ) ) ) ) );

                i += 48
            }

            vector<frmr::Triangle> portals;

            int16_t numOfPortals = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int portalIndex = 0; portalIndex < numOfPortals; portalIndex++ )
            {
                int16_t targetZoneNum = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;
                int16_t numOfTriangles = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;

                GLuint portalDisplayList = glGenLists(1);
                glNewList( zoneDisplayList, GL_COMPILE );

                for ( int triangleIndex = 0; triangleIndex < numOfTriangles; triangleIndex++ )
                {
                    frmr::Vec3f vert0( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                    frmr::Vec3f vert1( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) );
                    frmr::Vec3f vert2( frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ) );
                    i += 36;
                }
            }

            int16_t numOfLights = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int lightIndex = 0; lightIndex < numOfLights; lightIndex++ )
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

StaticGeometry::StaticGeometry( const string &zoneDataFilename, const AssetManager &assets )
    : zoneTree( frmr::Vec3f( -100.0f, -100.0f, -100.0f ), frmr::Vec3f( 100.0f, 100.0f, 100.0f ) )
{
    zones = LoadZoneFile( zoneDataFilename, assets );
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
