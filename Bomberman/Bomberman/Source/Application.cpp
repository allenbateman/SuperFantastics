#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "SceneInit.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneBossFight.h"
#include "ModuleParticles.h"
#include "ModuleEntities.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"
#include "ModuleLevel.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		  new ModuleWindow(true);
	modules[1] =	input =			  new ModuleInput(true);
	modules[2] =	textures =		  new ModuleTextures(true);
	modules[3] =	audio =			  new ModuleAudio(true);

	modules[4] =	sceneInit =		  new SceneInit(true);
	modules[5] =	sceneIntro =	  new SceneIntro(false);
	modules[6] =	sceneLevel1 =	  new SceneLevel1(false);	    //Gameplay scene starts disabled
	modules[7] =    sceneLevel2 =     new SceneLevel2(false);
	modules[8] =    sceneLevel3 =     new SceneLevel3(false);
	modules[9] =	sceneBossFight =  new SceneBossFight(false);
	modules[10] =	UI =			  new ModuleUI(false);		   
	modules[11] =	particles =		  new ModuleParticles(false);
	modules[12] =   entities =		  new ModuleEntities(false);    //Enemies start disabled
	modules[13] =	player =		  new ModulePlayer(false);	    //Player starts disabled

	modules[14] =	collisions =	  new ModuleCollisions(true);
	modules[15] =	fade =			  new ModuleFadeToBlack(true);
	modules[16] =	fonts =			  new ModuleFonts(true);
	modules[17] =	render =		  new ModuleRender(true);
	modules[18] =	powerUps =		  new ModulePowerUp(true);
	modules[19] =	levelManager =    new ModuleLevel(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	//Exit apication
	if (input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
		ret = Update_Status::UPDATE_STOP;
	

	frameCounter++;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
