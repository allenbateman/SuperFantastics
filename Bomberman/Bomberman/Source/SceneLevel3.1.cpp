#include "SceneLevel3.1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleUI.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleEntities.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"

#include <ctime>

SceneLevel3x1::SceneLevel3x1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel3x1::~SceneLevel3x1()
{

}

// Load assets
bool SceneLevel3x1::Start()
{


	App->render->levelBounds = levelBounds;

	App->levelManager->orbCount = orbs;
	App->levelManager->orbsLeft = orbs;

	App->levelManager->activeLevelWidth = LVL_THREEONE_WIDTH;

	App->player->Enable();
	App->entities->Enable();
	App->collisions->Enable();
	App->UI->Enable();



	App->UI->timeLeft = timeLevel;
	App->UI->timeLevel = timeLevel;

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background3.1.png");
	App->audio->PlayMusic("Assets/Music/SceneLevel1.ogg", 1.0f);

	//add bounding colliders
	//Left collider
	App->collisions->AddCollider({ 0,23,24,223 }, Collider::Type::BOUNDS);
	//Right Collider
	App->collisions->AddCollider({ 232,23,24,223 }, Collider::Type::BOUNDS);
	//Top Collider
	App->collisions->AddCollider({ 24,23,208,8 }, Collider::Type::BOUNDS);
	//Bot collider 
	App->collisions->AddCollider({ 24,208,208,8 }, Collider::Type::BOUNDS);


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

	grid[2][5] = ROCK;
	grid[4][5] = ROCK;
	grid[6][5] = ROCK;
	grid[8][5] = ROCK;
	grid[10][5] = ROCK;
	grid[2][7] = ROCK;
	grid[4][7] = ROCK;
	grid[6][7] = ROCK;
	grid[8][7] = ROCK;
	grid[1][0] = ROCK;
	grid[1][1] = ROCK;
	grid[1][2] = ROCK;
	grid[1][3] = ROCK;
	grid[1][4] = ROCK;
	grid[1][5] = ROCK;
	grid[1][9] = ROCK;
	grid[9][8] = ROCK;
	grid[9][10] = ROCK;
	grid[9][12] = ROCK;
	grid[0][9] = ROCK;
	grid[1][8] = ROCK;
	grid[0][9] = ROCK;
	grid[1][0] = ROCK;
	grid[7][6] = ROCK;
	grid[9][6] = ROCK;

	grid[2][1] = PLAYER;
	grid[6][4] = MOUSE;
	grid[8][2] = SNAIL;
	grid[8][9] = MECHA_WALKER;
	grid[0][11] = MECHA_WALKER;
	grid[10][2] = ORB;
	grid[2][10] = POKAPOKA;
	grid[3][9] = STRUCTURE;
	grid[3][10] = STRUCTURE;
	grid[3][11] = STRUCTURE;
	grid[4][9] = STRUCTURE;
	grid[4][11] = STRUCTURE;
	grid[5][9] = STRUCTURE;
	grid[5][11] = STRUCTURE;
	grid[4][10] = WIN_SPOT;

	int flowerAmount = rand() % 10 + 30;
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

	// Fixed empy positions
	grid[0][0] = EMPTY;
	grid[0][1] = EMPTY;
	grid[0][2] = EMPTY;
	grid[0][3] = EMPTY;
	grid[0][4] = EMPTY;
	grid[0][5] = EMPTY;
	grid[0][6] = EMPTY;
	grid[0][8] = EMPTY;
	grid[2][0] = EMPTY;
	grid[2][2] = EMPTY;
	grid[3][0] = EMPTY;
	grid[5][10] = EMPTY;
	grid[8][5] = EMPTY;
	grid[8][7] = EMPTY;
	grid[0][6] = EMPTY;
	grid[1][6] = EMPTY;
	grid[2][6] = EMPTY;
	grid[3][6] = EMPTY;
	grid[4][6] = EMPTY;
	grid[5][6] = EMPTY;
	grid[6][6] = EMPTY;
	grid[8][6] = EMPTY;
	grid[10][6] = EMPTY;
	grid[10][7] = EMPTY;
	grid[0][0] = EMPTY;
	grid[0][0] = EMPTY;
	grid[0][0] = EMPTY;
	grid[10][8] = EMPTY;
	grid[10][9] = EMPTY;
	grid[10][10] = EMPTY;
	grid[10][11] = EMPTY;
	grid[10][12] = EMPTY;

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
			else if (grid[i][j] == STRUCTURE)
			{
				if (!middleStructureIsSet)
				{
					App->entities->AddEntity(Entity_Type::MIDDLE_STRUCTURE, j, i);
					middleStructureIsSet = true;
				}
			}
			else if (grid[i][j] == WIN_SPOT)
			{
				App->entities->AddEntity(Entity_Type::WIN, j, i);
			}
			else if (grid[i][j] == POKAPOKA)
			{
				App->entities->AddEntity(Entity_Type::POKAPOKA, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == MOUSE)
			{
				App->entities->AddEntity(Entity_Type::MOUSE, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == SNAIL)
			{
				App->entities->AddEntity(Entity_Type::SNAIL, 24 + (j * 16), 32 - 16 + (i * 16));
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

Update_Status SceneLevel3x1::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel3x1::PostUpdate()
{
	//Draw background
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel3x1::CleanUp()
{
	App->player->Disable();
	App->entities->Disable();
	App->collisions->Disable();
	App->UI->Disable();

	return true;
}

SceneLevel3x1::GridType SceneLevel3x1::GetGridType(int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration];
}

SceneLevel3x1::GridType SceneLevel3x1::SetGridType(GridType type, int y, int x, int yIteration, int xIteration)
{
	return grid[(y - 32) / 16 + yIteration][(x - 24) / 16 + xIteration] = type;
}