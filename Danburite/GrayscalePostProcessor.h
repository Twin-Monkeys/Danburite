#pragma once

#include "ForwardPostProcessor.h"

namespace Danburite
{
	class GrayscalePostProcessor : public ForwardPostProcessor
	{
	public:
		GrayscalePostProcessor(const bool attachDepthBuffer = false);

		virtual ~GrayscalePostProcessor() = default;
	};
}