#include "ModuleEntities.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Entity.h"
#include "YellowFlower.h"
#include "RedFlower.h"
#include "Orb.h"
#include "MiddleStructure.h"
#include "Pokapoka.h"
#include "Bomb.h"
#include "CoreMechaWalker.h"
#include "Mouse.h"
#include "Snail.h"
#include "ModulePlayer.h"

#define SPAWN_MARGIN 50


ModuleEntities::ModuleEntities(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENTITIES; ++i)
		entities[i] = nullptr;
}

ModuleEntities::~ModuleEntities()
{

}

bool ModuleEntities::Start()
{
	//texture = App->textures->Load("Assets/Sprites/entities.png");
	texture = App->textures->Load("Assets/Sprites/entities.png");
	EntitieDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	bombCount = 0;

	return true;
}


Update_Status ModuleEntities::PreUpdate()
{
	// Remove all entities scheduled for deletion
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->pendingToDelete)
		{
			if (entities[i]->type == Entity_Type::BOMB) {
				bombCount--;
			}
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEntities::Update()
{
	HandleEntitiesSpawn();

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if(entities[i] != nullptr)
			entities[i]->Update();
	}

	HandleEntitiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEntities::PostUpdate()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			//check if player is behind or in front of any entity
			if (App->player->position.y < entities[i]->position.y)
			{
				if(App->player->isVisible)App->player->Draw();
				entities[i]->Draw();
			}
			else {
				entities[i]->Draw();
				if (App->player->isVisible)App->player->Draw();
			}
			
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEntities::CleanUp()
{
	LOG("Freeing all entities");

	for(uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if(entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEntities::AddEntity(Entity_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if(spawnQueue[i].type == Entity_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEntities::HandleEntitiesSpawn()
{
	// Iterate all the entities queue
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type != Entity_Type::NO_TYPE)
		{
			// Spawn a new Entitie if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning Entitie at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEntity(spawnQueue[i]);
				spawnQueue[i].type = Entity_Type::NO_TYPE; // Removing the newly spawned Entitie from the queue
			}
		}
	}
}

void ModuleEntities::HandleEntitiesDespawn()
{
	// Iterate existing entities
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			// Delete the Entitie when it has reached the end of the screen
			if (entities[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning Entitie at %d", entities[i]->position.x * SCREEN_SIZE);

				entities[i]->SetToDelete();
			}
		}
	}
}

void ModuleEntities::SpawnEntity(const EntitySpawnpoint& info)
{
	// Find an empty slot in the entities array
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			switch (info.type)
			{
				case Entity_Type::YELLOW_FLOWER:
					entities[i] = new YellowFlower(info.x, info.y);
					break;
				case Entity_Type::RED_FLOWER:
					entities[i] = new RedFlower(info.x, info.y);
					break;
				case Entity_Type::ORB:
					entities[i] = new Orb(info.x, info.y);
					break;
				case Entity_Type::MIDDLE_STRUCTURE:
					entities[i] = new MiddleStructure(info.x, info.y);
					break;
				case Entity_Type::POKAPOKA:
					entities[i] = new Pokapoka(info.x, info.y);
					break;
				case Entity_Type::MECHA_WALKER:
					entities[i] = new CoreMechaWalker(info.x, info.y);
					break;
				case Entity_Type::MOUSE:
					entities[i] = new CoreMechaWalker(info.x, info.y);
					break;
				case Entity_Type::SNAIL:
					entities[i] = new CoreMechaWalker(info.x, info.y);
					break;
				case Entity_Type::BOMB:
					entities[i] = new Bomb(info.x, info.y);
					bombCount++;
					break;
			}
			entities[i]->texture = texture;
			entities[i]->destroyedFx = EntitieDestroyedFx;
			entities[i]->type = info.type;
			break;
		}
	}
}

void ModuleEntities::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if(entities[i] != nullptr && entities[i]->GetCollider() == c1)
		{
			entities[i]->OnCollision(c2); //Notify the Entitie of a collision
			break;
		}
	}
}