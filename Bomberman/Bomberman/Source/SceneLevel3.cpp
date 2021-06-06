#include "SceneLevel3.h"

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

SceneLevel3::SceneLevel3(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel3::~SceneLevel3()
{

}

// Load assets
bool SceneLevel3::Start()
{



	App->render->levelBounds = levelBounds;

	App->levelManager->orbCount = orbs;
	App->levelManager->orbsLeft = orbs;

	App->levelManager->activeLevelWidth = LVL_THREE_WIDTH;

	App->player->Enable();
	App->entities->Enable();
	App->collisions->Enable();
	App->UI->Enable();

	App->UI->timeLeft = timeLevel;
	App->UI->timeLevel = timeLevel;



	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background3.png");
	App->audio->PlayMusic("Assets/Music/SceneLevel1.ogg", 1.0f);
	//add bounding colliders
	//Left collider
	App->collisions->AddCollider({ 0,23,24,223 }, Collider::Type::BOUNDS);
	//Right Collider
	App->collisions->AddCollider({ 232,23,24,223 }, Collider::Type::BOUNDS);
	//Top Collider
	App->collisions->AddCollider({ 24,24,208,8 }, Collider::Type::BOUNDS);
	//Bot collider 
	App->collisions->AddCollider({ 24,208,208,8 }, Collider::Type::BOUNDS);
	//Top left
	App->collisions->AddCollider({ 0,32,86,32 }, Collider::Type::BOUNDS);
	//Top right
	App->collisions->AddCollider({ 168,32,86,32 }, Collider::Type::BOUNDS);
	//Bottom left
	App->collisions->AddCollider({ 0,176,86,32 }, Collider::Type::BOUNDS);
	//Bottom right
	App->collisions->AddCollider({ 168,176,86,32 }, Collider::Type::BOUNDS);

	// Fixed positions
	
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			grid[i][j] = EMPTY;
		}
	}

	for (int i = 1; i < 11; i += 2)
	{
		for (int j = 1; j < 13; j += 2)
		{
			grid[i][j] = ROCK;
		}
	}

	grid[5][4] = ROCK;
	grid[4][5] = ROCK;
	grid[5][8] = ROCK;
	grid[6][7] = ROCK;

	grid[0][6] = PLAYER;
	grid[2][10] = MOUSE;
	grid[10][6] = POKAPOKA;
	grid[8][2] = MOUSE;
	grid[5][6] = RED_FLOWER;
	grid[3][2] = MECHA_WALKER;
	grid[5][10] = MECHA_WALKER;
	grid[4][4] = ORB;
	grid[6][8] = ORB;
	grid[0][11] = WIN_SPOT;

	int flowerAmount = rand() % 10 + 36;
	int x = 0;
	int y = 0;

	for (int i = 0; i < flowerAmount;)
	{
		x = rand() % 13;
		y = rand() % 11;

		if (grid[y][x] == EMPTY)
		{
			grid[y][x] = YELLOW_FLOWER;
			i++;
		}
	}

	// Fixed empty positions
	grid[0][4] = EMPTY;
	grid[0][5] = EMPTY;
	grid[0][7] = EMPTY;
	grid[1][11] = EMPTY;

	grid[0][0] = WALL;
	grid[0][1] = WALL;
	grid[0][2] = WALL;
	grid[0][3] = WALL;
	grid[0][9] = WALL;
	grid[0][10] = WALL;
	grid[0][12] = WALL;
	grid[10][0] = WALL;
	grid[10][1] = WALL;
	grid[10][2] = WALL;
	grid[10][3] = WALL;
	grid[10][10] = WALL;
	grid[10][11] = WALL;
	grid[10][12] = WALL;
	grid[1][0] = WALL;
	grid[1][1] = WALL;
	grid[1][2] = WALL;
	grid[1][3] = WALL;
	grid[1][9] = WALL;
	grid[1][10] = WALL;
	grid[1][11] = WALL;
	grid[1][12] = WALL;
	grid[9][1] = WALL;
	grid[9][2] = WALL;
	grid[9][3] = WALL;
	grid[9][9] = WALL;
	grid[9][10] = WALL;
	grid[9][11] = WALL;
	grid[9][12] = WALL;

	middleStructureIsSet = false;

	// generate scene elements or rock collisions
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++)
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
			else if (grid[i][j] == WIN_SPOT)
			{
				App->entities->AddEntity(Entity_Type::WIN, j, i);
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

	return ret;
}

Update_Status SceneLevel3::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel3::PostUpdate()
{
	//Draw background
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel3::CleanUp()
{
	App->player->Disable();
	App->entities->Disable();
	App->collisions->Disable();
	App->UI->Disable();

	return true;
}

SceneLevel3::GridType SceneLevel3::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

SceneLevel3::GridType SceneLevel3::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}