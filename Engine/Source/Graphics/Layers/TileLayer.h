#pragma once
#include "Layer.h"
#include "../BatchRenderer2d.h"

namespace loft {namespace graphics {

		class TileLayer : public Layer
		{

		public:
			TileLayer(Shader* shader);
			~TileLayer();


		};

} }
