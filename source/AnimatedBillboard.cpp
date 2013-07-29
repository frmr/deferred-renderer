#include "AnimatedBillboard.h"

AnimatedBillboard::AnimatedBillboard( irr::scene::IMeshSceneNode* const nodeRef, map< string, vector< pair<irr::scene::IMesh*, double> > >* const animationsRef )
	: rotation( 0.0f ),
	  frameTimer( 0.0 ),
	  frameIndex( 0 ),
	  nodeRef( nodeRef ),
	  animationsRef( animationsRef )
{
}
