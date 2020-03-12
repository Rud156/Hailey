#pragma once
#include "../../BaseComponents/Component.h"

namespace Math
{
	class Point3D;
}

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

				[[nodiscard]] Math::Point3D* GetPosition() const;
			};
		}
	}
}
