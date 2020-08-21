#pragma once
#include "BaseScene.h"
#include "../Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"

#include <SFML/Graphics.hpp>

namespace Game::Scenes
{
	class HomeScene : public BaseScene
	{
	private:
		sf::Font* _baseFont{};

		sf::Text* _headerText{};
		sf::Text* _controlText{};
		sf::Text* _playButtonText{};

		sf::Color _normalColor;
		sf::Color _hoverColor;
		sf::RectangleShape* _playButton{};
		sf::Rect<float>* _playCollider{};

		bool _sceneSwitchClicked = false;

	public:
		// Constructor and Destructor
		HomeScene();
		virtual ~HomeScene() override;

		// Scene LifeCycle Functions
		virtual void Init(Containers::SmartPtr<Commands::InputHandler>) override;
		virtual bool Update(float) override;
		virtual void Render(sf::RenderWindow* i_window) override;
		virtual void LMBClicked(sf::RenderWindow* i_window) override;
		virtual void SwitchSceneLoad() override;
		virtual void SwitchSceneUnload() override;
	};
}
