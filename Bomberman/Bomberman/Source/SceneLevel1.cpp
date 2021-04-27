#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Grid.h"

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
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	srand((unsigned)time(0));

	
	// Fixed positions

	Grid stage1[11][13];

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			if ((i % 2) == 1 && (i % 2) == 1) stage1[i][j].ROCK;
			else stage1[i][j].EMPTY;
		}
	}
	for (int i = 5; i < 8; i++) for (int j = 3; j < 6; j++) stage1[i][j].STRUCTURE;

	stage1[0][1].PLAYER;
	stage1[0][6].POKAPOKA;
	stage1[10][6].POKAPOKA;
	stage1[2][4].RED_FLOWER;
	stage1[2][8].RED_FLOWER;
	stage1[8][4].RED_FLOWER;
	stage1[8][8].RED_FLOWER;
	stage1[2][9].MECHA_WALKER;
	stage1[8][3].MECHA_WALKER;
	stage1[2][10].MACHINE_PIECE;
	stage1[8][2].MACHINE_PIECE;

	// Random positions
	int rand1 = 0;
	int rand2 = 0;
	int counter = 45;

	while (counter < 0) {
		rand1 = (rand() % 11);
		rand2 = (rand() % 13);
		if (stage1[rand1][rand2].EMPTY) {
			stage1[rand1][rand2].YELLOW_FLOWER;
		}
		counter--;
	}

	// Fixed empy positions
	stage1[0][0].EMPTY;
	stage1[0][2].EMPTY;
	stage1[0][5].EMPTY;
	stage1[0][7].EMPTY;
	stage1[1][0].EMPTY;
	stage1[2][0].EMPTY;
	stage1[10][5].EMPTY;

	// generate scene elements or rock collisions

	for (int i = 0; i < 11; i++) {
		for (int j = 0; i < 13; i++) {

			if (stage1[i][j].PLAYER) {

			}
			else if (stage1[i][j].ROCK ||stage1[i][j].STRUCTURE) {
				App->collisions->AddCollider({ 24 + (i * 16),32 + (j * 16),16,16 }, Collider::Type::WALL);
			}
			else if (stage1[i][j].YELLOW_FLOWER) {}
			else if (stage1[i][j].POKAPOKA)
			{
				App->enemies->AddEnemy(Enemy_Type::POKAPOKA, 24 + (i * 16), 32 + (j * 16));
			}
			else if (stage1[i][j].MECHA_WALKER) {}
			else if (stage1[i][j].RED_FLOWER) {}
			else if (stage1[i][j].MECHA_WALKER){}
			else if (stage1[i][j].MACHINE_PIECE) {}
		}
	}



	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x += 3;

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