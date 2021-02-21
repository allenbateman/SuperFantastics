#include "../headers/Input.h"
#include "../headers/Video.h"
#include "sdl.h"

Input::Input()
{
	windowQuit = false;
	mousePress = false;

	mSDLKeyState = SDL_GetKeyboardState(&mNumKeys);

	mKeyStates = new KeyState[mNumKeys];
}


Input::~Input()
{
	delete[] mKeyStates;
}

void Input::UpdateInputs()
{
	memset(mKeyStates, KS_NONE, mNumKeys);

	SDL_Event event_poll;

	while (SDL_PollEvent(&event_poll)) {
		switch (event_poll.type) {
		case SDL_QUIT:
			windowQuit = true;
			break;
		case SDL_KEYDOWN:
			if (event_poll.key.repeat) {
				mKeyStates[event_poll.key.keysym.scancode] = KS_KEYPRESS;
			}
			else {
				mKeyStates[event_poll.key.keysym.scancode] = KS_KEYDOWN;
			}
			break;
		case SDL_KEYUP:
			mKeyStates[event_poll.key.keysym.scancode] = KS_KEYUP;
			break;
		case SDL_MOUSEMOTION:
			mMousePositionScreen.x = event_poll.motion.x;
			mMousePositionScreen.y = event_poll.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mousePress = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mousePress = false;
			break;
		default:
			break;
		}
	}
}

bool Input::getKeyUp(uint32 key)
{
	return mKeyStates[key] == KS_KEYUP;
}

bool Input::getKeyDown(uint32 key)
{
	return mKeyStates[key] == KS_KEYDOWN;
}

bool Input::getKey(uint32 key)
{
	return mSDLKeyState[key];
}