#pragma once

#include <unordered_map>

namespace sf
{
	class Texture;
}

namespace Core::Controllers::Rendering
{
	class TextureDataCache
	{
	private:
		std::unordered_map<size_t, sf::Texture*> _inMemoryTextures;

	public:
		TextureDataCache();
		~TextureDataCache();

		bool HasTexture(const std::string& i_filePath);
		void AddTexture(const std::string& i_filePath, sf::Texture* i_texture);
		void RemoveTexture(const std::string& i_filePath);
		sf::Texture* GetTexture(const std::string& i_filePath);
	};
}
