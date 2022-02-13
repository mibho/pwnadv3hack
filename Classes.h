#pragma once
#include <cstdint>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <functional>

/*

LocalWorld: [<gamelogic.dll>+97D7C]	
	
	someClass: [[<gamelogic.dll>+97D7C]+4]

		Player: [[[[<gamelogic.dll>+97D7C]+4]]+10]-70

		health + decimal 80
GameAPI: [<gamelogic.dll>+97D80]s

*/

struct IActor;
struct IActorVtbl;
struct Actor;
struct IPlayer;
struct IPlayerVtbl;
struct Player;
struct ILocalPlayer;
struct GameAPI;
struct GameAPIVtbl;
struct IInventory;
struct IInventoryVtbl;
struct LocationAndRotation;
struct IItem;
struct IItemVtbl;
struct IQuest;
struct IQuestVtbl;
struct IQuestState;
struct IQuestStateVtbl;
struct GiantRatSpawner;
struct IUE4Actor;
struct IUE4ActorVtbl;
struct DamageType;
struct Vector3;
struct Rotation;
struct IActorFactory;
struct Enemy;
struct WorldVtbl;
struct World;
struct IWorld;
struct IFastTravel;
struct IFastTravelVtbl;
struct CharacterInfo;
struct IAchievement;
struct Spawner;
struct TimerSet;
struct ItemRarity;

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Rotation {
	float pitch;
	float yaw;
	float roll;

	Rotation();
	Rotation(float, float, float);
};


template <typename T> 
struct ActorRef {
	T* m_object;
	/*
	ActorRef();
	ActorRef(T*);
	ActorRef(const ActorRef<T>&);
	ActorRef<T>& operator=(T*);
	ActorRef<T>& operator=(const ActorRef<T>&);
	T* operator->() const;
	T* Get() const;
	bool operator<(const ActorRef<T>&) const;
	*/
};

struct LootTable {};

struct IActor {

	IActorVtbl* vfptr_actor;
};

struct Actor : IActor {
	//IActor vfptr;	//0x0
	unsigned int m_refs; //0x4
	unsigned int m_id; // 0x8
	IUE4Actor* m_target; // 0xC
	TimerSet* m_timers; // 0x10
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_blueprintName;
	//char dontknow[4];
	ActorRef<IActor> m_owner;
	int m_health; //0x30
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, bool> > > m_states;
	float m_forwardMovementFraction;
	float m_strafeMovementFraction;
	Vector3 m_remotePosition;
	Vector3 m_remoteVelocity;
	Rotation m_remoteRotation;
	float m_remoteLocationBlendFactor;
	Spawner* m_spawner;
};


struct AIActor : Actor {

};

struct Enemy : AIActor {
	LootTable m_loot;
};

struct IActorVtbl {
	void* (__thiscall* __vecDelDtor)(IActor* pThis, unsigned int);
	char gap4[12];
	IPlayer* (__thiscall* GetPlayerInterface)(IActor* pThis);
	void(__thiscall* AddRef)(IActor* pThis);
	void(__thiscall* Release)(IActor* pThis);
	void(__thiscall* OnSpawnActor)(IActor* pThis, IUE4Actor*);
	void(__thiscall* OnDestroyActor)(IActor* pThis);
	const char* (__thiscall* GetBlueprintName)(IActor* pThis);
	bool(__thiscall* IsCharacter)(IActor* pThis);
	bool(__thiscall* CanBeDamaged)(IActor* pThis, IActor*);
	int(__thiscall* GetHealth)(IActor* pThis);
	int(__thiscall* GetMaxHealth)(IActor* pThis);
	void(__thiscall* Damage)(IActor* pThis, IActor*, IItem*, int, DamageType);
	void(__thiscall* Tick)(IActor* pThis, float);
	bool(__thiscall* CanUse)(IActor* pThis, IPlayer*);
	void(__thiscall* OnUse)(IActor* pThis, IPlayer*);
	void(__thiscall* OnHit)(IActor* pThis, IActor*, Vector3*, Vector3*);
	void(__thiscall* OnAIMoveComplete)(IActor* pThis);
	const char* (__thiscall* GetDisplayName)(IActor* pThis);
	bool(__thiscall* IsElite)(IActor* pThis);
	bool(__thiscall* IsPvPEnabled)(IActor* pThis);
	IItem** (__thiscall* GetShopItems)(IActor* pThis, unsigned int*); void(__thiscall* FreeShopItems)(IActor* pThis, IItem**);
	int(__thiscall* GetBuyPriceForItem)(IActor* pThis, IItem*); int(__thiscall* GetSellPriceForItem)(IActor* pThis, IItem*);
	Vector3* (__thiscall* GetLookPosition)(IActor* pThis, Vector3* result);
	Rotation* (__thiscall* GetLookRotation)(IActor* pThis, Rotation* result);
	IActor* (__thiscall* GetOwner)(IActor* pThis);
};

struct IActorFactoryVtbl {
	Actor* (__thiscall* CreateActor)(IActorFactory* pThis);
};

struct IActorFactory {
	IActorFactoryVtbl* vfptr;
};


