#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>
#include <vector>
#include "frmr/Triangle.h"
#include "frmr/Vec2f.h"
#include "ProjectionState.h"

using std::array;
using std::vector;

class Frustum
{
private:
	frmr::Vec3f				position;
	vector<frmr::Vec3f>		edgeVectors;
    vector<frmr::Triangle> 	faces;

private:
	void					ConstructFaces( const vector<frmr::Vec3f> &vertices );

public:
    bool                	Contains( const frmr::Vec3f &point ) const;
    vector<frmr::Vec3f> 	GetLineIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const;
    vector<frmr::Vec3f>		GetVisibleTrianglePoints( const frmr::Triangle &triangle ) const;
    vector<frmr::Triangle>	GetFaces() const;
    frmr::Vec3f				GetPosition() const;

public:
    Frustum( const frmr::Vec3f &position, const frmr::Vec2f &cameraRotation, const int verticalFov, const float fovRatio );
    Frustum( const frmr::Vec3f &position, const vector<frmr::Vec3f> &vertices );
};

#endif // FRUSTUM_H
