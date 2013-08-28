#include "Actor.h"

void Actor::ApplyVelocity( const float deltaTime )
{
    position += velocity * deltaTime;
}

void Actor::RotateY( const float &change )
{
    rotation = frmr::Vec2f( rotation.GetX(), rotation.GetY() + change );
}

void Actor::SetRotationY( const float &newY )
{
    rotation = frmr::Vec2f( rotation.GetX(), newY );
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

Actor::Actor( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const frmr::Vec3f &velocity )
    : name( name ),
      position( position ),
      rotation( rotation ),
      velocity( velocity )
{
}