struct IQuest { IQuestVtbl* vfptr; };
struct IQuestState { IQuestStateVtbl* vfptr; };
struct IQuestStateVtbl {
	const char* (__thiscall* GetName)(IQuestState* pThis);
	const char* (__thiscall* GetDescription)(IQuestState* pThis);
	void(__thiscall* CheckForEarlyCompletion)(IQuestState* pThis,
		IPlayer*); void(__thiscall* OnItemAcquired)(IQuestState* pThis, IPlayer*, IItem*);
	void(__thiscall* OnItemPickupUsed)(IQuestState* pThis, IPlayer*, const char*);
};
struct IQuestVtbl {
	const char* (__thiscall* GetName)(IQuest* pThis); 
	const char* (__thiscall* GetDescription)(IQuest* pThis); 
	IQuestState* (__thiscall* GetStartingState)(IQuest* pThis); 
	IQuestState* (__thiscall* GetStateByName)(IQuest* pThis, const char*);
};

struct PlayerQuestState {

};

struct IPlayer {
	IPlayerVtbl* vfptr_player;

};

struct IPlayerVtbl {
	IActor* (__thiscall* GetActorInterface)(IPlayer* pThis);
	char gap4[32];
	IInventory* (__thiscall* GetInventory)(IPlayer* pThis);
	unsigned int(__thiscall* GetItemCount)(IPlayer* pThis, IItem*);
	unsigned int(__thiscall* GetLoadedAmmo)(IPlayer* pThis, IItem*);
	bool(__thiscall* AddItem)(IPlayer* pThis, IItem*, unsigned int, bool);
	bool(__thiscall* RemoveItem)(IPlayer* pThis, IItem*, unsigned int);
	bool(__thiscall* AddLoadedAmmo)(IPlayer* pThis, IItem*, IItem*, unsigned int);
	bool(__thiscall* RemoveLoadedAmmo)(IPlayer* pThis, IItem*, unsigned int);
	IItem* (__thiscall* GetItemForSlot)(IPlayer* pThis, unsigned int);
	void(__thiscall* EquipItem)(IPlayer* pThis, unsigned int, IItem*);
	unsigned int(__thiscall* GetCurrentSlot)(IPlayer* pThis);
	void(__thiscall* SetCurrentSlot)(IPlayer* pThis, unsigned int);
	IItem* (__thiscall* GetCurrentItem)(IPlayer* pThis);
	int(__thiscall* GetMana)(IPlayer* pThis);
	bool(__thiscall* UseMana)(IPlayer* pThis, int);
	void(__thiscall* SetItemCooldown)(IPlayer* pThis, IItem*, float, bool);
	bool(__thiscall* IsItemOnCooldown)(IPlayer* pThis, IItem*);
	float(__thiscall* GetItemCooldown)(IPlayer* pThis, IItem*);
	bool(__thiscall* HasPickedUp)(IPlayer* pThis, const char*);
	void(__thiscall* MarkAsPickedUp)(IPlayer* pThis, const char*);
	IQuest** (__thiscall* GetQuestList)(IPlayer* pThis, unsigned int*);
	void(__thiscall* FreeQuestList)(IPlayer* pThis, IQuest**);
	IQuest* (__thiscall* GetCurrentQuest)(IPlayer* pThis);
	void(__thiscall* SetCurrentQuest)(IPlayer* pThis, IQuest*);
	PlayerQuestState(__thiscall* GetStateForQuest)(IPlayer* pThis, IQuest*);
	void(__thiscall* StartQuest)(IPlayer* pThis, IQuest*);
	void(__thiscall* AdvanceQuestToState)(IPlayer* pThis, IQuest*, IQuestState*);
	void(__thiscall* CompleteQuest)(IPlayer* pThis, IQuest*);
	bool(__thiscall* IsQuestStarted)(IPlayer* pThis, IQuest*);
	bool(__thiscall* IsQuestCompleted)(IPlayer* pThis, IQuest*);
	void(__thiscall* EnterAIZone)(IPlayer* pThis, const char*);
	void(__thiscall* ExitAIZone)(IPlayer* pThis, const char*);
	void(__thiscall* UpdateCountdown)(IPlayer* pThis, int);
	bool(__thiscall* CanReload)(IPlayer* pThis);
	void(__thiscall* RequestReload)(IPlayer* pThis);
	float(__thiscall* GetWalkingSpeed)(IPlayer* pThis);
	float(__thiscall* GetSprintMultiplier)(IPlayer* pThis);
	float(__thiscall* GetJumpSpeed)(IPlayer* pThis);
	float(__thiscall* GetJumpHoldTime)(IPlayer* pThis);
	bool(__thiscall* CanJump)(IPlayer* pThis);
	void(__thiscall* SetJumpState)(IPlayer* pThis, bool);
	void(__thiscall* SetSprintState)(IPlayer* pThis, bool);
	void(__thiscall* SetFireRequestState)(IPlayer* pThis, bool);
	void(__thiscall* TransitionToNPCState)(IPlayer* pThis, const char*);
	void(__thiscall* BuyItem)(IPlayer* pThis, IActor*, IItem*, unsigned int);
	void(__thiscall* SellItem)(IPlayer* pThis, IActor*, IItem*, unsigned int);
	void(__thiscall* EnterRegion)(IPlayer* pThis, const char*);
	void(__thiscall* Respawn)(IPlayer* pThis);
	void(__thiscall* Teleport)(IPlayer* pThis, const char*);
	void(__thiscall* Chat)(IPlayer* pThis, const char*);
	IFastTravel* (__thiscall* GetFastTravelDestinations)(IPlayer* pThis, const char*);
	void(__thiscall* FastTravel)(IPlayer* pThis, const char*, const char*);
	void(__thiscall* MarkAsAchieved)(IPlayer* pThis, IAchievement*);
	bool(__thiscall* HasAchieved)(IPlayer* pThis, IAchievement*);
	void(__thiscall* SubmitDLCKey)(IPlayer* pThis, const char*);
	unsigned int(__thiscall* GetCircuitInputs)(IPlayer* pThis, const char*);
	void(__thiscall* SetCircuitInputs)(IPlayer* pThis, const char*, unsigned int);
	void(__thiscall* GetCircuitOutputs)(IPlayer* pThis, const char*, bool*, unsigned int);
};



