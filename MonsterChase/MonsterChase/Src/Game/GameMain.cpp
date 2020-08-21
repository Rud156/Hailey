#include "GameMain.h"
#include "Scenes/MainScene.h"
#include "Src/Core/Controllers/LoopTimer.h"
#include "Src/Containers/PointerIncludes.cpp"

namespace Game
{
#pragma region Constructor and Destructor

	GameMain::GameMain()
	{
		const Containers::SmartPtr<Scenes::HomeScene> homeScene(new Scenes::HomeScene());
		const Containers::SmartPtr<Scenes::MainScene> mainScene(new Scenes::MainScene());
		const Containers::SmartPtr<Scenes::GameOverScene> gameOverScene(new Scenes::GameOverScene());

		this->_homeScene = homeScene;
		this->_mainScene = mainScene;
		this->_gameOverScene = gameOverScene;

		const Containers::SmartPtr<Commands::InputHandler> inputHandler(new Commands::InputHandler());
		this->_inputHandler = inputHandler;

		this->_sceneType = SceneType::Home;
	}

	GameMain::~GameMain() = default;

#pragma endregion

#pragma region LifeCycle Functions

	void GameMain::Init()
	{
		_homeScene->Init(this->_inputHandler);
		_mainScene->Init(this->_inputHandler);
		_gameOverScene->Init(this->_inputHandler);

		SetSceneType(SceneType::Home);
	}

	void GameMain::Update()
	{
		const auto deltaTime = static_cast<float>(Core::Controllers::LoopTimer::DeltaTime);
		switch (this->_sceneType)
		{
		case SceneType::Home:
			{
				const bool switchScene = this->_homeScene->Update(deltaTime);
				if (switchScene)
				{
					SwitchScene(SceneType::GameOver); // TODO: Change this later on...
				}
			}
			break;

		case SceneType::Main:
			{
				const bool switchScene = this->_mainScene->Update(deltaTime);
				if (switchScene)
				{
					SwitchScene(SceneType::GameOver);
				}
			}
			break;

		case SceneType::GameOver:
			{
				const bool switchScene = this->_gameOverScene->Update(deltaTime);
				if (switchScene)
				{
					SwitchScene(SceneType::Home);
				}
			}
			break;

		default:
			break;
		}
	}

	void GameMain::Render(sf::RenderWindow* i_window)
	{
		switch (this->_sceneType)
		{
		case SceneType::Home:
			this->_homeScene->Render(i_window);
			break;

		case SceneType::Main:
			this->_mainScene->Render(i_window);
			break;

		case SceneType::GameOver:
			this->_gameOverScene->Render(i_window);
			break;

		default:
			break;
		}
	}

	void GameMain::LMBClicked(sf::RenderWindow* i_window)
	{
		switch (this->_sceneType)
		{
		case SceneType::Home:
			this->_homeScene->LMBClicked(i_window);
			break;

		case SceneType::Main:
			this->_mainScene->LMBClicked(i_window);
			break;

		case SceneType::GameOver:
			this->_gameOverScene->LMBClicked(i_window);
			break;

		default:
			break;
		}
	}

	void GameMain::Destroy()
	{
		this->_homeScene->RemoveSceneElements();
		this->_mainScene->RemoveSceneElements();
		this->_gameOverScene->RemoveSceneElements();
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
			this->_homeScene->SwitchSceneLoad();
			break;

		case SceneType::Main:
			this->_mainScene->SwitchSceneLoad();
			break;

		case SceneType::GameOver:
			this->_gameOverScene->SwitchSceneLoad();
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
			{
				const Containers::WeakPtr<Scenes::BaseScene> homeSceneRef(this->_homeScene);
				this->_currentScene = homeSceneRef;
			}
			break;

		case SceneType::Main:
			{
				const Containers::WeakPtr<Scenes::BaseScene> mainSceneRef(this->_mainScene);
				this->_currentScene = mainSceneRef;
			}
			break;

		case SceneType::GameOver:
			{
				const Containers::WeakPtr<Scenes::BaseScene> gameOverSceneRef(this->_gameOverScene);
				this->_currentScene = gameOverSceneRef;
			}
			break;
		}
	}

#pragma endregion
}
