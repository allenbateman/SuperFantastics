#ifndef __MODULE_ENTITIES_H__
#define __MODULE_ENTITIES_H__

#include "Module.h"

#define MAX_ENTITIES 100

enum class Entity_Type
{
	NO_TYPE,
	YELLOW_FLOWER,
	RED_FLOWER,
	ORB,
	MIDDLE_STRUCTURE,
	POKAPOKA,
	MECHA_WALKER,
	MOUSE,
	SNAIL,
	BOMB,
	BOMBUP
};

struct EntitySpawnpoint
{
	Entity_Type type = Entity_Type::NO_TYPE;
	int x, y;
};

class Entity;
struct SDL_Texture;

class ModuleEntities : public Module
{
public:
	// Constructor
	ModuleEntities(bool startEnabled);

	// Destructor
	~ModuleEntities();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The Entitie is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an Entitie into the queue to be spawned later
	bool AddEntity(Entity_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEntitiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEntitiesDespawn();

	int bombCount = 0;
private:
	// Spawns a new Entitie using the data from the queue
	void SpawnEntity(const EntitySpawnpoint& info);

private:
	// A queue with all spawn points information
	EntitySpawnpoint spawnQueue[MAX_ENTITIES];

	// All spawned enemies in the scene
	Entity* entities[MAX_ENTITIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an Entitie
	int EntitieDestroyedFx = 0;
};

#endif // __MODULE_ENTITIES_H__