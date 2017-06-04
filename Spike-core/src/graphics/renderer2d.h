#pragma once

#include "glew.h"
#include "../maths/maths.h"
#include "renderable2d.h"

namespace spike { namespace graphics {

	class Renderer2D
	{
	public:
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void begin() {}
		virtual void end() {}
		virtual void flush() = 0;
	};
} }