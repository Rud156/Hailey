#include "Node.h"
#include "../Controllers/GameObjectUpdater_Extern.h"

#include <algorithm>

namespace Core::BaseComponents
{
	// Constructor And Destructor

	Node::Node(const char* const i_name, bool i_addToGlobalList)
	{
		if (i_addToGlobalList)
		{
			gameObjectUpdater->AddGameObject(this);
		}

		this->_name = i_name;
	}

	Node::~Node()
	{
		for (auto component : _components)
		{
			delete component;
		}

		_components.clear();
		gameObjectUpdater->RemoveGameObject(this);
	}

	// Constructor And Destructor

	// Components

	void Node::SortComponents()
	{
		std::sort(_components.begin(), _components.end(), ComparePriority);
	}

	bool Node::ComparePriority(Component* i_a, Component* i_b)
	{
		return i_a->GetComponentPriority() > i_b->GetComponentPriority();
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

	void Node::Process(float i_deltaTime)
	{
		for (Component* component : _components)
		{
			component->Process(i_deltaTime);
		}
	}

	void Node::PhysicsProcess(float i_fixedDeltaTime)
	{
		for (Component* component : _components)
		{
			component->PhysicsProcess(i_fixedDeltaTime);
		}
	}

	void Node::SetupRender()
	{
		for (Component* component : _components)
		{
			component->SetupRender();
		}
	}

	void Node::Render(sf::RenderWindow* i_window)
	{
		for (Component* component : _components)
		{
			component->Render(i_window);
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

	// Component Specific Data for Fast Access

	void Node::SetRenderOrder(const float i_renderOrder)
	{
		this->_renderOrder = i_renderOrder;
	}

	float Node::GetRenderOrder() const
	{
		return this->_renderOrder;
	}

	// Component Specific Data for Fast Access
}