struct Player2
{
	uint32_t vTable; //0x0000
	char pad_0004[44]; //0x0004
	uint32_t p_Health; //0x0030
	char pad_0034[188]; //0x0034
	char N000040F0[8]; //0x00F4
	char pad_00FC[48]; //0x00FC
	uint32_t p_Mana; //0x012C
	char pad_0130[100]; // 96
	float p_WalkSpeed; //0x0190
	float p_JmpHeight; //0x0194
	float p_JmpHoldTime; //0x0198
	char pad_019C[2740]; //0x019C
};



struct IUE4Actor { IUE4ActorVtbl* vfptr; };

struct IUE4ActorVtbl {
	void* (__thiscall* GetUE4Actor)(IUE4Actor* pThis);	
	char gap4[8];
	Rotation* (__thiscall* GetRotation)(IUE4Actor* pThis, Rotation* result);
	Vector3* (__thiscall* GetProjectilePosition)(IUE4Actor* pThis, Vector3* result);
	Vector3* (__thiscall* GetCharacterVelocity)(IUE4Actor* pThis, Vector3* result);
	void(__thiscall* SetPosition)(IUE4Actor* pThis, Vector3*);
	void(__thiscall* SetRotation)(IUE4Actor* pThis, Rotation*);
	void(__thiscall* SetCharacterVelocity)(IUE4Actor* pThis, Vector3*);
	void(__thiscall* SetForwardAndStrafeMovement)(IUE4Actor* pThis, float, float);
	void(__thiscall* InterpolatePositionAndRotation)(IUE4Actor* pThis, Vector3*, Rotation*, float, float);
	bool(__thiscall* MoveToLocation)(IUE4Actor* pThis, Vector3*);
	bool(__thiscall* MoveToRandomLocationInRadius)(IUE4Actor* pThis, float);
	bool(__thiscall* MoveToActor)(IUE4Actor* pThis, IActor*);
	void(__thiscall* OnUpdateState)(IUE4Actor* pThis, const char*, bool);
	void(__thiscall* OnTriggerEvent)(IUE4Actor* pThis, const char*, IActor*);
	void(__thiscall* OnUpdatePvPEnabled)(IUE4Actor* pThis, bool);
	IActor* (__thiscall* LineTraceTo)(IUE4Actor* pThis, Vector3*);
	void(__thiscall* FireBullets)(IUE4Actor* pThis, IItem*, int, DamageType, Vector3*, unsigned int, float);
	void(__thiscall* LocalRespawn)(IUE4Actor* pThis, Vector3*, Rotation*);
	bool(__thiscall* IsOnGround)(IUE4Actor* pThis);
	void(__thiscall* OnReload)(IUE4Actor* pThis, unsigned int);
};


struct TimerSet {
	struct TimerEvent {
		float timeLeft;
		float initialTime;
		bool recurring;
		bool withContext;
		std::function<void()> callback;
		std::function<void(Actor*)> contextCallback;
	};
	std::map<std::string, TimerSet::TimerEvent> m_timers;


	void Add(const std::string&, float, const std::function<void()>&);
	void AddWithContext(const std::string&, float, const std::function<void(Actor*)>&);
	void AddRecurring(const std::string&, float, const std::function<void()>&);
	void AddRecurringWithContext(const std::string&, float, const std::function<void(Actor*)>&);
	void Cancel(const std::string&);
	void Clear();
	void Tick(Actor*, float);
};




struct AIZoneListener;

struct AIZone {
	const char* m_name;
	size_t m_playerCount;
	//std::set<AIZoneListener*, std::less<AIZoneListener*>, std::allocator<AIZoneListener*> > m_listeners;

	AIZone(const std::string&);
	const std::string& GetName() const;
	bool IsActive() const;
	void OnPlayerEntered();
	void OnPlayerLeft();
	void AddListener(AIZoneListener*);
	void RemoveListener(AIZoneListener*);
};

struct AIZoneListenerVtbl{ 
	void* (__thiscall* __vecDelDtor)(AIZoneListener* pThis, unsigned int); 
	void(__thiscall* OnAIZoneActivated)(AIZoneListener* pThis); 
	void(__thiscall* OnAIZoneDeactivated)(AIZoneListener* pThis); 
};


