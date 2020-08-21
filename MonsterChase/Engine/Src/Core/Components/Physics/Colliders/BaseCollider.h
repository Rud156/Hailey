#pragma once
#include "../../../BaseComponents/Component.h"
#include "../../../../Containers/SmartPtr.h"
#include "../../../../Containers/WeakPtr.h"
#include "../../Transform/Node2D.h"
#include "../../Transform/Rotate2D.h"
#include "../../../BaseComponents/Node.h"

#include <cstdint>

namespace Math
{
	class Point2D;
}

// Set Initial Extents from SpriteRender if it exists
namespace Core::Components::Physics::Colliders
{
	class BaseCollider : public BaseComponents::Component
	{
	public:
		enum class ColliderType
		{
			None,
			Rectangle,
			Circle
		};

	protected:
		size_t _instanceId;
		ColliderType _colliderType;

		Math::Point2D* _center;
		Math::Point2D* _offset;

		__int16 _groupIndex;
		uint16_t _categoryBits;
		uint16_t _maskBits;

		Containers::SmartPtr<Transform::Node2D> _node2d;
		Containers::SmartPtr<Transform::Rotate2D> _rotate2d;

	public:
		BaseCollider();
		virtual ~BaseCollider();
		void Ready(Containers::WeakPtr<BaseComponents::Node> i_node) override; // Probably not required to be overridden
		void Process(float) override;
		void Exit() override;

		// Getters And Setters
		[[nodiscard]] size_t GetInstanceId() const;
		[[nodiscard]] ColliderType GetColliderType() const;
		[[nodiscard]] virtual float GetColliderNormalizedAngle();;
		[[nodiscard]] Math::Point2D GetColliderCenter() const;
		[[nodiscard]] Math::Point2D GetColliderOffset() const;
		[[nodiscard]] virtual Math::Point2D GetColliderExtents();
		void SetColliderOffset(float i_x, float i_y);
		void SetColliderOffset(Math::Point2D& i_point2d);

		// Category, Mask and Group
		[[nodiscard]] __int16 GetGroupIndex() const;
		void SetGroupIndex(__int16 i_groupIndex);
		[[nodiscard]] uint16_t GetCategoryBits() const;
		void SetCategoryBits(uint16_t i_categoryBits);
		[[nodiscard]] uint16_t GetMaskBits() const;
		void SetMaskBits(uint16_t i_maskBits);
	};
}
