#pragma once
#include "Commands/InputHandler.h"
#include "Scenes/BaseScene.h"
#include "Scenes/GameOverScene.h"
#include "Scenes/HomeScene.h"
#include "Scenes/MainScene.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"

namespace sf
{
	class RenderWindow;
}

namespace Game
{
	class GameMain
	{
	private:
		enum class SceneType
		{
			Home,
			Main,
			GameOver
		};

		SceneType _sceneType;
		Containers::WeakPtr<Scenes::BaseScene> _currentScene;
		Containers::SmartPtr<Scenes::HomeScene> _homeScene;
		Containers::SmartPtr<Scenes::MainScene> _mainScene;
		Containers::SmartPtr<Scenes::GameOverScene> _gameOverScene;
		Containers::SmartPtr<Commands::InputHandler> _inputHandler;

		// Utility Functions
		void SwitchScene(SceneType i_sceneType);
		void SetSceneType(SceneType i_sceneType);

	public:
		// Constructor and Destructor
		GameMain();
		~GameMain();

		// LifeCycle Functions
		void Init();
		void Update();
		void Render(sf::RenderWindow* i_window);
		void LMBClicked(sf::RenderWindow* i_window);
		void Destroy();
	};
}
