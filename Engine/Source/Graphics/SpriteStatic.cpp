#include "SpriteStatic.h"

namespace loft { namespace graphics {

	SpriteStatic::SpriteStatic(float x, float y, float width, float height, const math::Vector4& color, Shader& shader)
		: Renderable2D(math::Vector3(x, y, 0),math::Vector2(width, height), 0xffffff), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0
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
		m_IndexBuffer = new IndexBuffer(indecies, 6);
	}

	SpriteStatic::~SpriteStatic()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}



} }