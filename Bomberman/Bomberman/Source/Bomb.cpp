#include "Bomb.h"
#include "Application.h"
#include "ModuleRender.h"

Bomb::Bomb(int x, int y):Enemy(x, y)
{
	idleAnim.PushBack({ 0,256,16,16 });
	idleAnim.PushBack({ 16,256,16,16 });
	idleAnim.PushBack({ 32,256,16,16 });
	idleAnim.loop = true;
	idleAnim.pingpong = true;
	idleAnim.speed = 0.1f;

	// Animacion centro explosion (SOLO IDA (como se hace ida y vuelta???))
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
	rightExtrAnim.PushBack({ 0,336,15,351 });
	rightExtrAnim.PushBack({ 16,336,31,351 });
	rightExtrAnim.PushBack({ 32,336,47,351 });
	rightExtrAnim.PushBack({ 48,336,63,351 });
	rightExtrAnim.loop = true;
	rightExtrAnim.pingpong = true;
	rightExtrAnim.speed = 0.1f;

	// Vertical side explosion
	vertSideAnim.PushBack({ 0,352,15,367 });
	vertSideAnim.PushBack({ 16,352,31,367 });
	vertSideAnim.PushBack({ 32,352,47,367 });
	vertSideAnim.PushBack({ 48,352,63,367 });
	vertSideAnim.loop = true;
	vertSideAnim.pingpong = true;
	vertSideAnim.speed = 0.1f;

	// Up extreme explosion
	upExtrAnim.PushBack({ 0,368,15,383 });
	upExtrAnim.PushBack({ 16,368,31,383 });
	upExtrAnim.PushBack({ 32,368,47,383 });
	upExtrAnim.PushBack({ 48,368,63,383 });
	upExtrAnim.loop = true;
	upExtrAnim.pingpong = true;
	upExtrAnim.speed = 0.1f;

	// Down extreme explosion
	downExtrAnim.PushBack({ 0,384,15,400 });
	downExtrAnim.PushBack({ 16,384,31,400 });
	downExtrAnim.PushBack({ 32,384,47,400 });
	downExtrAnim.PushBack({ 48,384,63,400 });
	downExtrAnim.loop = true;
	downExtrAnim.pingpong = true;
	downExtrAnim.speed = 0.1f;

	state = IDLE;

	currentAnim = &idleAnim;
	frameSpawn = App->frameCounter;
}

void Bomb::Update()
{
	Enemy::Update();
	switch (state) {
		case IDLE:
			// calculos de las 4 largadas
			if (App->frameCounter - frameSpawn >= 9) {
				state = EXPLOSION;
			}
			// colliders


			// Animaciones
			// Idle anim
			


		break;


		case EXPLOSION:
			// una vez calculadas las lngitudes poner animacion explosion

			

		break;
	}
}

void Bomb::OnCollision(Collider* collider)
{

}
