#include "Texture.h"

namespace loft { namespace graphics {


	Texture::Texture(const std::string& filename)
		: m_Filename(filename)
	{
		m_TID = load();
	}
	Texture::~Texture()
	{

	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID );
	}
	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	GLuint Texture::load()
	{
		BYTE* pixels = load_image(m_Filename.c_str(), &m_Width, &m_Height);

	}


} }
