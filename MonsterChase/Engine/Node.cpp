#include "Node.h"
#include <algorithm>

namespace Core
{
	// Constructor And Destructor

	Node::Node()
	{
	}

	Node::~Node()
	{
		for (Component* component : _components)
		{
			delete component;
		}

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
			component->Ready();
		}
	}

	void Node::Process()
	{
		for (Component* component : _components)
		{
			component->Process();
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
