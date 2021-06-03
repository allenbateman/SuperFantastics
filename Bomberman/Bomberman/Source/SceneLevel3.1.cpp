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
	App->player->EnablePlayer();
	App->entities->Enable();
	App->collisions->Enable();
	App->UI->Enable();

	App->UI->timeLeft = timeLevel;
	App->UI->timeLevel = timeLevel;

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Background3.1.png");
	App->audio->PlayMusic("Assets/Music/SceneLevel1.ogg", 1.0f);

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

	grid[0][6] = PLAYER;
	grid[2][10] = MOUSE;
	grid[10][6] = POKAPOKA;
	grid[8][2] = MOUSE;
	grid[5][6] = RED_FLOWER;
	grid[3][2] = MECHA_WALKER;
	grid[5][10] = MECHA_WALKER;
	grid[4][4] = ORB;
	grid[6][8] = ORB;
	grid[1][11] = WIN_SPOT;

	int flowerAmount = rand() % 10 + 27;
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
	grid[0][4] = EMPTY;
	grid[0][5] = EMPTY;
	grid[0][6] = EMPTY;
	grid[0][7] = EMPTY;
	grid[1][6] = EMPTY;
	grid[1][2] = EMPTY;
	grid[1][4] = EMPTY;
	grid[1][9] = EMPTY;

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
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	{
		App->player->DisablePlayer();
		App->entities->Disable();
		App->collisions->Disable();
		App->UI->Disable();


		App->fade->FadeToBlack(this, (Module*)App->sceneBossFight, 60);
	}

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