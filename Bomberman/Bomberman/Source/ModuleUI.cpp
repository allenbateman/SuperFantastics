#include "ModuleUI.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleEntities.h"
#include "ModulePlayer.h"
ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	numTex = App->textures->Load("Assets/Fonts/interface.png");
	powerupTex = App->textures->Load("Assets/Sprites/Power_Ups.png");
	return true;
}

Update_Status ModuleUI::Update()
{
	time = (App->frameCounter - initialFrame) / 60;
	timeLeft = timeLevel - time;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate(){
	int x = 136;
	int y = 8;
	int score = App->player->score;
	SDL_Rect rec = { 0 };

	// draw score
	int digits = 10000000;
	for (int i = 0; i < 8; i++) {
		int d = score / digits;
		if (d > 0 || i > 5) {
			rec = { d * 8,0,8,8 };
			App->render->Blit(numTex, x + (8 * i), y, &rec);
		}
		score = score % digits;
		digits /= 10;
	}

	// draw lifes
	rec = { App->player->lifes * 8,0,8,8 };
	App->render->Blit(numTex, 232, y, &rec);

	// draw time
	rec = { timeLeft / (60) * 8,0,8,8 };
	App->render->Blit(numTex, 16, y, &rec);
	rec = { (timeLeft % 60) / 10 * 8,0,8,8 };
	App->render->Blit(numTex, 32, y, &rec);
	rec = { (timeLeft % 10) * 8,0,8,8 };
	App->render->Blit(numTex, 40, y, &rec);
	
	//draw Orbs

	return  Update_Status::UPDATE_CONTINUE;
}
