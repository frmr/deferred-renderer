#include <iostream>
#include <fstream>

#include "StaticGeometry.h"
#include "frmr_encode.h"
#include "frmr_math.h"
#include "frmr_Vec2f.h"
#include "frmr_Vec3f.h"

using std::cout;
using std::endl;

bool StaticGeometry::Portal::IsVisible( const frmr::Vec3f &cameraPosition ) const
{
    for ( auto triangleIt : triangles )
    {
        //if triangle is within view frustum
        frmr::Vec3f cameraToTriangleVector = triangleIt.GetVert0() - cameraPosition;

        //if triangle is facing the camera
        if ( frmr::VectorDot( triangleIt.GetNormal(), cameraToTriangleVector.Unit() ) > 0.0f )
        {
            //if triangle is within view frustum
            return true;
        }
    }
    return false;
}

int16_t StaticGeometry::Portal::GetTargetZoneNum() const
{
    return targetZoneNum;
}

StaticGeometry::Portal::Portal( const vector<frmr::Triangle> &triangles, const int16_t targetZoneNum )
    : triangles( triangles ), targetZoneNum( targetZoneNum )
{
}

void StaticGeometry::Zone::TexTriangleGroup::DeleteDisplayList()
{
    glDeleteLists( displayList, 1 );
}

GLuint StaticGeometry::Zone::TexTriangleGroup::GetDisplayList() const
{
    return displayList;
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

}

void StaticGeometry::Zone::DeleteDisplayLists()
{
    for ( auto texTriangleGroupIt : texTriangleGroups )
    {
        texTriangleGroupIt.DeleteDisplayList();
    }
}

vector<Light> StaticGeometry::Zone::GetLights() const
{
    return lights;
}

int16_t StaticGeometry::Zone::GetZoneNum() const
{
    return zoneNum;
}

void StaticGeometry::Zone::Render( const frmr::Vec3f &cameraPosition, const vector<Zone> &zones, vector<int> &renderedZonesRef ) const
{
    renderedZonesRef.push_back( zoneNum );

    for ( auto renderedZoneIt : renderedZonesRef )
    {
        cout << renderedZoneIt;
    }
    cout << endl;

    for ( auto texTriangleGroupIt : texTriangleGroups )
    {
        texTriangleGroupIt.Render();
    }

    for ( auto portalIt : portals )
    {
        //if portal target zone not already rendered
        bool targetZoneRendered = false;

        for ( auto renderedZone : renderedZonesRef )
        {
            if ( portalIt.GetTargetZoneNum() == renderedZone )
            {
                targetZoneRendered = true;
                break;
            }
        }

        if ( !targetZoneRendered )
        {
            //if ( portalIt.IsVisible( cameraPosition, viewFrustum ) )
            if ( portalIt.IsVisible( cameraPosition ) )
            {
                zones[portalIt.GetTargetZoneNum()].Render( cameraPosition, zones, renderedZonesRef );
            }
        }
    }
}

StaticGeometry::Zone::Zone( const int16_t zoneNum, const vector<TexTriangleGroup> &texTriangleGroups, const vector<frmr::Triangle> &collTriangles, const vector<Portal> &portals, const vector<Light> &lights )
    : zoneNum( zoneNum ),
      texTriangleGroups( texTriangleGroups ),
      collTriangles( collTriangles ),
      portals( portals ),
      lights( lights )
{
}

