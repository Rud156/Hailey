#pragma once
#include "Component.h"
#include "Point3D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			class Node3D final : public BaseComponents::Component
			{
			private:
				Math::Point3D* _position;

			public:
				Node3D();
				~Node3D();

				Math::Point3D* GetPosition() const;
			};
		}
	}
}
