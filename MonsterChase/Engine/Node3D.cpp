#include "Node3D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			Node3D::Node3D()
			{
				_position = new Math::Point3D();
			}

			Node3D::~Node3D()
			{
				delete _position;
			}

			Math::Point3D* Node3D::GetPosition() const
			{
				return _position;
			}
		}
	}
}
