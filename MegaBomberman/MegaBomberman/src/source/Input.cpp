#include "../headers/Input.h"
#include "../headers/Video.h"
#include "sdl.h"

Input::Input()
{
	m_WindowQuit = false;
	m_MousePressed = false;

	m_SDLKeyState = SDL_GetKeyboardState(&m_NumKeys);

	m_KeyStates = new KeyState[m_NumKeys];
}


Input::~Input()
{
	delete[] m_KeyStates;
}

void Input::UpdateInputs()
{
	memset(m_KeyStates, KS_NONE, m_NumKeys);

	SDL_Event event_poll;

	while (SDL_PollEvent(&event_poll)) {
		switch (event_poll.type) {
		case SDL_QUIT:
			m_WindowQuit = true;
			break;
		case SDL_KEYDOWN:
			if (event_poll.key.repeat) {
				m_KeyStates[event_poll.key.keysym.scancode] = KS_KEYPRESS;
			}
			else {
				m_KeyStates[event_poll.key.keysym.scancode] = KS_KEYDOWN;
			}
			break;
		case SDL_KEYUP:
			m_KeyStates[event_poll.key.keysym.scancode] = KS_KEYUP;
			break;
		case SDL_MOUSEMOTION:
			m_MousePosition.x = event_poll.motion.x;
			m_MousePosition.y = event_poll.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_MousePressed = true;
			break;
		case SDL_MOUSEBUTTONUP:
			m_MousePressed = false;
			break;
		default:
			break;
		}
	}
}

bool Input::getKeyUp(uint32 key)
{
	return m_KeyStates[key] == KS_KEYUP;
}

bool Input::getKeyDown(uint32 key)
{
	return m_KeyStates[key] == KS_KEYDOWN;
}

bool Input::getKey(uint32 key)
{
	return m_SDLKeyState[key];
}