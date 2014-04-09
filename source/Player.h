#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Entity.h"
#include "AnimatedBillboard.h"
#include "Effect.h"
#include "Potion.h"
#include "SpellSet.h."
#include "frmr/Vec3f.h"

using std::vector;

class Player : public Entity
{
private:
    AnimatedBillboard       skinBillboard; //TODO: Have one billboard and use a shader to color the appropriate parts
    AnimatedBillboard       clothesBillboard;

	float 				    healthMax;
	float 				    health;
	float 				    magicMax;
	float 				    magic;

	float 				    controlSpeedMax;
	float 				    controlSpeed;
	float 				    controlAcceleration;
	frmr::Vec3f			    controlVelocity;
	float 				    fallSpeedMax;
	frmr::Vec3f			    fallVelocity;
	frmr::Vec3f 		    momentumVelocity;

	int32_t				    cooldownTimer;

	vector<Potion>		    potions;
	vector<SpellSet>	    spells;
	vector<Effect>		    effects;

	bool				    humanControlled;
	unsigned int		    humanNetworkId;
	frmr::Vec3f	            color;
	int8_t				    team;

private:
	bool				    HasEffect( const Effect::EffectType effect ) const;

public:
	void				    AddEffect( const Effect newEffect );
	bool				    IsDead() const;
	void 				    SetColor( const unsigned int newRed, const unsigned int newGreen, const unsigned int newBlue );
	void				    SetTeam( const uint8_t newTeam );
	void                    Update();

public:
    Player( const frmr::Vec3f &position, const frmr::Vec3f &rotation );

};

#endif
