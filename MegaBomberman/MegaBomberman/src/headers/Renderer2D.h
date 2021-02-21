#pragma once

#include "../Core.h"

#include "Singleton.h"

#include "Debug.h"

#include "../simple_types.h"

#include "utilities/Shader.h"
#include "utilities/Color.h"

#include "utilities/gui/Texture.h"

#include <SDL.h>

namespace EM {
	class EM_API Renderer2D : public Singleton<Renderer2D> {
		friend class Singleton<Renderer2D>;

	private:
		Renderer2D();

		uint32 m_VAO;

		Shader* m_TexColorShader;
		Shader* m_ColorShader;

		// TexColorShader Uniform locations
		uint32 m_TCSTextureLocation;

		// Uniform locations
		uint32 m_CSColorLocation;
		uint32 m_CSModelLocation;
	public:
		~Renderer2D();

		void RenderQuad(SDL_Rect rect, uint32 texture);
		void RenderQuad(SDL_Rect rect, Color color);
	};
}