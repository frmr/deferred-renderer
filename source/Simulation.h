#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <map>

#include "Player.h"

using std::string;
using std::map;
using std::vector;

class Simulation
{
private:
    //irr::scene::IAnimatedMesh*  mapMesh;
    //irr::scene::IMeshSceneNode* mapNode;
	//object lists
	vector<Player> 		        players;

    //AssetData temporaryAssets

	map<string, map<string, vector<AnimatedBillboard::Frame>>>  animations;

private:
    void LoadBillboardAnimation( const string filename );
    bool LoadMap( const string filename );
    void UnloadCurrentMap();

public:
    bool ChangeMap( const string filename );
    void RenderLit() const;
	void Update( const uint32_t elapsedTime, const float deltaTime );

public:
	Simulation();
	~Simulation();
};

#endif
