#pragma once
#include "Entity.h"

class MiddleStructure : public Entity
{
public:
	MiddleStructure(int x, int y);
	~MiddleStructure();
	void Update() override;
	void Draw() override;

private:

	Animation idleAnim, winAnim;
	

};