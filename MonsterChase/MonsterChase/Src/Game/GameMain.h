#pragma once
#include "Scenes/BaseScene.h"
#include "Scenes/MainScene.h"
#include "Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"

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
		Containers::SmartPtr<Scenes::MainScene> _mainScene;
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
		void Destroy();
	};
}
