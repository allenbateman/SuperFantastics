#pragma once
#include "Entity.h"

class NextSpot : public Entity
{
public:
	NextSpot(int x, int y);
	~NextSpot();
	void Update() override;
	void SetToDelete() override;

private:
};