#include "Sprite.h"

namespace loft { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, const math::Vector4& color)
		: Renderable2D(math::Vector3(x, y, 0),math::Vector2(width, height), color)
	{

	}





} }