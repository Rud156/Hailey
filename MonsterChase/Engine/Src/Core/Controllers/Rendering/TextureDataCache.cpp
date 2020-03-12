#include "TextureDataCache.h"
#include <SFML/Graphics.hpp>

#include <string>

Core::Controllers::Rendering::TextureDataCache* textureDataCache = nullptr;

namespace Core::Controllers::Rendering
{
	TextureDataCache::TextureDataCache()
	{
		textureDataCache = this;
	}

	TextureDataCache::~TextureDataCache()
	{
		for (auto ele : this->_inMemoryTextures)
		{
			delete ele.second;
		}

		textureDataCache = nullptr;
	}

	bool TextureDataCache::HasTexture(const std::string& i_filePath)
	{
		const std::hash<std::string> stringHasher;
		const auto fileHash = stringHasher(i_filePath);
		return this->_inMemoryTextures.find(fileHash) != this->_inMemoryTextures.end();
	}

	void TextureDataCache::AddTexture(const std::string& i_filePath, sf::Texture* i_texture)
	{
		const std::hash<std::string> stringHasher;
		const auto fileHash = stringHasher(i_filePath);
		this->_inMemoryTextures[fileHash] = i_texture;
	}

	void TextureDataCache::RemoveTexture(const std::string& i_filePath)
	{
		const std::hash<std::string> stringHasher;
		const auto fileHash = stringHasher(i_filePath);

		if (this->_inMemoryTextures.find(fileHash) != this->_inMemoryTextures.end())
		{
			delete this->_inMemoryTextures[fileHash];
			this->_inMemoryTextures.erase(fileHash);
		}
	}

	sf::Texture* TextureDataCache::GetTexture(const std::string& i_filePath)
	{
		const std::hash<std::string> stringHasher;
		const auto fileHash = stringHasher(i_filePath);
		return this->_inMemoryTextures[fileHash];
	}
}
