#include "..\headers\Renderer2D.h"

#include "..\headers\Video.h"

namespace EM {

	Renderer2D::Renderer2D() {
		m_TexColorShader = new Shader();
		m_TexColorShader->init("../Assets/Resources/Shaders/texcolorShader");

		m_TCSTextureLocation = m_TexColorShader->getUniformLocation("u_Texture");

		m_ColorShader = new Shader();
		m_ColorShader->init("../Assets/Resources/Shaders/colorShader");

		m_CSColorLocation = m_ColorShader->getUniformLocation("u_Color");
		m_CSModelLocation = m_ColorShader->getUniformLocation("u_Model");

		float vertices[] = {
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int indexes[] = {
			0, 1, 3,
			1, 2, 3
		};

		uint32 VBO, EBO;

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &m_VAO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	Renderer2D::~Renderer2D()
	{
		m_TexColorShader->Delete();
		delete m_TexColorShader;
	}

	void Renderer2D::RenderQuad(SDL_Rect rect, uint32 texture)
	{
		m_TexColorShader->Use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer2D::RenderQuad(SDL_Rect rect, Color color) {
		m_ColorShader->Use();

		m_ColorShader->setUniform(m_CSColorLocation, glm::vec4(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f, color.alpha / 255.0f));

		Video* video = Video::getInstance();

		Vector2i screen_pos = { rect.x, rect.y };
		Vector2f screen_pos_gl = video->screenPosToGl(screen_pos);

		Vector2i screen_scale = { rect.w, rect.h };
		Vector2f screen_scale_gl = video->screenSizeToGl(screen_scale);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(screen_pos_gl.x, screen_pos_gl.y, 0.0f));
		model = glm::scale(model, glm::vec3(screen_scale_gl.x, screen_scale_gl.y, 0.0f));

		m_ColorShader->setUniform(m_CSModelLocation, model);

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}