#include <SFML/OpenGL.hpp>

#include "ProjectionState.h"

void ProjectionState::CopyModelviewMatrix( double newModelview[] )
{
	for ( int i = 0; i < 16; i++ )
	{
		newModelview[i] = modelview[i];
	}
}

void ProjectionState::CopyProjectionMatrix( double newProjection[] )
{
	for ( int i = 0; i < 16; i++ )
	{
		newProjection[i] = projection[i];
	}
}

void ProjectionState::CopyViewportMatrix( int newViewport[] )
{
	for ( int i = 0; i < 16; i++ )
	{
		newViewport[i] = viewport[i];
	}
}

void ProjectionState::CopyPerspectiveMatrix( float newPerspective[] )
{
	for ( int i = 0; i < 16; i++ )
	{
		newPerspective[i] = perspective[i];
	}
}

//this code is from MESA implementation of GLU's gluInvertMatrix(), although it is slightly modified
bool ProjectionState::InvertMatrix( const float matIn[16], float matOut[16] ) const
{
	float inv[16];
    float det;
    int i;

    inv[0] = matIn[5] * matIn[10] * matIn[15] - matIn[5] * matIn[11] * matIn[14] - matIn[9] * matIn[6] * matIn[15] + matIn[9] * matIn[7] * matIn[14] + matIn[13] * matIn[6] * matIn[11] - matIn[13] * matIn[7] * matIn[10];
    inv[4] = -matIn[4] * matIn[10] * matIn[15] + matIn[4] * matIn[11] * matIn[14] + matIn[8] * matIn[6] * matIn[15] - matIn[8] * matIn[7] * matIn[14] - matIn[12] * matIn[6] * matIn[11] + matIn[12] * matIn[7] * matIn[10];
    inv[8] = matIn[4] * matIn[9] * matIn[15] - matIn[4] * matIn[11] * matIn[13] - matIn[8] * matIn[5] * matIn[15] + matIn[8] * matIn[7] * matIn[13] + matIn[12] * matIn[5] * matIn[11] - matIn[12] * matIn[7] * matIn[9];
    inv[12] = -matIn[4] * matIn[9] * matIn[14] + matIn[4] * matIn[10] * matIn[13] + matIn[8] * matIn[5] * matIn[14] - matIn[8] * matIn[6] * matIn[13] - matIn[12] * matIn[5] * matIn[10] + matIn[12] * matIn[6] * matIn[9];
    inv[1] = -matIn[1] * matIn[10] * matIn[15] + matIn[1] * matIn[11] * matIn[14] + matIn[9] * matIn[2] * matIn[15] - matIn[9] * matIn[3] * matIn[14] - matIn[13] * matIn[2] * matIn[11] + matIn[13] * matIn[3] * matIn[10];
    inv[5] = matIn[0] * matIn[10] * matIn[15] - matIn[0] * matIn[11] * matIn[14] - matIn[8] * matIn[2] * matIn[15] + matIn[8] * matIn[3] * matIn[14] + matIn[12] * matIn[2] * matIn[11] - matIn[12] * matIn[3] * matIn[10];
    inv[9] = -matIn[0] * matIn[9] * matIn[15] + matIn[0] * matIn[11] * matIn[13] + matIn[8] * matIn[1] * matIn[15] - matIn[8] * matIn[3] * matIn[13] - matIn[12] * matIn[1] * matIn[11] + matIn[12] * matIn[3] * matIn[9];
    inv[13] = matIn[0] * matIn[9] * matIn[14] - matIn[0] * matIn[10] * matIn[13] - matIn[8] * matIn[1] * matIn[14] + matIn[8] * matIn[2] * matIn[13] + matIn[12] * matIn[1] * matIn[10] - matIn[12] * matIn[2] * matIn[9];
    inv[2] = matIn[1] * matIn[6] * matIn[15] - matIn[1] * matIn[7] * matIn[14] - matIn[5] * matIn[2] * matIn[15] + matIn[5] * matIn[3] * matIn[14] + matIn[13] * matIn[2] * matIn[7] - matIn[13] * matIn[3] * matIn[6];
    inv[6] = -matIn[0] * matIn[6] * matIn[15] + matIn[0] * matIn[7] * matIn[14] + matIn[4] * matIn[2] * matIn[15] - matIn[4] * matIn[3] * matIn[14] - matIn[12] * matIn[2] * matIn[7] + matIn[12] * matIn[3] * matIn[6];
    inv[10] = matIn[0] * matIn[5] * matIn[15] - matIn[0] * matIn[7] * matIn[13] - matIn[4]  * matIn[1] * matIn[15] + matIn[4] * matIn[3] * matIn[13] + matIn[12] * matIn[1] * matIn[7] - matIn[12] * matIn[3] * matIn[5];
    inv[14] = -matIn[0] * matIn[5] * matIn[14] + matIn[0] * matIn[6] * matIn[13] + matIn[4] * matIn[1] * matIn[14] - matIn[4] * matIn[2] * matIn[13] - matIn[12] * matIn[1] * matIn[6] + matIn[12] * matIn[2] * matIn[5];
    inv[3] = -matIn[1] * matIn[6] * matIn[11] + matIn[1] * matIn[7] * matIn[10] + matIn[5] * matIn[2] * matIn[11] - matIn[5] * matIn[3] * matIn[10] - matIn[9] * matIn[2] * matIn[7] + matIn[9] * matIn[3] * matIn[6];
    inv[7] = matIn[0] * matIn[6] * matIn[11] - matIn[0] * matIn[7] * matIn[10] - matIn[4] * matIn[2] * matIn[11] + matIn[4] * matIn[3] * matIn[10] + matIn[8] * matIn[2] * matIn[7] - matIn[8] * matIn[3] * matIn[6];
    inv[11] = -matIn[0] * matIn[5] * matIn[11] + matIn[0] * matIn[7] * matIn[9] + matIn[4] * matIn[1] * matIn[11] - matIn[4] * matIn[3] * matIn[9] - matIn[8] * matIn[1] * matIn[7] + matIn[8] * matIn[3] * matIn[5];
    inv[15] = matIn[0] * matIn[5] * matIn[10] - matIn[0] * matIn[6] * matIn[9] - matIn[4] * matIn[1] * matIn[10] + matIn[4] * matIn[2] * matIn[9] + matIn[8] * matIn[1] * matIn[6] - matIn[8] * matIn[2] * matIn[5];

    det = matIn[0] * inv[0] + matIn[1] * inv[4] + matIn[2] * inv[8] + matIn[3] * inv[12];

    if ( det < 0.001f && det > -0.001f )
    {
        return false;
    }

    det = 1.0f / det;

    for ( i = 0; i < 16; i++ )
    {
        matOut[i] = inv[i] * det;
    }

    return true;
}

