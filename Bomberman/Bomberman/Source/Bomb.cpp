#include "Bomb.h"

Bomb::Bomb(int x, int y):Enemy(x, y)
{

}

void Bomb::Update()
{
	switch (state) {
		case IDLE:
			// calculos de las 4 largadas
			



			// colliders


			// Animaciones
			// Idle anim
			idleAnim.PushBack({ 0,256,14,271 });
			idleAnim.PushBack({ 16,257,29,271 });
			idleAnim.PushBack({ 32,256,47,271 });
		

			// Que hace esto?
			idleAnim.loop = true;
			idleAnim.mustFlip = false;
			idleAnim.speed = 0.1f;


		break;


		case EXPLOSION:
			// una vez calculadas las lngitudes poner animacion explosion

			// Animacion centro explosion (SOLO IDA (como se hace ida y vuelta???))
			centerAnim.PushBack({ 0,288,15,303 });
			centerAnim.PushBack({ 16,288,31,303 });
			centerAnim.PushBack({ 32,288,47,303 });
			centerAnim.PushBack({ 48,288,63,303 });

			// Horizontal side explosion
			horSideAnim.PushBack({ 0,304,15,319 });
			horSideAnim.PushBack({ 16,304,31,319 });
			horSideAnim.PushBack({ 32,304,47,319 });
			horSideAnim.PushBack({ 48,304,63,319 });

			// Left extreme explosion
			leftExtrAnim.PushBack({ 0,320,15,335 });
			leftExtrAnim.PushBack({ 16,320,31,335 });
			leftExtrAnim.PushBack({ 32,320,47,335 });
			leftExtrAnim.PushBack({ 48,320,63,335 });

			// Right extreme explosion
			rightExtrAnim.PushBack({ 0,336,15,351 });
			rightExtrAnim.PushBack({ 16,336,31,351 });
			rightExtrAnim.PushBack({ 32,336,47,351 });
			rightExtrAnim.PushBack({ 48,336,63,351 });

			// Vertical side explosion
			vertSideAnim.PushBack({ 0,352,15,367 });
			vertSideAnim.PushBack({ 16,352,31,367 });
			vertSideAnim.PushBack({ 32,352,47,367 });
			vertSideAnim.PushBack({ 48,352,63,367 });

			// Up extreme explosion
			upExtrAnim.PushBack({ 0,368,15,383 });
			upExtrAnim.PushBack({ 16,368,31,383 });
			upExtrAnim.PushBack({ 32,368,47,383 });
			upExtrAnim.PushBack({ 48,368,63,383 });

			// Down extreme explosion
			downExtrAnim.PushBack({ 0,384,15,400 });
			downExtrAnim.PushBack({ 16,384,31,400 });
			downExtrAnim.PushBack({ 32,384,47,400 });
			downExtrAnim.PushBack({ 48,384,63,400 });

		break;
	}
}

void Bomb::OnCollision(Collider* collider)
{

}
