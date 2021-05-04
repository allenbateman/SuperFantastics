#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

#include <ctime>

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	App->player->Enable();
	App->enemies->Enable();

	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	//App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);
	
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

	grid[0][1] = PLAYER;
	grid[0][6] = POKAPOKA;
	grid[10][6] = POKAPOKA;
	grid[2][4] = RED_FLOWER;
	grid[2][8] = RED_FLOWER;
	grid[8][4] = RED_FLOWER;
	grid[8][8] = RED_FLOWER;
	grid[2][9] = MECHA_WALKER;
	grid[8][3] = MECHA_WALKER;
	grid[2][10] = ORB;
	grid[8][2] = ORB;
	grid[3][5] = STRUCTURE;
	grid[3][6] = STRUCTURE;
	grid[3][7] = STRUCTURE;
	grid[4][5] = STRUCTURE;
	grid[4][7] = STRUCTURE;
	grid[5][5] = STRUCTURE;
	grid[5][7] = STRUCTURE;

	int flowerAmount = rand() % 10 + 35;
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
	grid[0][2] = EMPTY;
	grid[1][0] = EMPTY;
	grid[2][0] = EMPTY;
	grid[4][6] = EMPTY;
	grid[5][6] = EMPTY;

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
				App->enemies->AddEnemy(Enemy_Type::YELLOW_FLOWER, j, i);
			}
			else if (grid[i][j] == RED_FLOWER)
			{
				App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::RED_FLOWER);
			}
			else if (grid[i][j] == ORB)
			{
				App->enemies->AddEnemy(Enemy_Type::ORB, j, i);
			}
			else if (grid[i][j] == STRUCTURE)
			{
				App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::STRUCTURE);
			}
			else if (grid[i][j] == POKAPOKA)
			{
				App->enemies->AddEnemy(Enemy_Type::POKAPOKA, 24 + (j * 16), 32 - 16 + (i * 16));
			}
			else if (grid[i][j] == MECHA_WALKER)
			{
				App->collisions->AddCollider({ 24 + (j * 16),32 + (i * 16),16,16 }, Collider::Type::ENEMY);
			}
		}
	}

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneLevel1::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}