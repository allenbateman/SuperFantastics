#include "SceneInit.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneInit::SceneInit(bool startEnabled) : Module(startEnabled)
{

}

SceneInit::~SceneInit()
{

}

// Load assets
bool SceneInit::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/initScreen.bmp");
	//	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f); (copied from sceneIntro.cpp, maybe not useful here)

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneInit::Update()
{
	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 60);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneInit::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}