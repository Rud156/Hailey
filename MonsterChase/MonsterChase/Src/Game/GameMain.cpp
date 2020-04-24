#include "GameMain.h"
#include "Scenes/MainScene.h"
#include "Src/Core/Controllers/LoopTimer.h"
#include "Src/Containers/PointerIncludes.cpp"

namespace Game
{
#pragma region Constructor and Destructor

	GameMain::GameMain()
	{
		const Containers::SmartPtr<Scenes::MainScene> mainScene(new Scenes::MainScene());
		this->_mainScene = mainScene;

		const Containers::SmartPtr<Commands::InputHandler> inputHandler(new Commands::InputHandler());
		this->_inputHandler = inputHandler;

		this->_sceneType = SceneType::Home;
	}

	GameMain::~GameMain() = default;

#pragma endregion

#pragma region LifeCycle Functions

	void GameMain::Init()
	{
		_mainScene->Init(this->_inputHandler);

		SetSceneType(SceneType::Main);
	}

	void GameMain::Update()
	{
		const auto deltaTime = static_cast<float>(Core::Controllers::LoopTimer::DeltaTime);
		switch (this->_sceneType)
		{
		case SceneType::Home:
			break;

		case SceneType::Main:
			this->_mainScene->Update(deltaTime);
			break;

		case SceneType::GameOver:
			break;

		default:
			break;
		}
	}

	void GameMain::Destroy()
	{
		this->_mainScene->RemoveSceneElements();
	}

#pragma endregion

#pragma region Utility Functions

	void GameMain::SwitchScene(SceneType i_sceneType)
	{
		if (this->_currentScene)
		{
			auto sceneRef = this->_currentScene.Lock();
			sceneRef->SwitchSceneUnload();
		}

		switch (i_sceneType)
		{
		case SceneType::Home:
			break;

		case SceneType::Main:
			this->_mainScene->SwitchSceneLoad();
			break;

		case SceneType::GameOver:
			break;

		default:
			// Don't do anything here...
			break;
		}

		SetSceneType(i_sceneType);
	}

	void GameMain::SetSceneType(const SceneType i_sceneType)
	{
		this->_sceneType = i_sceneType;

		switch (i_sceneType)
		{
		case SceneType::Home:
			break;

		case SceneType::Main:
			{
				const Containers::WeakPtr<Scenes::BaseScene> mainSceneRef(this->_mainScene);
				this->_currentScene = mainSceneRef;
			}
			break;

		case SceneType::GameOver:
			break;
		}
	}

#pragma endregion
}
