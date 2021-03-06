#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <string>

#include "frmr/Vec2f.h"
#include "frmr/Vec3f.h"

using std::string;

class Entity
{
private:
    static int32_t  idIncrementor;

protected:
    int32_t         id;
    string          name;
    frmr::Vec3f     position;
    frmr::Vec3f     previousPosition;
    frmr::Vec2f     rotation;
    frmr::Vec3f     velocity;
    int16_t         currentZoneNum;

protected:
    void ApplyVelocity( const float deltaTime );
    void RotateY( const float &change );
    void SetRotationY( const float &newY );

public:
    int32_t     GetId() const;
    int16_t     GetCurrentZoneNum() const;
    string      GetName() const;
    frmr::Vec3f GetPosition() const;
    frmr::Vec2f GetRotation() const;

public:
    Entity( const string &name, const frmr::Vec3f &position, const frmr::Vec2f &rotation, const frmr::Vec3f &velocity, const int16_t zoneNum );
};

#endif // ACTOR_H
