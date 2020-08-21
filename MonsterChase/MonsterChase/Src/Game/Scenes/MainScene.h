#pragma once
#include "BaseScene.h"
#include "../Commands/InputHandler.h"
#include "../GameObjects/Enemy/Enemy.h"
#include "../GameObjects/Player/Player.h"
#include "Src/Containers/SmartPtr.h"

namespace Game::Scenes
{
	class MainScene final : public BaseScene
	{
	private:
		Containers::SmartPtr<GameObjects::Player::Player> _player;
		Containers::SmartPtr<GameObjects::Enemy::Enemy> _enemy;

	public:
		// Constructor and Destructor
		MainScene();
		~MainScene() override;

		// Scene LifeCycle Functions
		void Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler) override;
		bool Update(float i_deltaTime) override;
		void SwitchSceneLoad() override;
		void SwitchSceneUnload() override;
		void RemoveSceneElements() override;
	};
}
