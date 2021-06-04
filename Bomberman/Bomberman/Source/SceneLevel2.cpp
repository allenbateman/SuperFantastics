#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleEntities.h"
#include "ModulePlayer.h"
#include "MiddleStructure.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"

#include <ctime>

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	App->player->Enable();
	App->entities->Enable();
	App->collisions->Enable();
	App->UI->Enable();

	App->UI->timeLeft = timeLevel;
	App->UI->timeLevel = timeLevel;

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background2.png");
	App->audio->PlayMusic("Assets/Music/SceneLevel1.ogg", 1.0f);

	//BoundColliders
	//Left collider
	App->collisions->AddCollider({ 0,23,24,223 }, Collider::Type::BOUNDS);

	//Right Collider

	//Collider 

	//top river
	App->collisions->AddCollider({ 167,32,241,32 }, Collider::Type::BOUNDS);
	//botRiver
	App->collisions->AddCollider({ 167,176,241,32 }, Collider::Type::BOUNDS);


	// Fixed positions

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			grid[i][j] = EMPTY;
		}
	}
	
	for (int i = 1; i < 11; i += 2)
	{
		for (int j = 1; j < 28; j += 2)
		{
			grid[i][j] = ROCK;
		}
	}

	//Fixed rock positions
	
	grid[1][6] = ROCK;
	grid[2][7] = ROCK;
	grid[5][4] = ROCK;
	grid[7][1] = ROCK;
	grid[8][1] = ROCK;
	grid[9][2] = ROCK;
	grid[6][11] = ROCK;
	grid[7][10] = ROCK;
	grid[3][20] = ROCK;
	grid[7][20] = ROCK;
	grid[6][25] = ROCK;
	grid[7][26] = ROCK;
	grid[0][9] = ROCK;
	grid[1][10] = ROCK;
	grid[1][12] = ROCK;
	grid[1][14] = ROCK;
	grid[2][15] = ROCK;
	grid[4][15] = ROCK;
	grid[6][15] = ROCK;
	grid[8][15] = ROCK;
	grid[4][16] = ROCK;
	grid[6][16] = ROCK;
	grid[2][17] = ROCK;
	grid[4][17] = ROCK;
	grid[6][17] = ROCK;
	grid[8][17] = ROCK;
	grid[9][18] = ROCK;
	grid[9][20] = ROCK;
	grid[9][22] = ROCK;
	grid[10][22] = ROCK;
	grid[2][20] = ROCK;
	grid[2][22] = ROCK;
	grid[1][22] = ROCK;
	grid[10][9] = ROCK;
	grid[9][10] = ROCK;
	grid[9][12] = ROCK;
	grid[9][14] = ROCK;

	//Entities + Win spot
	grid[0][2] = PLAYER;
	grid[2][6] = MOUSE;
	grid[4][11] = SNAIL;
	grid[9][26] = SNAIL;
	grid[6][26] = RED_FLOWER;
	grid[6][2] = MECHA_WALKER;
	grid[6][14] = MECHA_WALKER;
	grid[7][22] = MECHA_WALKER;
	grid[8][2] = ORB;
	grid[6][20] = ORB;
	grid[1][25] = STRUCTURE;
	grid[1][26] = STRUCTURE;
	grid[1][27] = STRUCTURE;
	grid[2][25] = STRUCTURE;
	grid[2][26] = STRUCTURE;
	grid[2][27] = STRUCTURE;
	grid[3][25] = STRUCTURE;
	grid[3][27] = STRUCTURE;
	grid[2][26] = WIN_SPOT;

	int flowerAmount = rand() % 55 + 70;
	int x = 0;
	int y = 0;

	for (int i = 0; i < flowerAmount;)
	{
		x = rand() % 28;
		y = rand() % 11;

		if (grid[y][x] == EMPTY)
		{
			grid[y][x] = YELLOW_FLOWER;
			i++;
		}
	}

	// Fixed empty/rock positions
	grid[0][0] = EMPTY;
	grid[0][1] = EMPTY;
	grid[1][0] = EMPTY;
	grid[2][0] = EMPTY;
	grid[3][15] = EMPTY;
	grid[3][17] = EMPTY;
	grid[5][15] = EMPTY;
	grid[5][17] = EMPTY;
	grid[7][15] = EMPTY;
	grid[7][17] = EMPTY;
	grid[10][10] = EMPTY;
	grid[10][11] = EMPTY;
	grid[10][12] = EMPTY;
	grid[10][13] = EMPTY;
	grid[10][14] = EMPTY;
	grid[10][15] = EMPTY;
	grid[0][10] = EMPTY;
	grid[0][11] = EMPTY;
	grid[0][12] = EMPTY;
	grid[0][13] = EMPTY;
	grid[0][14] = EMPTY;
	grid[0][15] = EMPTY;

	middleStructureIsSet = false;

	// Generate scene entity or rock collisions
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 28; j++)
		{
			if (grid[i][j] == PLAYER)
			{
				iPoint pos;
				pos.x = 24 + j * 16;
				pos.y = 32 + i * 16;
				App->player->position = pos;
			}
			else if (grid[i][j] == ROCK)
			{
				App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::WALL);
			}
			else if (grid[i][j] == YELLOW_FLOWER)
			{
				App->entities->AddEntity(Entity_Type::YELLOW_FLOWER, j, i);
			}
			else if (grid[i][j] == RED_FLOWER)
			{
				App->entities->AddEntity(Entity_Type::RED_FLOWER, j, i);
			}
			else if (grid[i][j] == ORB)
			{
				App->entities->AddEntity(Entity_Type::ORB, j, i);
			}
			else if (grid[i][j] == STRUCTURE)
			{
				if (!middleStructureIsSet)
				{
					App->entities->AddEntity(Entity_Type::MIDDLE_STRUCTURE, j, i);
					middleStructureIsSet = true;
				}
			}
			else if (grid[i][j] == SNAIL)
			{
				App->entities->AddEntity(Entity_Type::SNAIL, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == MOUSE)
			{
				App->entities->AddEntity(Entity_Type::MOUSE, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == MECHA_WALKER)
			{
				App->entities->AddEntity(Entity_Type::MECHA_WALKER, 24 - 8 + (j * 16), 32 - 16 + (i * 16));
			}
		}
	}
	for (int y = 0; y < gridHeight; y++)
	{
	for (int x = 0; x < gridWidth; x++)
	{
		App->levelManager->grid[y][x] = grid[y][x];
	}
	}
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->player->SetSceneGrid(&grid[0][0], 28, 11);

	return ret;
}

Update_Status SceneLevel2::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel2::PostUpdate()
{
	//Draw background
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	App->player->Disable();
	App->entities->Disable();
	App->collisions->Disable();
	App->UI->Disable();

	return true;
}

SceneLevel2::GridType SceneLevel2::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

SceneLevel2::GridType SceneLevel2::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}