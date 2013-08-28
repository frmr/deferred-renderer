#ifndef STATIC_GEOMETRY_H
#define STATIC_GEOMETRY_H

#include "GL/gl.h"
#include <vector>

using std::vector;

class StaticGeometry
{
private:
    //zones, portals, etc.
    GLuint          zone;

public:
    void Render() const;

public:
    StaticGeometry();
    ~StaticGeometry();
};

#endif // STATIC_GEOMETRY_H
