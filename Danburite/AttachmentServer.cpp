#include "AttachmentServer.h"
#include <algorithm>

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<AttachableTextureRectangle>
		AttachmentServer::getTexRectangle(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
			const TextureDataType dataType,
			const TextureMinFilterValue minFilter, const TextureMagFilterValue magFilter) noexcept
	{
		const TexRectParam curParam =
			{ width, height, internalFormat, externalFormat, dataType, minFilter, magFilter };

		for (auto it = __texRectWeakPtrs.begin(); it != __texRectWeakPtrs.end(); it++)
		{
			const auto &[elemParam, elemTexPtr] = *it;
			if (elemTexPtr.expired())
			{
				it = __texRectWeakPtrs.erase(it);
				continue;
			}

			if (elemParam == curParam)
				return elemTexPtr.lock();
		}

		const shared_ptr<AttachableTextureRectangle> &pRetVal = make_shared<AttachableTextureRectangle>();
		pRetVal->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		pRetVal->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		pRetVal->setState(TextureParamType::TEXTURE_MIN_FILTER, minFilter);
		pRetVal->setState(TextureParamType::TEXTURE_MAG_FILTER, magFilter);
		pRetVal->memoryAlloc(width, height, internalFormat, externalFormat, dataType);

		__texRectWeakPtrs.emplace_back(curParam, pRetVal);
		return pRetVal;
	}
}