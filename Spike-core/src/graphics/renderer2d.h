#pragma once

#include "glew.h"
#include "../maths/maths.h"
#include "renderable2d.h"

namespace spike { namespace graphics {

	class Renderer2D
	{
	protected:
		std::vector<maths::mat4> m_TranformationStack;
		const maths::mat4* m_TransformationBack;
	protected:
		Renderer2D()
		{
			m_TranformationStack.push_back(maths::mat4::identity());
			m_TransformationBack = &m_TranformationStack.back();
		}
	public:

		void push(const maths::mat4& matrix, bool override = false)
		{
			if (override)
				m_TranformationStack.push_back(matrix);
			else
				m_TranformationStack.push_back(m_TranformationStack.back() * matrix);

			m_TransformationBack = &m_TranformationStack.back();
		}

		void pop()
		{
			if (m_TranformationStack.size() > 1)
				m_TranformationStack.pop_back();

			m_TransformationBack = &m_TranformationStack.back();
		}

		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void begin() {}
		virtual void end() {}
		virtual void flush() = 0;
	};
} }