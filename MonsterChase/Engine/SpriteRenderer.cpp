#include "SpriteRenderer.h"
#include "Node.h"
#include "Node3D.h"
#include <cassert>
#include <SFML/Graphics.hpp>

namespace Core
{
	namespace Components
	{
		namespace Rendering
		{
			SpriteRenderer::SpriteRenderer(): _node3d(nullptr), _sprite(nullptr), _texture(nullptr)
			{
			}

			SpriteRenderer::~SpriteRenderer()
			{
				delete this->_texture;
				delete this->_sprite;
			}

			void SpriteRenderer::Ready(BaseComponents::Node* node)
			{
				const auto node3d = node->GetComponent<Transform::Node3D>();
				assert(node3d != nullptr); // At this break as 3D node is required for positioning a sprite
				this->_node3d = node3d;
			}

			void SpriteRenderer::LoadTexture(const std::string& filePath)
			{
				auto texture = new sf::Texture();
				this->_texture = texture;
				if (!texture->loadFromFile(filePath))
				{
					std::cout << "Invalid File Path" << std::endl;
				}

				const auto position = _node3d->GetPosition();

				auto sprite = new sf::Sprite(*texture);
				sprite->setPosition(position->X(), position->Y());
				this->_sprite = sprite;
			}

			void SpriteRenderer::Render(sf::RenderWindow* window)
			{
				const auto position = this->_node3d->GetPosition();
				this->_sprite->setPosition(position->X(), position->Y());
				window->draw(*this->_sprite);
			}

			sf::Sprite* SpriteRenderer::GetSprite() const
			{
				return this->_sprite;
			}
		}
	}
}
