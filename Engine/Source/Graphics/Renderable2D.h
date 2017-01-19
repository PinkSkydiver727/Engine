#pragma once

#include "Renderer2D.h"
#include "Buffers/Buffer.h"
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexArray.h"
#include "../Math/math.h"
#include "Shader.h"
#include "Texture.h"

namespace loft { namespace graphics {
	using namespace math;

	struct VertexData
	{
		Vector3 vertex;
		//Vector4 color;

		Vector2 uv;
		float texID;
		unsigned int color;
	};


	class Renderable2D
	{
	protected:
		Vector3 m_Position;
		Vector2 m_Size;
		unsigned int m_Color;
		std::vector<Vector2> m_UV;
		Texture* m_Texture;

	protected:
		Renderable2D() 
			: m_Texture(nullptr)
		{
			setUVDefaults();
		};
	public:
		Renderable2D(Vector3 position, Vector2 size, unsigned int color)
			:	m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
		{
			setUVDefaults();
			/*m_VertexArray = new VertexArray();
			GLfloat vertices[] =
			{
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};

			GLfloat colors[]
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indecies[] = { 0, 1, 2, 2, 3, 0 };
			m_IndexBuffer = new IndexBuffer(indecies, 6); */
		}

		virtual ~Renderable2D()
		{
			//delete m_VertexArray;
			//delete m_IndexBuffer;
		}

		virtual void submit(Renderer2D* renderer)
		{
			renderer->submit(this);
		}

		void setColor(unsigned int color)
		{

		}

		void setColor(const math::Vector4& color)
		{
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			m_Color = (a << 24 | b << 16 | g << 8 | r);
		}

		inline const Vector3& getPosition() const { return m_Position; };
		inline const Vector2& getSize() const { return m_Size; };
		inline const unsigned int getColor() const { return m_Color; };
		inline const std::vector<Vector2>& getUV() const { return m_UV; };

		inline const GLuint getTextureID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); };

	private:
		void setUVDefaults()
		{
			m_UV.push_back(Vector2(0, 0));
			m_UV.push_back(Vector2(0, 1));
			m_UV.push_back(Vector2(1, 1));
			m_UV.push_back(Vector2(1, 0));
		}

	};

} }