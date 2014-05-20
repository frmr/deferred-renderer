#ifndef POTION_H
#define POTION_H

#include <vector>

#include "effect.h"

using std::vector;

class Potion
{
private:
	vector<Effect>	effects;

public:
	vector<Effect>	GetEffects() const;
	void			AddEffect( const Effect &newEffect )
	{
		effects.push_back( newEffect );
	}
};

#endif
