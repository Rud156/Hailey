#include "HomeScene.h"
#include "Src/Core/Controllers/CoreLoop.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Utils/Debug.h"

#include <cassert>
#include <string>

namespace Game::Scenes
{
#pragma region Constructor and Destructor

	HomeScene::HomeScene() = default;

	HomeScene::~HomeScene()
	{
		delete this->_baseFont;

		delete this->_headerText;
		delete this->_controlText;
		delete this->_playButtonText;

		delete this->_playButton;
		delete this->_playCollider;
	}

#pragma endregion

#pragma region LifeCycle Functions

	void HomeScene::Init(Containers::SmartPtr<Commands::InputHandler>)
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

		auto* headerText = new sf::Text();
		auto* playButtonText = new sf::Text();
		auto* controlText = new sf::Text();

		headerText->setFont(*this->_baseFont);
		controlText->setFont(*this->_baseFont);
		playButtonText->setFont(*this->_baseFont);

		headerText->setString("Space Shooter");
		controlText->setString("Use Arrow Keys to Move and Space to Shoot");
		playButtonText->setString("Play");

		headerText->setCharacterSize(27);
		controlText->setCharacterSize(22);
		playButtonText->setCharacterSize(25);

		headerText->setFillColor(sf::Color::Magenta);
		controlText->setFillColor(sf::Color::Yellow);

		const auto headerBounds = headerText->getLocalBounds();
		headerText->setOrigin(headerBounds.left + headerBounds.width / 2.0f,
		                      headerBounds.top + headerBounds.height / 2.0f);

		const auto controlBounds = controlText->getLocalBounds();
		controlText->setOrigin(controlBounds.left + controlBounds.width / 2.0f,
		                       controlBounds.top + controlBounds.height / 2.0f);

		const auto playBounds = playButtonText->getLocalBounds();
		playButtonText->setOrigin(playBounds.left + playBounds.width / 2.0f,
		                          playBounds.top + playBounds.height / 2.0f);

		const auto windowSize = Core::Controllers::CoreLoop::Window->getSize();
		headerText->setPosition(windowSize.x / 2.0f, 30);
		controlText->setPosition(windowSize.x / 2.0f, 150);
		playButtonText->setPosition(windowSize.x / 2.0f, 300);

		this->_headerText = headerText;
		this->_controlText = controlText;
		this->_playButtonText = playButtonText;

		this->_normalColor = sf::Color::Red;
		this->_hoverColor = sf::Color::Green;

		const auto playButtonWidth = 200.0f;
		const auto playButtonHeight = 50.0f;
		const auto buttonPosition = sf::Vector2f(windowSize.x / 2.0f - playButtonWidth / 2.0f,
		                                         300 - playButtonHeight / 2.0f);
		auto* playButton = new sf::RectangleShape();
		playButton->setFillColor(sf::Color::Transparent);
		playButton->setOutlineColor(this->_normalColor);
		playButton->setOutlineThickness(1.75f);
		playButton->setPosition(buttonPosition);
		playButton->setSize(sf::Vector2f(playButtonWidth, playButtonHeight));

		auto* playCollider = new sf::Rect<float>(buttonPosition, sf::Vector2f(playButtonWidth, playButtonHeight));

		this->_playCollider = playCollider;
		this->_playButton = playButton;
	}

	bool HomeScene::Update(float)
	{
		return this->_sceneSwitchClicked;
	}

	void HomeScene::Render(sf::RenderWindow* i_window)
	{
		const auto position = sf::Mouse::getPosition(*i_window);
		if (this->_playCollider->contains(static_cast<float>(position.x), static_cast<float>(position.y)))
		{
			this->_playButton->setOutlineColor(this->_hoverColor);
			this->_playButtonText->setFillColor(this->_hoverColor);
		}
		else
		{
			this->_playButton->setOutlineColor(this->_normalColor);
			this->_playButtonText->setFillColor(this->_normalColor);
		}

		i_window->draw(*this->_headerText);
		i_window->draw(*this->_controlText);
		i_window->draw(*this->_playButtonText);
		i_window->draw(*this->_playButton);
	}

	void HomeScene::LMBClicked(sf::RenderWindow* i_window)
	{
		const auto position = sf::Mouse::getPosition(*i_window);
		if (this->_playCollider->contains(static_cast<float>(position.x), static_cast<float>(position.y)))
		{
			this->_sceneSwitchClicked = true;
		}
		else
		{
			this->_sceneSwitchClicked = false;
		}
	}

	void HomeScene::SwitchSceneLoad()
	{
		this->_sceneSwitchClicked = false;
	}

	void HomeScene::SwitchSceneUnload()
	{
		this->_sceneSwitchClicked = false;
	}

#pragma endregion
}
