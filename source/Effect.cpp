#include "Effect.h"

bool Effect::GetStack() const
{
	return stack;
}

float Effect::GetStrength() const
{
	return strength;
}

Effect::EffectType Effect::GetType() const
{
	return type;
}

void Effect::MultiplyStrength( const float factor )
{
	strength *= factor;
}

bool Effect::UpdateTimer( const double elapsed )
{
	if ( permanent )
	{
		return true;
	}
	else
	{
		timer -= elapsed;
		return ( timer <= 0.0 ) ? false : true;
	}
}

Effect::Effect( const Effect::EffectType type, const double duration, const float strength, const bool stack )
	: type( type ),
	  timer( duration ),
	  strength( strength ),
	  stack( stack )
{
}
