#include "SpriteRenderController.h"
#include "SpriteRenderController_Extern.h"
#include "Node.h"

#include <algorithm>
#include <SFML/Graphics.hpp>

Core::Controllers::Rendering::SpriteRenderController* spriteRenderController = nullptr;

namespace Core::Controllers::Rendering
{
#pragma region Constructor/Destructor

	SpriteRenderController::SpriteRenderController()
	{
		spriteRenderController = this;
	}

	SpriteRenderController::~SpriteRenderController()
	{
		spriteRenderController = nullptr;
	}

#pragma endregion

#pragma region External Functions


	void SpriteRenderController::AddNodeRenderer(BaseComponents::Node* i_node)
	{
		this->_nodes.push_back(i_node);
	}

	void SpriteRenderController::RemoveNodeRender(BaseComponents::Node* i_node)
	{
		const auto position = std::find(this->_nodes.begin(), this->_nodes.end(), i_node);
		if (position != this->_nodes.end())
		{
			this->_nodes.erase(position);
		}
	}

	void SpriteRenderController::RenderNodes(sf::RenderWindow* i_window)
	{
		SortRenderer();
		for (auto node : this->_nodes)
		{
			node->Render(i_window);
		}
	}

#pragma endregion

#pragma region Render Queue Management


	bool SpriteRenderController::CompareRenderOrder(BaseComponents::Node* i_a, BaseComponents::Node* i_b)
	{
		return i_a->GetRenderOrder() < i_b->GetRenderOrder();
	}


	void SpriteRenderController::SortRenderer()
	{
		std::sort(this->_nodes.begin(), this->_nodes.end(), CompareRenderOrder);
	}

#pragma endregion
}