//this code is from GLU's MultiplyMatrices4by4OpenGL_FLOAT(), although the parameters have been renamed
void ProjectionState::MultiplyMatrices( const float matInA[16], const float matInB[16], float matOut[16] ) const
{
	matOut[0] = matInA[0] * matInB[0] + matInA[4] * matInB[1] + matInA[8] * matInB[2] + matInA[12] * matInB[3];
    matOut[4] = matInA[0] * matInB[4] + matInA[4] * matInB[5] + matInA[8] * matInB[6] + matInA[12] * matInB[7];
    matOut[8] = matInA[0] * matInB[8] + matInA[4] * matInB[9] + matInA[8] * matInB[10] + matInA[12] * matInB[11];
    matOut[12] = matInA[0] * matInB[12] + matInA[4] * matInB[13] + matInA[8] * matInB[14] + matInA[12] * matInB[15];
    matOut[1] = matInA[1] * matInB[0] + matInA[5] * matInB[1] + matInA[9] * matInB[2] + matInA[13] * matInB[3];
    matOut[5] = matInA[1] * matInB[4] + matInA[5] * matInB[5] + matInA[9] * matInB[6] + matInA[13] * matInB[7];
    matOut[9] = matInA[1] * matInB[8] + matInA[5] * matInB[9] + matInA[9] * matInB[10] + matInA[13] * matInB[11];
    matOut[13] = matInA[1] * matInB[12] + matInA[5] * matInB[13] + matInA[9] * matInB[14] + matInA[13] * matInB[15];
    matOut[2] = matInA[2] * matInB[0] + matInA[6] * matInB[1] + matInA[10] * matInB[2] + matInA[14] * matInB[3];
    matOut[6] = matInA[2] * matInB[4] + matInA[6] * matInB[5] + matInA[10] * matInB[6] + matInA[14] * matInB[7];
    matOut[10] = matInA[2] * matInB[8] + matInA[6] * matInB[9] + matInA[10] * matInB[10] + matInA[14] * matInB[11];
    matOut[14] = matInA[2] * matInB[12] + matInA[6] * matInB[13] + matInA[10] * matInB[14] + matInA[14] * matInB[15];
    matOut[3] = matInA[3] * matInB[0] + matInA[7] * matInB[1] + matInA[11] * matInB[2] + matInA[15] * matInB[3];
    matOut[7] = matInA[3] * matInB[4] + matInA[7] * matInB[5] + matInA[11] * matInB[6] + matInA[15] * matInB[7];
    matOut[11] = matInA[3] * matInB[8] + matInA[7] * matInB[9] + matInA[11] * matInB[10] + matInA[15] * matInB[11];
    matOut[15] = matInA[3] * matInB[12] + matInA[7] * matInB[13] + matInA[11] * matInB[14] + matInA[15] * matInB[15];
}

frmr::Vec3f ProjectionState::Project( const frmr::Vec3f &objectCoord )
{
	double winX, winY, winZ;
	gluProject( (double) objectCoord.GetX(), (double) objectCoord.GetY(), (double) objectCoord.GetZ(), modelview, projection, viewport, &winX, &winY, &winZ );
	return frmr::Vec3f( (float) winX, (float) winY, (float) winZ );
}

frmr::Vec3f ProjectionState::UnProject( const frmr::Vec3f &windowCoord )
{
	double objX, objY, objZ;
	gluUnProject( (double) windowCoord.GetX(), (double) windowCoord.GetY(), (double) windowCoord.GetZ(), modelview, projection, viewport, &objX, &objY, &objZ );
	return frmr::Vec3f( (float) objX, (float) objY, (float) objZ );
}

ProjectionState::ProjectionState()
{
	glGetIntegerv( GL_VIEWPORT, viewport );

	float modelviewFloat[16];
	float projectionFloat[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelviewFloat );
	glGetFloatv( GL_PROJECTION_MATRIX, projectionFloat );
	MultiplyMatrices( projectionFloat, modelviewFloat, perspective );
	InvertMatrix( perspective, perspective );

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
}
