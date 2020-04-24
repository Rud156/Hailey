#pragma once
#include "../../BaseComponents/Component.h"
#include "../../../Containers/SmartPtr.h"
#include "../../../Containers/WeakPtr.h"
#include "../../BaseComponents/Node.h"
#include "../Transform/Node2D.h"
#include "../Transform/Rotate2D.h"
#include "../Transform/Scale2D.h"

#include <string>

namespace sf
{
	class Sprite;
	class Texture;
}

namespace Core
{
	namespace Components
	{
		namespace Rendering
		{
			class SpriteRenderer final : public BaseComponents::Component
			{
			private:
				Containers::SmartPtr<Transform::Node2D> _node2d;
				Containers::SmartPtr<Transform::Rotate2D> _rotate2d;
				Containers::SmartPtr<Transform::Scale2D> _scale2d;

				sf::Sprite* _sprite;
				sf::Texture* _texture;

				bool _isVisible;
				float _depthLayer;

			public:
				SpriteRenderer();
				~SpriteRenderer();

				// Parent Overrides
				void Ready(Containers::WeakPtr<BaseComponents::Node> i_node) override;
				void SetupRender() override;
				void Render(sf::RenderWindow* i_window) override;

				void LoadEmpty();
				void LoadTexture(const std::string& i_filePath);

				[[nodiscard]] sf::Sprite* GetSprite() const;
				void SetSpriteDepth(float i_depthLayer);
				[[nodiscard]] float GetSpriteDepth() const;

				[[nodiscard]] bool GetIsVisible() const;
				void SetIsVisible(bool i_value);
			};
		}
	}
}
