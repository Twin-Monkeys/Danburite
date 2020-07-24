#pragma once

#include <list>
#include <memory>
#include "AttachableTextureRectangle.h"
#include "TextureMultisample.h"
#include "AttachmentServerException.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class AttachmentServer
	{
	private:
		using TexRectParamPack =
			std::tuple<
			GLsizei, GLsizei,
			ObjectGL::TextureInternalFormatType,
			ObjectGL::TextureExternalFormatType,
			ObjectGL::TextureDataType,
			ObjectGL::TextureMinFilterValue,
			ObjectGL::TextureMagFilterValue>;

		using TexMSParamPack =
			std::tuple<
			GLsizei, GLsizei,
			ObjectGL::TextureInternalFormatType, GLsizei, bool>;

		template<typename $ParamPackType, typename $AttachmentType>
		using AttachmentContainer =
			std::list<std::pair<$ParamPackType, std::weak_ptr<$AttachmentType>>>;

		AttachmentContainer<TexRectParamPack, ObjectGL::AttachableTextureRectangle> __texRectWeakPtrs;
		AttachmentContainer<TexMSParamPack, ObjectGL::TextureMultisample> __texMSWeakPtrs;

		template<typename $ParamPackType, typename $AttachmentType>
		[[nodiscard]]
		static std::shared_ptr<$AttachmentType> __retrieveContainer(
			const $ParamPackType &paramPack,
			AttachmentContainer<$ParamPackType, $AttachmentType> &targetContainer,
			const size_t retrievingIndex);

	public:
		[[nodiscard]]
		std::shared_ptr<ObjectGL::AttachableTextureRectangle>
			getTexRectangle(
			const GLsizei width, const GLsizei height,
			const ObjectGL::TextureInternalFormatType internalFormat,
			const ObjectGL::TextureExternalFormatType externalFormat,
			const ObjectGL::TextureDataType dataType,
			const ObjectGL::TextureMinFilterValue minFilter,
			const ObjectGL::TextureMagFilterValue magFilter,
			const size_t retrievingIndex = 0ULL);

		[[nodiscard]]
		std::shared_ptr<ObjectGL::TextureMultisample>
			getTexMultisample(
				const GLsizei width, const GLsizei height,
				const ObjectGL::TextureInternalFormatType internalFormat,
				const GLsizei numSamplePoints = ShaderIdentifier::Value::MSAA::NUM_SAMPLE_POINTS,
				const bool fixedSampleLocations = true,
				const size_t retrievingIndex = 0ULL);
	};

	template<typename $ParamPackType, typename $AttachmentType>
	std::shared_ptr<$AttachmentType> AttachmentServer::__retrieveContainer(
		const $ParamPackType &paramPack,
		AttachmentContainer<$ParamPackType, $AttachmentType> &targetContainer,
		const size_t retrievingIndex)
	{
		size_t skipCount = retrievingIndex;

		for (auto it = targetContainer.begin(); it != targetContainer.end();)
		{
			const auto &[elemParam, elemPtr] = *it;
			if (elemPtr.expired())
			{
				it = targetContainer.erase(it);
				continue;
			}

			if (elemParam == paramPack)
			{
				if (!skipCount)
					return elemPtr.lock();

				skipCount--;
			}

			it++;
		}

		if (skipCount > 1ULL)
			throw AttachmentServerException("Invalid retrievingIndex is detected.");

		return nullptr;
	}
}