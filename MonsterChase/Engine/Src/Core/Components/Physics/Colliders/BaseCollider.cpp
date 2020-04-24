#include "BaseCollider.h"
#include "../../../../Containers/PointerIncludes.cpp"
#include "../../../../Maths/Point2D.h"
#include "../../../../Containers/WeakPtr.h"
#include "../../../../Utils/Uuid.h"
#include "../../../Controllers/Physics/WorldCollisionController_Extern.h"
#include "../../../../Utils/Debug.h"

#include <cassert>

namespace Core::Components::Physics::Colliders
{
	BaseCollider::BaseCollider()
	{
		this->_instanceId = Utils::Uuid::GetUuid();
		this->_center = new Math::Point2D();
		this->_offset = new Math::Point2D();
		this->_colliderType = ColliderType::None;
	}

	BaseCollider::~BaseCollider()
	{
		delete this->_center;
		delete this->_offset;
	}

	void BaseCollider::Ready(Containers::WeakPtr<BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		this->_colliderType = ColliderType::None;
		Containers::SmartPtr<BaseComponents::Node> node = i_node.Lock();
		Containers::WeakPtr<Transform::Node2D> node2d = node->GetComponent<Transform::Node2D>();
		Containers::WeakPtr<Transform::Rotate2D> rotate2d = node->GetComponent<Transform::Rotate2D>();
		const Containers::WeakPtr<BaseCollider> collider = node->GetComponent<BaseCollider>();

		assert(node2d);
		assert(rotate2d);

		if (collider)
		{
			Utils::Debug::LogOutputToWindow("Collider Already Exists On This GameObject");
			assert(false);
		}

		this->_node2d = node2d.Lock();
		this->_rotate2d = rotate2d.Lock();
	}

	void BaseCollider::Process(float)
	{
		auto* const position = this->_node2d->GetPosition();
		this->_center->set(position->X() + this->_offset->X(), position->Y() + this->_offset->Y());
	}

	void BaseCollider::Exit()
	{
		const Containers::SmartPtr<BaseCollider> smartRef = this->_node.Lock()->GetComponent<BaseCollider>().Lock();
		worldCollisionController->RemoveColliderFromWorld(smartRef);
	}

#pragma region Getters And Setters

	size_t BaseCollider::GetInstanceId() const
	{
		return this->_instanceId;
	}

	BaseCollider::ColliderType BaseCollider::GetColliderType() const
	{
		return this->_colliderType;
	}

	float BaseCollider::GetColliderNormalizedAngle()
	{
		return this->_rotate2d->GetAngle();
	}

	Math::Point2D* BaseCollider::GetColliderCenter() const
	{
		return this->_center;
	}

	Math::Point2D* BaseCollider::GetColliderOffset() const
	{
		return this->_offset;
	}

	Math::Point2D BaseCollider::GetColliderExtents()
	{
		return Math::Point2D();
	}

	void BaseCollider::SetColliderOffset(const float i_x, const float i_y)
	{
		this->_offset->set(i_x, i_y);

		auto* const position = this->_node2d->GetPosition();
		this->_center->set(position->X() + i_x, position->Y() + i_y);
	}

	void BaseCollider::SetColliderOffset(Math::Point2D& i_point2d)
	{
		this->_offset->set(i_point2d.X(), i_point2d.Y());

		auto* const position = this->_node2d->GetPosition();
		this->_center->set(position->X() + i_point2d.X(), position->Y() + i_point2d.Y());
	}

	void BaseCollider::AddToWorld()
	{
		const Containers::SmartPtr<BaseCollider> smartRef = this->_node.Lock()->GetComponent<BaseCollider>().Lock();
		worldCollisionController->AddColliderToWorld(smartRef);
	}

#pragma endregion
}
