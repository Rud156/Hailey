#include "Node.h"
#include "../../Containers/PointerIncludes.cpp"
#include "../../Maths/Point2D.h"
#include "../../Utils/Debug.h"
#include "../../Utils/Uuid.h"
#include "../Components/Physics/Colliders/BaseCollider.h"
#include "../Controllers/GameObjectUpdater_Extern.h"

#include <algorithm>
#include <utility>

namespace Utils
{
	class Debug;
}

namespace Core::BaseComponents
{
	// Constructor And Destructor

	Node::Node(std::string i_name, bool i_addToGlobalList)
	{
		this->_instanceId = Utils::Uuid::GetUuid();
		this->_name = i_name;
		this->_tag = "";

		const Containers::SmartPtr<Node> selfSmartPtr(this);
		this->_selfWeakRef = selfSmartPtr;

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
		Utils::Debug::LogOutputToWindow("Node Removed\n");
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
			component->Ready(Containers::WeakPtr<Node>(this->_selfWeakRef));
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

		_components.clear();
		this->_selfWeakRef.ClearWeakRef();
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
		this->_tag = i_tag;
	}

	// General Data Access

	// Pointer Helpers

	void Node::AddToGlobalList()
	{
		gameObjectUpdater->AddGameObject(this->_selfWeakRef.Lock());
	}

	Containers::WeakPtr<Node> Node::GetWeakPointerRef() const
	{
		return this->_selfWeakRef;
	}

	std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>, Math::Point2D)>
	Node::__GetCollisionCallback() const
	{
		return this->_collisionCallback;
	}

	void Node::SetCollisionCallback(
		std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>, Math::Point2D)> i_function
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
