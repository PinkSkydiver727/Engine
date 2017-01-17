#pragma once
#include <deque>
#include "SpriteStatic.h"
#include "renderer2d.h"

namespace loft { namespace graphics {

	class SimpleRenderer2D : public Renderer2D
	{
	private:
		std::deque<const SpriteStatic*> m_RenderQueue;
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;

	};



}}