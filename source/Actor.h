#ifndef ACTOR_H
#define ACTOR_H

#include <stdint.h>
#include <string>

#include "frmr_Vec3f.h"
#include "frmr_Vec2f.h"

using std::string;

class Actor
{
protected:
    string          name;
    frmr::Vec3f     position;
    frmr::Vec2f     rotation;
    frmr::Vec3f     velocity;

protected:
    void ApplyVelocity( const float deltaTime );
    void RotateY( const float &change );
    void SetRotationY( const float &newY );

public:
    string      GetName() const;
    frmr::Vec3f GetPosition() const;
    frmr::Vec2f GetRotation() const;

public:
    Actor( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const frmr::Vec3f &velocity );
};

#endif // ACTOR_H
