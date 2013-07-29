#ifndef ANIMATED_BILLBOARD_H
#define ANIMATED_BILLBOARD_H

#include <string>
#include <vector>
#include <utility>
#include <map>

#include "irrlicht.h"
#include "frmr_Vec3f.h"

using std::string;
using std::map;
using std::pair;
using std::vector;

class AnimatedBillboard
{
private:
	float 			rotation;
	double 			frameTimer;
	unsigned int 	frameIndex;

	irr::scene::IMeshSceneNode*					                nodeRef;
	map<string, vector<pair<irr::scene::IMesh*, double>>>*   animationsRef;

private:
	void LookAt( const frmr::Vec3f pos );
	void SetAnimation( const string animationName );

public:
	void SetAlpha( const unsigned int newAlpha );
	void SetColor( const unsigned int newRed, const unsigned int newGreen, const unsigned int newBlue );

public:
	AnimatedBillboard( irr::scene::IMeshSceneNode* const nodeRef, map< string, vector< pair<irr::scene::IMesh*, double> > >* const animationsRef );
};

#endif
