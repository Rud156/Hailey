#pragma once
#include "BaseScene.h"

#include <SFML/Graphics.hpp>

namespace Game::Scenes
{
	class GameOverScene : public BaseScene
	{
	private:
		sf::Font* _baseFont{};

		sf::Text* _winStatusText{};
		sf::Text* _menuButtonText{};

		sf::Color _normalColor;
		sf::Color _hoverColor;
		sf::RectangleShape* _menuButton{};
		sf::Rect<float>* _menuCollider{};

		bool _sceneSwitchClicked = false;

	public:
		// Constructor and Destructor
		GameOverScene();
		virtual ~GameOverScene() override;

		// Scene LifeCycle Functions
		virtual void Init(Containers::SmartPtr<Commands::InputHandler>) override;
		virtual bool Update(float) override;
		virtual void Render(sf::RenderWindow* i_window) override;
		virtual void LMBClicked(sf::RenderWindow* i_window) override;
		virtual void SwitchSceneLoad() override;
		virtual void SwitchSceneUnload() override;
	};
}
