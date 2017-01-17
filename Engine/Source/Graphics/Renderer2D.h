#pragma once
#include "../Math/math.h"
#include <glew.h>
#include <vector>


namespace loft { namespace graphics {

	class Renderable2D;
	class Renderer2D
	{
	protected:
		std::vector<math::Matrix4> m_TransformationStack;
		const math::Matrix4* m_TransformationBack;
	protected:
		Renderer2D()
		{
			m_TransformationStack.push_back(math::Matrix4::identity());
			m_TransformationBack = &m_TransformationStack.back();
		}

	public:
		void push(math::Matrix4& matrix, bool override = false)
		{
			if (override)
			{
				m_TransformationStack.push_back(matrix);
			}
			else
			{
				m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
			}
			m_TransformationBack = &m_TransformationStack.back();
		}

		void pop()
		{
			if (m_TransformationStack.size() > 1)
			{
				m_TransformationStack.pop_back();
			}

			m_TransformationBack = &m_TransformationStack.back();

		}


		virtual void begin() {};
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void flush() = 0;
		virtual void end() {};
	
	};



} }