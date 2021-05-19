#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/entities.png");

	// Animacion centro explosion (SOLO IDA (como se hace ida y vuelta???))
	centerExplosion.anim.PushBack({ 0,288,16,16 });
	centerExplosion.anim.PushBack({ 16,288,16,16 });
	centerExplosion.anim.PushBack({ 32,288,16,16 });
	centerExplosion.anim.PushBack({ 48,288,16,16 });
	centerExplosion.anim.loop = true;
	centerExplosion.anim.pingpong = true;
	centerExplosion.anim.speed = 0.1f;

	// Horizontal side explosion
	horizontalExplosion.anim.PushBack({ 0,304,16,16 });
	horizontalExplosion.anim.PushBack({ 16,304,16,16 });
	horizontalExplosion.anim.PushBack({ 32,304,16,16 });
	horizontalExplosion.anim.PushBack({ 48,304,16,16 });
	horizontalExplosion.anim.loop = true;
	horizontalExplosion.anim.pingpong = true;
	horizontalExplosion.anim.speed = 0.1f;

	// Left extreme explosion
	endLeftExp.anim.PushBack({ 0,320,16,16 });
	endLeftExp.anim.PushBack({ 16,320,16,16 });
	endLeftExp.anim.PushBack({ 32,320,16,16 });
	endLeftExp.anim.PushBack({ 48,320,16,16 });
	endLeftExp.anim.loop = true;
	endLeftExp.anim.pingpong = true;
	endLeftExp.anim.speed = 0.1f;

	// Right extreme explosion
	endRightExp.anim.PushBack({ 0,336,16,16 });
	endRightExp.anim.PushBack({ 16,336,16,16 });
	endRightExp.anim.PushBack({ 32,336,16,16 });
	endRightExp.anim.PushBack({ 48,336,16,16 });
	endRightExp.anim.loop = true;
	endRightExp.anim.pingpong = true;
	endRightExp.anim.speed = 0.1f;

	// Vertical side explosion
	verticalExplosion.anim.PushBack({ 0,352,16,16 });
	verticalExplosion.anim.PushBack({ 16,352,16,16 });
	verticalExplosion.anim.PushBack({ 32,352,16,16 });
	verticalExplosion.anim.PushBack({ 48,352,16,16 });
	verticalExplosion.anim.loop = true;
	verticalExplosion.anim.pingpong = true;
	verticalExplosion.anim.speed = 0.1f;

	// Up extreme explosion
	endUpExp.anim.PushBack({ 0,368,16,16 });
	endUpExp.anim.PushBack({ 16,368,16,16 });
	endUpExp.anim.PushBack({ 32,368,16,16 });
	endUpExp.anim.PushBack({ 48,368,16,16 });
	endUpExp.anim.loop = true;
	endUpExp.anim.pingpong = true;
	endUpExp.anim.speed = 0.1f;

	// Down extreme explosion
	endDowExp.anim.PushBack({ 0,384,16,16 });
	endDowExp.anim.PushBack({ 16,384,16,16 });
	endDowExp.anim.PushBack({ 32,384,16,16 });
	endDowExp.anim.PushBack({ 48,384,16,16 });
	endDowExp.anim.loop = true;
	endDowExp.anim.pingpong = true;
	endDowExp.anim.speed = 0.1f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}