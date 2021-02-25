#pragma once

#include <SDL.h>

#include "Singleton.h"

#include "Debug.h"
#include "Video.h"

#include "../simple_types.h"

class Renderer2D : public Singleton<Renderer2D> {
	friend class Singleton<Renderer2D>;

private:
	Renderer2D();

	Video* m_Video;
public:
	~Renderer2D();

	// Implementar funciones de renderizado
};