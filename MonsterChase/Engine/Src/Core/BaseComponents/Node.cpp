#include "Node.h"
#include "../Controllers/GameObjectUpdater_Extern.h"
#include "../../Utils/Uuid.h"
#include "../Components/Physics/Colliders/BaseCollider.h"
#include "../../Containers/PointerIncludes.cpp"

#include <algorithm>
#include <utility>

namespace Core::BaseComponents
{
	// Constructor And Destructor

	Node::Node(std::string i_name, bool i_addToGlobalList)
	{
		this->_instanceId = Utils::Uuid::GetUuid();
		this->_name = std::move(i_name);
		this->_tag = "";

		const Containers::SmartPtr<Node> selfSmartPtr(this);
		this->_selfSmartRef = selfSmartPtr;

		if (i_addToGlobalList)
		{
			AddToGlobalList();
		}
	}

	Node::Node(const Node& i_node)
	{
		this->_instanceId = Utils::Uuid::GetUuid();
		this->_name = i_node._name;
		this->_tag = i_node._tag;
		this->_renderOrder = i_node._renderOrder;

		this->_components.clear();
		for (auto component : i_node._components)
		{
			this->_components.push_back(component);
		}
	}

	Node& Node::operator=(const Node& i_node)
	{
		if (&i_node == this)
		{
			return *this;
		}

		this->_instanceId = Utils::Uuid::GetUuid();
		this->_name = i_node._name;
		this->_tag = i_node._tag;
		this->_renderOrder = i_node._renderOrder;

		this->_components.clear();
		for (auto component : i_node._components)
		{
			this->_components.push_back(component);
		}

		return *this;
	}

	Node& Node::operator=(Node&& i_node)
	{
		// FIXME: Maybe this will break everything. Don't know yet...

		if (&i_node == this)
		{
			return *this;
		}

		this->_instanceId = i_node._instanceId;
		this->_name = i_node._name;
		this->_tag = i_node._tag;
		this->_renderOrder = i_node._renderOrder;

		this->_components.clear();
		for (auto component : i_node._components)
		{
			this->_components.push_back(component);
		}

		return *this;
	}

	Node::Node(Node&& i_node)
	{
		// FIXME: Maybe this will break everything. Don't know yet...

		this->_instanceId = i_node._instanceId;
		this->_name = i_node._name;
		this->_tag = i_node._tag;
		this->_renderOrder = i_node._renderOrder;

		this->_components.clear();
		for (auto component : i_node._components)
		{
			this->_components.push_back(component);
		}
	}

	Node::~Node()
	{
		_components.clear();
	}

	// Constructor And Destructor

	// Components

	void Node::SortComponents()
	{
		std::sort(_components.begin(), _components.end(), ComparePriority);
	}

	bool Node::ComparePriority(Containers::SmartPtr<Component> i_a, Containers::SmartPtr<Component> i_b)
	{
		return i_a->GetComponentPriority() > i_b->GetComponentPriority();
	}

	// Components

	// LifeCycle Methods

	void Node::Ready()
	{
		for (auto component : _components)
		{
			component->Ready(Containers::WeakPtr<Node>(this->_selfSmartRef));
		}
	}

	void Node::Process(float i_deltaTime)
	{
		for (auto component : _components)
		{
			component->Process(i_deltaTime);
		}
	}

	void Node::PhysicsProcess(float i_fixedDeltaTime)
	{
		for (auto component : _components)
		{
			component->PhysicsProcess(i_fixedDeltaTime);
		}
	}

	void Node::SetupRender()
	{
		for (auto component : _components)
		{
			component->SetupRender();
		}
	}

	void Node::Render(sf::RenderWindow* i_window)
	{
		for (auto component : _components)
		{
			component->Render(i_window);
		}
	}

	void Node::RenderDebug(sf::RenderWindow* i_window)
	{
		for (auto component : _components)
		{
			component->RenderDebug(i_window);
		}
	}


	void Node::Exit()
	{
		for (auto component : _components)
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

	// Pointer Helpers

	void Node::AddToGlobalList() const
	{
		const Containers::SmartPtr<Node> smartPtrCopy(this->_selfSmartRef);
		gameObjectUpdater->AddGameObject(smartPtrCopy);
	}

	Containers::SmartPtr<Node> Node::GetSmartPointerRef() const
	{
		Containers::SmartPtr<Node> smartPtrCopy(this->_selfSmartRef);
		return smartPtrCopy;
	}

	Containers::WeakPtr<Node> Node::GetWeakPointerRef() const
	{
		Containers::WeakPtr<Node> weakPtrCopy(this->_selfSmartRef);
		return weakPtrCopy;
	}

	void Node::__NotifyCollisionCallback(
		const Containers::WeakPtr<Components::Physics::Colliders::BaseCollider> i_collider) const
	{
		if (this->_collisionCallback)
		{
			this->_collisionCallback(i_collider);
		}
	}

	void Node::SetCollisionCallback(
		std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>)> i_function
	)
	{
		this->_collisionCallback = i_function;
	}

	// Pointer Helpers

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
