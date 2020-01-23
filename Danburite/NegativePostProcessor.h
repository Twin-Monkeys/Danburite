#pragma once

#include "ForwardPostProcessor.h"

namespace Danburite
{
	class NegativePostProcessor : public ForwardPostProcessor
	{
	public:
		NegativePostProcessor();

		virtual ~NegativePostProcessor() = default;
	};
}