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
			const TextureMinFilterValue minFilter, const TextureMagFilterValue magFilter,
			const size_t retrievingIndex)
	{
		const TexRectParamPack &curParam =
			{ width, height, internalFormat, externalFormat, dataType, minFilter, magFilter };

		shared_ptr<AttachableTextureRectangle> pRetVal =
			__retrieveContainer(curParam, __texRectWeakPtrs, retrievingIndex);

		if (pRetVal)
			return pRetVal;

		pRetVal = make_shared<AttachableTextureRectangle>();
		pRetVal->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		pRetVal->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		pRetVal->setState(TextureParamType::TEXTURE_MIN_FILTER, minFilter);
		pRetVal->setState(TextureParamType::TEXTURE_MAG_FILTER, magFilter);
		pRetVal->memoryAlloc(width, height, internalFormat, externalFormat, dataType);

		__texRectWeakPtrs.emplace_back(curParam, pRetVal);
		return pRetVal;
	}

	shared_ptr<TextureMultisample>
		AttachmentServer::getTexMultisample(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const GLsizei numSamplePoints, const bool fixedSampleLocations,
			const size_t retrievingIndex)
	{
		const TexMSParamPack &curParam =
			{ width, height, internalFormat, numSamplePoints, fixedSampleLocations };

		shared_ptr<TextureMultisample> pRetVal =
			__retrieveContainer(curParam, __texMSWeakPtrs, retrievingIndex);
		
		if (pRetVal)
			return pRetVal;

		pRetVal = make_shared<TextureMultisample>();
		pRetVal->memoryAlloc(width, height, internalFormat, numSamplePoints, fixedSampleLocations);

		__texMSWeakPtrs.emplace_back(curParam, pRetVal);
		return pRetVal;
	}

	[[nodiscard]]
	shared_ptr<RenderBufferMultisample>
		AttachmentServer::getRenderBufferMultisample(
			const GLsizei width, const GLsizei height,
			const RenderBufferInternalFormatType internalFormat,
			const GLsizei numSamplePoints, const size_t retrievingIndex)
	{
		const RBMSParamPack &curParam =
			{ width, height, internalFormat, numSamplePoints };

		shared_ptr<RenderBufferMultisample> pRetVal =
			__retrieveContainer(curParam, __RBMSWeakPtrs, retrievingIndex);

		if (pRetVal)
			return pRetVal;

		pRetVal = make_shared<RenderBufferMultisample>();
		pRetVal->memoryAlloc(width, height, internalFormat, numSamplePoints);

		__RBMSWeakPtrs.emplace_back(curParam, pRetVal);
		return pRetVal;
	}
}