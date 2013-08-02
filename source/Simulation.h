#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "irrlicht.h"
#include "Player.h"

using std::string;
using std::map;
using std::vector;
using std::pair;

class Simulation
{
private:
    irr::scene::ISceneManager*  sceneManager;
	//object lists
	vector<Player> 		        players;

	vector<map<string, vector<pair<irr::scene::IMesh*, double>>>>   animations;

public:
	void Update();

public:
	Simulation( irr::IrrlichtDevice* const device );
	~Simulation();
};

#endif
