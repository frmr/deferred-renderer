#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

class Effect
{
public:
	enum class EffectType
	{
		//reduces player health, measured in damage per second
		EFFECT_DAMAGE_FIRE,
		EFFECT_DAMAGE_HOLY,
		EFFECT_DAMAGE_ICE,
		EFFECT_DAMAGE_NORMAL,
		EFFECT_DAMAGE_SHOCK,

		//multiplies strength of EFFECT_DAMAGE_X when spawning projectiles
		EFFECT_MULTIPLY_FIRE_ATTACK,
		EFFECT_MULTIPLY_HOLY_ATTACK,
		EFFECT_MULTIPLY_ICE_ATTACK,
		EFFECT_MULTIPLY_NORMAL_ATTACK,
		EFFECT_MULTIPLY_SHOCK_ATTACK,

		//multiplies strength of EFFECT_DAMAGE_X when applying effects
		EFFECT_MULTIPLY_FIRE_DEFENSE,
		EFFECT_MULTIPLY_HOLY_DEFENSE,
		EFFECT_MULTIPLY_ICE_DEFENSE,
		EFFECT_MULTIPLY_NORMAL_DEFENSE,
		EFFECT_MULTIPLY_SHOCK_DEFENSE,

		EFFECT_MULTIPLY_HEALTH, 		//use for demi, quarter, etc.

		//status ailments, strength has no effect on these
		EFFECT_BLIND,					//blackens the screen
		EFFECT_CONFUSE,
		EFFECT_COUNTDOWN, 				//player dies when timer ends, must be cured
		EFFECT_PARALYZE,				//prevents movement
		EFFECT_SILENCE,					//prevents casting of spells

		EFFECT_CURE_BLIND,
		EFFECT_CURE_CONFUSE,
		EFFECT_CURE_COUNTDOWN,
		EFFECT_CURE_PARALYZE,
		EFFECT_CURE_SILENCE,

		//player stat modifications
		EFFECT_MODIFY_COOLDOWN,			//% remaining cooldown time, multiply to stack
		EFFECT_MODIFY_FALL_SPEED,		//% remaining fall speed, multiply to stack
		EFFECT_MODIFY_FRICTION,
		EFFECT_MODIFY_JUMP_STRENGTH,
		EFFECT_MODIFY_MOVE_SPEED,
		EFFECT_REGENERATE_MAGIC,		//most players regenerate magic

		//misc effects
		EFFECT_BAIT,					//draw enemies' attention and fire
		EFFECT_DEATH,					//for level boundaries, traps, etc.
		EFFECT_DETECT,      			//see invisible players
		EFFECT_ETHEREAL,				//disable collisions with projectiles
		EFFECT_ILLUMINATE,				//emits light from player
		EFFECT_INVISIBLE,
		EFFECT_LEVITATE,
		EFFECT_RECALL,					//teleport to nearest checkpoint
		EFFECT_RESURRECT,
		EFFECT_REVEAL,      			//negates invisibility
		EFFECT_SHADE,
		EFFECT_SUNLIGHT,    			//damages vampires
		EFFECT_UNDEAD,					//holy damage reduces health, everything else does 1 damage per second
		EFFECT_VAMPIRE,     			//damaged by sunlight, needs a benefit of some kind
		EFFECT_XRAY						//see players through walls
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