struct AIZoneListener {
	AIZoneListenerVtbl* vfptr;
	AIZone* m_zone;
};

/*
class AIZoneListener {

public:
	AIZone* m_zone;

public:
	AIZoneListener();
	virtual ~AIZoneListener();
	void SetAIZone(const std::string&);
	virtual void OnAIZoneActivated();
	virtual void OnAIZoneDeactivated();
	bool IsAIZoneActive();
};
*/




class Spawner : public AIZoneListener {
public:
	std::vector<Actor> m_actors;
	Vector3 m_position;
	Rotation m_rotation;
	size_t m_maxActors;
	float m_maxSpawnTimer;
	float m_currentSpawnTimer;


public:
	Spawner(const std::string&, const Vector3&, const Rotation&, size_t,
		float);
	virtual void OnAIZoneActivated();
	virtual void OnAIZoneDeactivated();
	virtual void Tick(float);
	virtual Actor* Spawn();
	void RemoveActor(Actor*);
	virtual size_t GetMaxActors();
	virtual float GetSpawnTimer();
};




/*
class BearSpawner : public Spawner
{
public:
	int32_t vftable; //0x0000
	char pad_0004[12]; //0x0004
	virtual  Actor*  Spawn(void); //0x0010

	virtual unsigned int GetMaxActors(void); //0x0014
//void* virtual float __thiscall Spawner::GetSpawnTimer(void); //0x0018
// 
//void* virtual class Actor* __thiscall BearSpawner::Spawn(void); //0x0010
//void* virtual unsigned int __thiscall BearSpawner::GetMaxActors(void); //0x0014
//void* virtual float __thiscall Spawner::GetSpawnTimer(void); //0x0018
			char pad_001C[36]; //0x001C
}; //Size: 0x0040
*/
/*

struct GiantRat : Enemy{
	//GiantRat();

};


class TownRatSpawner{};
struct BearChest {};




struct GiantRatVTable {
	void(__thiscall* OnAIZoneActivated)(Spawner* pThis);
	void(__thiscall* OnAIZoneDeactivated)(Spawner* pThis);
	void(__thiscall* Tick)(Spawner* pThis, float deltaTime);
	Actor* (__thiscall* Spawn)(GiantRatSpawner* pThis);
};

struct GiantRatSpawner
{
public:
	GiantRatVTable* vtbptr;
	
	char pad_0014[44]; //0x0014
}; //Size: 0x0040


struct Bear : Enemy {
	int m_attacksLeftInPosition;
	ActorRef<BearChest> m_chest;
};

struct BearSpawner : Spawner {
	ActorRef<BearChest> m_chest;
};



struct CliffRatSpawner : Spawner {};
*/

struct GameAPI {
	GameAPIVtbl* vfptr;
};


struct GameAPIVtbl {
	bool(__thiscall* SpawnActor)(GameAPI* pThis, IActor*, Vector3*, Rotation*, bool);
	//char gap4[12]; 
	bool(__thiscall* SpawnActorAtNamedLocation)(GameAPI* pThis, IActor*, const char*);
	bool(__thiscall* SpawnRemotePlayer)(GameAPI* pThis, IPlayer*, Vector3*, Rotation*);
	void(__thiscall* DamageInRadius)(GameAPI* pThis, IActor*, IItem*, Vector3*, float, int, DamageType);
	unsigned int(__thiscall* GetNamedLocationPoints)(GameAPI* pThis, const char*, LocationAndRotation**);
	void(__thiscall* FreeNamedLocationPoints)(GameAPI* pThis, LocationAndRotation*);
	Vector3* (__thiscall* GetDirectionFromRotation)(GameAPI* pThis, Vector3* result, Rotation*);
	Rotation* (__thiscall* GetRotationFromDirection)(GameAPI* pThis, Rotation* result, Vector3*);
	void(__thiscall* OnWeaponFired)(GameAPI* pThis, IItem*, Vector3*, Vector3*);
	void(__thiscall* OnBulletHitActor)(GameAPI* pThis, IItem*, IActor*, Vector3*, Vector3*);
	void(__thiscall* OnBulletHitWorld)(GameAPI* pThis, IItem*, Vector3*, Vector3*);
	void(__thiscall* OnLog)(GameAPI* pThis, const char*); 
	void(__thiscall* OnMasterServerConnected)(GameAPI* pThis, bool, const char*, const char*);
	void(__thiscall* OnLoginComplete)(GameAPI* pThis, bool, const char*, bool, CharacterInfo*, unsigned int);
	void(__thiscall* OnRegisterComplete)(GameAPI* pThis, bool, const char*, const char*, bool);
	void(__thiscall* OnCreateCharacterComplete)(GameAPI* pThis, bool, const char*, int);
	void(__thiscall* OnDeleteCharacterComplete)(GameAPI* pThis, bool, int);
	void(__thiscall* OnJoinGameServerComplete)(GameAPI* pThis, bool, const char*, bool, const char*, unsigned __int16, const char*);
	void(__thiscall* OnGameServerConnected)(GameAPI* pThis, bool, const char*, Vector3*, Rotation*);
	void(__thiscall* OnTransitionToNewServer)(GameAPI* pThis);
	void(__thiscall* OnSubmitAnswerComplete)(GameAPI* pThis, bool, const char*);
	void(__thiscall* OnTeammatesListed)(GameAPI* pThis, const char**, const char**, unsigned int);
	unsigned int(__thiscall* GetDefaultCircuitInputs)(GameAPI* pThis, const char*);
	unsigned int(__thiscall* GetCircuitOutputCount)(GameAPI* pThis, const char*);
	void(__thiscall* GetCircuitOutputs)(GameAPI* pThis, const char*, unsigned int, bool*, unsigned int, bool*);
};



