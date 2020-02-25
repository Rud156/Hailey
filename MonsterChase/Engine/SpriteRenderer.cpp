#include "SpriteRenderer.h"
#include "Node.h"
#include "Node2D.h"
#include "Rotate2D.h"
#include "Scale2D.h"

#include <cassert>
#include <SFML/Graphics.hpp>

namespace Core::Components::Rendering
{
	SpriteRenderer::SpriteRenderer(): _node(nullptr), _node2d(nullptr), _rotate2d(nullptr), _scale2d(nullptr),
	                                  _sprite(nullptr),
	                                  _texture(nullptr),
	                                  _isVisible(true),
	                                  _depthLayer(0)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete this->_texture;
		delete this->_sprite;
	}

	void SpriteRenderer::Ready(BaseComponents::Node* i_node)
	{
		const auto node2d = i_node->GetComponent<Transform::Node2D>();
		const auto rotate2d = i_node->GetComponent<Transform::Rotate2D>();
		const auto scale2d = i_node->GetComponent<Transform::Scale2D>();

		assert(node2d != nullptr);
		assert(rotate2d != nullptr);
		assert(scale2d != nullptr);

		this->_node = i_node;
		this->_node2d = node2d;
		this->_rotate2d = rotate2d;
		this->_scale2d = scale2d;
	}

	void SpriteRenderer::LoadEmpty() // Can be primarily used for animations
	{
		this->_sprite = new sf::Sprite();
		this->_texture = new sf::Texture();
		this->_isVisible = true;
	}

	void SpriteRenderer::LoadTexture(const std::string& i_filePath)
	{
		auto texture = new sf::Texture();
		this->_texture = texture;
		if (!texture->loadFromFile(i_filePath))
		{
			std::cout << "Invalid File Path" << std::endl;
		}

		const auto position = _node2d->GetPosition();

		auto sprite = new sf::Sprite(*texture);
		sprite->setPosition(position->X(), position->Y());

		this->_sprite = sprite;
		this->_isVisible = true;
	}

	void SpriteRenderer::SetupRender()
	{
		if (!this->_isVisible)
		{
			return;
		}

		const auto position = this->_node2d->GetPosition();
		const auto angle = this->_rotate2d->GetAngle();
		const auto scale = this->_scale2d->GetScale();

		this->_sprite->setPosition(position->X(), position->Y());
		this->_sprite->setRotation(angle);
		this->_sprite->setScale(scale->X(), scale->Y());
	}

	void SpriteRenderer::Render(sf::RenderWindow* i_window)
	{
		i_window->draw(*this->_sprite);
	}


	sf::Sprite* SpriteRenderer::GetSprite() const
	{
		return this->_sprite;
	}

	void SpriteRenderer::SetSpriteDepth(const float i_depthLayer)
	{
		this->_depthLayer = i_depthLayer;
		this->_node->SetRenderOrder(i_depthLayer);
	}

	float SpriteRenderer::GetSpriteDepth() const
	{
		return this->_depthLayer;
	}

	bool SpriteRenderer::GetIsVisible() const
	{
		return this->_isVisible;
	}

	void SpriteRenderer::SetIsVisible(const bool i_value)
	{
		this->_isVisible = i_value;
	}
}
