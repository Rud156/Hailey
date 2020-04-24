#include "WorldCollisionController.h"
#include "../GameObjectUpdater_Extern.h"
#include "../../BaseComponents/Node.h"
#include "../../../Containers/WeakPtr.h"
#include "../../../Maths/Point2D.h"
#include "../../Components/Physics/Rigidbody2D.h"
#include "../../../Containers/PointerIncludes.cpp"
#include "../../../Utils/MathUtils.h"
#include "../../Components/Physics/Colliders/RectangleCollider.h"

#include <limits>

Core::Controllers::Physics::WorldCollisionController* worldCollisionController = nullptr;

namespace Core::Controllers::Physics
{
#pragma region Constrcutor and Destructor

	WorldCollisionController::WorldCollisionController()
	{
		worldCollisionController = this;
	}

	WorldCollisionController::~WorldCollisionController()
	{
		worldCollisionController = nullptr;
	}

#pragma endregion

#pragma region Collision

	void WorldCollisionController::ProcessCollisions(float i_deltaTime)
	{
		this->_worldCollisionMutex.lock();

		UpdateCollisionCheckData();

		if (this->_worldObjectColliders.size() <= 1)
		{
			this->_worldCollisionMutex.unlock();
			return;
		}

		for (size_t i = 0; i < this->_worldObjectColliders.size() - 1; i++)
		{
			for (size_t j = i + 1; j < this->_worldObjectColliders.size(); j++)
			{
				if (CheckCollision(this->_worldObjectColliders[i], this->_worldObjectColliders[j],
				                   i_deltaTime))
				{
					this->_worldObjectColliders[i].collider->GetNode().Lock()->__NotifyCollisionCallback(
						Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>
						(this->_worldObjectColliders[j].collider)
					);

					this->_worldObjectColliders[j].collider->GetNode().Lock()->__NotifyCollisionCallback(
						Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>
						(this->_worldObjectColliders[i].collider)
					);
				};
			}
		}

		this->_worldCollisionMutex.unlock();
	}

	void WorldCollisionController::UpdateCollisionCheckData()
	{
		for (auto& worldObjectCollider : this->_worldObjectColliders)
		{
			auto collider = worldObjectCollider.collider;
			const float rotationAngle = collider->GetColliderNormalizedAngle();

			const auto rotationMatrix = Math::Matrix4::CreateZRotationCV(rotationAngle * Utils::MathUtils::Deg2Rad);
			auto* const position = collider->GetColliderCenter();

			const auto objectToWorld = Math::Matrix4::CreateTranslationCV(*position) * rotationMatrix;
			const auto centerInWorld = Math::Point4D(0, 0, 0, 1);

			auto rigidBody = collider->GetNode().Lock()->GetComponent<Components::Physics::Rigidbody2D>();
			Math::Point3D velocity = Math::Point3D();
			if (rigidBody)
			{
				velocity = Math::Point3D(*rigidBody.Lock()->GetVelocity(), 0);
			}

			worldObjectCollider.objectToWorld = objectToWorld;
			worldObjectCollider.centerInWorld = centerInWorld;
			worldObjectCollider.velocity = velocity;
		}
	}

