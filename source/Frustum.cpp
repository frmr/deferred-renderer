#include "Frustum.h"

#include <iostream>

#include "frmr_math.h"

using std::cout;
using std::endl;

bool Frustum::Contains( const frmr::Vec3f &point ) const
{
    for ( auto faceIt : faces )
    {
        //if point is on the wrong side of the face
        //  return false
    }
    return true;
}

vector<frmr::Vec3f> Frustum::GetIntersections( const frmr::Vec3f &lineStart, const frmr::Vec3f &lineVector ) const
{
    vector<frmr::Vec3f> intersections;

    for ( auto faceIt : faces )
    {
        //get point of intersection
        //check if point is within face
        //if so, add to intersections
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
    float halfFovX = fovX / 2.0f;
    float halfFovY = fovY / 2.0f;

    frmr::Vec3f topLeftPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() - halfFovY, cameraRotation.GetY() - halfFovX ) * 1000.0f;
    frmr::Vec3f topRightPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() + halfFovY, cameraRotation.GetY() - halfFovX ) * 1000.0f;
    frmr::Vec3f bottomRightPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() + halfFovY, cameraRotation.GetY() + halfFovX ) * 1000.0f;
    frmr::Vec3f bottomLeftPoint = cameraPosition + frmr::CalculateVectorFromRotation( cameraRotation.GetX() - halfFovY, cameraRotation.GetY() + halfFovX ) * 1000.0f;

	faces.push_back( frmr::Triangle( cameraPosition, topLeftPoint, topRightPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, topRightPoint, bottomRightPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, bottomRightPoint, bottomLeftPoint ) );
	faces.push_back( frmr::Triangle( cameraPosition, bottomLeftPoint, topLeftPoint ) );
}

Frustum::Frustum( const frmr::Vec3f &cameraPosition, const frmr::Vec2f &cameraRotation, const float fovX, const float fovY, const float nearPlane, const float farPlane )
{
    //create 12 triangles
}

Frustum::Frustum( const frmr::Vec3f &cameraPosition, const vector<frmr::Vec3f> &vertices )
{
	if ( vertices.size() < 2 )
	{
		cout << "Frustum::Frustum() - Not enough vertices supplied to frustum constructor." << endl;
	}
	else
	{
		//create faces between the camera position, a given vertex, and the next vertex in the list
		for ( int vertexIndex = 0; vertexIndex < vertices.size() - 1; vertexIndex++ )
		{
			faces.push_back( frmr::Triangle( cameraPosition, vertices[vertexIndex], vertices[vertexIndex+1] ) );
		}
		//create a final vertex from the first and last vertices
		faces.push_back( frmr::Triangle( cameraPosition, vertices[vertices.size()-1], vertices[0] ) );
	}
}
