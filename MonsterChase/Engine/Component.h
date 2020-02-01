#pragma once

namespace Core
{
	namespace BaseComponents
	{
		class Component
		{
		public:
			Component();
			virtual ~Component();

			// Priority
			virtual int GetComponentPriority();

			//LifeCycle Functions
			virtual void Ready();
			virtual void Process(float);
			virtual void Exit();
		};
	}
}
