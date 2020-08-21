#include "GameOverScene.h"

#include <cassert>


#include "SceneData.h"
#include "Src/Core/Controllers/CoreLoop.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Utils/Debug.h"

namespace Game::Scenes
{
#pragma region Constrcutor and Destructor

	GameOverScene::GameOverScene() = default;

	GameOverScene::~GameOverScene()
	{
		delete this->_baseFont;

		delete this->_winStatusText;
		delete this->_menuButtonText;

		delete this->_menuButton;
		delete this->_menuCollider;
	}

#pragma endregion

#pragma region Scene LifeCycle Functions

	void GameOverScene::Init(Containers::SmartPtr<Commands::InputHandler>)
	{
		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Fonts/Oswald-Medium.ttf";

		auto* font = new sf::Font();
		if (!font->loadFromFile(filePath))
		{
			Utils::Debug::LogOutputToWindow("Unable to load font file\n");
			assert(false);
		}

		this->_baseFont = font;

		auto* winStatusText = new sf::Text();
		auto* menuButtonText = new sf::Text();

		winStatusText->setFont(*this->_baseFont);
		menuButtonText->setFont(*this->_baseFont);

		menuButtonText->setString("Main Menu");

		winStatusText->setCharacterSize(27);
		menuButtonText->setCharacterSize(25);

		const auto menuTextBounds = menuButtonText->getLocalBounds();
		menuButtonText->setOrigin(menuTextBounds.left + menuTextBounds.width / 2.0f,
		                          menuTextBounds.top + menuTextBounds.height / 2.0f);

		const auto windowSize = Core::Controllers::CoreLoop::Window->getSize();
		winStatusText->setPosition(windowSize.x / 2.0f, 150);
		menuButtonText->setPosition(windowSize.x / 2.0f, 300);

		this->_winStatusText = winStatusText;
		this->_menuButtonText = menuButtonText;

		this->_normalColor = sf::Color::Red;
		this->_hoverColor = sf::Color::Green;

		const auto menuButtonWidth = 200.0f;
		const auto menuButtonHeight = 50.0f;
		const auto buttonPosition = sf::Vector2f(windowSize.x / 2.0f - menuButtonWidth / 2.0f,
		                                         300 - menuButtonHeight / 2.0f);

		auto* menuButton = new sf::RectangleShape();
		menuButton->setFillColor(sf::Color::Transparent);
		menuButton->setOutlineColor(this->_normalColor);
		menuButton->setOutlineThickness(1.75f);
		menuButton->setPosition(buttonPosition);
		menuButton->setSize(sf::Vector2f(menuButtonWidth, menuButtonHeight));

		auto* menuCollider = new sf::Rect<float>(buttonPosition, sf::Vector2f(menuButtonWidth, menuButtonHeight));

		this->_menuButton = menuButton;
		this->_menuCollider = menuCollider;
	}

	bool GameOverScene::Update(float)
	{
		return this->_sceneSwitchClicked;
	}

	void GameOverScene::Render(sf::RenderWindow* i_window)
	{
		const auto position = sf::Mouse::getPosition(*i_window);
		if (this->_menuCollider->contains(static_cast<float>(position.x), static_cast<float>(position.y)))
		{
			this->_menuButton->setOutlineColor(this->_hoverColor);
			this->_menuButtonText->setFillColor(this->_hoverColor);
		}
		else
		{
			this->_menuButton->setOutlineColor(this->_normalColor);
			this->_menuButtonText->setFillColor(this->_normalColor);
		}

		i_window->draw(*this->_winStatusText);
		i_window->draw(*this->_menuButtonText);
		i_window->draw(*this->_menuButton);
	}

	void GameOverScene::LMBClicked(sf::RenderWindow* i_window)
	{
		const auto position = sf::Mouse::getPosition(*i_window);
		if (this->_menuCollider->contains(static_cast<float>(position.x), static_cast<float>(position.y)))
		{
			this->_sceneSwitchClicked = true;
		}
		else
		{
			this->_sceneSwitchClicked = false;
		}
	}

	void GameOverScene::SwitchSceneLoad()
	{
		const bool didPlayerWin = SceneData::PlayWon;

		if (didPlayerWin)
		{
			this->_winStatusText->setString("You Won!!!");
			this->_winStatusText->setFillColor(sf::Color::Green);
		}
		else
		{
			this->_winStatusText->setString("You Died!!!");
			this->_winStatusText->setFillColor(sf::Color::Red);
		}

		const auto winStatusBounds = this->_winStatusText->getLocalBounds();
		this->_winStatusText->setOrigin(winStatusBounds.left + winStatusBounds.width / 2.0f,
		                                winStatusBounds.top + winStatusBounds.height / 2.0f);

		this->_sceneSwitchClicked = false;
	}

	void GameOverScene::SwitchSceneUnload()
	{
		this->_sceneSwitchClicked = false;
	}

#pragma endregion
}
