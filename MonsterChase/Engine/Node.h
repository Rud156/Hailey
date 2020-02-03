#pragma once
#include "Component.h"
#include <vector>

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace BaseComponents
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
			T* AddComponent();

			template <class T>
			void RemoveComponent();

			template <class T>
			T* GetComponent();

			// LifeCycle Methods
			void Ready();
			void Process(float deltaTime);
			void Render(sf::RenderWindow* window);
			void Exit();
		};

		template <class T>
		T* Node::AddComponent()
		{
			T* t = new T();

			static_cast<Component*>(t)->Ready(this); // TODO: fix this...
			_components.push_back(t);

			SortComponents();

			return t;
		}

		template <class T>
		void Node::RemoveComponent()
		{
			int componentIndex = -1;
			for (Component* component : _components)
			{
				if (dynamic_cast<T*>(component))
				{
					component->Exit();
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
		T* Node::GetComponent()
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
	}
}