	bool WorldCollisionController::CheckCollision(CollisionCacheData& i_collision_1,
	                                              CollisionCacheData& i_collision_2, float i_deltaTime)
	const
	{
		float latestTClose = std::numeric_limits<float>::min();
		float earliestTOpen = std::numeric_limits<float>::max();

		// Object A In B
		{
			auto matrixWorldToB = Math::Matrix4();
			matrixWorldToB = i_collision_2.objectToWorld;
			matrixWorldToB.Inverse();

			const Math::Point3D velARelToB = i_collision_1.velocity - i_collision_2.velocity;
			const Math::Point4D aVelocityInB = matrixWorldToB * Math::Point4D(velARelToB, 0);

			const auto matrixAToB = matrixWorldToB * i_collision_1.objectToWorld;
			const auto aCenterInB = matrixAToB * i_collision_1.centerInWorld;

			const auto aExtentXInB = matrixAToB * Math::Point4D(i_collision_1.collider->GetColliderExtents().X(), 0, 0,
			                                                    0);
			const auto aExtentYInB = matrixAToB * Math::Point4D(0, i_collision_1.collider->GetColliderExtents().Y(), 0,
			                                                    0);

			// X Axis
			{
				const float aProjectionOnToB_X = std::fabs(aExtentXInB.X()) + std::fabs(aExtentYInB.X());

				const float bExtents = i_collision_2.collider->GetColliderExtents().X() + aProjectionOnToB_X;
				const float bLeft = i_collision_2.centerInWorld.X() - bExtents;
				const float bRight = i_collision_2.centerInWorld.X() + bExtents;

				const float dClose = bLeft - aCenterInB.X();
				const float dOpen = bRight - aCenterInB.X();

				if (Utils::MathUtils::IsZero(aVelocityInB.X()))
				{
					const bool isSeparated = aCenterInB.X() < bLeft || aCenterInB.X() > bRight;
					if (isSeparated)
					{
						return false;
					}
				}
				else
				{
					float tClose = dClose / aVelocityInB.X();
					float tOpen = dOpen / aVelocityInB.X();

					if (tOpen < tClose)
					{
						const auto temp = tOpen;
						tOpen = tClose;
						tClose = temp;
					}

					if (tOpen < 0 || tClose > i_deltaTime)
					{
						return false;
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						latestTClose = tClose;
					}
				}
			}

			// Y Axis
			{
				const float aProjectionOnToB_Y = std::fabs(aExtentXInB.Y()) + std::fabs(aExtentYInB.Y());

				const float bExtents = i_collision_2.collider->GetColliderExtents().Y() + aProjectionOnToB_Y;
				const float bTop = i_collision_2.centerInWorld.Y() - bExtents;
				const float bBottom = i_collision_2.centerInWorld.Y() + bExtents;

				const float dClose = bTop - aCenterInB.Y();
				const float dOpen = bBottom - aCenterInB.Y();

				if (Utils::MathUtils::IsZero(aVelocityInB.Y()))
				{
					const bool isSeparated = aCenterInB.Y() < bTop || aCenterInB.Y() > bBottom;
					if (isSeparated)
					{
						return false;
					}
				}
				else
				{
					float tClose = dClose / aVelocityInB.Y();
					float tOpen = dOpen / aVelocityInB.Y();

					if (tOpen < tClose)
					{
						const auto temp = tOpen;
						tOpen = tClose;
						tClose = temp;
					}

					if (tOpen < 0 || tClose > i_deltaTime)
					{
						return false;
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						latestTClose = tClose;
					}
				}
			}
		}

		// Object B In A
		{
			auto matrixWorldToA = Math::Matrix4();
			matrixWorldToA = i_collision_1.objectToWorld;
			matrixWorldToA.Inverse();

			const Math::Point3D velBRelToA = i_collision_2.velocity - i_collision_1.velocity;
			const Math::Point4D bVelocityInA = matrixWorldToA * Math::Point4D(velBRelToA, 0);

			const auto matrixBToA = matrixWorldToA * i_collision_2.objectToWorld;
			const auto bCenterInA = matrixBToA * i_collision_2.centerInWorld;

			const auto bExtentXInA = matrixBToA * Math::Point4D(i_collision_2.collider->GetColliderExtents().X(), 0, 0,
			                                                    0);
			const auto bExtentYInA = matrixBToA * Math::Point4D(0, i_collision_2.collider->GetColliderExtents().Y(), 0,
			                                                    0);
			// X Axis
			{
				const float bProjectionOnToA_X = std::fabs(bExtentXInA.X()) + std::fabs(bExtentYInA.X());

				const float aExtents = i_collision_1.collider->GetColliderExtents().X() + bProjectionOnToA_X;
				const float aLeft = i_collision_1.centerInWorld.X() - aExtents;
				const float aRight = i_collision_1.centerInWorld.X() + aExtents;

				const float dClose = aLeft - bCenterInA.X();
				const float dOpen = aRight - bCenterInA.X();

				if (Utils::MathUtils::IsZero(bVelocityInA.X()))
				{
					const bool isSeparated = bCenterInA.X() < aLeft || bCenterInA.X() > aRight;
					if (isSeparated)
					{
						return false;
					}
				}
				else
				{
					float tClose = dClose / bVelocityInA.X();
					float tOpen = dOpen / bVelocityInA.X();

					if (tOpen < tClose)
					{
						const auto temp = tOpen;
						tOpen = tClose;
						tClose = temp;
					}

					if (tOpen < 0 || tClose > i_deltaTime)
					{
						return false;
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						latestTClose = tClose;
					}
				}
			}

			// Y Axis
			{
				const float bProjectionOnToA_Y = std::fabs(bExtentXInA.X()) + std::fabs(bExtentYInA.X());

				const float aExtents = i_collision_1.collider->GetColliderExtents().Y() + bProjectionOnToA_Y;
				const float aTop = i_collision_1.centerInWorld.Y() - aExtents;
				const float aBottom = i_collision_1.centerInWorld.Y() + aExtents;

				const float dClose = aTop - bCenterInA.Y();
				const float dOpen = aBottom - bCenterInA.Y();

				if (Utils::MathUtils::IsZero(bVelocityInA.Y()))
				{
					const bool isSeparated = bCenterInA.Y() < aTop || bCenterInA.Y() > aBottom;
					if (isSeparated)
					{
						return false;
					}
				}
				else
				{
					float tClose = dClose / bVelocityInA.Y();
					float tOpen = dOpen / bVelocityInA.Y();

					if (tOpen < tClose)
					{
						const auto temp = tOpen;
						tOpen = tClose;
						tClose = temp;
					}

					if (tOpen < 0 || tClose > i_deltaTime)
					{
						return false;
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						latestTClose = tClose;
					}
				}
			}
		}

		return !(earliestTOpen < latestTClose);
	}

#pragma endregion

#pragma region Collision Array Modification

