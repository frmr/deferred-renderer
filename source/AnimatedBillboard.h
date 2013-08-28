#ifndef ANIMATED_BILLBOARD_H
#define ANIMATED_BILLBOARD_H

#include <string>
#include <vector>
#include <map>

#include <SFML/OpenGL.hpp>

#include "frmr_Vec3f.h"

using std::string;
using std::map;
using std::vector;

class AnimatedBillboard
{
public:
    enum class BillboardType
    {
        ROTATION,
        POSITION
    };

    class Frame
    {
    private:
        vector<GLuint*> meshes; //eight directions
        int32_t         duration;

    public:
        GLuint* GetMesh( const float angle ) const;

    public:
        Frame();
        //~Frame();
    };

private:
    BillboardType   type;
	int32_t 		frameTimer;
	unsigned int 	frameIndex;

	map<string, vector<Frame>>* animations;

private:
	void LookAt( const frmr::Vec3f pos );
	void SetAnimation( const string animationName );

public:

public:
	AnimatedBillboard( const BillboardType type, map<string, vector<Frame>>* const animations );
};

#endif
