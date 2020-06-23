#include "TextureUtil.h"
#include "stb_image.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	shared_ptr<Texture2D> TextureUtil::createTexture2DFromImage(
		const string_view &imagePath, const TextureDataType dataType, const GLint mipmapLevel, const bool mipmapCreation)
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, numChannels;

		const unique_ptr<stbi_uc[]> &pImage =
			unique_ptr<stbi_uc[]>(stbi_load(imagePath.data(), &width, &height, &numChannels, 0));

		if (!pImage)
			return nullptr;

		TextureInternalFormatType internalFormat;
		TextureExternalFormatType externalFormat;
		switch (numChannels)
		{
		case 1:
			internalFormat = TextureInternalFormatType::RED;
			externalFormat = TextureExternalFormatType::RED;
			break;

		case 2:
			internalFormat = TextureInternalFormatType::RG;
			externalFormat = TextureExternalFormatType::RG;
			break;

		case 3:
			internalFormat = TextureInternalFormatType::RGB;
			externalFormat = TextureExternalFormatType::RGB;
			break;

		case 4:
			internalFormat = TextureInternalFormatType::RGBA;
			externalFormat = TextureExternalFormatType::RGBA;
			break;

		default:
			throw TextureUtilException("Unknown image format");
		}

		const shared_ptr<Texture2D> &pRetVal = make_shared<Texture2D>();
		pRetVal->memoryAlloc(
			width, height, pImage.get(), internalFormat, externalFormat, dataType, mipmapLevel, mipmapCreation);

		return pRetVal;
	}

	shared_ptr<TextureCubemap> TextureUtil::createTextureCubemapFromImage(
		const vector<string_view> &imagePaths, const TextureDataType dataType,
		const GLint mipmapLevel, const bool mipmapCreation)
	{
		const shared_ptr<TextureCubemap> &pRetVal = make_shared<TextureCubemap>();

		// Texture cubemap은 flip되지 않음.
		stbi_set_flip_vertically_on_load(false);
		int width, height, numChannels;

		unique_ptr<stbi_uc[]> pImage;
		for (int i = 0; i < 6; i++)
		{
			const string_view &imagePath = imagePaths[i];
			pImage = unique_ptr<stbi_uc[]>(stbi_load(imagePath.data(), &width, &height, &numChannels, 0));

			TextureInternalFormatType internalFormat;
			TextureExternalFormatType externalFormat;
			switch (numChannels)
			{
			case 1:
				internalFormat = TextureInternalFormatType::RED;
				externalFormat = TextureExternalFormatType::RED;
				break;

			case 3:
				internalFormat = TextureInternalFormatType::RGB;
				externalFormat = TextureExternalFormatType::RGB;
				break;

			case 4:
				internalFormat = TextureInternalFormatType::RGBA;
				externalFormat = TextureExternalFormatType::RGBA;
				break;

			default:
				throw TextureUtilException("Unknown image format");
			}

			pRetVal->memoryAlloc(
				CubemapSideType::POSITIVE_X + i, width, height, pImage.get(),
				internalFormat, externalFormat, dataType, mipmapLevel);
		}

		if (mipmapCreation)
			pRetVal->createMipmap();

		return pRetVal;
	}
}