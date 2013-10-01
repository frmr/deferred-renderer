#ifndef STATIC_GEOMETRY_H
#define STATIC_GEOMETRY_H

#include <SFML/OpenGL.hpp>
#include <vector>

#include "Light.h"
#include "frmr_Octree.h"

using std::vector;

class Portal
{
private:
    GLuint  displayList;
    int16_t targetZoneIndex;

public:
    GLuint  GetDisplayList() const;
    int16_t GetTargetZoneIndex() const;

public:
    Portal( const GLuint displayList, const int16_t targetZoneIndex )
        : displayList( displayList ), targetZoneIndex( targetZoneIndex )
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
    //Octree
    GLuint          displayList;
    vector<Portal>  portals;
    //vector<Light>

public:
    vector<int16_t> Render() const; //returns a list of visible zones

public:
    Zone( const GLuint displayList, const vector<Portal> &portals )
        : displayList( displayList ),
          portals( portals )
    {
    }
};



class StaticGeometry
{
private:
    vector<Zone> zones;

public:
    void Render() const;

public:
    StaticGeometry();
    ~StaticGeometry();
};

#endif // STATIC_GEOMETRY_H
