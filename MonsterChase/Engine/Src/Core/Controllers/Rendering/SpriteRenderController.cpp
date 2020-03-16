#include "SpriteRenderController.h"
#include "SpriteRenderController_Extern.h"
#include "TextureDataCache.h"
#include "../../BaseComponents/Node.h"
#include "../GameObjectUpdater_Extern.h"

#include <algorithm>
#include <SFML/Graphics.hpp>


Core::Controllers::Rendering::SpriteRenderController* spriteRenderController = nullptr;

namespace Core::Controllers::Rendering
{
#pragma region Constructor/Destructor

	SpriteRenderController::SpriteRenderController()
	{
		this->_textureDataCache = new TextureDataCache();
		spriteRenderController = this;
	}

	SpriteRenderController::~SpriteRenderController()
	{
		delete this->_textureDataCache;
		spriteRenderController = nullptr;
	}

#pragma endregion

#pragma region External Functions

	void SpriteRenderController::RenderNodes(sf::RenderWindow* i_window) const
	{
		auto nodes = gameObjectUpdater->GetAllGameObjects();
		std::sort(nodes.begin(), nodes.end(), CompareRenderOrder);

		for (auto node : nodes)
		{
			node->Render(i_window);
		}
	}

#pragma endregion

#pragma region Render Queue Management


	bool SpriteRenderController::CompareRenderOrder(BaseComponents::Node* i_a, BaseComponents::Node* i_b)
	{
		if (i_a == nullptr)
		{
			return true;
		}
		else if (i_b == nullptr)
		{
			return false;
		}

		return i_a->GetRenderOrder() < i_b->GetRenderOrder();
	}

#pragma endregion
}