bool StaticGeometry::LoadZoneFile( const string &zoneDataFilename, const AssetManager &assets )
{
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

        if ( zoneString.substr( i, 3 ) != "WZZ" )
        {
            cout << "StaticGeometry::LoadZoneFile() - " << zoneDataFilename << "is not a zone file." << endl;
            return false;
        }

        i += 3;
        int16_t numOfZones = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
        i += 2;

        for ( int zoneIndex = 0; zoneIndex < numOfZones; zoneIndex++ )
        {
            int16_t zoneNum = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;
            int16_t numOfTexTriangleGroups = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            vector<StaticGeometry::Zone::TexTriangleGroup> texTriangleGroups;

            for ( int texTriangleGroupIndex = 0; texTriangleGroupIndex < numOfTexTriangleGroups; texTriangleGroupIndex++ )
            {
                int16_t texNameLength = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;
                string texName = zoneString.substr( i, texNameLength );
                i += texNameLength;
                GLuint textureNum = assets.GetTexture( texName, AssetManager::SearchMode::PERMANENT );
                int32_t numOfTexTriangles = frmr::DecodeINT32( zoneString.substr( i, 4 ) );
                i += 4;

                GLuint texTriangleGroupDisplayList = glGenLists(1);
                glNewList( texTriangleGroupDisplayList, GL_COMPILE );
                glBegin( GL_TRIANGLES );

                for ( int texTriangleIndex = 0; texTriangleIndex < numOfTexTriangles; texTriangleIndex++ )
                {
                    glNormal3f( frmr::DecodeFloat( zoneString.substr( i+60, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+64, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+68, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+36, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ) );
                    glTexCoord2f( frmr::DecodeFloat( zoneString.substr( i+52, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+56, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+40, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+44, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+48, 4 ) ) );
                    i += 72;
                }
                glEnd();
                glEndList();
                texTriangleGroups.push_back( StaticGeometry::Zone::TexTriangleGroup( texTriangleGroupDisplayList, textureNum ) );
            }

            vector<frmr::Triangle> collTriangles;

            int32_t numOfCollTriangles = frmr::DecodeINT32( zoneString.substr( i, 4 ) );
            i += 4;

            for ( int collTriangleIndex = 0; collTriangleIndex < numOfCollTriangles; collTriangleIndex++ )
            {
                collTriangles.push_back( frmr::Triangle( frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ) ),
                                                         frmr::Vec3f( frmr::DecodeFloat( zoneString.substr( i+36, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+40, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+44, 4 ) ) ) ) );
                i += 48;
            }

            vector<StaticGeometry::Portal> portals;

            int16_t numOfPortals = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int portalIndex = 0; portalIndex < numOfPortals; portalIndex++ )
            {
                int16_t targetZoneNum = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;
                int16_t numOfTriangles = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
                i += 2;

                vector<frmr::Triangle> triangles;
                for ( int triangleIndex = 0; triangleIndex < numOfTriangles; triangleIndex++ )
                {
                    frmr::Vec3f vert0( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                    frmr::Vec3f vert1( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) );
                    frmr::Vec3f vert2( frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ) );
                    frmr::Vec3f normal( frmr::DecodeFloat( zoneString.substr( i+36, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+40, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+44, 4 ) ) );
                    triangles.push_back( frmr::Triangle( vert0, vert1, vert2, normal ) );
                    i += 48;
                }
                portals.push_back( StaticGeometry::Portal( triangles, targetZoneNum ) );
            }

            vector<Light> lights;

            int16_t numOfLights = frmr::DecodeINT16( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int lightIndex = 0; lightIndex < numOfLights; lightIndex++ )
            {
                frmr::Vec3f position( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                frmr::Vec3f color( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) );
                float radius = frmr::DecodeFloat( zoneString.substr( i+24, 4 ) );
                int32_t numOfTriangles = frmr::DecodeINT32( zoneString.substr( i+28, 4 ) );
                i += 32;

                GLuint lightDisplayList = glGenLists( 1 );
                glNewList( lightDisplayList, GL_COMPILE );
                glBegin( GL_TRIANGLES );

                for ( int triangleIndex = 0; triangleIndex < numOfTriangles; triangleIndex++ )
                {
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+4, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+8, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+12, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+16, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+20, 4 ) ) );
                    glVertex3f( frmr::DecodeFloat( zoneString.substr( i+24, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+28, 4 ) ), frmr::DecodeFloat( zoneString.substr( i+32, 4 ) ) );
                    i += 36;
                }

                glEnd();
                glEndList();

                lights.push_back( Light( position, color, radius, lightDisplayList ) );
            }
            cout << texTriangleGroups[0].GetDisplayList() << endl;
            zones.push_back( StaticGeometry::Zone( zoneNum, texTriangleGroups, collTriangles, portals, lights ) );
            cout << "StaticGeometry::LoadZoneFile() - Successfully loaded zone file: " << zoneDataFilename << endl;
        }
    }
    else
    {
        cout << "StaticGeometry::LoadZoneFile() - Failed to open zone file: " << zoneDataFilename << endl;
        return false;
    }
    return true;
}

vector<Light> StaticGeometry::GetStaticLights() const
{
    vector<Light> foundLights;

    for ( auto zoneIt : zones )
    {
        vector<Light> zoneLights = zoneIt.GetLights();
        foundLights.insert( foundLights.end(), zoneLights.begin(), zoneLights.end() );
    }
    return foundLights;
}

void StaticGeometry::Render( const int16_t cameraZoneNum, const frmr::Vec3f &cameraPosition ) const
{
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    //draw current zone
        //draw the geometry
        //draw the portals

    vector<int> renderedZones;

    zones[cameraZoneNum].Render( cameraPosition, zones, renderedZones );
}

StaticGeometry::StaticGeometry( const string &zoneDataFilename, const AssetManager &assets )
{
    LoadZoneFile( zoneDataFilename, assets );
}

StaticGeometry::~StaticGeometry()
{
    //free display list
    for ( auto zoneIt : zones )
    {
        zoneIt.DeleteDisplayLists();
    }
}
