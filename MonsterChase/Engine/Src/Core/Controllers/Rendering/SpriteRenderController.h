#pragma once
#include <vector>

namespace Core
{
	namespace BaseComponents
	{
		class Node;
	}
}

namespace sf
{
	class RenderWindow;
}

namespace Core::Controllers::Rendering
{
	class TextureDataCache;

	class SpriteRenderController
	{
	private:
		TextureDataCache* _textureDataCache;

		static bool CompareRenderOrder(BaseComponents::Node* i_a,
		                               BaseComponents::Node* i_b);
		void SortRenderer(std::vector<BaseComponents::Node*>& nodes) const;

	public:
		// Constructor/Destructor
		SpriteRenderController();
		~SpriteRenderController();

		void RenderNodes(sf::RenderWindow* i_window) const;
	};
}
