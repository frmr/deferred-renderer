#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <map>

#include "AssetManager.h"
#include "Camera.h"
#include "InputState.h"
#include "Light.h"
#include "Player.h"
#include "StaticGeometry.h"

using std::string;
using std::map;
using std::vector;

class Simulation
{
private:
	//object lists
	Camera          activeCamera;
	StaticGeometry  staticGeometry;
	vector<Player>  players;

	map<string, map<string, vector<AnimatedBillboard::Frame>>>  animations;

private:
    void LoadBillboardAnimation( const string filename );
    bool LoadMap( const string filename );
    void UnloadCurrentMap();

public:
    bool            ChangeMap( const string filename );
    Camera          GetCamera() const;
    vector<Light>   GetStaticLights() const;
    void            RenderLit() const;
	void            Update( const int32_t elapsedTime, const float deltaTime, const InputState &inputs, const float mouseSensitivity );

public:
	Simulation( const AssetManager &assets );
	~Simulation();
};

#endif
