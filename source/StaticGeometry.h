#ifndef STATIC_GEOMETRY_H
#define STATIC_GEOMETRY_H

#include <SFML/OpenGL.hpp>
#include <vector>
#include <string>

#include "Light.h"
#include "frmr_Octree.h"

using std::vector;
using std::string;

class StaticGeometry
{
private:
    class Portal
    {
    private:
        GLuint  displayList;
        int16_t targetZoneNum;

    public:
        GLuint  GetDisplayList() const;
        int16_t GetTargetZoneNum() const;

    public:
        Portal( const GLuint displayList, const int16_t targetZoneNum )
            : displayList( displayList ), targetZoneNum( targetZoneNum )
        {
        }
        ~Portal()
        {
            glDeleteLists( displayList, 1 );
        }
    };

    class Zone
    {
    private:
        int16_t         zoneNum;
        GLuint          displayList;
        vector<Portal>  portals;
        vector<Light>   lights;

    public:
        int16_t GetZoneNum() const;
        vector<int16_t> Render() const; //renders and returns a list of visible zones

    public:
        Zone( const GLuint displayList, const vector<Portal> &portals, const vector<Light> &lights )
            : displayList( displayList ),
              portals( portals ),
              lights( lights )
        {
        }
        ~Zone()
        {
            glDeleteLists( displayList, 1 );
        }
    };

private:
    vector<Zone> LoadZoneFile( const string &zoneDataFilename ) const;

private:
    frmr::Octree<int16_t>   zoneTree;
    vector<Zone>            zones;

public:
    void Render() const;

public:
    //StaticGeometry( const string &octreeFilename, const string &zoneDataFilename,  );
    StaticGeometry( const string &zoneDataFilename );
    StaticGeometry();
    ~StaticGeometry();
};

#endif // STATIC_GEOMETRY_H
