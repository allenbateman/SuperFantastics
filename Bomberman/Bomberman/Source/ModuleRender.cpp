#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "Collider.h"

#include "SDL/include/SDL_render.h"

ModuleRender::ModuleRender(bool startEnabled) : Module(startEnabled)
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	debug = false;
	// Set render logical size
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);		// Uncomment previous for fullscreen

	return ret;
}

// Called every draw update
Update_Status ModuleRender::PreUpdate()
{
	// Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear rendering target
	SDL_RenderClear(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	//camera scroll
	if (App->player->IsEnabled())
	{
		//right box detection
		if (App->player->position.x > rightBox.x && camera.x + camera.w < levelBounds.w )
		{
			camera.x += cameraSpeed;
			leftBox.x += App->player->speed;
			rightBox.x += App->player->speed;
		}
		//left box detection
		if (App->player->position.x + App->player->collider->rect.w < leftBox.x + leftBox.w && camera.x > levelBounds.x  )
		{
			camera.x -= cameraSpeed;
			leftBox.x -= App->player->speed;
			rightBox.x -= App->player->speed;
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleRender::PostUpdate()
{

	if (debug) {
		DrawQuad(leftBox, 255, 255, 255, 50);
		DrawQuad(rightBox, 255, 255, 255, 50);
	}
	// Update the screen
	SDL_RenderPresent(renderer);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	// Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, bool useCamera, RenderFlip flip)
{
	bool ret = true;

	SDL_Rect dstRect{ x * SCREEN_SIZE, y * SCREEN_SIZE, 0, 0 };

	if (useCamera)
	{
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}

	if (section != nullptr)
	{
		dstRect.w = section->w;
		dstRect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
	}

	dstRect.w *= SCREEN_SIZE;
	dstRect.h *= SCREEN_SIZE;

	if (SDL_RenderCopyEx(renderer, texture, section, &dstRect, 0, NULL, (SDL_RendererFlip)flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed, bool useCamera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{ rect.x * SCREEN_SIZE, rect.y * SCREEN_SIZE, rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (useCamera)
	{
		dstRect.x -= (camera.x * speed);
		dstRect.y -= (camera.y * speed);
	}

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::ResetScrollBoxPositions()
{
	leftBox = { 0,0,boxWidth,SCREEN_HEIGHT };
	rightBox = { SCREEN_WIDTH - boxWidth,0, boxWidth, SCREEN_HEIGHT };
}

iPoint ModuleRender::GetCenterRectPos(SDL_Rect rect)
{
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	iPoint center;
	//
	//  1---2
	//  |   |
	//	3---4
	//
	x1 = rect.x;
	x2 = rect.x + rect.w;
	x3 = rect.x;
	x4 = rect.x + rect.w;

	y1 = rect.y;
	y2 = rect.y;
	y3 = rect.y + rect.h;
	y4 = rect.y + rect.h;

	center.x = (x1 + x2 + x3 + x4) / 4;
	center.y = (y1 + y2 + y3 + y4) / 4;


	return center;
}

iPoint ModuleRender::SetCenterRectPos(SDL_Rect rect)
{
	return iPoint();
}
