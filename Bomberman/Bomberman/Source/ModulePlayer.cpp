#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleEntities.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel.h"
#include "ModuleFonts.h"
#include "SDL.h"
#include "SceneLevel1.h"
#include "MiddleStructure.h"
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
	winAnim.PushBack({ 18,73,17,20 });
	winAnim.PushBack({ 40,71,15,23 });
	winAnim.loop = true;
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


	currentIdleAnim = downIdleAnim;
	currentAnimation = &downAnim;

	bomb = App->audio->LoadFx("Assets/Fx/19Bomb.wav");

	destroyed = false;
	
	isVisible = true;
	frameCounter = 0;
    currentBombs = 1;
	rangeExplosion = 1;
	CollectedOrbs = false;
	currentState = PlayerState::ALIVE;

	collider = App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Collider::Type::PLAYER, this);
	EnablePlayer();

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	int y = 0;
	int x = 0;
	frameCounter++;
	switch (currentState){
		case PlayerState::ALIVE:
			//Movement
			y = (collider->GetPos().y - 32) / 16;
			x = (collider->GetPos().x - 24) / 16;

			App->levelManager->SetGridType(Module::GridType::PLAYER, position.y, position.x);

			lastPos = position;
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT) {
				position.x -= speed;
				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					currentIdleAnim = leftIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_LEFT;

				if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y += speed;
					isStuck = false;
				}
			}
			else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT) {
				position.x += speed;
				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					currentIdleAnim = rightIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_RIGHT;

				if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y += speed;
					isStuck = false;
				}

			}
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT) {
				position.y += speed;
				if (currentAnimation != &downAnim)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
					currentIdleAnim = downIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_DOWN;

				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x += speed;
					isStuck = false;
				}

			}
			else if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT) {
				position.y -= speed;
				if (currentAnimation != &upAnim)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
					currentIdleAnim = upIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_UP;

				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x += speed;
					isStuck = false;
				}
			}


			// GAMEPAD SUPPORT

			// Debug key for gamepad rumble testing purposes
			if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN)
			{
				App->input->ShakeController(0, 12, 0.33f);
			}

			// Debug key for gamepad rumble testing purposes
			if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
			{
				App->input->ShakeController(0, 36, 0.66f);
			}

			// Debug key for gamepad rumble testing purposes
			if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
			{
				App->input->ShakeController(0, 60, 1.0f);
			}


			// Implement gamepad support

			if (pad.left_x < 0.0f || pad.left == true)
			{
				position.x -= speed;
				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
					currentIdleAnim = leftIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_LEFT;

				if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y += speed;
					isStuck = false;
				}
			}

			if (pad.left_x > 0.0f || pad.right == true)
			{
				position.x += speed;
				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
					currentIdleAnim = rightIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_RIGHT;

				if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT && isStuck)
				{
					position.y += speed;
					isStuck = false;
				}
			}

			if (pad.left_y > 0.0f || pad.down == true)
			{
				position.y += speed;
				if (currentAnimation != &downAnim)
				{
					downAnim.Reset();
					currentAnimation = &downAnim;
					currentIdleAnim = downIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_DOWN;

				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x += speed;
					isStuck = false;
				}
			}

			if (pad.left_y < 0.0f || pad.up == true)
			{
				position.y -= speed;
				if (currentAnimation != &upAnim)
				{
					upAnim.Reset();
					currentAnimation = &upAnim;
					currentIdleAnim = upIdleAnim;
				}
				lastKeyPressed = SDL_SCANCODE_UP;

				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x -= speed;
					isStuck = false;
				}
				else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && isStuck)
				{
					position.x += speed;
					isStuck = false;
				}
			}

			// If no movement detected, set the current animation back to idle
			if (pad.enabled)
			{
				if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentAnimation = &currentIdleAnim;
			}
			
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& currentAnimation != &deathAnim)
				currentAnimation = &currentIdleAnim;
			
			//move collider
			collider->SetPos(position.x, position.y);

			//Update player position in the grid
			App->levelManager->SetGridType(Module::GridType::PLAYER, position.y, position.x);

			//check border colliders
			if (position.y < 32 || position.y > 192 || position.x < 24 || position.x > 216) {
				//position = lastPos;
			}

			//Update grid 
			if ((position.x - 24) % 16 == 0 && (position.y - 32 + 8) % 16 == 0)
			{
				App->levelManager->grid[(lastPos.x - 24) % 16][(lastPos.y - 32 + 8) % 16] = Module::GridType::EMPTY;
				App->levelManager->grid[(position.x - 24) % 16][(position.y - 32 + 8) % 16] = Module::GridType::PLAYER;
			}

			//Place Bomb
			if (App->input->keys[SDL_SCANCODE_C] == Key_State::KEY_DOWN || pad.x == true)
			{
				if (App->entities->bombCount < currentBombs) {
					App->entities->AddEntity(Entity_Type::BOMB, position.x, position.y);
					App->audio->PlayFx(bomb);
				}
			}

			//End Game with F2
			if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
			{
				currentState = PlayerState::DEAD;
			}
			//Win Game with F3
			if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
			{
				currentState = PlayerState::WINING;
			}

			//check if player collected all orbs
			if (App->levelManager->orbsLeft == 0)
			{
				CollectedOrbs = true;
			}

			break;
		case PlayerState::DEAD:
		
			if (currentAnimation != &deathAnim) {
				deathAnim.Reset();
				currentAnimation = &deathAnim;
				frameCounter = 0;
			}
			else if (currentAnimation == &deathAnim && currentAnimation->HasFinished() && frameCounter > 60){
				
				destroyed = true;
				App->levelManager->RetunrToMainMenu();
			}

			break;
		case PlayerState::WINING:
			if (currentAnimation != &winAnim) {
				
				App->audio->PlayMusic("Assets/Music/Victory.ogg", 0.0f);
				winAnim.Reset();
				currentAnimation = &winAnim;
				frameCounter = 0;
			}
			else if (currentAnimation == &winAnim && frameCounter > 550) {
				
				//save player status...
				//Disable current level...
				//DisablePlayer();
				App->levelManager->RetunrToLevelSelection();
				App->levelManager->currentLevel++;
				currentState = PlayerState::WAITNING;
			}
			break;
		case PlayerState::WAITNING:
				break;
		default:
			break;
	}

	//update animations
	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	return true;
}

