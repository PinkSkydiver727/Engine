#pragma once
#include "../Renderable2D.h"
namespace loft { namespace graphics {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		math::Matrix4 m_Transformations;
	public:
		Group(const math::Matrix4& transform);
		~Group();
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer) override;
	};
} }