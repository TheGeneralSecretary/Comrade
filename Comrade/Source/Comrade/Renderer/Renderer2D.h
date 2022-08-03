#pragma once

#include "Comrade/Utils/Memory.h"
#include "Comrade/Renderer/Shader.h"
#include "Comrade/Renderer/VertexArray.h"
#include "Comrade/Renderer/VertexBuffer.h"
#include "Comrade/Renderer/IndexBuffer.h"
#include "Comrade/Renderer/Texture.h"
#include "Comrade/Renderer/Camera.h"

#include <glm/glm.hpp>
#include <array>

namespace Comrade
{
	struct RenderStats
	{
		uint32_t DrawCallCount = 0;
		uint32_t QuadCount = 0;
		uint32_t GetVertexCount() const { return QuadCount * 4; }
		uint32_t GetIndexCount() const { return QuadCount * 6; }
	};

	class Renderer2D
	{
	public:
		bool Init();
		void Destroy();

		void BeginRender();
		void BeginRender(const Camera& camera, const glm::mat4& transform);
		void EndRender();

		void RenderQuad(const glm::mat4& transform, const glm::vec4& color);
		void RenderQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);

		void RenderQuad(const glm::mat4& transform, const MemoryRef<Texture2D>& texture);
		void RenderQuad(const glm::vec3& position, const glm::vec3& scale, const MemoryRef<Texture2D>& texture);

		inline RenderStats GetRenderStats() const { return m_RenderStats; }
		inline void ResetRenderStats() { memset(&m_RenderStats, 0, sizeof(RenderStats)); }

	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TextureUV;
			float TextureID;
		};

		std::array<QuadVertex, 4> CreateQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, float texID = 0.0f);
		std::array<QuadVertex, 4> CreateCenteredQuad(const glm::vec4& color, float texID = 0.0f);
		MemoryRef<uint32_t[]> GenerateIndices();
		void ResetBatch();

	private:
		bool m_Initialized = false;

		uint32_t m_MaxQuadCount;
		uint32_t m_MaxVertexCount;
		uint32_t m_MaxIndexCount;
		uint32_t m_MaxTextureCount;

		std::array<QuadVertex, 4> m_QuadTemplate;
		MemoryScope<QuadVertex[]> m_QuadVertices;
		uint32_t m_QuadVertexIndex;

		MemoryRef<Shader> m_Shader;
		MemoryRef<VertexArray> m_QuadVertexArray;
		MemoryRef<VertexBuffer> m_QuadVertexBuffer;
		MemoryRef<IndexBuffer> m_QuadIndexBuffer;

		MemoryRef<Texture2D> m_BlankTexture;
		MemoryScope<MemoryRef<Texture2D>[]> m_Textures;
		uint32_t m_TextureIndex;

		RenderStats m_RenderStats;
	};
}
