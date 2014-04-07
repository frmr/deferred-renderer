#include <SFML/OpenGL.hpp>

#include <vector>

#include "frmr/Vec3f.h"

using std::vector;

class IcosphereGenerator
{
private:
    struct Triangle
    {
        frmr::Vec3f v0, v1, v2;
        Triangle( const frmr::Vec3f v0, const frmr::Vec3f v1, const frmr::Vec3f v2 )
            : v0( v0 ), v1( v1 ), v2( v2 )
        {
        }

        Triangle()
            : v0( frmr::Vec3f() ), v1( frmr::Vec3f() ), v2( frmr::Vec3f() )
        {
        }
    };

private:
    static vector<Triangle> icosahedron;

private:
    static vector<Triangle> DefineIcosahedron();

public:
    static GLuint GenerateIcosphereDisplayList( const int subdivisions );
};
