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
	App->audio->PlayMusic("Assets/Music/01OpeningTheme.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneInit::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneInit::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}