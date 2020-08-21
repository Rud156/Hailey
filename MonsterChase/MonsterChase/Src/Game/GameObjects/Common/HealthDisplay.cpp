#include "HealthDisplay.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Maths/Point2D.h"

#include <cassert>

namespace Game::GameObjects::Common
{
#pragma region Overridden Parent

	void HealthDisplay::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		auto scale2d = i_node.Lock()->GetComponent<Core::Components::Transform::Scale2D>();
		auto spriteRenderer = i_node.Lock()->GetComponent<Core::Components::Rendering::SpriteRenderer>();
		assert(scale2d);

		this->_scale2d = scale2d.Lock();
	}


#pragma endregion

#pragma region External Functions

	void HealthDisplay::SetXScaleRatio(const float i_scaleRatio)
	{
		this->_defaultScaleRatio = i_scaleRatio;
	}

	void HealthDisplay::UpdateHealthDisplay(const float i_healthRatio)
	{
		assert(i_healthRatio <= 1);

		this->_scale2d->GetScale()->setX(i_healthRatio * this->_defaultScaleRatio);
	}

#pragma endregion
}
