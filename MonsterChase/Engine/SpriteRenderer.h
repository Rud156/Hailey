#pragma once
#include "Component.h"
#include "Point3D.h"

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			class Node3D;
		}
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
			class SpriteRenderer final : public BaseComponents::Component
			{
			private:
				Transform::Node3D* _node3d;
				sf::Sprite* _sprite;
				sf::Texture* _texture;

			public:
				SpriteRenderer();
				~SpriteRenderer();

				void Ready(BaseComponents::Node* node) override;
				void LoadTexture(const std::string& filePath);

				void Render(sf::RenderWindow* window) override;

				sf::Sprite* GetSprite() const;
			};
		}
	}
}