struct IItem { IItemVtbl* vfptr; };
struct IItemVtbl {
	void* (__thiscall* __vecDelDtor)(IItem* pThis, unsigned int);
	const char* (__thiscall* GetDescription)(IItem* pThis); //__declspec(align(16));
	const char* (__thiscall* GetFlavorText)(IItem* pThis);
	bool(__thiscall* CanEquip)(IItem* pThis); unsigned int(__thiscall* GetMaximumCount)(IItem* pThis);
	bool(__thiscall* CanActivate)(IItem* pThis, IPlayer*);
	bool(__thiscall* CanActivateInInventory)(IItem* pThis);
	void(__thiscall* Activate)(IItem* pThis, IPlayer*);
	bool(__thiscall* ShowInInventory)(IItem* pThis);
	bool(__thiscall* ShowEventOnPickup)(IItem* pThis);
	bool(__thiscall* ShowEventOnDuplicatePickup)(IItem* pThis);
	bool(__thiscall* ShowNotificationOnPickup)(IItem* pThis);
	float(__thiscall* GetCooldownTime)(IItem* pThis);
	ItemRarity(__thiscall* GetItemRarity)(IItem* pThis);
	IItem* (__thiscall* GetAmmoType)(IItem* pThis);
	unsigned int(__thiscall* GetClipSize)(IItem* pThis);
	int(__thiscall* GetDamage)(IItem* pThis);
	int(__thiscall* GetDamagePerSecond)(IItem* pThis);
	DamageType(__thiscall* GetDamageType)(IItem* pThis);
	int(__thiscall* GetManaCost)(IItem* pThis);
	const char* (__thiscall* GetCustomCostDescription)(IItem* pThis);
	bool(__thiscall* IsAutoFire)(IItem* pThis);
	unsigned int(__thiscall* GetNumberOfProjectiles)(IItem* pThis);
	float(__thiscall* GetReloadTime)(IItem* pThis, int);
	bool(__thiscall* HasPartialReload)(IItem* pThis);
	float(__thiscall* GetRange)(IItem* pThis);
	int(__thiscall* GetTradeValue)(IItem* pThis);
	bool(__thiscall* IsDynamic)(IItem* pThis);
	bool(__thiscall* IsUpdating)(IItem* pThis);
};


struct IInventory { IInventoryVtbl* vfptr; };
struct IInventoryVtbl {
	void* (__thiscall* __vecDelDtor)(IInventory* pThis, unsigned int);
	unsigned int(__thiscall* GetCount)(IInventory* pThis);
	IItem* (__thiscall* GetItem)(IInventory* pThis, unsigned int);
	unsigned int(__thiscall* GetItemCount)(IInventory* pThis, unsigned int);
	unsigned int(__thiscall* GetItemLoadedAmmo)(IInventory* pThis, unsigned int);
	void(__thiscall* Destroy)(IInventory* pThis);
};

struct IFastTravel { IFastTravelVtbl* vfptr; };
struct IFastTravelVtbl {
	void* (__thiscall* __vecDelDtor)(IFastTravel* pThis, unsigned int); unsigned int(__thiscall* GetCount)(IFastTravel* pThis); const char* (__thiscall* GetRegionName)(IFastTravel* pThis, unsigned int); const char* (__thiscall* GetDisplayName)(IFastTravel* pThis, unsigned int); void(__thiscall* Destroy)(IFastTravel* pThis);
};




struct World {
	WorldVtbl* vfptr;
	std::set<ActorRef<IPlayer>, std::less<ActorRef<IPlayer> >, std::allocator<ActorRef<IPlayer> > > m_players;
	std::set<ActorRef<IActor>, std::less<ActorRef<IActor> >, std::allocator<ActorRef<IActor> > > m_actors;
	std::map<unsigned int, ActorRef<IActor>, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, ActorRef<IActor> > > > m_actorsById;
	ILocalPlayer* m_localPlayer;
	unsigned int m_nextId;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, AIZone*, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, AIZone*> > > m_aiZones;
};

