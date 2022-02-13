#include "hack.h"

#define TOTAL_LOCATIONS 8

void pwnHack::init()
{
	baseAddr = reinterpret_cast<DWORD>(GetModuleHandleA("gamelogic.dll"));

	if (!baseAddr) {
		MessageBoxA(NULL, ".dll not found. Is the game running?", "Oops!", MB_OK);
		passed = FALSE;
	}
	else {

		storeLocationNames();
		getAddresses();
		getWorldAndGameAPI();
		myPlayerActorBase = reinterpret_cast<Player*>(addrList[address::PLAYER_ACTOR]);

		passed = TRUE;
	}
}
bool pwnHack::isLoaded()
{
	return passed;
}
void pwnHack::storeLocationNames()
{
	locations.push_back("Sewer");
	locations.push_back("MoltenCave");
	locations.push_back("LostCave");
	locations.push_back("PirateBay");
	locations.push_back("GoldFarm");
	locations.push_back("CowLevel");
	locations.push_back("UnbearableWoods");
	locations.push_back("PwnieIsland");
}
/*
void pwnHack::summon()
{
}
*/
/*
World + 0x60 = TownBears

World + 0xD0 = CliffRats

World + 0x140 = TownRats
	[World + 0x140] + 0x120 = EnemyChaseState: AIState
	[World + 0x140] + 0x124 = GiantRat:Enemy:AiActor:Actor :D//


	GiantRatSpawner = baseAddr + 7260c
	GiantRat = GiantRatSpawner + 3A78 
*/


int pwnHack::getPlayerHealth()
{
	return myPlayerActorBase->m_health;
}

int pwnHack::getPlayerMana()
{
	return myPlayerActorBase->m_mana;
}

void pwnHack::setPlayerHealth(int value)
{
	myPlayerActorBase->m_health = value;
} 

void pwnHack::setPlayerMana(int value)
{
	myPlayerActorBase->m_mana = value;
}


void pwnHack::teleToRegion(BYTE choice) {

	if (choice >= 1 && choice <= TOTAL_LOCATIONS) {
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, locations[choice - 1]);
	}
	/*
	switch (choice) {
	case 1:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc1); // loc1 = "Sewer" - F1 key
		break;
	case 2:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc2); // loc2 = "MoltenCave" - F2 key
		break;
	case 3:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc3); // loc3 = "LostCave" - F3 key
		break;
	case 4:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc4); // loc4 = "PirateBay" - F4 key
		break;
	case 5:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc5); // loc6 = "GoldFarm" - F5 key
		break;
	case 6:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc6); // loc6 = "CowLevel" - F6 key
		break;
	case 7:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc7); // loc6 = "BallmerPeak" - F7 key
		break;
	case 8:
		myPlayerActorBase->vfptr_player->Teleport(myPlayerActorBase, loc8); // loc6 = "UnbearableWoods" - F8 key
		break;
	default:
		return;

	}
	*/

}

void pwnHack::setPlayerMove(float walkspd, float jmpheight, float jmptime) {

	playerMoveInfo pMoveStats = getMovementStats();
	pMoveStats.adjust(walkspd, jmpheight, jmptime);
	setMovementStats(pMoveStats);
}

/*
https://github.com/zku/PwnAdventure3Hacks/tree/master/PwnAdventureSku

taken from zku's base (link above; original func. used to teleport to actors) and modified to iterate through every
Actor object to get more insight on how the spawners/test if my spawning code was correct.
*/
void pwnHack::printActorList() {

	unsigned int giantRatTotal = 0;
	unsigned int bearTotal = 0;
	unsigned int angryBearTotal = 0;

	for (auto const& actorRef : myWorld_t->m_actors) {

		IActor* actor = actorRef.m_object;

		if (actor != nullptr) {

			char firstLetter = actor->vfptr_actor->GetBlueprintName(actor)[0];
			char secondLetter = actor->vfptr_actor->GetBlueprintName(actor)[1];

			if (firstLetter == 'G' && secondLetter == 'i') giantRatTotal += 1;
			else if (firstLetter == 'A' && secondLetter == 'n') angryBearTotal += 1;
			else if (firstLetter == 'B' && secondLetter == 'e') bearTotal += 1;


		}
	}
	/*
	std::cout << "total rats = " << giantRatTotal << std::endl;
	std::cout << "total bears = " << bearTotal << std::endl;
	std::cout << "total angryBears = " << angryBearTotal << std::endl;
	*/
}

void pwnHack::getAddresses()
{
	std::vector<DWORD> offsets = { 0x97D7C, 0x4, 0x0, 0x10 };	// Offsets required to find the Player class vtable 

	DWORD addrIPlayer = tools::applyOffsets(baseAddr, offsets, true); // Address of Player class 
		

	addrList.push_back((DWORD*)(baseAddr + 0x97D7C));	// Offset for World class
	addrList.push_back((DWORD*)(baseAddr + 0x97D80));   // Offset for GameAPI class 
	addrList.push_back((DWORD*)(addrIPlayer));			// Offset for Player part of Player class (ie, Player: IPlayer)
	addrList.push_back((DWORD*)(addrIPlayer - 0x70));	// Offset for Actor portion of Player class (ie, Player : Actor )

}


void pwnHack::getWorldAndGameAPI()
{
	myGame_t = *reinterpret_cast<GameAPI**>(addrList[address::GAMEAPI]);
	myWorld_t = *reinterpret_cast<World**>(addrList[address::WORLD]);

	//myWorld = (World*)addrList[address::WORLD];
	//myGame = (GameAPI*)addrList[address::GAMEAPI];
}


void pwnHack::setMovementStats(const playerMoveInfo& desiredStats)
{
	myPlayerActorBase->m_walkingSpeed = desiredStats.walkSpeed;
	myPlayerActorBase->m_jumpSpeed = desiredStats.jumpHeight;
	myPlayerActorBase->m_jumpHoldTime = desiredStats.jumpHoldTime;
}

playerMoveInfo pwnHack::getMovementStats()
{
	playerMoveInfo pMove;

	pMove.walkSpeed = myPlayerActorBase->m_walkingSpeed;
	pMove.jumpHeight = myPlayerActorBase->m_jumpSpeed;
	pMove.jumpHoldTime = myPlayerActorBase->m_jumpHoldTime;

	return pMove;

}

