#pragma once

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace Controllers
	{
		class CoreLoop;
	}
}

namespace Engine
{
	class Engine
	{
	private:
		Core::Controllers::CoreLoop* _coreLoop{};

	public:
		// Constructor and Destructor
		Engine();
		~Engine();

		void Init(sf::RenderWindow* window);
		void Run() const;
		void ShutDown() const;
	};
}
