#pragma once
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Scale2D.h"

namespace Game::GameObjects::Common
{
	class HealthDisplay : public Core::BaseComponents::Component
	{
	private:
		Containers::SmartPtr<Core::Components::Transform::Scale2D> _scale2d;

		float _defaultScaleRatio = 1;

	public:
		// Overridden Parent
		void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;

		// External Functions
		void SetXScaleRatio(float i_scaleRatio);
		void UpdateHealthDisplay(float i_healthRatio);
	};
}
