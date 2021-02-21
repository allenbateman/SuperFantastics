#include "../headers/Video.h"
#include <string>

Video::Video()
{
	mScreenWidth = 600;
	mScreenHeight = 600;

	pWindow = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	pWindow = SDL_CreateWindow("MegaBomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);

	lastTime = 0;
	msFrame = static_cast<uint32>(1.0f / (FPS / 1000.0f));
	currentTime = 0;

	deltaTime = 0;
}

Video::~Video()
{

}

unsigned int Video::getDeltaTime()
{
	return deltaTime;
}

void Video::renderGraphic(int img, int posX, int posY)
{
	/*Sprite* sprite = Resources::getInstance()->GetResourceById<Sprite>(img);

	if (sprite) {
		renderGraphic(img, 0, 0, posX, posY, sprite->Width, sprite->Height);
	}*/
}

void Video::renderGraphic(int img, int sourcePosX, int sourcePosY, int posX, int posY, int width, int height)
{
	//Sprite* sprite = Resources::getInstance()->GetResourceById<Sprite>(img);

	//if (sprite) {
	//	// Normal way
	//	/*SDL_Rect r, rectAux;
	//	r.x = posX;
	//	r.y = posY;
	//	rectAux.h = height;
	//	rectAux.w = width;
	//	rectAux.x = sourcePosX;
	//	rectAux.y = sourcePosY;*/

	//	updatePositionToEndScreen(posX, posY);

	//	float scaleX = mEndScreenWidth / static_cast<float>(SCREEN_WIDTH);
	//	float scaleY = mEndScreenHeight / static_cast<float>(SCREEN_HEIGHT);

	//	// Scaled draw
	//	SDL_Rect r, rectAux;
	//	r.x = posX;
	//	r.y = posY;
	//	r.w = static_cast<int>(width * scaleX);
	//	r.h = static_cast<int>(height * scaleY);
	//	rectAux.h = height;
	//	rectAux.w = width;
	//	rectAux.x = sourcePosX;
	//	rectAux.y = sourcePosY;

	//	// Normal draw
	//	//SDL_BlitSurface(sprite->getSurface(), &rectAux, gScreenSurface, &r);

	//	// Scaled draw
	//	SDL_BlitScaled(sprite->getSurface(), &rectAux, gScreenSurface, &r);
	//}
}

void Video::ResizeWindow(int width, int height)
{
	SDL_SetWindowSize(pWindow, width, height);
	mScreenWidth = width;
	mScreenHeight = height;
}

void Video::clearScreen()
{
	// TODO: Clear screen
}

void Video::updateScreen()
{
	std::string title = "MegaBomberman - ";
	title += std::to_string(deltaTime);
	SDL_SetWindowTitle(pWindow, title.c_str());
	SDL_GL_SwapWindow(pWindow);
}

void Video::waitTime(int ms)
{
	SDL_Delay(ms);
}

void Video::tickDelay()
{
	currentTime = SDL_GetTicks();

	deltaTime = currentTime - lastTime;

	if (deltaTime < msFrame) {
		SDL_Delay(msFrame - deltaTime);
	}

	lastTime = currentTime;
}

void Video::close()
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}