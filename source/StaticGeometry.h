#ifndef STATIC_GEOMETRY_H
#define STATIC_GEOMETRY_H

#include <SFML/OpenGL.hpp>
#include <vector>
#include <string>

#include "AssetManager.h"
#include "Frustum.h"
#include "Light.h"
#include "ProjectionState.h"
#include "frmr/Triangle.h"

using std::vector;
using std::string;

class StaticGeometry
{
private:
    class Portal
    {
    private:
        vector<frmr::Triangle>  triangles;
        int16_t                 targetZoneNum;

    public:
        vector<frmr::Vec3f>		CheckVisibility( const frmr::Vec3f &cameraPosition, const Frustum &viewFrustum ) const;
        void    				Render() const;
        int16_t 				GetTargetZoneNum() const;

    public:
        Portal( const vector<frmr::Triangle> &triangles, const int16_t targetZoneNum );
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
            void 	DeleteDisplayList();
            GLuint 	GetDisplayList() const;
            void 	Render() const;

        public:
            TexTriangleGroup( const GLuint displayList, GLuint textureNum );
            ~TexTriangleGroup();
        };

    private:
        int16_t                     zoneNum;
        vector<TexTriangleGroup>    texTriangleGroups;
        vector<frmr::Triangle>      collTriangles; //collision surfaces //TODO: MAKE THIS A OCTREE
        vector<Portal>              portals;
        vector<Light>               lights;

    public:
        void 			DeleteDisplayLists();
        vector<Light> 	GetLights() const;
        int16_t 		GetZoneNum() const;
        void 			Render( const frmr::Vec3f &cameraPosition, const ProjectionState &cameraProjection, const Frustum &viewFrustum, const vector<Zone> &zones, vector<int> &renderedZonesRef ) const; //recusively renders all visible zones

    public:
        Zone( const int16_t zoneNum, const vector<TexTriangleGroup> &texTriangleGroups, const vector<frmr::Triangle> &collTriangles, const vector<Portal> &portals, const vector<Light> &lights );
    };

private:
    bool LoadZoneFile( const string &zoneDataFilename, const AssetManager &assets );

private:
    vector<Zone> zones; //zone::zoneNum = index in zone vector

public:
    vector<Light>   GetStaticLights() const;
    void 			Render( const int16_t cameraZoneNum, const frmr::Vec3f &cameraPosition, const ProjectionState &cameraProjection, const Frustum &viewFrustum ) const;

public:
    //StaticGeometry( const string &octreeFilename, const string &zoneDataFilename,  );
    StaticGeometry( const string &zoneDataFilename, const AssetManager &assets );
    ~StaticGeometry();
};

#endif // STATIC_GEOMETRY_H
