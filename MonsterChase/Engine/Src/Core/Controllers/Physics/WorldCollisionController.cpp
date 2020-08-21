#include "WorldCollisionController.h"
#include "../GameObjectUpdater_Extern.h"
#include "../../../Containers/PointerIncludes.cpp"
#include "../../../Containers/WeakPtr.h"
#include "../../../Utils/CollisionUtils.h"
#include "../../../Utils/Debug.h"
#include "../../../Utils/MathUtils.h"
#include "../../BaseComponents/Node.h"
#include "../../Components/Physics/Rigidbody2D.h"
#include "../../Components/Physics/Colliders/RectangleCollider.h"

#include <cstdint>
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
		std::lock_guard<std::mutex> lockGuard(this->_worldCollisionMutex);

		if (this->_worldObjectColliders.size() <= 1)
		{
			return;
		}

		for (size_t i = 0; i < this->_worldObjectColliders.size() - 1; i++)
		{
			for (size_t j = i + 1; j < this->_worldObjectColliders.size(); j++)
			{
				const auto collisionResult = CheckCollision(this->_worldObjectColliders[i],
				                                            this->_worldObjectColliders[j],
				                                            i_deltaTime);
				if (collisionResult.collided)
				{
					if (this->_worldObjectColliders[i].collisionCallback)
					{
						this->_worldObjectColliders[i].collisionCallback(
							Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>
							(this->_worldObjectColliders[j].collider),
							collisionResult.collisionNormal
						);
					}

					if (this->_worldObjectColliders[j].collisionCallback)
					{
						this->_worldObjectColliders[j].collisionCallback(
							Containers::WeakPtr<Components::Physics::Colliders::BaseCollider>
							(this->_worldObjectColliders[i].collider),
							collisionResult.collisionNormal
						);
					}
				};
			}
		}
	}

	void WorldCollisionController::UpdateCollisionCheckData()
	{
		std::lock_guard<std::mutex> lockGuard(this->_worldCollisionMutex);

		for (auto& worldObjectCollider : this->_worldObjectColliders)
		{
			auto collider = worldObjectCollider.collider;
			const float rotationAngle = collider->GetColliderNormalizedAngle();

			const auto rotationMatrix = Math::Matrix4::CreateZRotationCV(rotationAngle * Utils::MathUtils::Deg2Rad);
			auto position = collider->GetColliderCenter();

			const auto objectToWorld = Math::Matrix4::CreateTranslationCV(position) * rotationMatrix;
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
			worldObjectCollider.colliderExtents = collider->GetColliderExtents();
			worldObjectCollider.collisionCallback = collider->GetNode().Lock()->__GetCollisionCallback();
		}
	}

	WorldCollisionController::CollisionHitResult WorldCollisionController::CheckCollision(
		CollisionCacheData& i_collision_1,
		CollisionCacheData& i_collision_2, float i_deltaTime)
	const
	{
		// Find Normal to Latest TClose and then reflect velocity based on that

		__int16 group1 = i_collision_1.collider->GetGroupIndex();
		__int16 group2 = i_collision_2.collider->GetGroupIndex();

		if (group1 == 0 || group2 == 0 || (group1 != 0 && group2 != 0 && group1 != group2))
		{
			uint16_t category1 = i_collision_1.collider->GetCategoryBits();
			uint16_t mask1 = i_collision_1.collider->GetMaskBits();
			uint16_t category2 = i_collision_2.collider->GetCategoryBits();
			uint16_t mask2 = i_collision_2.collider->GetMaskBits();

			if ((category1 & mask2) != 0 && (category2 & mask1) != 0)
			{
				// Then Collide
			}
			else
			{
				return WorldCollisionController::CollisionHitResult({
					false,
					Math::Point2D()
				});
			}
		}
		else if (group1 < 0 && group2 < 0 && group1 == group2)
		{
			return WorldCollisionController::CollisionHitResult({
				false,
				Math::Point2D()
			});
		}


		float latestTClose = std::numeric_limits<float>::min();
		float earliestTOpen = std::numeric_limits<float>::max();
		WorldCollisionController::CollisionHitResult hitResult = WorldCollisionController::CollisionHitResult();

		// Object A In B
		{
			auto matrixWorldToB = Math::Matrix4();
			matrixWorldToB = i_collision_2.objectToWorld;
			matrixWorldToB.Inverse();

			const Math::Point3D velARelToB = i_collision_1.velocity - i_collision_2.velocity;
			const Math::Point4D aVelocityInB = matrixWorldToB * Math::Point4D(velARelToB, 0);

			const auto matrixAToB = matrixWorldToB * i_collision_1.objectToWorld;
			const auto aCenterInB = matrixAToB * i_collision_1.centerInWorld;

			const auto aExtentXInB = matrixAToB * Math::Point4D(i_collision_1.colliderExtents.X(), 0, 0,
			                                                    0);
			const auto aExtentYInB = matrixAToB * Math::Point4D(0, i_collision_1.colliderExtents.Y(), 0,
			                                                    0);

			// X Axis
			{
				const float aProjectionOnToB_X = std::fabs(aExtentXInB.X()) + std::fabs(aExtentYInB.X());

				const float bExtents = i_collision_2.colliderExtents.X() + aProjectionOnToB_X;
				const float bLeft = i_collision_2.centerInWorld.X() - bExtents;
				const float bRight = i_collision_2.centerInWorld.X() + bExtents;

				const float dClose = bLeft - aCenterInB.X();
				const float dOpen = bRight - aCenterInB.X();

				auto bCenter = i_collision_2.collider->GetColliderCenter();
				auto bExtentsOriginal = i_collision_2.collider->GetColliderExtents();
				auto bLeftOriginal = bCenter + Math::Point2D(-bExtentsOriginal.X(), bExtentsOriginal.Y());
				auto bRightOriginal = bCenter + Math::Point2D(bExtentsOriginal.X(), bExtentsOriginal.Y());
				auto bRotatedLeft = Utils::CollisionUtils::RotatePointAroundOrigin(
					bLeftOriginal, bCenter, i_collision_2.collider->GetColliderNormalizedAngle());
				auto bRotatedRight = Utils::CollisionUtils::RotatePointAroundOrigin(
					bRightOriginal, bCenter, i_collision_2.collider->GetColliderNormalizedAngle());
				auto xAxisNormal = Utils::CollisionUtils::Get2DNormal(bRotatedLeft, bRotatedRight);

				if (Utils::MathUtils::IsZero(aVelocityInB.X()))
				{
					const bool isSeparated = aCenterInB.X() < bLeft || aCenterInB.X() > bRight;
					if (isSeparated)
					{
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}
					else
					{
						hitResult.collisionNormal = xAxisNormal;
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
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						hitResult.collisionNormal = xAxisNormal;
						latestTClose = tClose;
					}
				}
			}

			// Y Axis
			{
				const float aProjectionOnToB_Y = std::fabs(aExtentXInB.Y()) + std::fabs(aExtentYInB.Y());

				const float bExtents = i_collision_2.colliderExtents.Y() + aProjectionOnToB_Y;
				const float bTop = i_collision_2.centerInWorld.Y() - bExtents;
				const float bBottom = i_collision_2.centerInWorld.Y() + bExtents;

				const float dClose = bTop - aCenterInB.Y();
				const float dOpen = bBottom - aCenterInB.Y();

				auto bCenter = i_collision_2.collider->GetColliderCenter();
				auto bExtentsOriginal = i_collision_2.collider->GetColliderExtents();
				auto bTopOriginal = bCenter + Math::Point2D(bExtentsOriginal.X(), -bExtentsOriginal.Y());
				auto bBottomOriginal = bCenter + Math::Point2D(bExtentsOriginal.X(), bExtentsOriginal.Y());
				auto bRotatedTop = Utils::CollisionUtils::RotatePointAroundOrigin(
					bTopOriginal, bCenter, i_collision_2.collider->GetColliderNormalizedAngle());
				auto bRotatedBottom = Utils::CollisionUtils::RotatePointAroundOrigin(
					bBottomOriginal, bCenter, i_collision_2.collider->GetColliderNormalizedAngle());
				auto yAxisNormal = Utils::CollisionUtils::Get2DNormal(bRotatedTop, bRotatedBottom);

				if (Utils::MathUtils::IsZero(aVelocityInB.Y()))
				{
					const bool isSeparated = aCenterInB.Y() < bTop || aCenterInB.Y() > bBottom;
					if (isSeparated)
					{
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}
					else
					{
						hitResult.collisionNormal = yAxisNormal;
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
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						hitResult.collisionNormal = yAxisNormal;
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

			const auto bExtentXInA = matrixBToA * Math::Point4D(i_collision_2.colliderExtents.X(), 0, 0,
			                                                    0);
			const auto bExtentYInA = matrixBToA * Math::Point4D(0, i_collision_2.colliderExtents.Y(), 0,
			                                                    0);
			// X Axis
			{
				const float bProjectionOnToA_X = std::fabs(bExtentXInA.X()) + std::fabs(bExtentYInA.X());

				const float aExtents = i_collision_1.colliderExtents.X() + bProjectionOnToA_X;
				const float aLeft = i_collision_1.centerInWorld.X() - aExtents;
				const float aRight = i_collision_1.centerInWorld.X() + aExtents;

				const float dClose = aLeft - bCenterInA.X();
				const float dOpen = aRight - bCenterInA.X();

				auto aCenter = i_collision_1.collider->GetColliderCenter();
				auto aExtentsOriginal = i_collision_1.collider->GetColliderExtents();
				auto aLeftOriginal = aCenter + Math::Point2D(-aExtentsOriginal.X(), aExtentsOriginal.Y());
				auto aRightOriginal = aCenter + Math::Point2D(aExtentsOriginal.X(), aExtentsOriginal.Y());
				auto aRotatedLeft = Utils::CollisionUtils::RotatePointAroundOrigin(
					aLeftOriginal, aCenter, i_collision_1.collider->GetColliderNormalizedAngle());
				auto aRotatedRight = Utils::CollisionUtils::RotatePointAroundOrigin(
					aRightOriginal, aCenter, i_collision_1.collider->GetColliderNormalizedAngle());
				auto xAxisNormal = Utils::CollisionUtils::Get2DNormal(aRotatedLeft, aRotatedRight);

				if (Utils::MathUtils::IsZero(bVelocityInA.X()))
				{
					const bool isSeparated = bCenterInA.X() < aLeft || bCenterInA.X() > aRight;
					if (isSeparated)
					{
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}
					else
					{
						hitResult.collisionNormal = xAxisNormal;
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
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						hitResult.collisionNormal = xAxisNormal;
						latestTClose = tClose;
					}
				}
			}

			// Y Axis
			{
				const float bProjectionOnToA_Y = std::fabs(bExtentXInA.X()) + std::fabs(bExtentYInA.X());

				const float aExtents = i_collision_1.colliderExtents.Y() + bProjectionOnToA_Y;
				const float aTop = i_collision_1.centerInWorld.Y() - aExtents;
				const float aBottom = i_collision_1.centerInWorld.Y() + aExtents;

				const float dClose = aTop - bCenterInA.Y();
				const float dOpen = aBottom - bCenterInA.Y();

				auto aCenter = i_collision_1.collider->GetColliderCenter();
				auto aExtentsOriginal = i_collision_1.collider->GetColliderExtents();
				auto aTopOriginal = aCenter + Math::Point2D(aExtentsOriginal.X(), -aExtentsOriginal.Y());
				auto aBottomOriginal = aCenter + Math::Point2D(aExtentsOriginal.X(), aExtentsOriginal.Y());
				auto aRotatedTop = Utils::CollisionUtils::RotatePointAroundOrigin(
					aTopOriginal, aCenter, i_collision_1.collider->GetColliderNormalizedAngle());
				auto aRotatedBottom = Utils::CollisionUtils::RotatePointAroundOrigin(
					aBottomOriginal, aCenter, i_collision_1.collider->GetColliderNormalizedAngle());
				auto yAxisNormal = Utils::CollisionUtils::Get2DNormal(aRotatedTop, aRotatedBottom);

				if (Utils::MathUtils::IsZero(bVelocityInA.Y()))
				{
					const bool isSeparated = bCenterInA.Y() < aTop || bCenterInA.Y() > aBottom;
					if (isSeparated)
					{
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}
					else
					{
						hitResult.collisionNormal = yAxisNormal;
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
						return WorldCollisionController::CollisionHitResult({
							false,
							Math::Point2D()
						});
					}

					if (tOpen < earliestTOpen)
					{
						earliestTOpen = tOpen;
					}
					if (tClose > latestTClose)
					{
						hitResult.collisionNormal = yAxisNormal;
						latestTClose = tClose;
					}
				}
			}
		}

		const bool didCollide = !(earliestTOpen < latestTClose);
		hitResult.collided = didCollide;
		return hitResult;
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
			auto position = i_collider->GetColliderCenter();

			const auto objectToWorld = Math::Matrix4::CreateTranslationCV(position) * orientationInWorld;
			const auto centerInWorld = objectToWorld * Math::Point4D(position, 0, 1);

			auto rigidBody = i_collider->GetNode().Lock()->GetComponent<Components::Physics::Rigidbody2D>();
			Math::Point3D velocity = Math::Point3D();
			if (rigidBody)
			{
				velocity = Math::Point3D(*rigidBody.Lock()->GetVelocity(), 0);
			}

			this->_worldObjectColliders.push_back({
				i_collider, objectToWorld, centerInWorld, velocity,
				i_collider->GetColliderExtents(),
				i_collider->GetNode().Lock()->__GetCollisionCallback()
			});
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
		UpdateCollisionCheckData();
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
