#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "AnimatedBillboard.h"
#include "Effect.h"
#include "Potion.h"
#include "SpellSet.h."
#include "frmr_Vec3f.h"

using std::vector;

class Player
{
private:
    static int16_t          playerNumIncrementer;
    int16_t                 playerNum;

    AnimatedBillboard       skinBillboard;
    AnimatedBillboard       clothesBillboard;

	float 				    maxHealth;
	float 				    health;
	float 				    maxMagic;
	float 				    magic;

	float 				    maxControlSpeed;
	float 				    controlSpeed;
	float 				    controlAcceleration;
	frmr::Vec3f			    controlVelocity;
	float 				    maxFallSpeed;
	frmr::Vec3f			    fallVelocity;
	frmr::Vec3f 		    momentumVelocity;
    frmr::Vec3f             finalVelocity;

	double				    cooldownTimer;

	vector<Potion>		    potions;
	vector<SpellSet>	    spells;
	vector<Effect>		    effects;

	bool				    humanControlled;
	unsigned int		    humanNetworkID;
	frmr::Vec3f	            color;
	uint8_t				    team;

private:
	bool				    HasEffect( const Effect::EffectType effect ) const;

public:
	void				    AddEffect( const Effect newEffect );
	bool				    IsDead() const;
	void 				    SetColor( const unsigned int newRed, const unsigned int newGreen, const unsigned int newBlue );
	void				    SetTeam( const uint8_t newTeam );

};

#endif
