#include "Component.h"

namespace Core
{
	namespace BaseComponents
	{
		// Constructor And Destructor

		Component::Component()
		= default;

		Component::~Component()
		= default;

		// Constructor And Destructor

		// Priority

		int Component::GetComponentPriority()
		{
			return 0;
		}

		// Priority

		// LifeCycle Functions

		void Component::Ready(Node*)
		{
		}

		void Component::Process(float)
		{
		}

		void Component::Render(sf::RenderWindow*)
		{
		}

		void Component::Exit()
		{
		}

		// LifeCycle Functions
	}
}
