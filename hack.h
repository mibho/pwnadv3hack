#pragma once

#include "Classes.h"
#include "tools.h"

//GIANT_RAT = 5.0 <- float constant used as argument for spawn..
enum address {
	WORLD,
	GAMEAPI,
	PLAYER,
	PLAYER_ACTOR,
	GIANTRATSPAWNER,
	BEARSPAWNER
	
};

enum location {
	SEWER,
	MOLTENCAVE,
	LOSTCAVE,
	PIRATEBAY,
	GOLDFARM,
	COWLEVEL,
	BALLMERPEAK,
	UNBEARABLEWOODS
};
struct playerMoveInfo {
	float walkSpeed    = 0;
	float jumpHeight   = 0;
	float jumpHoldTime = 0;

	void adjust(float spd, float jmpHi, float jmpTi) { walkSpeed = spd, jumpHeight = jmpHi, jumpHoldTime = jmpTi; };
};

class pwnHack {

public: 
	
	pwnHack() { init(); };
	void init();
	bool isLoaded();
	void storeLocationNames();
	//void summon();
	int getPlayerHealth();
	int getPlayerMana();
	

	void setPlayerHealth(int value);
	void setPlayerMana(int value);
	
	void teleToRegion(BYTE choice);
	void setPlayerMove(float walkspd, float jmpheight, float jmptime);
	
	void printActorList();	

private:

	bool passed;
	DWORD baseAddr;
	std::vector<DWORD*> addrList;
	std::vector<const char*> locations;
	Player* myPlayerActorBase;
	// "new" way; are obj same?
	World* myWorld_t;
	GameAPI* myGame_t;

	void getAddresses();
	void getWorldAndGameAPI();
	void setMovementStats(const playerMoveInfo& desiredStats);
	playerMoveInfo getMovementStats();
};

/*
World* myWorld;
GameAPI* myGame;
*/