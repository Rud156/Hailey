#pragma once

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace BaseComponents
	{
		class Node;

		class Component
		{
		public:
			Component();
			virtual ~Component();

			// Priority
			virtual int GetComponentPriority();

			//LifeCycle Functions
			virtual void Ready(Node*);
			virtual void Process(float);
			virtual void Render(sf::RenderWindow*);
			virtual void Exit();
		};
	}
}
