#include "AnimatedBillboard.h"

AnimatedBillboard::AnimatedBillboard( const BillboardType type, map<string, vector<Frame>>* const animations )
	: type( type ),
      frameTimer( 0 ),
	  frameIndex( 0 ),
	  animations( animations )
{
}
