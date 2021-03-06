#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <map>

#include "AssetManager.h"
#include "PerspectiveCamera.h"
#include "InputState.h"
#include "Light.h"
#include "Player.h"
#include "ProjectionState.h"
#include "Spectator.h"
#include "StaticGeometry.h"

using std::string;
using std::map;
using std::vector;

class Simulation
{
private:
	//object lists
	PerspectiveCamera	activeCamera;
	Spectator			spectator;
	StaticGeometry		staticGeometry;
	vector<Player>		players; //TODO: make sure this list is sorted by actorNumEncoded when constructed, then use encoded num sent through network to find actor without decoding. Further players can just be added to the end

	map<string, map<string, vector<AnimatedBillboard::Frame>>>  animations; //this is silly, make an Animation class?

private:
    void LoadBillboardAnimation( const string filename );
    bool LoadMap( const string filename );
    void UnloadCurrentMap();

public:
    bool				ChangeMap( const string filename );
    PerspectiveCamera	GetActiveCamera() const;
    vector<Light>		GetStaticLights() const;
	ProjectionState		RenderLit() const;
	ProjectionState		RenderShadowCasters( const PerspectiveCamera &lightView ) const;
	void				Update( const int32_t elapsedTime, const float deltaTime, const InputState &inputs, const float mouseSensitivity );

public:
	Simulation( const AssetManager &assets );
	~Simulation();
};

#endif
