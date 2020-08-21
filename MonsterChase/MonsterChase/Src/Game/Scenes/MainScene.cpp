#include "MainScene.h"

#include "../Utils/GameConfig.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Maths/Point2D.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Utils/Debug.h"

namespace Game::Scenes
{
#pragma region Constructor and Destructor

	MainScene::MainScene()
	{
		// const Containers::SmartPtr<GameObjects::Player::Player> player(new GameObjects::Player::Player());
		// this->_player = player;
		//
		// const Containers::SmartPtr<GameObjects::Enemy::Enemy> enemy(new GameObjects::Enemy::Enemy());
		// this->_enemy = enemy;
	}

	MainScene::~MainScene() = default;


#pragma endregion

#pragma region LifeCycle Functions

	void MainScene::Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler)
	{
		// this->_player->Init(i_inputHandler);
		// this->_enemy->Init();
	}

	bool MainScene::Update(float)
	{
		// this->_player->Update(i_deltaTime);
		// this->_enemy->Update(i_deltaTime);


		return false;
	}

	void MainScene::SwitchSceneLoad()
	{
	}

	void MainScene::SwitchSceneUnload()
	{
	}

	void MainScene::RemoveSceneElements()
	{
	}

#pragma endregion
}
