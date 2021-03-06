#include "Sprite.h"

namespace loft { namespace graphics {

	Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
		: Renderable2D(math::Vector3(x, y, 0),math::Vector2(width, height), color), position(m_Position)
	{

	}


	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(math::Vector3(x, y, 0), math::Vector2(width, height),0xffffffff), position(m_Position)
	{
		m_Texture = texture;
	}





} }