bool ModulePlayer::DisablePlayer()
{
	isVisible = false;
	return true;
}

bool ModulePlayer::EnablePlayer()
{
	isVisible = true;
	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	//world element collision movement
    if (c2->type == Collider::Type::WALL || c2->type == Collider::Type::YELLOW_FLOWER || c2->type == Collider::Type::STRUCTURE 
		|| c2->type == Collider::Type::RED_FLOWER || c2->type == Collider::Type::ORB || c2->type == Collider::Type::BOMB)
	{
		isStuck = true;
		switch (lastKeyPressed)
		{
			case SDL_SCANCODE_LEFT:
				position.x += speed;
				if (position.y + 16 >= c2->rect.y + 23)
				{
					position.y += 1;
					position.x -= 1;
				}
				if (position.y <= c2->rect.y - 7)
				{
					position.y -= 1;
					position.x -= 1;
				}
				break;
			case SDL_SCANCODE_RIGHT:
				position.x -= speed;
				if (position.y + 16 >= c2->rect.y + 23)
				{
					position.y += 1;
					position.x += 1;
				}
				if (position.y <= c2->rect.y - 7)
				{
					position.y -= 1;
					position.x += 1;
				}
				break;
			case SDL_SCANCODE_DOWN:
				position.y -= speed;
				if (position.x + 16 <= c2->rect.x + 7)
				{
					position.x -= 1;
					position.y += 1;
				}
				if (position.x >= c2->rect.x + 9)
				{
					position.x += 1;
					position.y += 1;
				}
				break;
			case SDL_SCANCODE_UP:
				position.y += speed;
				if (position.x + 16 <= c2->rect.x + 7)
				{
					position.x -= 1;
					position.y -= 1;
				}
				if (position.x >= c2->rect.x + 9)
				{
					position.x += 1;
					position.y -= 1;
				}
				break;
			 default:
				break;
		}
		
		c1->SetPos(position.x, position.y);


	}
	else if (c2->type == Collider::Type::WIN)
	{
		if (CollectedOrbs == false && lastKeyPressed == SDL_SCANCODE_UP)
		{
			position.y += speed;
			if (position.x + 16 <= c2->rect.x + 7)
			{
				position.x -= 1;
				position.y -= 1;
			}
			if (position.x >= c2->rect.x + 9)
			{
				position.x += 1;
				position.y -= 1;
			}
		}
		else
		{
			if (position.y <= c2->rect.y + 3)
			{
				currentState = PlayerState::WINING;
			}
		}
	}
	else if(c2->type == Collider::Type::BOUNDS){
		position = lastPos;
	}
	else if (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT || c2->type == Collider::Type::EXPLOSION)
	{
		currentState = PlayerState::DEAD;
	}
}

void ModulePlayer::Draw()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y - 8, &rect);
	}
}

