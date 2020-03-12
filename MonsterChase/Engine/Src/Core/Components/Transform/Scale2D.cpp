#include "Scale2D.h"
#include "../../../Maths/Point2D.h"

namespace Core::Components::Transform
{
	Scale2D::Scale2D()
	{
		this->_scale = new Math::Point2D(1, 1);
	}

	Scale2D::~Scale2D()
	{
		delete this->_scale;
	}

	Math::Point2D* Scale2D::GetScale() const
	{
		return this->_scale;
	}
}
