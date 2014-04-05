#ifndef PROJECTION_STATE_H
#define PROJECTION_STATE_H

#include <memory>

#include "frmr_Vec3f.h"

class ProjectionState
{
private:
	double	modelview[16];
	double	projection[16];
	int		viewport[4];
	float	perspective[16];

private:
	bool InvertMatrix( const float matIn[16], float matOut[16] ) const;
	void MultiplyMatrices( const float matInA[16], const float matInB[16], float matOut[16] ) const;

public:
	frmr::Vec3f	Project( const frmr::Vec3f &objectCoord );
	frmr::Vec3f	UnProject( const frmr::Vec3f &windowCoord );

public:
	void		CopyModelviewMatrix( double newModel[] );
	void		CopyProjectionMatrix( double newProj[]  );
	void		CopyViewportMatrix( int newView[] );
	void		CopyPerspectiveMatrix( float newPerspective[] );

public:
	ProjectionState();
};

#endif // TRANSFORMATION_MATRICES_H