	void WorldCollisionController::AddColliderToWorld(
		Containers::SmartPtr<Components::Physics::Colliders::BaseCollider> i_collider
	)
	{
		this->_worldCollisionMutex.lock();

		size_t instanceId = i_collider->GetInstanceId();
		const auto index = std::find_if(this->_worldObjectColliders.begin(), this->_worldObjectColliders.end(),
		                                [&instanceId](
		                                CollisionCacheData collisionCacheData)
		                                {
			                                return collisionCacheData.collider->GetInstanceId() == instanceId;
		                                });
		if (index == this->_worldObjectColliders.end())
		{
			const float rotationAngle = i_collider->GetColliderNormalizedAngle();

			const auto orientationInWorld = Math::Matrix4::CreateZRotationCV(rotationAngle);
			auto* const position = i_collider->GetColliderCenter();

			const auto objectToWorld = Math::Matrix4::CreateTranslationCV(*position) * orientationInWorld;
			const auto centerInWorld = objectToWorld * Math::Point4D(*position, 0, 1);

			auto rigidBody = i_collider->GetNode().Lock()->GetComponent<Components::Physics::Rigidbody2D>();
			Math::Point3D velocity = Math::Point3D();
			if (rigidBody)
			{
				velocity = Math::Point3D(*rigidBody.Lock()->GetVelocity(), 0);
			}

			this->_worldObjectColliders.push_back({i_collider, objectToWorld, centerInWorld, velocity});
		}

		this->_worldCollisionMutex.unlock();
	}

	void WorldCollisionController::RemoveColliderFromWorld(
		Containers::SmartPtr<Components::Physics::Colliders::BaseCollider> i_collider
	)
	{
		this->_worldCollisionMutex.lock();

		size_t instanceId = i_collider->GetInstanceId();
		const auto index = std::find_if(this->_worldObjectColliders.begin(), this->_worldObjectColliders.end(),
		                                [&instanceId](
		                                CollisionCacheData collisionCacheData)
		                                {
			                                return collisionCacheData.collider->GetInstanceId() == instanceId;
		                                });
		if (index != this->_worldObjectColliders.end())
		{
			this->_worldObjectColliders.erase(index);
		}

		this->_worldCollisionMutex.unlock();
	}

#pragma endregion

#pragma region LifeCycle Functions

	void WorldCollisionController::Process(float i_deltaTime)
	{
		ProcessCollisions(i_deltaTime);
	}

	void WorldCollisionController::RenderDebug(sf::RenderWindow* i_window)
	{
#ifdef _DEBUG
		auto nodes = gameObjectUpdater->GetAllGameObjects();
		for (auto node : nodes)
		{
			node->RenderDebug(i_window);
		}

#endif
	}

	void WorldCollisionController::Exit()
	{
		this->_worldCollisionMutex.lock();
		this->_worldObjectColliders.clear();
		this->_worldCollisionMutex.unlock();
	}

#pragma endregion
}
