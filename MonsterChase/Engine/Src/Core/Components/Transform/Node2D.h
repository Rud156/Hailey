#pragma once
#include "../../BaseComponents/Component.h"

namespace Math
{
	class Point2D;
}

namespace Core::Components::Transform
{
	class Node2D final : public BaseComponents::Component
	{
	private:
		Math::Point2D* _position;

	public:
		Node2D();
		~Node2D();

		[[nodiscard]] Math::Point2D* GetPosition() const;
	};
}
