#pragma once
#include "BaseScene.h"
#include "../Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"
#include "../GameObjects/Player/Player.h"

namespace Game::Scenes
{
	class MainScene final : public BaseScene
	{
	private:
		Containers::SmartPtr<GameObjects::Player::Player> _player;

	public:
		// Constructor and Destructor
		MainScene();
		~MainScene() override;

		// Scene LifeCycle Functions
		void Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler) override;
		void Update(float i_deltaTime) override;
		void SwitchSceneLoad() override;
		void SwitchSceneUnload() override;
		void RemoveSceneElements() override;
	};
}
