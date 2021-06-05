#include "ModuleUI.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleEntities.h"
#include "ModulePlayer.h"
#include "ModuleLevel.h"

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
	uiTex = App->textures->Load("Assets/Sprites/Ui.png");
	initialFrame = 0;
	return true;
}

Update_Status ModuleUI::Update()
{
	if (startTiming) {
		time = (App->frameCounter - initialFrame) / 60;
		timeLeft = timeLevel - time;

		if (timeLeft <= 0) {
			App->levelManager->RetunrToMainMenu();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate(){
	int x = 136;
	int y = 8;
	int score = App->player->score;
	SDL_Rect rec = { 0 };

	// draw score
	bool draw = false;
	int digits = 10000000;
	for (int i = 0; i < 8; i++) {
		int d = score / digits;

		if (d > 0) {
			draw = true;
		}

		if (draw || i > 5) {
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
	for (int i = 0; i < App->levelManager->orbCount; i++)
	{
		if (i < App->levelManager->orbsLeft)
		{
			App->render->Blit(uiTex, orbPos.x + i * 8, orbPos.y, &orbRect);
		}
		else {
			App->render->Blit(uiTex, orbPos.x + i * 8, orbPos.y, &deletedOrbRect);
		}
	}

	return  Update_Status::UPDATE_CONTINUE;
}
