#include "Frustum.h"

#include <iostream>

#include "frmr/frmrMath.h"

using std::cout;
using std::endl;

//returns true if point is facing the back side of each triangle
bool Frustum::Contains( const frmr::Vec3f &point ) const
{
    for ( auto faceIt : faces )
    {
        //if point is on the wrong side of the face
        if ( frmr::VectorDot( faceIt.GetNormal(), point - faceIt.GetVert0() ) > 0.0f )
		{
			return false;
		}
    }
    return true;
}

//returns a vector of any intersections of a line cutting through the frustum's faces
vector<frmr::Vec3f> Frustum::GetLineIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const
{
    vector<frmr::Vec3f> intersections;

    for ( auto faceIt : faces )
    {
        frmr::Vec3f intersect;
        bool doesIntersect = faceIt.LineIntersection( lineStart, lineVector, true, false, intersect );
        if ( doesIntersect )
		{
			intersections.push_back( intersect );
		}
    }
    return intersections;
}

vector<frmr::Vec3f> Frustum::GetVisibleTrianglePoints( const frmr::Triangle &triangle ) const
{
	vector<frmr::Vec3f> visiblePoints;

	//check if each vertex is within the view frustum
	bool vert0Visible = Contains( triangle.GetVert0() );
	bool vert1Visible = Contains( triangle.GetVert1() );
	bool vert2Visible = Contains( triangle.GetVert2() );

	if ( vert0Visible ) { visiblePoints.push_back( triangle.GetVert0() ); }
	if ( vert1Visible ) { visiblePoints.push_back( triangle.GetVert1() ); }
	if ( vert2Visible ) { visiblePoints.push_back( triangle.GetVert2() ); }

	//if the entire triangle is not within the view frustum
	if ( visiblePoints.size() != 3 )
	{
		vector<frmr::Vec3f> intersections;
		//get intersections between triangle edges and the faces of the view frustum
		intersections = GetLineIntersections( triangle.GetVert0(), triangle.GetVec01() );
		visiblePoints.insert( visiblePoints.end(), intersections.begin(), intersections.end() );
		intersections = GetLineIntersections( triangle.GetVert0(), triangle.GetVec02() );
		visiblePoints.insert( visiblePoints.end(), intersections.begin(), intersections.end() );
		intersections = GetLineIntersections( triangle.GetVert1(), triangle.GetVec12() );
		visiblePoints.insert( visiblePoints.end(), intersections.begin(), intersections.end() );

		//get intersections between edges of the view frustum and the triangle
		for ( auto vectorIt : edgeVectors )
		{
			frmr::Vec3f intersect;
			bool doesIntersect = triangle.LineIntersection( position, vectorIt, false, true, intersect );
			if ( doesIntersect )
			{
				visiblePoints.push_back( intersect );
			}
		}
	}
	return visiblePoints;
}

vector<frmr::Triangle> Frustum::GetFaces() const
{
	return faces;
}

Frustum::Frustum( const frmr::Vec3f &cameraPosition, const frmr::Vec2f &cameraRotation, const float fovX, const float fovY, const float nearPlane, const float farPlane )
{
    //create 12 triangles
}

//vertices must be listed counter-clockwise
Frustum::Frustum( const frmr::Vec3f &cameraPosition, const vector<frmr::Vec3f> &vertices )
	: position( cameraPosition )
{
	for ( auto vertexIt : vertices )
	{
		edgeVectors.push_back( vertexIt - cameraPosition );
	}

	if ( vertices.size() < 3 )
	{
		cout << "Frustum::Frustum() - Not enough vertices supplied to frustum constructor." << endl;
	}
	else
	{
		//create faces between the camera position, a given vertex, and the next vertex in the list
		for ( unsigned int vertexIndex = 0; vertexIndex < vertices.size() - 1; vertexIndex++ )
		{
			faces.push_back( frmr::Triangle( cameraPosition, vertices[vertexIndex], vertices[vertexIndex+1] ) );
		}
		//create a final vertex from the first and last vertices
		faces.push_back( frmr::Triangle( cameraPosition, vertices[vertices.size()-1], vertices[0] ) );
	}
}
