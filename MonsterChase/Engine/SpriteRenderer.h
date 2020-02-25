#pragma once
#include "Component.h"
#include "Point3D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			class Node2D;
			class Rotate2D;
			class Scale2D;
		}
	}

	namespace BaseComponents
	{
		class Node;
	}
}

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
			// TODO: Z Ordering of Sprites
			class SpriteRenderer final : public BaseComponents::Component
			{
			private:
				BaseComponents::Node* _node;
				
				Transform::Node2D* _node2d;
				Transform::Rotate2D* _rotate2d;
				Transform::Scale2D* _scale2d;

				sf::Sprite* _sprite;
				sf::Texture* _texture;

				bool _isVisible;
				float _depthLayer;

			public:
				SpriteRenderer();
				~SpriteRenderer();

				// Parent Overrides
				void Ready(BaseComponents::Node* i_node) override;
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
