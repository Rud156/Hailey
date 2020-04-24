#include "Component.h"
#include "Node.h"
#include "../../Containers/PointerIncludes.cpp"

namespace Core::BaseComponents
{
	// Constructor And Destructor

	Component::Component() = default;

	Component::~Component() = default;

	// Constructor And Destructor

	// Priority

	int Component::GetComponentPriority()
	{
		return 0;
	}

	// Priority

	// LifeCycle Functions

	void Component::Ready(const Containers::WeakPtr<Node> i_node)
	{
		this->_node = i_node;
	}

	void Component::Process(float)
	{
	}

	void Component::PhysicsProcess(float)
	{
	}

	void Component::SetupRender()
	{
	}

	void Component::Render(sf::RenderWindow*)
	{
	}

	void Component::RenderDebug(sf::RenderWindow*)
	{
	}


	void Component::Exit()
	{
	}

	// LifeCycle Functions

	// Utility Methods

	Containers::WeakPtr<Node> Component::GetNode() const
	{
		return this->_node;
	}

	// Utility Methods
}
