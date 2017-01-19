#pragma once
#include <glew.h>
#include <string>
#include <FreeImage.h>
#include "../Utilities/ImageLoader.h"
namespace loft { namespace graphics {

	class Texture
	{
	private:
		std::string m_Filename;
		GLuint m_TID;
		GLsizei m_Width, m_Height;
	public:
		Texture(const std::string& path);
		~Texture();

		void bind() const;
		void unbind() const;

		inline unsigned int getID() { return m_TID; };
		inline unsigned int getWidth() { return m_Width; };
		inline unsigned int getHeight() { return m_Height; };
	private:
		GLuint load();

	};

} }
