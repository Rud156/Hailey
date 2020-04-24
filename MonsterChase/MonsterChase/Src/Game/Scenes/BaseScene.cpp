#include "BaseScene.h"

namespace Game::Scenes
{
	BaseScene::BaseScene() = default;

	BaseScene::~BaseScene() = default;

	void BaseScene::Init(Containers::SmartPtr<Commands::InputHandler>)
	{
	}

	void BaseScene::Update(float)
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
