#include "Actor.h"

#include "frmr_encode.h"

int32_t Actor::actorNumIncrementor = 0;

void Actor::ApplyVelocity( const float deltaTime )
{
    previousPosition = position;
    position += velocity * deltaTime;
}

void Actor::RotateY( const float &change )
{
    rotation = frmr::Vec2f( rotation.GetX(), rotation.GetY() + change );
    //TODO normalise angle
}

void Actor::SetRotationY( const float &newY )
{
    rotation = frmr::Vec2f( rotation.GetX(), newY );
}

int32_t Actor::GetActorNum() const
{
    return actorNum;
}

int16_t Actor::GetCurrentZoneNum() const
{
    return currentZoneNum;
}

string Actor::GetName() const
{
    return name;
}

frmr::Vec3f Actor::GetPosition() const
{
    return position;
}

frmr::Vec2f Actor::GetRotation() const
{
    return rotation;
}

Actor::Actor( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const frmr::Vec3f &velocity, const int16_t zoneNum )
    : actorNum( actorNumIncrementor++ ),
      actorNumEncoded( frmr::EncodeINT32( actorNum ) ),
      name( name ),
      position( position ),
      previousPosition( position ),
      rotation( rotation ),
      velocity( velocity ),
      currentZoneNum( zoneNum )
{
}
