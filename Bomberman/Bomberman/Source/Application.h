#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 23

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneInit;
class SceneIntro;
class SceneSelectLevel;
class SceneLevel1;
class SceneLevel2;
class SceneLevel3;
class SceneLevel3x1;
class SceneBossFight;
class SceneGameOver;
class ModuleParticles;
class ModuleCollisions;
class ModuleEntities;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleUI;
class ModuleLevel;
class ModulePowerUp;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	ModuleUI* UI = nullptr;

	SceneInit* sceneInit = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneSelectLevel* sceneSelectLevel = nullptr;
	SceneLevel1* sceneLevel1 = nullptr;
	SceneLevel2* sceneLevel2 = nullptr;
	SceneLevel3* sceneLevel3 = nullptr;
	SceneLevel3x1* sceneLevel3x1 = nullptr;
	SceneBossFight* sceneBossFight = nullptr;
	SceneGameOver* sceneGameOver = nullptr;

	ModuleEntities* entities = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePowerUp* powerUps = nullptr;

	ModuleLevel* levelManager = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;

	int frameCounter = 0;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__