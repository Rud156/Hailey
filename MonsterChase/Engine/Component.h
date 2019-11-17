#pragma once

namespace Core
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
		virtual void Process();
		virtual void Exit();
	};
}
