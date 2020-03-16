#include "Node.h"
#include "../Controllers/GameObjectUpdater_Extern.h"
#include "../../Utils/Uuid.h"

#include <algorithm>
#include <utility>

namespace Core::BaseComponents
{
	// Constructor And Destructor

	Node::Node(std::string i_name, bool i_addToGlobalList)
	{
		if (i_addToGlobalList)
		{
			gameObjectUpdater->AddGameObject(this);
		}

		this->_instanceId = Utils::Uuid::getUuid();
		this->_name = std::move(i_name);
		this->_tag = "";
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

	size_t Node::GetInstanceId() const
	{
		return this->_instanceId;
	}

	// LifeCycle Methods

	// General Data Access

	std::string Node::GetName() const
	{
		return this->_name;
	}

	std::string Node::GetTag() const
	{
		return this->_tag;
	}

	void Node::SetTag(std::string i_tag)
	{
		this->_tag = std::move(i_tag);
	}

	// General Data Access

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
