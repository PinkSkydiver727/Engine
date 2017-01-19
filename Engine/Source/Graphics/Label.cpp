#include "Label.h"

namespace loft { namespace graphics {

	Label::Label(std::string text, float x, float y, unsigned int color)
		: Renderable2D(), m_Text(text)
	{
		m_Position = math::Vector3(x, y, 0.0f);
		m_Color = color;
	}

	void Label::submit(Renderer2D* renderer)
	{
		renderer->drawString(m_Text, m_Position, m_Color);
	}

} }