#include "comradepch.h"
#include "Comrade/Renderer/Renderer2D.h"
#include "Comrade/Renderer/Render.h"

#include <glad/glad.h>

namespace Comrade
{
	bool Renderer2D::Init()
	{
		m_MaxQuadCount = 1000;
		m_MaxVertexCount = m_MaxQuadCount * 4;
		m_MaxIndexCount = m_MaxQuadCount * 6;
		m_MaxTextureCount = 32;

		MemoryScope<int[]> samplers(new int[m_MaxTextureCount]);
		for (int i = 0; i < m_MaxTextureCount; i++)
			samplers[i] = i;

		m_Shader = CreateRef<Shader>("Assets/Shaders/QuadVertex.glsl", "Assets/Shaders/QuadFragment.glsl");
		m_Shader->Bind();
		m_Shader->SetIntArray("u_Textures", samplers.get(), m_MaxTextureCount);

		m_QuadVertexArray = CreateRef<VertexArray>();
		m_QuadVertexArray->Bind();

		m_QuadVertexBuffer = CreateRef<VertexBuffer>(m_MaxVertexCount * sizeof(QuadVertex), GL_STATIC_DRAW);
		m_QuadVertexBuffer->Bind();
		m_QuadVertexBuffer->SetLayout({
			{"a_Position", 3, ShaderDataType::Float},
			{"a_Color", 4, ShaderDataType::Float},
			{"a_TextureUV", 2, ShaderDataType::Float},
			{"a_TextureID", 1, ShaderDataType::Float},
			});

		auto indices = GenerateIndices();
		m_QuadIndexBuffer = CreateRef<IndexBuffer>(indices.get(), m_MaxIndexCount, GL_STATIC_DRAW);
		m_QuadIndexBuffer->Bind();

		m_QuadVertexArray->AddVertexBuffer(m_QuadVertexBuffer);
		m_QuadVertexArray->SetIndexBuffer(m_QuadIndexBuffer);
	
		m_QuadTemplate = CreateCenteredQuad({ 1.0f, 1.0f, 1.0f, 1.0f });
		m_QuadVertices = CreateScope<QuadVertex[]>(m_MaxVertexCount);

		uint32_t blank = 0xffffffff;
		m_BlankTexture = CreateRef<Texture2D>(1, 1, 4);
		m_BlankTexture->SetBuffer(&blank);

		m_Textures = CreateScope<MemoryRef<Texture2D>[]>(m_MaxTextureCount);
		m_Textures[0] = m_BlankTexture;

		return m_Initialized = true;
	}

	void Renderer2D::Destroy()
	{
		if (m_Initialized)
		{
			m_Initialized = false;
		}
	}

	void Renderer2D::BeginRender()
	{
		m_Shader->Bind();
		m_Shader->SetMat4("u_ProjectionViewMatrix", glm::mat4(1.0f));
		m_QuadVertexIndex = 0;
		m_TextureIndex = 1;
	}

	void Renderer2D::BeginRender(const Camera& camera, const glm::mat4& transform)
	{
		glm::mat4 projectionView = camera.GetProjection() * glm::inverse(transform);
		m_Shader->Bind();
		m_Shader->SetMat4("u_ProjectionViewMatrix", projectionView);
		m_QuadVertexIndex = 0;
		m_TextureIndex = 1;
	}

	void Renderer2D::EndRender()
	{
		if (m_QuadVertexIndex)
		{
			m_QuadVertexBuffer->SetBuffer(m_QuadVertices.get(), m_QuadVertexIndex * sizeof(QuadVertex));

			for (uint32_t i = 0; i < m_TextureIndex; i++)
				m_Textures[i]->Bind(i);

			m_QuadVertexArray->Bind();
			Render::DrawIndexed(m_QuadVertexArray, (m_QuadVertexIndex / 4) * 6);

			m_RenderStats.DrawCallCount++;
		}
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		auto quad = m_QuadTemplate;
		for (int i = 0; i < 4; i++)
		{
			quad[i].Color = color;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		auto quad = CreateQuad(position, scale, color);
		for (uint32_t i = 0; i < 4; i++)
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::mat4& transform, const MemoryRef<Texture2D>& texture)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 0; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}

