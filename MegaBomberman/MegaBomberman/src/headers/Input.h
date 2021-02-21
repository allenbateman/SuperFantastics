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
	bool m_WindowQuit;
	bool m_MousePressed;

	Vector2i m_MousePosition;

	const uint8* m_SDLKeyState;
	KeyState* m_KeyStates;
	int m_NumKeys;
public:
	Input();
	~Input();
	void UpdateInputs();
	bool WindowQuit() { return m_WindowQuit; }
	void QuitGame() { m_WindowQuit = true; }

	bool getKeyUp(uint32 key);
	bool getKeyDown(uint32 key);
	bool getKey(uint32 key);
	Vector2i getMousePos() { return m_MousePosition; }
	bool getMousePress() { return m_MousePressed; }
};