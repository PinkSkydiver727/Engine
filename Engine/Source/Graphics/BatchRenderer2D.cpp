#include "BatchRenderer2d.h"


namespace loft { namespace graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	void BatchRenderer2D::init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//Enable vertex atributes
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		//Set up pointers to vertex attributes 

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::texID)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::color)));
		
		//unbind buffer
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		//populate index buffer
		GLushort indices[RENDERER_INDICES_SIZE];
		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
		{
			indices[i	 ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			
			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		glBindVertexArray(0);
	}
	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{
		//submit 4 new vetecies into the buffer each time a sprite is submitted. 
		//assign each vertecies position, textcoords and color or texture 

		const math::Vector3& position = renderable->getPosition();
		const math::Vector2& size = renderable->getSize();
		const unsigned int color = renderable->getColor();
		const std::vector<math::Vector2>& uv = renderable->getUV();
		const GLuint tid = renderable->getTextureID();

		float texSample = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			// search for texture id 
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
				{
					//save samplers
					texSample = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found) // Need to update texture slots
			{
				if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES) // too many active textures
				{
					end(); // unmap buffer
					flush(); // should update texture slots
					begin(); // restart rendering
				}
				m_TextureSlots.push_back(tid);
				texSample = (float)(m_TextureSlots.size());
			}
		}

		m_Buffer->vertex = *m_TransformationBack * position;
		m_Buffer->uv = uv[0];
		m_Buffer->texID = texSample;
		m_Buffer->color = color;			   
		m_Buffer++;						   
										   
		m_Buffer->vertex = *m_TransformationBack * math::Vector3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[1];
		m_Buffer->texID = texSample;
		m_Buffer->color = color;
		m_Buffer++;						   
										   
		m_Buffer->vertex = *m_TransformationBack * math::Vector3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[2];
		m_Buffer->texID = texSample;
		m_Buffer->color = color;
		m_Buffer++;						   
										   
		m_Buffer->vertex = *m_TransformationBack * math::Vector3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uv[3];
		m_Buffer->texID = texSample;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;

	}

	void BatchRenderer2D::drawString(const std::string& text, const math::Vector3 position, unsigned int color)
	{
		//TODO text rendering
	}

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		glBindVertexArray(m_VAO);
		m_IBO->bind();
		//render everything mapped
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		//reset index count after everything is rendered
		m_IndexCount = 0;

		m_TextureSlots.clear();

	}

	

}	}