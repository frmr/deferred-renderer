#include "Entity.h"

int32_t Entity::idIncrementor = 0;

void Entity::ApplyVelocity( const float deltaTime )
{
    previousPosition = position;
    position += velocity * deltaTime;
}

void Entity::RotateY( const float &change )
{
    rotation.SetY( rotation.GetY() + change );
    //TODO normalise angle
}

void Entity::SetRotationY( const float &newY )
{
    rotation.SetY( newY );
}

int32_t Entity::GetId() const
{
    return id;
}

int16_t Entity::GetCurrentZoneNum() const
{
    return currentZoneNum;
}

string Entity::GetName() const
{
    return name;
}

frmr::Vec3f Entity::GetPosition() const
{
    return position;
}

frmr::Vec3f Entity::GetRotation() const
{
    return rotation;
}

Entity::Entity( const string &name, const frmr::Vec3f &position, const frmr::Vec3f &rotation, const frmr::Vec3f &velocity, const int16_t zoneNum )
    : id( idIncrementor++ ),
      name( name ),
      position( position ),
      previousPosition( position ),
      rotation( rotation ),
      velocity( velocity ),
      currentZoneNum( zoneNum )
{
}
