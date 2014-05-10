#include <iostream>
#include <fstream>

#include "StaticGeometry.h"
#include "frmr/BoundingBox.h"
#include "frmr/Encoder.h"
#include "frmr/frmrMath.h"
#include "frmr/Vec2f.h"
#include "frmr/Vec3f.h"

using std::cout;
using std::endl;

vector<frmr::Vec3f> StaticGeometry::Portal::CheckVisibility( const Frustum &viewFrustum ) const
{
    vector<frmr::Vec3f> visiblePoints;

    for ( auto triangleIt : triangles )
    {
        frmr::Vec3f cameraToTriangleVector = triangleIt.GetVert0() - viewFrustum.GetPosition();

        if ( frmr::VectorDot( triangleIt.GetNormal(), cameraToTriangleVector.Unit() ) > 0.0f ) //TODO: Make sure portal faces are declared counter-clockwise when exported
        {
        	vector<frmr::Vec3f> trianglePoints = viewFrustum.GetVisibleTrianglePoints( triangleIt );
        	visiblePoints.insert( visiblePoints.end(), trianglePoints.begin(), trianglePoints.end() );
        }
    }

    return visiblePoints;
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

void StaticGeometry::Zone::Render( const ProjectionState &cameraProjection, const Frustum &viewFrustum, const vector<Zone> &zones, vector<int> &renderedZonesRef ) const
{
    renderedZonesRef.push_back( zoneNum );

	//draw the zone
    for ( auto texTriangleGroupIt : texTriangleGroups )
    {
        texTriangleGroupIt.Render();
    }

	//draw zones that are visible through a portal
    for ( auto portalIt : portals )
    {
        //if portal target zone not already rendered
        if ( std::find( renderedZonesRef.begin(), renderedZonesRef.end(), portalIt.GetTargetZoneNum() ) == renderedZonesRef.end() )
		{
			vector<frmr::Vec3f> visiblePoints = portalIt.CheckVisibility( viewFrustum );
            if ( !visiblePoints.empty() )
            {
            	//project all points
            	vector<frmr::Vec3f> projectedPoints;
            	for ( auto pointIt : visiblePoints )
				{
					projectedPoints.push_back( cameraProjection.Project( pointIt ) );
				}

				//find bounding box
				frmr::BoundingBox<frmr::Vec3f> portalBox( projectedPoints );

				//apply glScissor
				int scissorWidth = frmr::Round( portalBox.GetMax().GetX() - portalBox.GetMin().GetX() );
				int scissorHeight = frmr::Round( portalBox.GetMax().GetY() - portalBox.GetMin().GetY() );
				glScissor( frmr::Round( portalBox.GetMin().GetX() ), frmr::Round( portalBox.GetMin().GetY() ), scissorWidth, scissorHeight );

				//construct new frustum from AABB vertices
				vector<frmr::Vec3f> newFrustumVertices;
				newFrustumVertices.reserve( 4 );
				newFrustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( portalBox.GetMin().GetX(), portalBox.GetMax().GetY(), 0.0f ) ) );	//top left
				newFrustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( portalBox.GetMin().GetX(), portalBox.GetMin().GetY(), 0.0f ) ) );	//bottom left
				newFrustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( portalBox.GetMax().GetX(), portalBox.GetMin().GetY(), 0.0f ) ) );	//bottom right
				newFrustumVertices.push_back( cameraProjection.UnProject( frmr::Vec3f( portalBox.GetMax().GetX(), portalBox.GetMax().GetY(), 0.0f ) ) );	//top right

				Frustum newFrustum( viewFrustum.GetPosition(), newFrustumVertices );

				glEnable( GL_SCISSOR_TEST );
					zones[portalIt.GetTargetZoneNum()].Render( cameraProjection, newFrustum, zones, renderedZonesRef );
                glDisable( GL_SCISSOR_TEST );
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
        int16_t numOfZones = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
        i += 2;

        for ( int zoneIndex = 0; zoneIndex < numOfZones; zoneIndex++ )
        {
            int16_t zoneNum = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
            i += 2;
            int16_t numOfTexTriangleGroups = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
            i += 2;

            vector<StaticGeometry::Zone::TexTriangleGroup> texTriangleGroups;

            for ( int texTriangleGroupIndex = 0; texTriangleGroupIndex < numOfTexTriangleGroups; texTriangleGroupIndex++ )
            {
                int16_t texNameLength = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
                i += 2;
                string texName = zoneString.substr( i, texNameLength );
                i += texNameLength;
                GLuint textureNum = assets.GetTexture( texName, AssetManager::SearchMode::PERMANENT );
                int32_t numOfTexTriangles = frmr::Encoder<int32_t>::Decode( zoneString.substr( i, 4 ) );
                i += 4;

                GLuint texTriangleGroupDisplayList = glGenLists(1);
                glNewList( texTriangleGroupDisplayList, GL_COMPILE );
                glBegin( GL_TRIANGLES );

                for ( int texTriangleIndex = 0; texTriangleIndex < numOfTexTriangles; texTriangleIndex++ )
                {
                    glNormal3f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+60, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+64, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+68, 4 ) ) );
                    glTexCoord2f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+12, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+16, 4 ) ) );
                    glVertex3f( 	frmr::Encoder<float>::Decode( zoneString.substr( i, 4 ) ), 		frmr::Encoder<float>::Decode( zoneString.substr( i+4, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+8, 4 ) ) );
                    glTexCoord2f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+32, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+36, 4 ) ) );
                    glVertex3f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+20, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+24, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+28, 4 ) ) );
                    glTexCoord2f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+52, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+56, 4 ) ) );
                    glVertex3f( 	frmr::Encoder<float>::Decode( zoneString.substr( i+40, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+44, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+48, 4 ) ) );
                    i += 72;
                }
                glEnd();
                glEndList();
                texTriangleGroups.push_back( StaticGeometry::Zone::TexTriangleGroup( texTriangleGroupDisplayList, textureNum ) );
            }

            vector<frmr::Triangle> collTriangles;

            int32_t numOfCollTriangles = frmr::Encoder<int32_t>::Decode( zoneString.substr( i, 4 ) );
            i += 4;

            for ( int collTriangleIndex = 0; collTriangleIndex < numOfCollTriangles; collTriangleIndex++ )
            {
                collTriangles.push_back( frmr::Triangle( frmr::Vec3f( frmr::Encoder<float>::Decode( zoneString.substr( i, 4 ) ),	frmr::Encoder<float>::Decode( zoneString.substr( i+4, 4 ) ),	frmr::Encoder<float>::Decode( zoneString.substr( i+8, 4 ) ) ),
                                                         frmr::Vec3f( frmr::Encoder<float>::Decode( zoneString.substr( i+12, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+16, 4 ) ),	frmr::Encoder<float>::Decode( zoneString.substr( i+20, 4 ) ) ),
                                                         frmr::Vec3f( frmr::Encoder<float>::Decode( zoneString.substr( i+24, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+28, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+32, 4 ) ) ),
                                                         frmr::Vec3f( frmr::Encoder<float>::Decode( zoneString.substr( i+36, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+40, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+44, 4 ) ) ) ) );
                i += 48;
            }

            vector<StaticGeometry::Portal> portals;

            int16_t numOfPortals = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int portalIndex = 0; portalIndex < numOfPortals; portalIndex++ )
            {
                int16_t targetZoneNum = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
                i += 2;
                int16_t numOfTriangles = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
                i += 2;

                vector<frmr::Triangle> triangles;
                for ( int triangleIndex = 0; triangleIndex < numOfTriangles; triangleIndex++ )
                {
                    frmr::Vec3f vert0( frmr::Encoder<float>::Decode( zoneString.substr( i, 4 ) ), 		frmr::Encoder<float>::Decode( zoneString.substr( i+4, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+8, 4 ) ) );
                    frmr::Vec3f vert1( frmr::Encoder<float>::Decode( zoneString.substr( i+12, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+16, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+20, 4 ) ) );
                    frmr::Vec3f vert2( frmr::Encoder<float>::Decode( zoneString.substr( i+24, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+28, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+32, 4 ) ) );
                    frmr::Vec3f normal( frmr::Encoder<float>::Decode( zoneString.substr( i+36, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+40, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+44, 4 ) ) );
                    triangles.push_back( frmr::Triangle( vert0, vert1, vert2, normal ) );
                    i += 48;
                }
                portals.push_back( StaticGeometry::Portal( triangles, targetZoneNum ) );
            }

            vector<Light> lights;

            int16_t numOfLights = frmr::Encoder<int16_t>::Decode( zoneString.substr( i, 2 ) );
            i += 2;

            for ( int lightIndex = 0; lightIndex < numOfLights; lightIndex++ )
            {
                frmr::Vec3f position( frmr::Encoder<float>::Decode( zoneString.substr( i, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+4, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+8, 4 ) ) );
                frmr::Vec3f color( frmr::Encoder<float>::Decode( zoneString.substr( i+12, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+16, 4 ) ), frmr::Encoder<float>::Decode( zoneString.substr( i+20, 4 ) ) );
                float radius = frmr::Encoder<float>::Decode( zoneString.substr( i+24, 4 ) );
                int32_t numOfTriangles = frmr::Encoder<int32_t>::Decode( zoneString.substr( i+28, 4 ) );
                i += 32;

                GLuint lightDisplayList = glGenLists( 1 );
                glNewList( lightDisplayList, GL_COMPILE );
                glBegin( GL_TRIANGLES );

                for ( int triangleIndex = 0; triangleIndex < numOfTriangles; triangleIndex++ )
                {
                    glVertex3f( frmr::Encoder<float>::Decode( zoneString.substr( i, 4 ) ), 		frmr::Encoder<float>::Decode( zoneString.substr( i+4, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+8, 4 ) ) );
                    glVertex3f( frmr::Encoder<float>::Decode( zoneString.substr( i+12, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+16, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+20, 4 ) ) );
                    glVertex3f( frmr::Encoder<float>::Decode( zoneString.substr( i+24, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+28, 4 ) ), 	frmr::Encoder<float>::Decode( zoneString.substr( i+32, 4 ) ) );
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

vector<Light> StaticGeometry::GetStaticLights() const //TODO: only return lights that could be visible
{
    vector<Light> foundLights;

    for ( auto zoneIt : zones )
    {
        vector<Light> zoneLights = zoneIt.GetLights();
        foundLights.insert( foundLights.end(), zoneLights.begin(), zoneLights.end() );
    }
    return foundLights;
}

void StaticGeometry::Render( const int16_t cameraZoneNum, const ProjectionState &cameraProjection, const Frustum &viewFrustum ) const
{
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    //draw current zone
        //draw the geometry
        //draw the portals

    vector<int> renderedZones;

    zones[cameraZoneNum].Render( cameraProjection, viewFrustum, zones, renderedZones );

    for ( auto renderedZoneIt : renderedZones )
    {
        cout << renderedZoneIt << " ";
    }
    cout << std::endl;

    vector<int> visibleEntityZones = renderedZones; //TODO: Return this when we're done so that Simulation knows which Entities to render
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
