#include "Actor.h"

int32_t Actor::idIncrementor = 0;

void Actor::ApplyVelocity( const float deltaTime )
{
    previousPosition = position;
    position += velocity * deltaTime;
}

void Actor::RotateY( const float &change )
{
    rotation = frmr::Vec3f( rotation.GetX(), rotation.GetY() + change, rotation.GetZ() );
    //TODO normalise angle
}

void Actor::SetRotationY( const float &newY )
{
    rotation.SetY( newY );
}

int32_t Actor::GetId() const
{
    return id;
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

frmr::Vec3f Actor::GetRotation() const
{
    return rotation;
}

Actor::Actor( const string &name, const frmr::Vec3f &position, const frmr::Vec3f &rotation, const frmr::Vec3f &velocity, const int16_t zoneNum )
    : id( idIncrementor++ ),
      name( name ),
      position( position ),
      previousPosition( position ),
      rotation( rotation ),
      velocity( velocity ),
      currentZoneNum( zoneNum )
{
}
