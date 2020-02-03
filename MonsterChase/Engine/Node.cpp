#include "Node.h"
#include <algorithm>
#include "GameObjectUpdater_Extern.h"

namespace Core
{
	namespace BaseComponents
	{
		// Constructor And Destructor

		Node::Node()
		{
			gameObjectUpdater->AddGameObject(this);
		}

		Node::~Node()
		{
			Exit();
			_components.clear();
		}

		// Constructor And Destructor

		// Components

		void Node::SortComponents()
		{
			std::sort(_components.begin(), _components.end(), ComparePriority);
		}

		bool Node::ComparePriority(Component* a, Component* b)
		{
			return a->GetComponentPriority() > b->GetComponentPriority();
		}

		// Components

		// LifeCycle Methods

		void Node::Ready()
		{
			for (Component* component : _components)
			{
				component->Ready(this);
			}
		}

		void Node::Process(float deltaTime)
		{
			for (Component* component : _components)
			{
				component->Process(deltaTime);
			}
		}

		void Node::Render(sf::RenderWindow* window)
		{
			for (Component* component : _components)
			{
				component->Render(window);
			}
		}


		void Node::Exit()
		{
			for (Component* component : _components)
			{
				component->Exit();
			}
		}

		// LifeCycle Methods
	}
}
