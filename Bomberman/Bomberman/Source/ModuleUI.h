#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__


#include "Module.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleUI : public Module
{
private:
	bool startTiming = false;
public: 
	ModuleUI(bool startEnabled);
	~ModuleUI();
	bool Start() override;
	Update_Status Update() override;
	Update_Status PostUpdate() override;
public: 

	int timeLeft = 0;
	int timeLevel = 0;
	int initialFrame = 0;
	int time = 0;
	
	SDL_Texture* numTex  = nullptr;
	SDL_Texture* powerupTex = nullptr;

	void StartTiming() { startTiming = true; }
	void StopTiming() { startTiming = false; }
};

#endif //!__MODULE_UI_H__