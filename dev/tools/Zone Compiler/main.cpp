#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "frmr_Vec3f.h"
#include "frmr_Vec2f.h"
#include "frmr_textfile.h"
#include "frmr_Encoder.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using frmr::Encoder;

using namespace frmr;

struct Triangle
{
    Vec3f   vert0;
    Vec3f   vert1;
    Vec3f   vert2;
    Vec3f   normal;
};

struct CollTriangle
{
    Vec3f   vert0;
    Vec3f   vert1;
    Vec3f   vert2;
    Vec3f   normal;
};

struct TexTriangle
{
    Vec3f   vert0;
    Vec2f   vert0Tex;
    Vec3f   vert1;
    Vec2f   vert1Tex;
    Vec3f   vert2;
    Vec2f   vert2Tex;
    Vec3f   normal;
};

struct TexTriangleGroup
{
    string              texName;
    vector<TexTriangle> texTriangles;
};

struct Portal
{
    int16_t             targetZoneNum;
    vector<Triangle>    triangles;
};

struct Light
{
    Vec3f               position;
    Vec3f               color;
    float               radius;
    vector<Triangle>    triangles;
};

struct Zone
{
    int16_t                     zoneNum;
    vector<TexTriangleGroup>    texTriangleGroups;
    vector<CollTriangle>        collTriangles;
    vector<Portal>              portals;
    vector<Light>               lights;

};

