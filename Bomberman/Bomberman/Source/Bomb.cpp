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



		break;


		case EXPLOSION:
			// una ves calculadas la +s lngitudes poner animacion explosion

		break;
	}
}

void Bomb::OnCollision(Collider* collider)
{

}
