#include "Rotate2D.h"

#include "../../../Utils/Debug.h"

namespace Core::Components::Transform
{
	void Rotate2D::Rotate(const float i_degrees)
	{
		this->_angle += i_degrees;
	}

	void Rotate2D::SetAngle(const float i_angle)
	{
		this->_angle = i_angle;
	}

	float Rotate2D::GetAngle() const
	{
		return this->_angle;
	}
}
