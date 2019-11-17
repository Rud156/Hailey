#pragma once
#include "Component.h"
#include "Point2D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			class Node2D final : public Component
			{
			private:
				Math::Point2D* _position;

			public:
				Node2D();
				~Node2D();

				Math::Point2D* GetPosition() const;
			};
		}
	}
}
