#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"


struct Collider;

class Module
{
public:
	Module(bool startEnabled);

	//Called at the beginning of the application execution
	virtual bool Init();

	//Called when the module is activated
	//By now we will consider all modules to be permanently active
	virtual bool Start();

	//Called at the beginning of each application loop
	virtual Update_Status PreUpdate();

	//Called at the middle of each application loop
	virtual Update_Status Update();

	//Called at the end of each application loop
	virtual Update_Status PostUpdate();

	//Called at the end of the application
	virtual bool CleanUp();

	//Called when two colliders are intersecting
	//and the module is registered as the listener
	virtual void OnCollision(Collider* c1, Collider* c2);

	// Switches isEnabled and calls Start() method
	void Enable();

	// Switches isEnabled and calls CleanUp() method
	void Disable();

	inline bool IsEnabled() const { return isEnabled; }

	enum GridType
	{
		EMPTY = 0,
		WALL,
		PLAYER,
		BOMB,
		ROCK,
		STRUCTURE,
		ORB,
		POKAPOKA,
		MECHA_WALKER,
		MOUSE,
		SNAIL,
		RED_FLOWER,
		YELLOW_FLOWER,
		WIN_SPOT,
		NEXT_SPOT,
		POWER_UP, 
		SARU,
		BANANACHER
	};
	inline const char* GridToString(GridType gridCell);
private:
	bool isEnabled = true;
};

#endif // __MODULE_H__