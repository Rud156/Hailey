#pragma once
#include "Component.h"
#include "../../Containers/SmartPtr.h"
#include "../../Containers/WeakPtr.h"

#include <typeinfo>
#include <vector>
#include <string>
#include <functional>
#include <mutex>

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace Components::Physics::Colliders
	{
		class BaseCollider;
	}

	namespace BaseComponents
	{
		class Component;

		class Node
		{
		private:
			size_t _instanceId;
			Containers::SmartPtr<Node> _selfSmartRef;
			std::recursive_mutex _nodeMutex;

			std::string _name;
			std::string _tag;

			std::vector<Containers::SmartPtr<Component>> _components;

			void SortComponents();
			static bool ComparePriority(Containers::SmartPtr<Component> i_a, Containers::SmartPtr<Component> i_b);

			// Component Specific Data for Fast Access
			std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>)> _collisionCallback;
			float _renderOrder{};

		public:
			// Constructor and Destructor
			Node(std::string i_name, bool i_addToGlobalList = true);
			Node(const Node& i_node);
			Node& operator=(const Node& i_node);
			Node& operator=(Node&& i_node);
			Node(Node&& i_node);
			~Node();

			// Component
			template <class T>
			Containers::WeakPtr<T> AddComponent();

			template <class T>
			void RemoveComponent();

			template <class T>
			Containers::WeakPtr<T> GetComponent();

			// LifeCycle Methods
			void Ready();
			void Process(float i_deltaTime);
			void PhysicsProcess(float i_fixedDeltaTime);
			void SetupRender();
			void Render(sf::RenderWindow* i_window);
			void RenderDebug(sf::RenderWindow* i_window);
			void Exit();

			// General Data Access/Update
			[[nodiscard]] size_t GetInstanceId() const;
			[[nodiscard]] std::string GetName() const;
			[[nodiscard]] std::string GetTag() const;
			void SetTag(std::string i_tag);

			// Pointer Helpers
			void AddToGlobalList() const;
			[[nodiscard]] Containers::SmartPtr<Node> GetSmartPointerRef() const;
			[[nodiscard]] Containers::WeakPtr<Node> GetWeakPointerRef() const;

			// Component Specific Data for Fast Access
			void __NotifyCollisionCallback(
				Containers::WeakPtr<Components::Physics::Colliders::BaseCollider> i_collider
			) const;
			void SetCollisionCallback(
				std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>)> i_function
			);
			void SetRenderOrder(float i_renderOrder);
			[[nodiscard]] float GetRenderOrder() const;
		};

		template <class T>
		Containers::WeakPtr<T> Node::AddComponent()
		{
			_nodeMutex.lock();

			T* tRawPtr = new T();
			auto* const tPtr = reinterpret_cast<Component*>(tRawPtr);
			Containers::SmartPtr<Component> tSmartRef(tPtr);

			const Containers::WeakPtr<Node> weakPtrRef(this->_selfSmartRef);
			tSmartRef->Ready(weakPtrRef);
			_components.push_back(tSmartRef);

			SortComponents();

			Containers::WeakPtr<T> weakPtrCopy(tSmartRef);

			_nodeMutex.unlock();
			return weakPtrCopy;
		}

		template <class T>
		void Node::RemoveComponent()
		{
			_nodeMutex.lock();
			int componentIndex = -1;

			for (auto component : _components)
			{
				if (component.CompareBaseType<T>())
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

			_nodeMutex.unlock();
		}

		template <class T>
		Containers::WeakPtr<T> Node::GetComponent()
		{
			_nodeMutex.lock();

			for (auto component : _components)
			{
				if (component.CompareBaseType<T>())
				{
					Containers::WeakPtr<T> weakPtrCopy(component);

					_nodeMutex.unlock();
					return weakPtrCopy;
				}
			}

			Containers::WeakPtr<T> weakPtr;

			_nodeMutex.unlock();
			return weakPtr;
		}
	}
}
