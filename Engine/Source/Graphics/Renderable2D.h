#pragma once

#include "Renderer2D.h"
#include "Buffers/Buffer.h"
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexArray.h"
#include "../Math/math.h"
#include "Shader.h"

namespace loft { namespace graphics {
	using namespace math;

	struct VertexData
	{
		Vector3 vertex;
		//Vector4 color;
		unsigned int color;
	};


	class Renderable2D
	{
	protected:
		Vector3 m_Position;
		Vector2 m_Size;
		Vector4 m_Color;
	protected:
		Renderable2D() {};
	public:
		Renderable2D(Vector3 position, Vector2 size, Vector4 color)
			:	m_Position(position), m_Size(size), m_Color(color)
		{
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

		inline const Vector3& getPosition() const { return m_Position; };
		inline const Vector2& getSize() const { return m_Size; };
		inline const Vector4& getColor() const { return m_Color; };
	};

} }