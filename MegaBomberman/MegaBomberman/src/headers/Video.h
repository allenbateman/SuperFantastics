#pragma once

#include "sdl.h"

#include "../simple_types.h"

#include "Singleton.h"

#define FPS 60

class Video : public Singleton<Video>
{
	friend class Singleton<Video>;
private:
	unsigned int
		m_LastTime,
		m_CurrentTime,
		m_DeltaTime;

	uint32 m_FrameMS;

	SDL_Window* m_Window;

	int m_ScreenWidth, mScreenHeight;
public:
	Video();
	~Video();

	unsigned int getDeltaTime();

	void renderGraphic(int img, int posX, int posY);
	void renderGraphic(int img, int sourcePosX, int sourcePosY, int posX, int posY, int width, int height);

	void ResizeWindow(int width, int height);

	void clearScreen();
	void updateScreen();
	void waitTime(int ms);
	void tickDelay();
	void close();

	int getScreenWidth() { return m_ScreenWidth; }
	int getScreenHeight() { return mScreenHeight; }
};