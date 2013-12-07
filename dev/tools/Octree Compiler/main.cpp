#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "frmr_Vec3f.h"
#include "frmr_Vec2f.h"
#include "frmr_textfile.h"
#include "frmr_encode.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace frmr;

void ReadNode( const vector<vector<string>> lines, int &lineIndex )
{

}

int main( int argc, char *argv[] )
{
    for ( int i = 1; i < argc; i++ )
    {
        TextFile file( argv[i] );
        vector<vector<string>> lines = file.GetLines();

        frmr::Vec3f octreeMin( atof( lines[0][0] ), atof( lines[1][0] ), atof( lines[2][0] ) );
        frmr::Vec3f octreeMax( atof( lines[3][0] ), atof( lines[4][0] ), atof( lines[5][0] ) );

        int lineIndex = 0;

        for ( int l)

        for ( auto lineIt : lines )
        {
            if ( !loadingZone )
            {
                if ( lineIt[0] == "zone" )
                {
                    currentZone = Zone();
                    loadingZone = true;
                }
            }
            else
            {
                if ( loadingTexTriangleGroup )
                {
                    if ( loadingTexTriangle )
                    {
                        if ( lineIt[0] == "vert0" )
                        {
                            currentTexTriangle.vert0 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert0Tex" )
                        {
                            currentTexTriangle.vert0Tex = Vec2f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert1" )
                        {
                            currentTexTriangle.vert1 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert1Tex" )
                        {
                            currentTexTriangle.vert1Tex = Vec2f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert2" )
                        {
                            currentTexTriangle.vert2 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert2Tex" )
                        {
                            currentTexTriangle.vert2Tex = Vec2f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ) );
                        }
                        else if ( lineIt[0] == "normal" )
                        {
                            currentTexTriangle.normal = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "/texTriangle" )
                        {
                            currentTexTriangleGroup.texTriangles.push_back( currentTexTriangle );
                            loadingTexTriangle = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading TexTriangle: " << lineIt[0] << endl;
                        }
                    }
                    else
                    {
                        if ( lineIt[0] == "texName" )
                        {
                            currentTexTriangleGroup.texName = lineIt[1];
                        }
                        else if ( lineIt[0] == "texTriangle" )
                        {
                            currentTexTriangle = TexTriangle();
                            loadingTexTriangle = true;
                        }
                        else if ( lineIt[0] == "/texTriangleGroup" )
                        {
                            currentZone.texTriangleGroups.push_back( currentTexTriangleGroup );
                            loadingTexTriangleGroup = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading TexTriangleGroup: " << lineIt[0] << endl;
                        }
                    }
                }
                else if ( loadingCollTriangle )
                {
                    if ( lineIt[0] == "vert0" )
                    {
                        currentCollTriangle.vert0 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                    }
                    else if ( lineIt[0] == "vert1" )
                    {
                        currentCollTriangle.vert1 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                    }
                    else if ( lineIt[0] == "vert2" )
                    {
                        currentCollTriangle.vert2 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                    }
                    else if ( lineIt[0] == "normal" )
                    {
                        currentCollTriangle.normal = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                    }
                    else if ( lineIt[0] == "/collTriangle" )
                    {
                        currentZone.collTriangles.push_back( currentCollTriangle );
                        loadingCollTriangle = false;
                    }
                    else
                    {
                        cout << "Unrecognised command while loading CollTriangle: " << lineIt[0] << endl;
                    }
                }
                else if ( loadingPortal )
                {
                    if ( loadingTriangle )
                    {
                        if ( lineIt[0] == "vert0" )
                        {
                            currentTriangle.vert0 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert1" )
                        {
                            currentTriangle.vert1 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert2" )
                        {
                            currentTriangle.vert2 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "/triangle" )
                        {
                            currentPortal.triangles.push_back( currentTriangle );
                            loadingTriangle = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading Triangle in Portal: " << lineIt[0] << endl;
                        }
                    }
                    else
                    {
                        if ( lineIt[0] == "targetZoneNum" )
                        {
                            currentPortal.targetZoneNum = atoi( lineIt[1].c_str() );
                        }
                        else if ( lineIt[0] == "triangle" )
                        {
                            loadingTriangle = true;
                            currentTriangle = Triangle();
                        }
                        else if ( lineIt[0] == "/portal" )
                        {
                            currentZone.portals.push_back( currentPortal );
                            loadingPortal = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading Portal: " << lineIt[0] << endl;
                        }
                    }

                }
                else if ( loadingLight )
                {
                    if ( loadingTriangle )
                    {
                        if ( lineIt[0] == "vert0" )
                        {
                            currentTriangle.vert0 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert1" )
                        {
                            currentTriangle.vert1 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "vert2" )
                        {
                            currentTriangle.vert2 = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "/triangle" )
                        {
                            currentLight.triangles.push_back( currentTriangle );
                            loadingTriangle = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading Triangle in Light: " << lineIt[0] << endl;
                        }
                    }
                    else
                    {
                        if ( lineIt[0] == "position" )
                        {
                            currentLight.position = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "color" )
                        {
                            currentLight.color = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
                        }
                        else if ( lineIt[0] == "radius" )
                        {
                            currentLight.radius = atof( lineIt[1].c_str() );
                        }
                        else if ( lineIt[0] == "triangle" )
                        {
                            loadingTriangle = true;
                            currentTriangle = Triangle();
                        }
                        else if ( lineIt[0] == "/light" )
                        {
                            currentZone.lights.push_back( currentLight );
                            loadingLight = false;
                        }
                        else
                        {
                            cout << "Unrecognised command while loading Light: " << lineIt[0] << endl;
                        }
                    }
                }
                else
                {
                    if ( lineIt[0] == "zoneNum" )
                    {
                        currentZone.zoneNum = atoi( lineIt[1].c_str() );
                    }
                    else if ( lineIt[0] == "texTriangleGroup" )
                    {
                        currentTexTriangleGroup = TexTriangleGroup();
                        loadingTexTriangleGroup = true;
                    }
                    else if ( lineIt[0] == "collTriangle" )
                    {
                        currentCollTriangle = CollTriangle();
                        loadingCollTriangle = true;
                    }
                    else if ( lineIt[0] == "portal" )
                    {
                        currentPortal = Portal();
                        loadingPortal = true;
                    }
                    else if ( lineIt[0] == "light" )
                    {
                        currentLight = Light();
                        loadingLight = true;
                    }
                    else if ( lineIt[0] == "/zone" )
                    {
                        zones.push_back( currentZone );
                        loadingZone = false;
                    }
                    else
                    {
                        cout << "Unrecognised command while loading Zone: " << lineIt[0] << endl;
                    }
                }
            }
        }

        //print all the data for debugging purposes
        for ( auto zoneIt : zones )
        {
            cout << zoneIt.zoneNum << endl;
            for ( auto texTriangleGroupIt : zoneIt.texTriangleGroups )
            {

                cout << texTriangleGroupIt.texName << endl;
                for ( auto texTriangleIt : texTriangleGroupIt.texTriangles )
                {
                    cout << texTriangleIt.vert0.GetX() << " " << texTriangleIt.vert0.GetY() << " " << texTriangleIt.vert0.GetZ() << endl;
                    cout << texTriangleIt.vert0Tex.GetX() << " " << texTriangleIt.vert0Tex.GetY() << endl;
                    cout << texTriangleIt.vert1.GetX() << " " << texTriangleIt.vert1.GetY() << " " << texTriangleIt.vert1.GetZ() << endl;
                    cout << texTriangleIt.vert1Tex.GetX() << " " << texTriangleIt.vert1Tex.GetY() << endl;
                    cout << texTriangleIt.vert2.GetX() << " " << texTriangleIt.vert2.GetY() << " " << texTriangleIt.vert2.GetZ() << endl;
                    cout << texTriangleIt.vert2Tex.GetX() << " " << texTriangleIt.vert2Tex.GetY() << endl;
                    cout << texTriangleIt.normal.GetX() << " " << texTriangleIt.normal.GetY() << " " << texTriangleIt.normal.GetZ() << endl;
                }
            }
        }
//
//            for ( auto portalIt : zoneIt.portals )
//            {
//                cout << portalIt.targetZoneNum << endl;
//                for ( auto triangleIt : portalIt.triangles )
//                {
//                    cout << triangleIt.vert0.GetX() << " " << triangleIt.vert0.GetY() << " " << triangleIt.vert0.GetZ() << endl;
//                    cout << triangleIt.vert1.GetX() << " " << triangleIt.vert1.GetY() << " " << triangleIt.vert1.GetZ() << endl;
//                    cout << triangleIt.vert2.GetX() << " " << triangleIt.vert2.GetY() << " " << triangleIt.vert2.GetZ() << endl;
//                }
//            }
//
//            for ( auto lightIt : zoneIt.lights )
//            {
//                cout << lightIt.position.GetX() << " " << lightIt.position.GetY() << " " << lightIt.position.GetZ() << endl;
//                cout << lightIt.color.GetX() << " " << lightIt.color.GetY() << " " << lightIt.color.GetZ() << endl;
//                cout << lightIt.radius << endl;
//                for ( auto triangleIt : lightIt.triangles )
//                {
//                    cout << triangleIt.vert0.GetX() << " " << triangleIt.vert0.GetY() << " " << triangleIt.vert0.GetZ() << endl;
//                    cout << triangleIt.vert1.GetX() << " " << triangleIt.vert1.GetY() << " " << triangleIt.vert1.GetZ() << endl;
//                    cout << triangleIt.vert2.GetX() << " " << triangleIt.vert2.GetY() << " " << triangleIt.vert2.GetZ() << endl;
//                }
//            }
//        }

        //write the byte file
        string inFilename = argv[1];
        size_t lastDot = inFilename.find_last_of( "." );
        string outFilename;
        if ( lastDot == string::npos )
        {
            outFilename = inFilename;
        }
        else
        {
            outFilename = inFilename.substr( 0, lastDot );
        }

        std::ofstream outFile( outFilename + ".wzz" );

        outFile << "WZZ";
        outFile << EncodeINT16( zones.size() );

        for ( auto zoneIt : zones )
        {
            outFile << EncodeINT16( zoneIt.zoneNum );
            outFile << EncodeINT16( zoneIt.texTriangleGroups.size() );

            for ( auto texTriangleGroupIt : zoneIt.texTriangleGroups )
            {
                outFile << EncodeINT16( texTriangleGroupIt.texName.size() );
                outFile << texTriangleGroupIt.texName;
                outFile << EncodeINT32( texTriangleGroupIt.texTriangles.size() );

                for ( auto texTriangleIt : texTriangleGroupIt.texTriangles )
                {
                    outFile << EncodeFloat( texTriangleIt.vert0.GetX() ) << EncodeFloat( texTriangleIt.vert0.GetY() ) << EncodeFloat( texTriangleIt.vert0.GetZ() );
                    outFile << EncodeFloat( texTriangleIt.vert0Tex.GetX() ) << EncodeFloat( texTriangleIt.vert0Tex.GetY() );
                    outFile << EncodeFloat( texTriangleIt.vert1.GetX() ) << EncodeFloat( texTriangleIt.vert1.GetY() ) << EncodeFloat( texTriangleIt.vert1.GetZ() );
                    outFile << EncodeFloat( texTriangleIt.vert1Tex.GetX() ) << EncodeFloat( texTriangleIt.vert1Tex.GetY() );
                    outFile << EncodeFloat( texTriangleIt.vert2.GetX() ) << EncodeFloat( texTriangleIt.vert2.GetY() ) << EncodeFloat( texTriangleIt.vert2.GetZ() );
                    outFile << EncodeFloat( texTriangleIt.vert2Tex.GetX() ) << EncodeFloat( texTriangleIt.vert2Tex.GetY() );
                    outFile << EncodeFloat( texTriangleIt.normal.GetX() ) << EncodeFloat( texTriangleIt.normal.GetY() ) << EncodeFloat( texTriangleIt.normal.GetZ() );
                }
            }

            outFile << EncodeINT32( zoneIt.collTriangles.size() );

            for ( auto collTriangleIt : zoneIt.collTriangles )
            {
                outFile << EncodeFloat( collTriangleIt.vert0.GetX() ) << EncodeFloat( collTriangleIt.vert0.GetY() ) << EncodeFloat( collTriangleIt.vert0.GetZ() );
                outFile << EncodeFloat( collTriangleIt.vert1.GetX() ) << EncodeFloat( collTriangleIt.vert1.GetY() ) << EncodeFloat( collTriangleIt.vert1.GetZ() );
                outFile << EncodeFloat( collTriangleIt.vert2.GetX() ) << EncodeFloat( collTriangleIt.vert2.GetY() ) << EncodeFloat( collTriangleIt.vert2.GetZ() );
                outFile << EncodeFloat( collTriangleIt.normal.GetX() ) << EncodeFloat( collTriangleIt.normal.GetY() ) << EncodeFloat( collTriangleIt.normal.GetZ() );
            }

            outFile << EncodeINT16( zoneIt.portals.size() );

            for ( auto portalIt : zoneIt.portals )
            {
                outFile << EncodeINT16( portalIt.targetZoneNum );
                outFile << EncodeINT16( portalIt.triangles.size() );

                for ( auto triangleIt : portalIt.triangles )
                {
                    outFile << EncodeFloat( triangleIt.vert0.GetX() ) << EncodeFloat( triangleIt.vert0.GetY() ) << EncodeFloat( triangleIt.vert0.GetZ() );
                    outFile << EncodeFloat( triangleIt.vert1.GetX() ) << EncodeFloat( triangleIt.vert1.GetY() ) << EncodeFloat( triangleIt.vert1.GetZ() );
                    outFile << EncodeFloat( triangleIt.vert2.GetX() ) << EncodeFloat( triangleIt.vert2.GetY() ) << EncodeFloat( triangleIt.vert2.GetZ() );
                }
            }

            outFile << EncodeINT16( zoneIt.lights.size() );

            for ( auto lightIt : zoneIt.lights )
            {
                outFile << EncodeFloat( lightIt.position.GetX() ) << EncodeFloat( lightIt.position.GetY() ) << EncodeFloat( lightIt.position.GetZ() );
                outFile << EncodeFloat( lightIt.color.GetX() ) << EncodeFloat( lightIt.color.GetY() ) << EncodeFloat( lightIt.color.GetZ() );
                outFile << EncodeFloat( lightIt.radius );
                outFile << EncodeINT32( lightIt.triangles.size() );

                for ( auto triangleIt : lightIt.triangles )
                {
                    outFile << EncodeFloat( triangleIt.vert0.GetX() ) << EncodeFloat( triangleIt.vert0.GetY() ) << EncodeFloat( triangleIt.vert0.GetZ() );
                    outFile << EncodeFloat( triangleIt.vert1.GetX() ) << EncodeFloat( triangleIt.vert1.GetY() ) << EncodeFloat( triangleIt.vert1.GetZ() );
                    outFile << EncodeFloat( triangleIt.vert2.GetX() ) << EncodeFloat( triangleIt.vert2.GetY() ) << EncodeFloat( triangleIt.vert2.GetZ() );
                }
            }
        }
        outFile.close();
    }
    return 0;
}
