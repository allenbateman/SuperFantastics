#include "SceneSelectLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleFadeToBlack.h"

SceneSelectLevel::SceneSelectLevel(bool startEnabled) : Module(startEnabled)
{

}

SceneSelectLevel::~SceneSelectLevel()
{

}

// Load assets
bool SceneSelectLevel::Start()
{
	LOG("Loading background assets");

	App->UI->Enable();
	App->UI->timeLevel = 5000;
	App->UI->timeLeft = 300;

	bool ret = true;

	sheetTexture = App->textures->Load("Assets/Sprites/selectLevelSpritesheet.png");
	//	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f); (copied from sceneIntro.cpp, maybe not useful here)

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	selectedStage = 0;

	for (int i = 0; i < 8; i++) {
		partAnimation.PushBack({i * 16, 416, 16, 16});
	}
	partAnimation.loop = true;
	partAnimation.speed = 0.1f;

	selectedLevelPoints[0].create(43, 55);
	selectedLevelPoints[1].create(51, 75);
	selectedLevelPoints[2].create(94, 79);

	return ret;
}

Update_Status SceneSelectLevel::Update()
{
	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN)
	{
		if (!exit) {
			Module* selectedLevel = nullptr;

			switch (selectedStage) {
			case 0:
				selectedLevel = (Module*)App->sceneLevel1;
				break;
			case 1:
				selectedLevel = (Module*)App->sceneLevel2;
				break;
			case 2:
				selectedLevel = (Module*)App->sceneLevel3;
				break;
			}

			App->fade->FadeToBlack(this, selectedLevel, 60);
		}
		else {
			// FIX: Go main menu or exit game?
			return Update_Status::UPDATE_STOP;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
	{
		selectedStage++;

		if (selectedStage >= maxStage)
		{
			selectedStage = 0;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
	{
		selectedStage--;

		if (selectedStage < 0)
		{
			selectedStage = maxStage - 1;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN)
	{
		exit = !exit;
	}

	partAnimation.Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneSelectLevel::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(sheetTexture, 0, 0, &backgroundRect);
	App->render->Blit(sheetTexture, 32, 24, &selectLevelRect);
	App->render->Blit(sheetTexture, 152, 32, &stageRect);

	if (App->frameCounter % 30 == 0)
	{
		showSelectedLevel = !showSelectedLevel;
	}

	if (showSelectedLevel) {
		App->render->Blit(sheetTexture, selectedLevelPoints[selectedStage].x, selectedLevelPoints[selectedStage].y, &selectedLevelRect);
	}

	SDL_Rect rect = partAnimation.GetCurrentFrame();
	App->render->Blit(sheetTexture, 52, 56, &rect);
	App->render->Blit(sheetTexture, 60, 76, &rect);
	App->render->Blit(sheetTexture, 103, 80, &rect);

	if (!exit) {
		stageNumberRect.x = selectedStage * 16;

		App->render->Blit(sheetTexture, 152, 48, &stageTitleRect);
		App->render->Blit(sheetTexture, 184, 72, &stageNumberRect);
	}
	else {
		App->render->Blit(sheetTexture, 152, 48, &stageExitRect);
	}

	return Update_Status::UPDATE_CONTINUE;
}