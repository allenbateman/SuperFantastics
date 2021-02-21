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
		lastTime,
		currentTime,
		deltaTime;

	uint32 msFrame;

	SDL_Window* pWindow;

	int mScreenWidth, mScreenHeight;
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

	int getScreenWidth() { return mScreenWidth; }
	int getScreenHeight() { return mScreenHeight; }
};