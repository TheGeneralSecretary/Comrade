#include "comradepch.h"
#include "Comrade/Renderer/Renderer.h"
#include "Comrade/Renderer/Render.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <array>

namespace Comrade
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	std::array<QuadVertex, 4> CreateQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
	{
		float size = 1.0f;

		QuadVertex v0;
		v0.Position = position;
		v0.Color = color;

		QuadVertex v1;
		v1.Position = { position.x + (size * scale.x), position.y, position.z };
		v1.Color = color;

		QuadVertex v2;
		v2.Position = { position.x + (size * scale.x),  position.y + (size * scale.y), position.z, };
		v2.Color = color;

		QuadVertex v3;
		v3.Position = { position.x,  position.y + (size * scale.y), position.z, };
		v3.Color = color;

		return { v0, v1, v2, v3 };
	}

	Renderer::Renderer()
	{
		m_Shader = CreateRef<Shader>("Assets/Shaders/ColorVertex.glsl", "Assets/Shaders/ColorFragment.glsl");

		static auto vertices = CreateQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });

		static unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VertexArray = CreateRef<VertexArray>();
		m_VertexArray->Bind();

		m_VertexBuffer = CreateRef<VertexBuffer>(vertices.data(), vertices.size() * sizeof(QuadVertex), GL_STATIC_DRAW);
		m_VertexBuffer->Bind();

		m_VertexBuffer->SetLayout({
			{"a_Position", 3, ShaderDataType::Float},
			{"a_Color", 4, ShaderDataType::Float},
			});

		m_IndexBuffer = CreateRef<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]), GL_STATIC_DRAW);
		m_IndexBuffer->Bind();

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	void Renderer::RenderSample()
	{
		m_Shader->Bind();
		m_VertexArray->Bind();
		Render::DrawIndexed(m_VertexArray);
	}
}
