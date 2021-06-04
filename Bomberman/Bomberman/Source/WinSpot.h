#pragma once
#include "Entity.h"

class WinSpot : public Entity
{
public:
	WinSpot(int x, int y);
	~WinSpot();
	void Update() override;
	void SetToDelete() override;

private:

	Collider* winCollider = nullptr;
};