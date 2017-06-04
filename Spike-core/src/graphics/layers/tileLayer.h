#pragma once

#include "layer.h"
#include "../2dbatchrenderer.h"

namespace spike { namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			virtual ~TileLayer();
		};

} }