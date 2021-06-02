#pragma once
#include "Module.h"
#include "p2Point.h"
#define MAX_POWER_UPS 3

class ModulePowerUp : public Module
{
public:
	ModulePowerUp(bool startEnabled);
	~ModulePowerUp();
	void SpawnPowerUp(iPoint position);

private:
};

