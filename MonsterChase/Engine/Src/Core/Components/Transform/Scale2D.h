#pragma once
#include "../../BaseComponents/Component.h"

namespace Math
{
	class Point2D;
}

namespace Core::Components::Transform
{
	class Scale2D final : public BaseComponents::Component
	{
	private:
		Math::Point2D* _scale;

	public:
		Scale2D();
		~Scale2D();

		Math::Point2D* GetScale() const;
	};
}
