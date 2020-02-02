#pragma once

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

		void Init();
		void Run() const;
		void ShutDown() const;
	};
}
