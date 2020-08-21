#include "BaseScene.h"

namespace Game::Scenes
{
	BaseScene::BaseScene() = default;

	BaseScene::~BaseScene() = default;

	void BaseScene::Init(Containers::SmartPtr<Commands::InputHandler>)
	{
	}

	bool BaseScene::Update(float)
	{
		return false;
	}

	void BaseScene::Render(sf::RenderWindow*)
	{
	}

	void BaseScene::LMBClicked(sf::RenderWindow*)
	{
	}

	void BaseScene::SwitchSceneLoad()
	{
	}

	void BaseScene::SwitchSceneUnload()
	{
	}

	void BaseScene::RemoveSceneElements()
	{
	}
}
