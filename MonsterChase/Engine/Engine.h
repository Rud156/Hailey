#pragma once
#include <string>

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

		sf::RenderWindow* Init(int windowWidth, int windowHeight, const std::string& windowTitle);
		void Run() const;
		void ShutDown() const;
	};
}
