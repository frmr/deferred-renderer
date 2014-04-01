#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

class Effect
{
public:
	enum class EffectType
	{
		//reduces player health, measured in damage per second
		DAMAGE_FIRE,
		DAMAGE_HOLY,
		DAMAGE_ICE,
		DAMAGE_NORMAL,
		DAMAGE_SHOCK,

		//multiplies strength of DAMAGE_X when spawning projectiles
		MULTIPLY_FIRE_ATTACK,
		MULTIPLY_HOLY_ATTACK,
		MULTIPLY_ICE_ATTACK,
		MULTIPLY_NORMAL_ATTACK,
		MULTIPLY_SHOCK_ATTACK,

		//multiplies strength of DAMAGE_X when applying effects
		MULTIPLY_FIRE_DEFENSE,
		MULTIPLY_HOLY_DEFENSE,
		MULTIPLY_ICE_DEFENSE,
		MULTIPLY_NORMAL_DEFENSE,
		MULTIPLY_SHOCK_DEFENSE,

		MULTIPLY_HEALTH, 		//use for demi, quarter, etc.

		//status ailments, strength has no effect on these
		BLIND,					//blackens the screen
		CONFUSE,
		COUNTDOWN, 				//player dies when timer ends, must be cured
		PARALYZE,				//prevents movement
		SILENCE,				//prevents casting of spells

		CURE_BLIND,
		CURE_CONFUSE,
		CURE_COUNTDOWN,
		CURE_PARALYZE,
		CURE_SILENCE,

		//player stat modifications
		MODIFY_COOLDOWN,		//% remaining cooldown time, multiply to stack
		MODIFY_FALL_SPEED,		//% remaining fall speed, multiply to stack
		MODIFY_FRICTION,
		MODIFY_JUMP_STRENGTH,
		MODIFY_MOVE_SPEED,
		REGENERATE_MAGIC,		//most players regenerate magic

		//misc effects
		BAIT,					//draw enemies' attention and fire
		DEATH,					//for level boundaries, traps, etc.
		DETECT,      			//see invisible players
		ETHEREAL,				//disable collisions with projectiles
		ILLUMINATE,				//emits light from player
		INVISIBLE,
		LEVITATE,
		RECALL,					//teleport to nearest checkpoint
		RESURRECT,
		REVEAL,      			//negates invisibility
		SHADE,
		SUNLIGHT,    			//damages vampires
		UNDEAD,					//holy damage reduces health, everything else does 1 damage per second
		VAMPIRE,     			//damaged by sunlight, needs a benefit of some kind
		XRAY					//see players through walls
	};

private:
	EffectType	type;
	int32_t 	timer; // Negative indicates permanent effect, zero indicates active for one update cycle
	float		strength;
	bool		canStack;

public:
	bool		GetCanStack() const;
	float		GetStrength() const;
	EffectType	GetType() const;

	void 		MultiplyStrength( const float factor );
	bool 		UpdateTimer( const int32_t elapsed );

public:
	Effect( const EffectType type, const int32_t duration, const float strength, const bool canStack );
};

#endif
