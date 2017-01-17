#pragma once
#include "Renderable2D.h"

namespace loft { namespace graphics {

	class SpriteStatic : public Renderable2D
	{
	private:
		Shader& m_Shader;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
	public:
		SpriteStatic(float x, float y, float width, float height, const math::Vector4& color, Shader& shader);
		~SpriteStatic();

		inline const VertexArray* getVAO() const { return m_VertexArray; };
		inline const IndexBuffer* getIBO() const { return m_IndexBuffer; };

		inline Shader& getShader() const { return m_Shader; };

	};
} }
