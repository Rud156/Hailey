#include "Node2D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			Node2D::Node2D()
			{
				_position = new Math::Point2D();
			}

			Node2D::~Node2D()
			{
				delete _position;
			}

			Math::Point2D* Node2D::GetPosition() const
			{
				return _position;
			}
		}
	}
}
