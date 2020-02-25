#include "SpriteAnimationSS.h"
#include "Node.h"
#include "SpriteRenderer.h"

#include "SFML/Graphics.hpp"
#include <cassert>

namespace Core::Components::Rendering
{
#pragma region Constructor and Destructor
	SpriteAnimationSS::SpriteAnimationSS() = default;

	SpriteAnimationSS::~SpriteAnimationSS()
	{
		delete this->_baseTexture;
	}

#pragma endregion

#pragma region Frame Control

	void SpriteAnimationSS::SetTexture(sf::Texture* i_texture)
	{
		this->_baseTexture = i_texture;
		this->_targetSprite->setTexture(*i_texture);
	}

	void SpriteAnimationSS::AddFrame(int i_x, int i_y, int i_width, int i_height)
	{
		const auto intRect = new sf::IntRect(i_x, i_y, i_width, i_height);
		this->_animations.push_back(intRect);
	}

	void SpriteAnimationSS::ClearFrames()
	{
		this->_animations.clear();
	}

	void SpriteAnimationSS::SetFrameTime(const float i_value)
	{
		this->_frameTime = i_value;
	}

#pragma endregion

#pragma region Animation Control

	void SpriteAnimationSS::StartAnimation()
	{
		this->_isAnimationActive = true;
		this->_targetSprite->setTextureRect(*this->_animations[this->_currentAnimIndex]);
	}

	void SpriteAnimationSS::StopAnimation(const bool i_reset)
	{
		this->_isAnimationActive = false;
		if (i_reset)
		{
			ResetAnimation();
		}
	}

	void SpriteAnimationSS::ResetAnimation()
	{
		this->_currentAnimIndex = 0;
		this->_currentFrameTime = 0;
		this->_isAnimationActive = false;
	}

	void SpriteAnimationSS::SetIsRepeating(const bool i_value)
	{
		this->_isRepeating = i_value;
	}

#pragma endregion

#pragma region LifeCycle Functions

	void SpriteAnimationSS::Ready(BaseComponents::Node* i_node)
	{
		const auto spriteRenderer = i_node->GetComponent<Rendering::SpriteRenderer>();
		assert(spriteRenderer != nullptr); // Break if this happens

		spriteRenderer->LoadEmpty();
		this->_targetSprite = spriteRenderer->GetSprite();
		this->_currentAnimIndex = 0;

		this->_currentFrameTime = 0;
		this->_isAnimationActive = false;
		this->_isRepeating = true;
	}

	void SpriteAnimationSS::Process(float i_deltaTime)
	{
		if (!this->_isAnimationActive)
		{
			return;
		}

		this->_currentFrameTime += i_deltaTime;
		if (this->_currentFrameTime >= this->_frameTime)
		{
			this->_currentFrameTime = 0;
			this->_currentAnimIndex += 1;

			if (this->_currentAnimIndex >= this->_animations.size())
			{
				if (this->_isRepeating)
				{
					this->_currentAnimIndex = 0;
				}
				else
				{
					this->_isAnimationActive = false;
				}
			}
		}

		if (this->_isAnimationActive)
		{
			this->_targetSprite->setTextureRect(*this->_animations[this->_currentAnimIndex]);
		}
	}

	void SpriteAnimationSS::Exit()
	{
		this->_animations.clear();
	}

#pragma endregion
}
