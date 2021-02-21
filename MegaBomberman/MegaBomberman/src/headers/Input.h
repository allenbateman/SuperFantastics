#pragma once

#include "Singleton.h"

#include "../simple_types.h"
#include "math/Vector2f.h"
#include "math/Vector2i.h"

#include <vector>

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	enum KeyState {
		KS_KEYDOWN,
		KS_KEYUP,
		KS_KEYPRESS,
		KS_NONE
	};
private:
	bool windowQuit;
	bool mousePress;

	Vector2i mMousePositionScreen;

	const uint8* mSDLKeyState;
	KeyState* mKeyStates;
	int mNumKeys;
public:
	Input();
	~Input();
	void UpdateInputs();
	bool WindowQuit() { return windowQuit; }
	void QuitGame() { windowQuit = true; }

	bool getKeyUp(uint32 key);
	bool getKeyDown(uint32 key);
	bool getKey(uint32 key);
	Vector2i getMousePos() { return mMousePositionScreen; }
	bool getMousePress() { return mousePress; }
};