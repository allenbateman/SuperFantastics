#include "../headers/Video.h"
#include <string>

Video::Video()
{
	m_ScreenWidth = 600;
	mScreenHeight = 600;

	m_Window = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_Window = SDL_CreateWindow("MegaBomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_ScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);

	m_LastTime = 0;
	m_FrameMS = static_cast<uint32>(1.0f / (FPS / 1000.0f));
	m_CurrentTime = 0;

	m_DeltaTime = 0;
}

Video::~Video()
{

}

unsigned int Video::getDeltaTime()
{
	return m_DeltaTime;
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
	SDL_SetWindowSize(m_Window, width, height);
	m_ScreenWidth = width;
	mScreenHeight = height;
}

void Video::clearScreen()
{
	// TODO: Clear screen
}

void Video::updateScreen()
{
	std::string title = "MegaBomberman - ";
	title += std::to_string(m_DeltaTime);
	SDL_SetWindowTitle(m_Window, title.c_str());
	SDL_GL_SwapWindow(m_Window);
}

void Video::waitTime(int ms)
{
	SDL_Delay(ms);
}

void Video::tickDelay()
{
	m_CurrentTime = SDL_GetTicks();

	m_DeltaTime = m_CurrentTime - m_LastTime;

	if (m_DeltaTime < m_FrameMS) {
		SDL_Delay(m_FrameMS - m_DeltaTime);
	}

	m_LastTime = m_CurrentTime;
}

void Video::close()
{
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}