#pragma once

#include "Singleton.h"

#include "../simple_types.h"

class GameState : public Singleton<GameState>{
	friend class Singleton<GameState>;
	public:
		// Enum of the types of entity that exist in the game
		enum EntityType {
			ET_LAST
		};

	private:
		GameState();
};