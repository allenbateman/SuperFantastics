#include "Bomb.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"
#include "ModuleCollisions.h"
#include "p2Point.h"

Bomb::Bomb(int x, int y):Entity(x, y)
{
	int diffX = (x - 24) % 16;
	int diffY = (y - 32) % 16;

	if (diffX > 8)
	{
		position.x += 16;
	}

	position.x -= diffX;

	if (diffY > 8)
	{
		position.y += 16;
	}

	position.y -= diffY;

	idleAnim.PushBack({ 0,256,16,16 });
	idleAnim.PushBack({ 16,256,16,16 });
	idleAnim.PushBack({ 32,256,16,16 });
	idleAnim.loop = true;
	idleAnim.pingpong = true;
	idleAnim.speed = 0.1f;

	// Animacion centro explosion
	centerAnim.PushBack({ 0,288,16,16 });
	centerAnim.PushBack({ 16,288,16,16 });
	centerAnim.PushBack({ 32,288,16,16 });
	centerAnim.PushBack({ 48,288,16,16 });
	centerAnim.loop = true;
	centerAnim.pingpong = true;
	centerAnim.speed = 0.1f;

	// Horizontal side explosion
	horSideAnim.PushBack({ 0,304,16,16 });
	horSideAnim.PushBack({ 16,304,16,16 });
	horSideAnim.PushBack({ 32,304,16,16 });
	horSideAnim.PushBack({ 48,304,16,16 });
	horSideAnim.loop = true;
	horSideAnim.pingpong = true;
	horSideAnim.speed = 0.1f;

	// Left extreme explosion
	leftExtrAnim.PushBack({ 0,320,16,16 });
	leftExtrAnim.PushBack({ 16,320,16,16 });
	leftExtrAnim.PushBack({ 32,320,16,16 });
	leftExtrAnim.PushBack({ 48,320,16,16 });
	leftExtrAnim.loop = true;
	leftExtrAnim.pingpong = true;
	leftExtrAnim.speed = 0.1f;

	// Right extreme explosion
	rightExtrAnim.PushBack({ 0,336,16,16 });
	rightExtrAnim.PushBack({ 16,336,16,16 });
	rightExtrAnim.PushBack({ 32,336,16,16 });
	rightExtrAnim.PushBack({ 48,336,16,16 });
	rightExtrAnim.loop = true;
	rightExtrAnim.pingpong = true;
	rightExtrAnim.speed = 0.1f;

	// Vertical side explosion
	vertSideAnim.PushBack({ 0,352,16,16 });
	vertSideAnim.PushBack({ 16,352,16,16 });
	vertSideAnim.PushBack({ 32,352,16,16 });
	vertSideAnim.PushBack({ 48,352,16,16 });
	vertSideAnim.loop = true;
	vertSideAnim.pingpong = true;
	vertSideAnim.speed = 0.1f;

	// Up extreme explosion
	upExtrAnim.PushBack({ 0,368,16,16 });
	upExtrAnim.PushBack({ 16,368,16,16 });
	upExtrAnim.PushBack({ 32,368,16,16 });
	upExtrAnim.PushBack({ 48,368,16,16 });
	upExtrAnim.loop = true;
	upExtrAnim.pingpong = true;
	upExtrAnim.speed = 0.1f;

	// Down extreme explosion
	downExtrAnim.PushBack({ 0,384,16,16 });
	downExtrAnim.PushBack({ 16,384,16,16 });
	downExtrAnim.PushBack({ 32,384,16,16 });
	downExtrAnim.PushBack({ 48,384,16,16 });
	downExtrAnim.loop = true;
	downExtrAnim.pingpong = true;
	downExtrAnim.speed = 0.1f;

	state = IDLE;

	currentAnim = &idleAnim;
	frameSpawn = App->frameCounter;
	collider = nullptr;
}

