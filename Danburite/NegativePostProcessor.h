#pragma once

#include "ForwardPostProcessor.h"

namespace Danburite
{
	class NegativePostProcessor : public ForwardPostProcessor
	{
	public:
		NegativePostProcessor(const bool attachDepthBuffer = false);

		virtual ~NegativePostProcessor() = default;
	};
}