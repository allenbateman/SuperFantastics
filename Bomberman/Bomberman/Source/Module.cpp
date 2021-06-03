#include "Module.h"

Module::Module(bool startEnabled) : isEnabled(startEnabled)
{

}

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

Update_Status Module::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Module::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status Module::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}

void Module::OnCollision(Collider* c1, Collider* c2)
{

}

void Module::Enable() 
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}

void Module::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}

inline const char* Module::GridToString(GridType gridCell)
{
	switch (gridCell)
	{
		case EMPTY:			return"EMPTY";
		case PLAYER:		return"PLAYER";
		case BOMB:			return"BOMB";
		case ROCK:			return"ROCK";
		case STRUCTURE:		return"STRUCTURE";
		case ORB:			return"ORB";
		case POKAPOKA:		return"POKAPOKA";
		case MECHA_WALKER:  return"MECHA_WALKER";
		case MOUSE:			return"MOUSE";
		case SNAIL:			return"SNAIL";
		case RED_FLOWER:	return"RED_FLOWER";
		case YELLOW_FLOWER: return"YELLOW_FLOWER";
		case WIN_SPOT:		return"WIN_SPOT";
		case POWER_UP:		return"POWER_UP";
		case SARU:			return"SARU";
		case BANANACHER:	return"BANANACHER";
		default:			return "[Unknown grid type]";
	}
}

