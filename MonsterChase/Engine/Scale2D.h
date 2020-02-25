#pragma once
#include "Component.h"
#include "Point2D.h"

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