struct WorldVtbl { 
	void* (__thiscall* __vecDelDtor)(World* pThis, unsigned int); 
	char gap4[32]; 
	void(__thiscall* Activate)(World* pThis, Player*, IItem*); 
	void(__thiscall* Reload)(World* pThis, Player*); 
	void(__thiscall* Jump)(World* pThis, bool); 
	void(__thiscall* Sprint)(World* pThis, bool); 
	void(__thiscall* FireRequest)(World* pThis, bool); 
	void(__thiscall* TransitionToNPCState)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); void(__thiscall* BuyItem)(World* pThis, Player*, Actor*, IItem*, unsigned int); 
	void(__thiscall* SellItem)(World* pThis, Player*, Actor*, IItem*, unsigned int); 
	void(__thiscall* Respawn)(World* pThis, Player*); 
	void(__thiscall* Teleport)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* Chat)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* FastTravel)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* SetPvPDesired)(World* pThis, Player*, bool); 
	void(__thiscall* SubmitDLCKey)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* SetCircuitInputs)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, unsigned int); 
	void(__thiscall* SendAddItemEvent)(World* pThis, Player*, IItem*, unsigned int); 
	void(__thiscall* SendRemoveItemEvent)(World* pThis, Player*, IItem*, unsigned int); 
	void(__thiscall* SendLoadedAmmoEvent)(World* pThis, Player*, IItem*, unsigned int); 
	void(__thiscall* SendPickedUpEvent)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* EquipItem)(World* pThis, Player*, char, IItem*); 
	void(__thiscall* SetCurrentSlot)(World* pThis, Player*, char); 
	void(__thiscall* SendEquipItemEvent)(World* pThis, Player*, char, IItem*); 
	void(__thiscall* SendCurrentSlotEvent)(World* pThis, Player*, char); 
	void(__thiscall* SetCurrentQuest)(World* pThis, Player*, IQuest*); 
	void(__thiscall* SendSetCurrentQuestEvent)(World* pThis, Player*, IQuest*); 
	void(__thiscall* SendStartQuestEvent)(World* pThis, Player*, IQuest*); 
	void(__thiscall* SendAdvanceQuestToStateEvent)(World* pThis, Player*, IQuest*, IQuestState*); 
	void(__thiscall* SendCompleteQuestEvent)(World* pThis, Player*, IQuest*); 
	void(__thiscall* SendHealthUpdateEvent)(World* pThis, Actor*, int); 
	void(__thiscall* SendManaUpdateEvent)(World* pThis, Player*, int); 
	void(__thiscall* SendCountdownUpdateEvent)(World* pThis, Player*, int); 
	void(__thiscall* SendPvPCountdownUpdateEvent)(World* pThis, Player*, bool, int); 
	void(__thiscall* SendPvPEnableEvent)(World* pThis, Player*, bool); 
	void(__thiscall* SendStateEvent)(World* pThis, Actor*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, bool); 
	void(__thiscall* SendTriggerEvent)(World* pThis, Actor*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, Actor*, bool); 
	void(__thiscall* SendFireBulletsEvent)(World* pThis, Actor*, IItem*, Vector3*, unsigned int, float); 
	void(__thiscall* SendDisplayEvent)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* SendNPCConversationStateEvent)(World* pThis, Player*, Actor*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); 
	void(__thiscall* SendNPCConversationEndEvent)(World* pThis, Player*); 
	void(__thiscall* SendNPCShopEvent)(World* pThis, Player*, Actor*); 
	void(__thiscall* SendRespawnEvent)(World* pThis, Player*, Vector3*, Rotation*); 
	void(__thiscall* SendTeleportEvent)(World* pThis, Actor*, Vector3*, Rotation*); 
	void(__thiscall* SendRelativeTeleportEvent)(World* pThis, Actor*, Vector3*); 
	void(__thiscall* SendReloadEvent)(World* pThis, Player*, IItem*, IItem*, unsigned int); 
	void(__thiscall* SendPlayerJoinedEvent)(World* pThis, Player*); void(__thiscall* SendPlayerLeftEvent)(World* pThis, Player*); 
	void(__thiscall* SendPlayerItemEvent)(World* pThis, Player*); void(__thiscall* SendActorSpawnEvent)(World* pThis, Actor*); void(__thiscall* SendActorDestroyEvent)(World* pThis, Actor*); void(__thiscall* SendExistingPlayerEvent)(World* pThis, Player*, Player*); void(__thiscall* SendExistingActorEvent)(World* pThis, Player*, Actor*); void(__thiscall* SendChatEvent)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); void(__thiscall* SendKillEvent)(World* pThis, Player*, Actor*, IItem*); void(__thiscall* SendCircuitOutputEvent)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*, unsigned int, std::vector<bool, std::allocator<bool> >*); void(__thiscall* SendActorPositionEvents)(World* pThis, Player*); void(__thiscall* SendRegionChangeEvent)(World* pThis, Player*, std::basic_string<char, std::char_traits<char>, std::allocator<char> >*); void(__thiscall* SendLastHitByItemEvent)(World* pThis, Player*, IItem*); 
};

struct ItemAndCount {};
struct NPC{};

struct ILocalPlayer{};
struct WriteStream {};
struct QuestStateInfo{};

struct ItemCountInfo{};
struct LocationAndRotation {};
struct IAchievement {};

struct DamageType {};

struct ItemRarity {};

struct CharacterInfo {};



