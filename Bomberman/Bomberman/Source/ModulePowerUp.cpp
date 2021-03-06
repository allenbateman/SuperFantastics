#include "ModulePowerUp.h"
#include "Application.h"
#include "ModuleEntities.h"
#include "ModuleLevel.h"


ModulePowerUp::ModulePowerUp(bool startEnabled) : Module(startEnabled)
{
}

ModulePowerUp::~ModulePowerUp()
{
}

void ModulePowerUp::SpawnPowerUp(iPoint position)
{
	int chance = rand() % 100;
	if (chance <50)
	{
		if (chance<10) {
			App->entities->AddEntity(Entity_Type::BOMB_UP, position.x, position.y);
			App->levelManager->SetGridType(Module::GridType::POWER_UP, position.y, position.x, 0, 0);
		}
		else if (chance > 10 && chance < 20) {
			App->entities->AddEntity(Entity_Type::FIRE, position.x, position.y);
			App->levelManager->SetGridType(Module::GridType::POWER_UP, position.y, position.x, 0, 0);
		}
		else if (chance > 10 && chance < 15) {

		}
		else if (chance >15 && chance < 20) {

		}
		else if (chance > 20 && chance <25) {

		}
	}
}
