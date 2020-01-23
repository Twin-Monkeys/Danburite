#pragma once

#include "AttachmentType.h"

namespace ObjectGL
{
	class Attachable abstract
	{
		friend class FrameBuffer;

	protected:
		virtual void _onAttach(const AttachmentType type) noexcept = 0;
		virtual void _onDetach(const AttachmentType type) noexcept = 0;
	};
}
