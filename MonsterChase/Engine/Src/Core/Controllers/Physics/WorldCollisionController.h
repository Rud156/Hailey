#pragma once
#include "../../../Containers/SmartPtr.h"
#include "../../../Maths/Matrix4.h"
#include "../../../Maths/Point2D.h"
#include "../../../Maths/Point3D.h"
#include "../../../Maths/Point4D.h"
#include "../../Components/Physics/Colliders/BaseCollider.h"

#include <mutex>
#include <vector>

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
			Math::Point2D colliderExtents;

			std::function<void(Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>, Math::Point2D)>
			collisionCallback;
		};

		struct CollisionHitResult
		{
			bool collided;
			Math::Point2D collisionNormal;
		};

		std::vector<CollisionCacheData> _worldObjectColliders;
		std::mutex _worldCollisionMutex;

		// Collision
		void ProcessCollisions(float i_deltaTime);
		void UpdateCollisionCheckData();
		[[nodiscard]] CollisionHitResult CheckCollision(CollisionCacheData& i_collision_1,
		                                                CollisionCacheData& i_collision_2,
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