		auto quad = m_QuadTemplate;
		for (uint32_t i = 0; i < 4; i++)
		{
			quad[i].TextureID = texID;
			quad[i].Position = transform * glm::vec4({ quad[i].Position.x, quad[i].Position.y, quad[i].Position.z, 1.0f });
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];
		}

		m_RenderStats.QuadCount++;
	}

	void Renderer2D::RenderQuad(const glm::vec3& position, const glm::vec3& scale, const MemoryRef<Texture2D>& texture)
	{
		if (m_QuadVertexIndex >= m_MaxVertexCount)
			ResetBatch();

		float texID = 0.0f;
		for (uint32_t i = 0; i < m_TextureIndex; i++)
		{
			if (*texture == *m_Textures[i])
			{
				texID = i;
				break;
			}
		}

		if (!texID)
		{
			texID = m_TextureIndex;
			m_Textures[m_TextureIndex++] = texture;
		}
	
		auto quad = CreateQuad(position, scale, {1.0f, 1.0f, 1.0f, 1.0f}, texID);
		for (uint32_t i = 0; i < 4; i++)
			m_QuadVertices[m_QuadVertexIndex++] = quad[i];

		m_RenderStats.QuadCount++;
	}

	std::array<Renderer2D::QuadVertex, 4> Renderer2D::CreateQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, float texID)
	{
		float size = 1.0f;

		QuadVertex v0;
		v0.Position = position;
		v0.Color = color;
		v0.TextureUV = { 0.0f, 0.0f };
		v0.TextureID = texID;

		QuadVertex v1;
		v1.Position = { position.x + (size * scale.x), position.y, position.z };
		v1.Color = color;
		v1.TextureUV = { 1.0f, 0.0f };
		v1.TextureID = texID;

		QuadVertex v2;
		v2.Position = { position.x + (size * scale.x),  position.y + (size * scale.y), position.z, };
		v2.Color = color;
		v2.TextureUV = { 1.0f, 1.0f };
		v2.TextureID = texID;

		QuadVertex v3;
		v3.Position = { position.x,  position.y + (size * scale.y), position.z, };
		v3.Color = color;
		v3.TextureUV = { 0.0f, 1.0f };
		v3.TextureID = texID;

		return { v0, v1, v2, v3 };
	}

	std::array<Renderer2D::QuadVertex, 4> Renderer2D::CreateCenteredQuad(const glm::vec4& color, float texID)
	{
		QuadVertex v0;
		v0.Position = { -0.5f, -0.5f, 0.0f };
		v0.Color = color;
		v0.TextureUV = { 0.0f, 0.0f };
		v0.TextureID = texID;

		QuadVertex v1;
		v1.Position = { 0.5f, -0.5f, 0.0f };
		v1.Color = color;
		v1.TextureUV = { 1.0f, 0.0f };
		v1.TextureID = texID;

		QuadVertex v2;
		v2.Position = { 0.5f, 0.5f, 0.0f };
		v2.Color = color;
		v2.TextureUV = { 1.0f, 1.0f };
		v2.TextureID = texID;

		QuadVertex v3;
		v3.Position = { -0.5f, 0.5f, 0.0f };
		v3.Color = color;
		v3.TextureUV = { 0.0f, 1.0f };
		v3.TextureID = texID;

		return { v0, v1, v2, v3 };
	}

	MemoryRef<uint32_t[]> Renderer2D::GenerateIndices()
	{
		MemoryRef<uint32_t[]> indices(new uint32_t[m_MaxIndexCount]);

		uint32_t offset = 0;
		for (size_t i = 0; i < m_MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;
			offset += 4;
		}

		return indices;
	}

	void Renderer2D::ResetBatch()
	{
		EndRender();
		m_QuadVertexIndex = 0;
		m_TextureIndex = 1;
	}
}
