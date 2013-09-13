#ifndef EFFECT_H
#define EFFECT_H

#include <stdint.h>

class Effect
{
public:
	enum class EffectType
	{
		//most players regenerate magic
		EFFECT_REGENERATE_MAGIC,

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

		//status ailments, strength has no effect on these
		EFFECT_BLIND,
		EFFECT_CONFUSE,
		EFFECT_COUNTDOWN, //player dies when timer ends, must be cured
		EFFECT_PARALYZE,
		EFFECT_SILENCE,
		EFFECT_CURE_BLIND,
		EFFECT_CURE_CONFUSE,
		EFFECT_CURE_COUNTDOWN,
		EFFECT_CURE_PARALYZE,
		EFFECT_CURE_SILENCE,
		EFFECT_IMMUNE_BLIND,
		EFFECT_IMMUNE_CONFUSE,
		EFFECT_IMMUNE_COUNTDOWN,
		EFFECT_IMMUNE_PARALYZE,
		EFFECT_IMMUNE_SILENCE,

		//player stat modifications
		EFFECT_MODIFY_COOLDOWN,
		EFFECT_MODIFY_JUMP_STRENGTH,
		EFFECT_MODIFY_MOVE_SPEED,

		//misc effects, strength has no effect on these
		EFFECT_BAIT,		//draw enemies' attention and fire
		EFFECT_DEATH,		//for level boundaries, traps, etc.
		EFFECT_ETHEREAL,	//disable collisions with projectiles
		EFFECT_ILLUMINATE,	//emits light from player
		EFFECT_INVISIBLE,
		EFFECT_LEVITATE,
		EFFECT_RECALL,		//teleport to nearest checkpoint
		EFFECT_RESURRECT,
		EFFECT_SUNLIGHT,    //damages vampires
		EFFECT_UNDEAD,		//holy damage reduces health, everything else does 1 damage per second
		EFFECT_VAMPIRE      //damaged by sunlight, needs a benefit of some kind
	};

private:
	EffectType	type;
	int32_t 	timer; //negative value indicated permanent effect
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
