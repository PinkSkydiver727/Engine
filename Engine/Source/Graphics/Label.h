#pragma once
#include "Renderable2D.h"

namespace loft { namespace graphics {

	class Label : public Renderable2D
	{
		std::string m_Text;
	public:
		Label(std::string text, float x, float y, unsigned int color);

		void  submit(Renderer2D* renderer) override;

	};

} }