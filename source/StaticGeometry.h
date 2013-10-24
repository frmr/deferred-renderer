#ifndef STATIC_GEOMETRY_H
#define STATIC_GEOMETRY_H

#include <SFML/OpenGL.hpp>
#include <vector>
#include <string>

#include "Light.h"
#include "frmr_Octree.h"
#include "AssetManager.h"
#include "frmr_Triangle.h"

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
        void    Render() const;
        int16_t GetTargetZoneNum() const;

    public:
        Portal( const GLuint displayList, const int16_t targetZoneNum );
        ~Portal();
    };

    class Zone
    {
    public:
        class TexTriangleGroup
        {
        private:
            GLuint  displayList;
            GLuint  textureNum;

        public:
            void Render() const;

        public:
            TexTriangleGroup( const GLuint displayList, GLuint textureNum );
            ~TexTriangleGroup();
        };

    private:
        int16_t                     zoneNum;
        vector<TexTriangleGroup>    texTriangleGroups;
        vector<Portal>              portals;
        vector<Light>               lights;
        vector<frmr::Triangle>      collTriangles; //collision surfaces //TODO: MAKE THIS A QUADTREE

    public:
        int16_t GetZoneNum() const;
        vector<int16_t> Render() const; //renders and returns a list of visible zones

    public:
        Zone( const vector<TexTriangleGroup> &texTriangleGroups, const vector<frmr::Triangle> &collTriangles, const vector<Portal> &portals, const vector<Light> &lights )
            : texTriangleGroups( texTriangleGroups ),
              collTriangles( collTriangles ),
              portals( portals ),
              lights( lights )
        {
        }
    };

private:
    vector<Zone> LoadZoneFile( const string &zoneDataFilename, const AssetManager &assets ) const;

private:
    frmr::Octree<int16_t>   zoneTree;
    vector<Zone>            zones;

public:
    void Render() const;

public:
    //StaticGeometry( const string &octreeFilename, const string &zoneDataFilename,  );
    StaticGeometry( const string &zoneDataFilename, const AssetManager &assets );
    StaticGeometry();
    ~StaticGeometry();
};

#endif // STATIC_GEOMETRY_H