void Bomb::Update()
{
	Entity::Update();

	iPoint diff;
	frameCounter++;

	switch (state) {
	case IDLE:

		idleAnim.Update();

		diff.x = App->player->position.x - position.x;
		diff.y = App->player->position.y - position.y;
		if (diff.x < 0) diff.x *= -1;
		if (diff.y < 0) diff.y *= -1;

		// TODO: START SOUND

		if (collider!=nullptr) {
			if (diff.x >= 16 && diff.y >= 16)
			{
				collider = App->collisions->AddCollider({ 0,0,16,16 }, Collider::WALL);
			}
		}
		if (collider != nullptr) collider->SetPos(position.x, position.y);

		if (frameCounter > 120) state = EXPLOSION;

		
		lastVal = collidingCounter;
			
		break;

	case EXPLOSION:
		if(collider!=nullptr) collider->pendingToDelete = true;
		currentAnim = nullptr;

		if (withColliders == false) {
			withColliders = true;
			// initialize all particles
			int range = App->player->rangeExplosion;

			// CENTER
			int index = ChooseArrayIndex();
			colliderList[index] = App->collisions->AddCollider({ 0,0,16,16 }, Collider::EXPLOSION);
			colliderList[index]->SetPos(position.x, position.y);
			particle[index].type = CENTER;
			particle[index].x = position.x;
			particle[index].y = position.y;

			// UP
			for (int i = 0; i < range; i++) {
				if (((position.y - 32) / 16) - (i + 1) >= 0) {
					if (App->sceneLevel1->GetGridType(position.y, position.x, i - 1, 0) == SceneLevel1::STRUCTURE ||
						App->sceneLevel1->GetGridType(position.y, position.x, i - 1, 0) == SceneLevel1::ROCK) {
						break;
					}

					index = ChooseArrayIndex();
					colliderList[index] = App->collisions->AddCollider({ 0,0,16,16 }, Collider::EXPLOSION);
					colliderList[index]->SetPos(position.x, position.y - (i * 16 + 16));
					if (i == range - 1) particle[index].type = END_UP;
					else particle[index].type = VERTICAL;
					particle[index].x = position.x;
					particle[index].y = position.y - (i * 16 + 16);

					if (App->sceneLevel1->GetGridType(position.y, position.x, i - 1, 0) != SceneLevel1::EMPTY)
						break;
				}
			}

			// DOWN
			for (int i = 0; i < range; i++) {
				if (((position.y - 32) / 16) + (i + 1) <= 10) {
					if (App->sceneLevel1->GetGridType(position.y, position.x, i + 1, 0) == SceneLevel1::STRUCTURE ||
						App->sceneLevel1->GetGridType(position.y, position.x, i + 1, 0) == SceneLevel1::ROCK) {
						break;
					}

					index = ChooseArrayIndex();
					colliderList[index] = App->collisions->AddCollider({ 0,0,16,16 }, Collider::EXPLOSION);
					colliderList[index]->SetPos(position.x, position.y + (i * 16 + 16));
					if (i == range - 1) particle[index].type = END_DOWN;
					else particle[index].type = VERTICAL;
					particle[index].x = position.x;
					particle[index].y = position.y + (i * 16 + 16);

					if (App->sceneLevel1->GetGridType(position.y, position.x, i + 1, 0) != SceneLevel1::EMPTY)
						break;
				}
			}

			// LEFT
			for (int i = 0; i < range; i++) {
				if (((position.x - 24) / 16) - (i + 1) >= 0) {
					if (App->sceneLevel1->GetGridType(position.y, position.x, 0, i - 1) == SceneLevel1::STRUCTURE ||
						App->sceneLevel1->GetGridType(position.y, position.x, 0, i - 1) == SceneLevel1::ROCK) {
						break;
					}

					index = ChooseArrayIndex();
					colliderList[index] = App->collisions->AddCollider({ 0,0,16,16 }, Collider::EXPLOSION);
					colliderList[index]->SetPos(position.x - (i * 16 + 16), position.y);
					if (i == range - 1) particle[index].type = END_LEFT;
					else particle[index].type = HORIZONTAL;
					particle[index].x = position.x - (i * 16 + 16);
					particle[index].y = position.y;

					if (App->sceneLevel1->GetGridType(position.y, position.x, 0, i - 1) != SceneLevel1::EMPTY)
						break;
				}
			}

			// RIGHT
			for (int i = 0; i < range; i++) {
				if (((position.x - 24) / 16) + (i + 1) <= 12) {
					if (App->sceneLevel1->GetGridType(position.y, position.x, 0, i + 1) == SceneLevel1::STRUCTURE ||
						App->sceneLevel1->GetGridType(position.y, position.x, 0, i + 1) == SceneLevel1::ROCK) {
						break;
					}

					index = ChooseArrayIndex();
					colliderList[index] = App->collisions->AddCollider({ 0,0,16,16 }, Collider::EXPLOSION);
					colliderList[index]->SetPos(position.x + (i * 16 + 16), position.y);
					if (i == range - 1) particle[index].type = END_RIGHT;
					else particle[index].type = HORIZONTAL;
					particle[index].x = position.x + (i * 16 + 16);
					particle[index].y = position.y;

					if (App->sceneLevel1->GetGridType(position.y, position.x, 0, i + 1) != SceneLevel1::EMPTY)
						break;
				}
			}
		}
		else {
			centerAnim.Update();
			vertSideAnim.Update();
			upExtrAnim.Update();
			downExtrAnim.Update();
			horSideAnim.Update();
			leftExtrAnim.Update();
			rightExtrAnim.Update();
		}
		if (frameCounter>150)SetToDelete();
		state = EXPLOSION;
		break;
	/*case EXPLOSION:
		if (frameCounter > 240) SetToDelete();
		break;*/
	}
}


int Bomb::ChooseArrayIndex() {
	int res = 0;
	for (int i = 0; i != MAX_BOMB_COLLIDERS; i++) {
		res = i;
		if (colliderList[i] == nullptr) break;
	}
	return res;
}

void Bomb::Draw()
{
	SDL_Rect rect;
	switch (state)
	{
	case IDLE:
		rect = idleAnim.GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);

		break;
	case EXPLOSION:
		//draw bomb here
		for (int i = 0; i != MAX_BOMB_COLLIDERS; i++) {

			if (particle[i].type != NONE) {

				switch (particle[i].type)
				{
				case CENTER:
					rect = centerAnim.GetCurrentFrame();
					break;
				case VERTICAL:
					rect = vertSideAnim.GetCurrentFrame();
					break;
				case END_UP:
					rect = upExtrAnim.GetCurrentFrame();
					break;
				case END_DOWN:
					rect = downExtrAnim.GetCurrentFrame();
					break;
				case HORIZONTAL:
					rect = horSideAnim.GetCurrentFrame();
					break;
				case END_LEFT:
					rect = leftExtrAnim.GetCurrentFrame();
					break;
				case END_RIGHT:
					rect = rightExtrAnim.GetCurrentFrame();
					break;
				}
				App->render->Blit(texture, particle[i].x, particle[i].y, &rect);
			}
			
		}
		
		break;
	}
	
}


void Bomb::OnCollision(Collider* collider)
{

}

void Bomb::SetToDelete()
{
	//currentAnim = nullptr;
	pendingToDelete = true;
	
	for (int i = 0; i != MAX_BOMB_COLLIDERS; i++) {
		if (colliderList[i] != nullptr) colliderList[i]->pendingToDelete = true;
		colliderList[i] = nullptr;
	}
	
}


