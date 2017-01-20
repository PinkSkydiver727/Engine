#pragma once
#include "../Renderable2D.h"
#include "../Renderer2D.h"
namespace loft { namespace graphics {

	class Layer
	{
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		math::Matrix4 m_ProjectionMatrix;
	public:
		Layer();
	public:
		Layer(Renderer2D* renderer, Shader* shader, math::Matrix4 projectionMatrix);
		virtual ~Layer();
		virtual void add(Renderable2D* renderable);
		virtual void render();

	};

} }