#include "SceneSelectLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"

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

	App->levelManager->orbCount = 0;
	App->levelManager->orbsLeft = 0;

	App->UI->StopTiming();

	bool ret = true;

	sheetTexture = App->textures->Load("Assets/Sprites/selectLevelSpritesheet.png");
	//	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f); (copied from sceneIntro.cpp, maybe not useful here)
	App->audio->PlayMusic("Assets/Music/05StageSelect.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	for (int i = 0; i < 8; i++) {
		partAnimation.PushBack({i * 16, 416, 16, 16});
	}
	partAnimation.loop = true;
	partAnimation.speed = 0.1f;

	selectedLevelPoints[0].create(43, 55);
	selectedLevelPoints[1].create(94, 79);
	selectedLevelPoints[2].create(51, 75);

	return ret;
}

Update_Status SceneSelectLevel::Update()
{
	GamePad& pad = App->input->pads[0]; // Gamepad support for level selection
	


	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.a == true)
	{
		if (!exit) {
			Module* selectedLevel = nullptr;
			ModuleLevel::GameState state;

			switch (selectedStage) {
			case 0:
				selectedLevel = (Module*)App->sceneLevel1;
				state = ModuleLevel::LEVEL1;
				break;
			case 1:
				selectedLevel = (Module*)App->sceneLevel2;
				state = ModuleLevel::LEVEL2;
				break;
			case 2:
				selectedLevel = (Module*)App->sceneLevel3;
				state = ModuleLevel::LEVEL3;
				break;		
			default:
				selectedLevel = (Module*)App->sceneInit;
				state = ModuleLevel::MAIN_MENU;
					break;
			}

			App->fade->FadeToBlack(this, selectedLevel, 60);
			App->levelManager->currentScene = selectedLevel;
			App->levelManager->gameState = state;
		}
		else {
			return Update_Status::UPDATE_STOP;
		}
	}

	if(!pad.right)
	{
		rightPadContinue = false;
	}
	else if (!pad.left)
	{
		leftPadContinue = false;
	}

	if (pad.left_x == 0.0f) {
		joystickContinue = false;
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN || (pad.left_x > 0.0f && !joystickContinue) || (pad.right == true && !rightPadContinue))
	{
		rightPadContinue = true;
		joystickContinue = true;
		selectedStage++;

		if (selectedStage > App->levelManager->levelsPassed || selectedStage >= MAX_STAGES)
		{
			selectedStage = 0;
		}
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN || (pad.left_x < 0.0f && !joystickContinue) || (pad.left == true && !leftPadContinue))
	{
		leftPadContinue = true;
		joystickContinue = true;
		selectedStage--;

		if (selectedStage < 0)
		{
			selectedStage = App->levelManager->levelsPassed;

			if (selectedStage >= MAX_STAGES) {
				selectedStage = MAX_STAGES - 1;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN || pad.left_y < 0.0f || pad.down == true)
	{
		exit = true;
	}
	
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN || pad.left_y > 0.0f || pad.up == true)
	{
		exit = false;
	}

	partAnimation.Update();

	// DEBUGGING

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	{
		if (App->levelManager->levelsPassed < MAX_STAGES) {
			App->levelManager->levelsPassed++;
		}
	}

	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN)
	{
		App->levelManager->levelsPassed = 0;
		selectedStage = 0;
	}

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

	switch (App->levelManager->levelsPassed) {
		case 0:
			App->render->Blit(sheetTexture, 52, 56, &rect);
		case 1:
			App->render->Blit(sheetTexture, 103, 80, &rect);
		case 2:
			App->render->Blit(sheetTexture, 60, 76, &rect);
	}
	

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