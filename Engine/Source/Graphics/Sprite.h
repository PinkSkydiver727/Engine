#pragma once

#pragma once
#include "Renderable2D.h"

namespace loft { namespace graphics {

	class Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(float x, float y, float width, float height, const math::Vector4& color);
	};
} }
