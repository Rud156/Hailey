#pragma once
#include "../../BaseComponents/Component.h"

namespace Core::Components::Transform
{
	class Rotate2D final : public BaseComponents::Component
	{
	private:
		float _angle = 0;

	public:
		void Rotate(float i_degrees);
		void SetAngle(float i_angle);
		[[nodiscard]] float GetAngle() const;
	};
}
