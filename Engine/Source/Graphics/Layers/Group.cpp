#include "Group.h"

namespace loft{ namespace graphics {

	Group::Group(const math::Matrix4& transform)
		:m_Transformations(transform)
	{

	}

	Group::~Group()
	{
		for (int i = 0; i < m_Renderables.size(); i++)
		{
			delete m_Renderables[i];
		}
	}

	void Group::add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) 
	{
		renderer->push(m_Transformations);
		for (Renderable2D* renderable : m_Renderables)
		{
			renderable->submit(renderer);
		}
		renderer->pop();
	}


} }