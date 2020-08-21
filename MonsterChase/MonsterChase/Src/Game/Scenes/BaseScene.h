#pragma once
#include "../Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"

namespace sf
{
	class RenderWindow;
}

namespace Game::Scenes
{
	class BaseScene
	{
	public:
		BaseScene();
		virtual ~BaseScene();

		virtual void Init(Containers::SmartPtr<Commands::InputHandler>);
		virtual bool Update(float);
		virtual void Render(sf::RenderWindow*);
		virtual void LMBClicked(sf::RenderWindow*);
		virtual void SwitchSceneLoad();
		virtual void SwitchSceneUnload();
		virtual void RemoveSceneElements();
	};
}
