#pragma once
#include <glew.h>
#include "../Math/math.h"
namespace loft { namespace graphics {
	
	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char *m_VertPath, *m_FragPath;
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, math::Vector2 vector);
		void setUniform3f(const GLchar* name, math::Vector3 vector);
		void setUniform4f(const GLchar* name, math::Vector4 vector);
		void setUniformMat4(const GLchar* name, const math::Matrix4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLint getUniformLocation(const GLchar* name);
		GLuint load();
	};


} }