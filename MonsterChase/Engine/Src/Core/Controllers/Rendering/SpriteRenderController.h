#pragma once
#include "../../../Containers/SmartPtr.h"
#include "../../BaseComponents/Node.h"

#include <vector>

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

		static bool CompareRenderOrder(Containers::SmartPtr<BaseComponents::Node> i_a,
		                               Containers::SmartPtr<BaseComponents::Node> i_b
		);

	public:
		// Constructor/Destructor
		SpriteRenderController();
		~SpriteRenderController();

		void RenderNodes(sf::RenderWindow* i_window) const;
	};
}
