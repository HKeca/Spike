#include "tileLayer.h"


namespace spike { namespace graphics {

	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0, 16.0, -9.0f, 9.0f, -1.0, 1.0f))
	{
	}

	TileLayer::~TileLayer()
	{
	}

} }