int main( int argc, char *argv[] )
{
    for ( int i = 1; i < argc; i++ )
    {
        bool loadingZone = false;
        bool loadingTexTriangleGroup = false;
        bool loadingTexTriangle = false;
        bool loadingCollTriangle = false;
        bool loadingPortal = false;
        bool loadingLight = false;
        bool loadingTriangle = false;

        vector<Zone>    zones;

        Zone currentZone;
        TexTriangleGroup currentTexTriangleGroup;
        TexTriangle currentTexTriangle;
        CollTriangle currentCollTriangle;
        Portal currentPortal;
        Light currentLight;
        Triangle currentTriangle;

        TextFile file( argv[i] );
        vector<vector<string>> lines = file.GetLines();

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
                        else if ( lineIt[0] == "normal" )
                        {
                            currentTriangle.normal = Vec3f( atof( lineIt[1].c_str() ), atof( lineIt[2].c_str() ), atof( lineIt[3].c_str() ) );
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
//            for ( auto texTriangleGroupIt : zoneIt.texTriangleGroups )
//            {
//
//                cout << texTriangleGroupIt.texName << endl;
//                for ( auto texTriangleIt : texTriangleGroupIt.texTriangles )
//                {
//                    cout << texTriangleIt.vert0.GetX() << " " << texTriangleIt.vert0.GetY() << " " << texTriangleIt.vert0.GetZ() << endl;
//                    cout << texTriangleIt.vert0Tex.GetX() << " " << texTriangleIt.vert0Tex.GetY() << endl;
//                    cout << texTriangleIt.vert1.GetX() << " " << texTriangleIt.vert1.GetY() << " " << texTriangleIt.vert1.GetZ() << endl;
//                    cout << texTriangleIt.vert1Tex.GetX() << " " << texTriangleIt.vert1Tex.GetY() << endl;
//                    cout << texTriangleIt.vert2.GetX() << " " << texTriangleIt.vert2.GetY() << " " << texTriangleIt.vert2.GetZ() << endl;
//                    cout << texTriangleIt.vert2Tex.GetX() << " " << texTriangleIt.vert2Tex.GetY() << endl;
//                    cout << texTriangleIt.normal.GetX() << " " << texTriangleIt.normal.GetY() << " " << texTriangleIt.normal.GetZ() << endl;
//                }
//            }

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

            for ( auto lightIt : zoneIt.lights )
            {
                cout << lightIt.position.GetX() << " " << lightIt.position.GetY() << " " << lightIt.position.GetZ() << endl;
                cout << lightIt.color.GetX() << " " << lightIt.color.GetY() << " " << lightIt.color.GetZ() << endl;
                cout << lightIt.radius << endl;
            }
        }

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
        outFile << Encoder<int16_t>::Encode( (int16_t) zones.size() );

        for ( auto zoneIt : zones )
        {
            outFile << Encoder<int16_t>::Encode( zoneIt.zoneNum );
            outFile << Encoder<int16_t>::Encode( (int16_t) zoneIt.texTriangleGroups.size() );

            for ( auto texTriangleGroupIt : zoneIt.texTriangleGroups )
            {
                outFile << Encoder<int16_t>::Encode( (int16_t) texTriangleGroupIt.texName.size() );
                outFile << texTriangleGroupIt.texName;
                outFile << Encoder<int32_t>::Encode( (int32_t) texTriangleGroupIt.texTriangles.size() );

                for ( auto texTriangleIt : texTriangleGroupIt.texTriangles )
                {
                    outFile << Encoder<float>::Encode( texTriangleIt.vert0.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert0.GetY() ) << Encoder<float>::Encode( texTriangleIt.vert0.GetZ() );
                    outFile << Encoder<float>::Encode( texTriangleIt.vert0Tex.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert0Tex.GetY() );
                    outFile << Encoder<float>::Encode( texTriangleIt.vert1.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert1.GetY() ) << Encoder<float>::Encode( texTriangleIt.vert1.GetZ() );
                    outFile << Encoder<float>::Encode( texTriangleIt.vert1Tex.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert1Tex.GetY() );
                    outFile << Encoder<float>::Encode( texTriangleIt.vert2.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert2.GetY() ) << Encoder<float>::Encode( texTriangleIt.vert2.GetZ() );
                    outFile << Encoder<float>::Encode( texTriangleIt.vert2Tex.GetX() ) << Encoder<float>::Encode( texTriangleIt.vert2Tex.GetY() );
                    outFile << Encoder<float>::Encode( texTriangleIt.normal.GetX() ) << Encoder<float>::Encode( texTriangleIt.normal.GetY() ) << Encoder<float>::Encode( texTriangleIt.normal.GetZ() );
                }
            }

            outFile << Encoder<int32_t>::Encode( (int32_t) zoneIt.collTriangles.size() );

            for ( auto collTriangleIt : zoneIt.collTriangles )
            {
                outFile << Encoder<float>::Encode( collTriangleIt.vert0.GetX() ) << Encoder<float>::Encode( collTriangleIt.vert0.GetY() ) << Encoder<float>::Encode( collTriangleIt.vert0.GetZ() );
                outFile << Encoder<float>::Encode( collTriangleIt.vert1.GetX() ) << Encoder<float>::Encode( collTriangleIt.vert1.GetY() ) << Encoder<float>::Encode( collTriangleIt.vert1.GetZ() );
                outFile << Encoder<float>::Encode( collTriangleIt.vert2.GetX() ) << Encoder<float>::Encode( collTriangleIt.vert2.GetY() ) << Encoder<float>::Encode( collTriangleIt.vert2.GetZ() );
                outFile << Encoder<float>::Encode( collTriangleIt.normal.GetX() ) << Encoder<float>::Encode( collTriangleIt.normal.GetY() ) << Encoder<float>::Encode( collTriangleIt.normal.GetZ() );
            }

            outFile << Encoder<int16_t>::Encode( (int16_t) zoneIt.portals.size() );

            for ( auto portalIt : zoneIt.portals )
            {
                outFile << Encoder<int16_t>::Encode( portalIt.targetZoneNum );
                outFile << Encoder<int16_t>::Encode( (int16_t) portalIt.triangles.size() );

                for ( auto triangleIt : portalIt.triangles )
                {
                    outFile << Encoder<float>::Encode( triangleIt.vert0.GetX() ) << Encoder<float>::Encode( triangleIt.vert0.GetY() ) << Encoder<float>::Encode( triangleIt.vert0.GetZ() );
                    outFile << Encoder<float>::Encode( triangleIt.vert1.GetX() ) << Encoder<float>::Encode( triangleIt.vert1.GetY() ) << Encoder<float>::Encode( triangleIt.vert1.GetZ() );
                    outFile << Encoder<float>::Encode( triangleIt.vert2.GetX() ) << Encoder<float>::Encode( triangleIt.vert2.GetY() ) << Encoder<float>::Encode( triangleIt.vert2.GetZ() );
                    outFile << Encoder<float>::Encode( triangleIt.normal.GetX() ) << Encoder<float>::Encode( triangleIt.normal.GetY() ) << Encoder<float>::Encode( triangleIt.normal.GetZ() );
                }
            }

            outFile << Encoder<int16_t>::Encode( (int16_t) zoneIt.lights.size() );

            for ( auto lightIt : zoneIt.lights )
            {
                outFile << Encoder<float>::Encode( lightIt.position.GetX() ) << Encoder<float>::Encode( lightIt.position.GetY() ) << Encoder<float>::Encode( lightIt.position.GetZ() );
                outFile << Encoder<float>::Encode( lightIt.color.GetX() ) << Encoder<float>::Encode( lightIt.color.GetY() ) << Encoder<float>::Encode( lightIt.color.GetZ() );
                outFile << Encoder<float>::Encode( lightIt.radius );
            }
        }
        outFile.close();
    }
    return 0;
}
