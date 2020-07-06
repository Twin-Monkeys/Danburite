#pragma once

#include "ForwardPostProcessor.h"

namespace Danburite
{
	class GrayscalePostProcessor : public ForwardPostProcessor
	{
	public:
		GrayscalePostProcessor();

		virtual ~GrayscalePostProcessor() = default;
	};
}