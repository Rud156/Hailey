#pragma once
#include "../../../Containers/SmartPtr.h"
#include "../../Components/Physics/Colliders/BaseCollider.h"
#include "../../../Maths/Matrix4.h"
#include "../../../Maths/Point4D.h"

#include <vector>
#include <future>

namespace sf
{
	class RenderWindow;
}

namespace Core::Controllers::Physics
{
	class WorldCollisionController
	{
	private:
		struct CollisionCacheData
		{
			Containers::SmartPtr<Components::Physics::Colliders::BaseCollider> collider;

			Math::Matrix4 objectToWorld;
			Math::Point4D centerInWorld;
			Math::Point3D velocity;
		};

		std::vector<CollisionCacheData> _worldObjectColliders;
		std::mutex _worldCollisionMutex;

		// Collision
		void ProcessCollisions(float i_deltaTime);
		void UpdateCollisionCheckData();
		bool CheckCollision(CollisionCacheData& i_collision_1, CollisionCacheData& i_collision_2,
		                    float i_deltaTime) const;

	public:
		// Constructor and Destructor
		WorldCollisionController();
		~WorldCollisionController();

		// Collision Array Modification
		void AddColliderToWorld(Containers::SmartPtr<Components::Physics::Colliders::BaseCollider> i_collider);
		void RemoveColliderFromWorld(Containers::SmartPtr<Components::Physics::Colliders::BaseCollider> i_collider);

		// LifeCycle Functions
		void Process(float i_deltaTime);
		static void RenderDebug(sf::RenderWindow* i_window);
		void Exit();
	};
}
