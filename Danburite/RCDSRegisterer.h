#pragma once

namespace Danburite
{
	// Render Context-Dependent Singleton Registerer
	class RCDSRegisterer abstract final
	{
	public:
		static void batchRegister() noexcept;
	};
}