#include "Layer.h"

namespace loft { namespace graphics {

	Layer::Layer()
	{
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->disable();
	}

	Layer::Layer(Renderer2D* renderer, Shader* shader, math::Matrix4 projectionMatrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->disable();
	}

	Layer::~Layer()
	{
		delete m_Shader;
		delete m_Renderer;

		for (int i = 0; i < m_Renderables.size(); i++)
		{
			delete m_Renderables[i];
		}
	}
	void Layer::add(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::render()
	{
		m_Shader->enable();
		m_Renderer->begin();
		m_Renderer->push(math::Matrix4::translation(Vector3(1, 1, 0)));
		for (Renderable2D* renderable : m_Renderables)
		{
			renderable->submit(m_Renderer);
		}
		m_Renderer->pop();
		m_Renderer->end();
		m_Renderer->flush();
	}

} }