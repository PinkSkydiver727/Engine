#pragma once

#pragma once
#include "Renderable2D.h"

namespace loft { namespace graphics {

	class Sprite : public Renderable2D
	{
	private:

	public:
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};
} }
