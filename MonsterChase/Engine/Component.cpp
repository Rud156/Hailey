#include "Component.h"

namespace Core
{
	namespace BaseComponents
	{
	// Constructor And Destructor

	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	// Constructor And Destructor

	// Priority

	int Component::GetComponentPriority()
	{
		return 0;
	}

	// Priority

	// LifeCycle Functions

	void Component::Ready()
	{
	}

	void Component::Process(float)
	{
	}

	void Component::Exit()
	{
	}

	// LifeCycle Functions
	}
}
