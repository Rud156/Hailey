#pragma once
#include "../Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"

namespace Game::Scenes
{
	class BaseScene
	{
	public:
		BaseScene();
		virtual ~BaseScene();

		virtual void Init(Containers::SmartPtr<Commands::InputHandler>);
		virtual void Update(float);
		virtual void SwitchSceneLoad();
		virtual void SwitchSceneUnload();
		virtual void RemoveSceneElements();
	};
}
