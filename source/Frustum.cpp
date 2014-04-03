#include "Frustum.h"

#include <iostream>

#include "frmr_math.h"

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

//returns a vector of any intersections of a line cutting throw the frustum's faces
vector<frmr::Vec3f> Frustum::GetIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const
{
    vector<frmr::Vec3f> intersections;

    for ( auto faceIt : faces )
    {
        frmr::Vec3f intersect;
        bool doesIntersect = frmr::LinePlaneIntersection(  faceIt.GetNormal(), faceIt.GetVert0(), lineStart, lineVector, true, intersect );
        if ( doesIntersect )
		{
			if ( faceIt.ContainsPoint( intersect ) )
			{
				intersections.push_back( intersect );
			}
		}
    }
    return intersections;
}

vector<frmr::Triangle> Frustum::GetFaces() const
{
	return faces;
}

Frustum::Frustum( const frmr::Vec3f &cameraPosition, const frmr::Vec2f &cameraRotation, const float fovX, const float fovY )
{
    //create four triangles
    //calculate the four far points
    float halfFovX = 0.5f * fovX;
    float halfFovY = 0.5f * fovY;

    frmr::Vec3f topLeftPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() + halfFovY, cameraRotation.GetY() + halfFovX ) * 1000.0f;
    frmr::Vec3f topRightPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() + halfFovY, cameraRotation.GetY() - halfFovX ) * 1000.0f;
    frmr::Vec3f bottomRightPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() - halfFovY, cameraRotation.GetY() - halfFovX ) * 1000.0f;
    frmr::Vec3f bottomLeftPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() - halfFovY, cameraRotation.GetY() + halfFovX ) * 1000.0f;

	//face vertices declared counter-clockwise
	faces.push_back( frmr::Triangle( cameraPosition, topRightPoint,		topLeftPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, topLeftPoint, 		bottomLeftPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, bottomLeftPoint,	bottomRightPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, bottomRightPoint, 	topRightPoint ) );
}

Frustum::Frustum( const frmr::Vec3f &cameraPosition, const frmr::Vec2f &cameraRotation, const float fovX, const float fovY, const float nearPlane, const float farPlane )
{
    //create 12 triangles
}

//vertices must be listed counter-clockwise
Frustum::Frustum( const frmr::Vec3f &cameraPosition, const vector<frmr::Vec3f> &vertices )
{
	if ( vertices.size() < 2 )
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
