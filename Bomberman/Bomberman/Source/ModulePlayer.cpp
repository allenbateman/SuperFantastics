#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SDL.h"
#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	upIdleAnim.PushBack({ 65 , 1, 15, 22 });
	downIdleAnim.PushBack({ 17, 1, 15, 22 });
	leftIdleAnim.PushBack({ 16, 25, 16, 22 });
	rightIdleAnim.PushBack({ 64, 25, 16, 22 });

	// Move left
	leftAnim.PushBack({ 32, 25, 15, 22 });
	leftAnim.PushBack({ 16, 25, 16, 22 });
	leftAnim.PushBack({ 0, 25, 15, 22 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	// Move right 
	rightAnim.PushBack({ 48, 25, 16, 22 });
	rightAnim.PushBack({ 64, 25, 16, 22 });
	rightAnim.PushBack({ 81, 25 , 15 , 22 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Move upwards
	upAnim.PushBack({ 49, 1, 15, 22 });
	upAnim.PushBack({ 65 , 1, 15, 22 });
	upAnim.PushBack({ 80 , 1, 15, 22 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 0, 1, 15, 22 });
	downAnim.PushBack({ 17, 1, 15, 22 });
	downAnim.PushBack({ 33, 1, 15, 22 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Death animation
	deathAnim.PushBack({ 1,49,15,20 });
	deathAnim.PushBack({ 17 ,49,13,19 });
	deathAnim.PushBack({ 31,50,17,18 });
	deathAnim.PushBack({ 49,49,19,20 });
	deathAnim.PushBack({ 89,50,21,19 });
	deathAnim.PushBack({ 91,48,22,21 });
	deathAnim.loop = false;
	deathAnim.speed = 0.15f;

	// Win Animation
	winAnim.PushBack({ 0,74,17,19 });
	winAnim.PushBack({ 18,73,17,20 });
	winAnim.PushBack({ 40,71,15,23 });
	winAnim.loop = false;
	winAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/BomberManAnimations.png");
	currentAnimation = &downIdleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 150;
	//position.y = 120;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 15, 22 }, Collider::Type::PLAYER, this);

	// LOAD UI FONT
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	

	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
			currentIdleAnim = leftIdleAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
			currentIdleAnim = rightIdleAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
			currentIdleAnim = downIdleAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
			currentIdleAnim = upIdleAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		//add bomb here
		//Particle* newParticle = App->particles->AddParticle(App->particles->bomb, position.x, position.y, Collider::Type::PLAYER_SHOT);
		//newParticle->collider->AddListener(this);
		//App->audio->PlayFx(laserFx);
	}

	// If no movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE 
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &currentIdleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		currentAnimation = &deathAnim;			
		SDL_Delay(1000);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		destroyed = true;		
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}