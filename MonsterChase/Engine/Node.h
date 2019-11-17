#pragma once
#include "Component.h"
#include <vector>

namespace Core
{
	class Node
	{
	private:
		std::vector<Component*> _components;

		void SortComponents();
		static bool ComparePriority(Component* a, Component* b);

	public:
		// Constructor and Destructor
		Node();
		~Node();

		// Component
		template <class T>
		T* AddComponent()
		{
			T* t = new T();
			_components.push_back(t);

			SortComponents();

			return t;
		}

		template <class T>
		void RemoveComponent()
		{
			int componentIndex = -1;
			for (Component* component : _components)
			{
				if (dynamic_cast<T*>(component))
				{
					break;
				}

				componentIndex += 1;
			}

			if (componentIndex != -1)
			{
				_components.erase(_components.begin() + componentIndex);
			}
		}

		template <class T>
		T* GetComponent()
		{
			for (Component* component : _components)
			{
				if (auto ptr = dynamic_cast<T*>(component))
				{
					return ptr;
				}
			}

			return nullptr;
		}

		// LifeCycle Methods
		void Ready();
		void Process();
		void Exit();
	};
}
