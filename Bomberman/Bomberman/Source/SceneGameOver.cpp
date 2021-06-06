#include "SceneGameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"
#include "ModulePlayer.h"

SceneGameOver::SceneGameOver(bool startEnabled) : Module(startEnabled)
{

}

SceneGameOver::~SceneGameOver()
{

}

// Load assets
bool SceneGameOver::Start()
{
	LOG("Loading background assets");

	App->levelManager->currentScene = (Module*)this;

	App->audio->StopMusic();

	bool ret = true;

	gameOverTex = App->textures->Load("Assets/Sprites/gameOverScene.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	bgAnimations[0].PushBack({ 0,0,256,224 });
	bgAnimations[0].PushBack({ 256,0,256,224 });
	bgAnimations[0].PushBack({ 512,0,256,224 });
	bgAnimations[0].loop = true;
	bgAnimations[0].speed = 0.1f;

	bgAnimations[1].PushBack({ 0,224,256,224 });
	bgAnimations[1].PushBack({ 256,224,256,224 });
	bgAnimations[1].PushBack({ 512,224,256,224 });
	bgAnimations[1].loop = true;
	bgAnimations[1].speed = 0.1f;

	//App->audio->PlayFx(App->audio->LoadFx("Assets/Fx/22GameClear.mp3"));

	return ret;
}

Update_Status SceneGameOver::Update()
{
	bgAnimations[0].Update();
	bgAnimations[1].Update();

	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN || pad.left_y < 0.0f || pad.down == true)
	{
		optionSelected = 1;
	}

	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN || pad.left_y > 0.0f || pad.up == true)
	{
		optionSelected = 0;
	}

	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN) {
		if (optionSelected == 0) {
			App->player->score = 0;
			App->player->lifes = 3;
			App->levelManager->levelsPassed = 0;
			App->levelManager->RetunrToMainMenu();
		}
		else {
			return Update_Status::UPDATE_STOP;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect bg = bgAnimations[optionSelected].GetCurrentFrame();
	App->render->Blit(gameOverTex, 0, 0, &bg);

	return Update_Status::UPDATE_CONTINUE;
}