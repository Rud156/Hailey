#pragma once
#include "../../Containers/WeakPtr.h"
#include "Node.h"

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
		protected:
			Containers::WeakPtr<Node> _node;

		public:
			Component();
			virtual ~Component();

			// Priority
			virtual int GetComponentPriority();

			//LifeCycle Functions
			virtual void Ready(Containers::WeakPtr<Node> i_node);
			virtual void Process(float);
			virtual void PhysicsProcess(float);
			virtual void SetupRender();
			virtual void Render(sf::RenderWindow* i_window);
			virtual void RenderDebug(sf::RenderWindow* i_window);
			virtual void Exit();

			// Utility Methods
			[[nodiscard]] Containers::WeakPtr<Node> GetNode() const;
		};
	}
}