struct Player : public Actor, public IPlayer {
public:
	//IPlayer pvtbl;
	//IPlayerVtbl* vfptr; //0x70
	uint32_t m_characterId; // 0x4
	char test[24];//const char* m_playerName; //0x8
	char test2[24];//const char* m_teamName; // 0xC
	uint8_t m_avatarIndex; // 0x10
	bool wat1;
	bool wat2;
	bool wat3;
	uint32_t m_colors[4]; // 0x14 
	char test3[8];//std::map<IItem*, ItemAndCount, std::less<IItem*>, std::allocator<std::pair<IItem* const, ItemAndCount> > > m_inventory; //0x18
	char test4[8]; // std::set<std::basic_string<char>, std::less<std::basic_string<char> >, std::allocator<std::basic_string<char> > > m_pickups; // 0x1C
	char test5[8];//std::map<IItem*, float, std::less<IItem*>, std::allocator<std::pair<IItem* const, float> > > m_cooldowns; // 0x20
	char test6[8];//std::map<std::basic_string<char>, unsigned int, std::less<std::basic_string<char> >, std::allocator<std::pair<const std::basic_string<char>, unsigned int> > > m_circuitInputs; // 0x24
	char test7[8]; //std::map<std::basic_string<char>, std::vector<bool, std::allocator<bool> >, std::less<std::basic_string<char> >, std::allocator<std::pair<const std::basic_string<char>, std::vector<bool, std::allocator<bool> > > > > m_circuitOutputs; // 0x28
	bool m_admin;
	bool m_pvpEnabled;
	bool m_pvpDesired;
	bool wat4;
	float m_pvpChangeTimer;
	int32_t m_pvpChangeReportedTimer;
	bool m_changingServerRegion;
	bool wat5;
	bool wat6;
	bool wat7;
	char test8[24];//const char* m_currentRegion;
	char test9[24]; // const char* m_changeRegion;
	char test10[8]; //std::set<std::string> m_aiZones;
	int32_t m_mana;
	float m_manaRegenTimer;
	float m_healthRegenCooldown;
	float m_healthRegenTimer;
	int32_t m_countdown;
	Vector3 m_remoteLookPosition;
	Rotation m_remoteLookRotation;
	IItem* m_equipped[10];
	size_t m_currentSlot;
	std::map<IQuest*, PlayerQuestState, std::less<IQuest*>, std::allocator<std::pair<IQuest* const, PlayerQuestState> > > m_questStates;
	IQuest* m_currentQuest;
	float m_walkingSpeed;
	float m_jumpSpeed;
	float m_jumpHoldTime;
	ActorRef<NPC> m_currentNPC;
	const char* m_currentNPCState;
	ILocalPlayer* m_localPlayer;
	WriteStream* m_eventsToSend;
	bool m_itemsUpdated;
	bool wat8;
	bool wat9;
	bool wat10;
	float m_itemSyncTimer;
	uint32_t m_chatMessageCounter;
	float m_chatFloodDecayTimer;
	IItem* m_lastHitByItem;
	float m_lastHitItemTimeLeft;
	float m_circuitStateCooldownTimer;
/*
protected:
	virtual void OnKilled(IActor*, IItem*);
public:
	Player(bool);
	virtual ~Player();
	virtual bool IsPlayer();
	virtual IPlayer* GetPlayerInterface();
	virtual IActor* GetActorInterface();
	virtual bool CanBeDamaged(IActor*);
	virtual bool IsCharacter();
	virtual bool ShouldSendPositionUpdates();
	virtual bool ShouldReceivePositionUpdates();
	virtual void Tick(float);
	virtual void Damage(IActor*, IItem*, int32_t, DamageType);
	virtual void OnDestroyActor();
	void OnKillEvent(IPlayer*, IActor*, IItem*);
	virtual Vector3 GetLookPosition();
	virtual Rotation GetLookRotation();
	void SetRemoteLookPosition(const Vector3&);
	void SetRemoteLookRotation(const Rotation&);
	virtual bool CanJump();
	virtual bool IsLocalPlayer() const;
	virtual ILocalPlayer* GetLocalPlayer() const;
	void InitLocalPlayer(ILocalPlayer*);
	bool IsAdmin() const;
	void SetPlayerName(const std::string&);
	void SetTeamName(const std::string&);
	void SetAvatarIndex(uint8_t);
	void SetColors(const uint32_t*);
	void SetCharacterId(uint32_t);
	virtual bool IsPvPEnabled();
	virtual bool IsPvPDesired();
	virtual void SetPvPDesired(bool);
	void PerformSetPvPEnabled(bool);
	void PerformSetPvPDesired(bool);
	void PerformUpdatePvPCountdown(bool, int32_t);
	virtual void UpdateState(const std::string&, bool);
	virtual const char* GetPlayerName();
	virtual const char* GetTeamName();
	virtual uint8_t GetAvatarIndex();
	virtual const uint32_t* GetColors();
	uint32_t GetCharacterId() const;
	const std::map<IItem*, ItemAndCount, std::less<IItem*>, std::allocator<std::pair<IItem* const, ItemAndCount> > >& GetItemList() const;
	virtual IInventory* GetInventory();
	virtual uint32_t GetItemCount(IItem*);
	virtual uint32_t GetLoadedAmmo(IItem*);
	virtual bool AddItem(IItem*, uint32_t, bool);
	virtual bool RemoveItem(IItem*, uint32_t);
	bool PerformAddItem(IItem*, uint32_t, bool);
	bool PerformRemoveItem(IItem*, uint32_t);
	virtual bool AddLoadedAmmo(IItem*, IItem*, uint32_t);
	virtual bool RemoveLoadedAmmo(IItem*, uint32_t);
	void PerformSetLoadedAmmo(IItem*, uint32_t);
	virtual IItem* GetItemForSlot(size_t);
	virtual void EquipItem(size_t, IItem*);
	void PerformEquipItem(size_t, IItem*);
	virtual size_t GetCurrentSlot();
	virtual IItem* GetCurrentItem();
	virtual void SetCurrentSlot(size_t);
	void PerformSetCurrentSlot(size_t);
	void SetRemoteItem(IItem*);
	virtual int32_t GetMana();
	virtual bool UseMana(int32_t);
	void PerformSetMana(int32_t);
	virtual void SetItemCooldown(IItem*, float, bool);
	virtual bool IsItemOnCooldown(IItem*);
	virtual float GetItemCooldown(IItem*);
	virtual bool HasPickedUp(const char*);
	virtual void MarkAsPickedUp(const char*);
	void PerformMarkAsPickedUp(const std::string&);
	virtual IQuest** GetQuestList(size_t*);
	virtual void FreeQuestList(IQuest**);
	virtual IQuest* GetCurrentQuest();
	virtual PlayerQuestState GetStateForQuest(IQuest*);
	virtual bool IsQuestStarted(IQuest*);
	virtual bool IsQuestCompleted(IQuest*);
	virtual void SetCurrentQuest(IQuest*);
	virtual void StartQuest(IQuest*);
	virtual void AdvanceQuestToState(IQuest*, IQuestState*);
	virtual void CompleteQuest(IQuest*);
	void PerformSetCurrentQuest(IQuest*);
	void PerformStartQuest(IQuest*);
	void PerformAdvanceQuestToState(IQuest*, IQuestState*);
	void PerformCompleteQuest(IQuest*);
	void SetInitialQuestStates(const std::map<std::string, QuestStateInfo>&,
		const std::string&);
	void SetInitialItemState(const std::map<std::string, ItemCountInfo>&,
		const std::vector<std::string>&, uint8_t);
	void SetInitialPickupState(const std::set<std::string>&);
	virtual void EnterAIZone(const char*);
	virtual void ExitAIZone(const char*);
	virtual void UpdateCountdown(int32_t);
	void PerformUpdateCountdown(int32_t);
	virtual void TriggerEvent(const std::string&, IActor*, bool);
	virtual bool CanReload();
	virtual void RequestReload();
	void PerformRequestReload();
	virtual float GetWalkingSpeed();
	virtual float GetSprintMultiplier();
	virtual float GetJumpSpeed();
	virtual float GetJumpHoldTime();
	virtual void SetJumpState(bool);
	virtual void SetSprintState(bool);
	virtual void SetFireRequestState(bool);
	void SetCurrentNPCState(NPC*, const std::string&);
	void EndNPCConversation();
	void EnterNPCShop(NPC*);
	NPC* GetCurrentNPC() const;
	const std::string& GetCurrentNPCState() const;
	virtual void TransitionToNPCState(const char*);
	void PerformTransitionToNPCState(const std::string&);
	virtual void BuyItem(IActor*, IItem*, uint32_t);
	void PerformBuyItem(IActor*, IItem*, uint32_t);
	virtual void SellItem(IActor*, IItem*, uint32_t);
	void PerformSellItem(IActor*, IItem*, uint32_t);
	virtual void EnterRegion(const char*);
	bool IsChangingRegion() const;
	const std::string& GetChangeRegionDestination() const;
	void PerformEnterRegion(const std::string&);
	LocationAndRotation GetSpawnLocation();
	virtual void Respawn();
	void PerformRespawn();
	void PerformRespawnAtLocation(const Vector3&, const Rotation&);
	virtual void Teleport(const char*);
	void PerformTeleport(const std::string&);
	virtual void SendEvent(const WriteStream&);
	virtual void WriteAllEvents(WriteStream&);
	void SyncItems();
	virtual void Chat(const char*);
	void PerformChat(const std::string&);
	void ReceiveChat(Player*, const std::string&);
	virtual IFastTravel* GetFastTravelDestinations(const char*);
	virtual void FastTravel(const char*, const char*);
	void PerformFastTravel(const std::string&, const std::string&);
	void OnTravelComplete(const std::string&);
	IItem* GetLastHitByItem() const;
	void PerformSetLastHitByItem(IItem*);
	virtual void MarkAsAchieved(IAchievement*);
	virtual bool HasAchieved(IAchievement*);
	virtual void SubmitDLCKey(const char*);
	void PerformSubmitDLCKey(const std::string&);
	virtual uint32_t GetCircuitInputs(const char*);
	virtual void SetCircuitInputs(const char*, uint32_t);
	void PerformSetCircuitInputs(const std::string&, uint32_t);
	virtual void GetCircuitOutputs(const char*, bool*, size_t);
	void PerformSetCircuitOutputs(const std::string&, std::vector<bool>);
	void InitCircuitStates();
	*/
};

struct ClientWorld : World {
	ActorRef<IPlayer> m_activePlayer;
	float m_timeUntilNextNetTick;
};
