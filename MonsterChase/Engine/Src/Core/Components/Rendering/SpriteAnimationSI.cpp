#include "SpriteAnimationSI.h"
#include "SpriteRenderer.h"
#include "../../../Containers/PointerIncludes.cpp"

#include "SFML/Graphics.hpp"
#include <cassert>

namespace Core::Components::Rendering
{
#pragma region Constructor and Destructor
	SpriteAnimationSI::SpriteAnimationSI() = default;

	SpriteAnimationSI::~SpriteAnimationSI() = default;

#pragma endregion

#pragma region Frame Control

	void SpriteAnimationSI::AddFrame(sf::Texture* i_texture)
	{
		this->_animations.push_back(i_texture);
	}

	void SpriteAnimationSI::ClearFrames()
	{
		this->_animations.clear();
	}

	void SpriteAnimationSI::SetFrameTime(const float i_value)
	{
		this->_frameTime = i_value;
	}

#pragma endregion

#pragma region Animation Control

	void SpriteAnimationSI::StartAnimation()
	{
		this->_isAnimationActive = true;
		this->_targetSprite->setTexture(*this->_animations[this->_currentAnimIndex]);
	}

	void SpriteAnimationSI::StopAnimation(const bool i_reset)
	{
		this->_isAnimationActive = false;
		if (i_reset)
		{
			ResetAnimation();
		}
	}

	void SpriteAnimationSI::ResetAnimation()
	{
		this->_currentAnimIndex = 0;
		this->_currentFrameTime = 0;
		this->_isAnimationActive = false;
	}

	void SpriteAnimationSI::SetIsRepeating(const bool i_value)
	{
		this->_isRepeating = i_value;
	}

#pragma endregion

#pragma region LifeCycle Functions

	void SpriteAnimationSI::Ready(Containers::WeakPtr<BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		auto spriteRenderer = i_node.Lock()->GetComponent<SpriteRenderer>().Lock();
		assert(spriteRenderer.IsValid()); // Break if this happens

		spriteRenderer->LoadEmpty();
		this->_targetSprite = spriteRenderer->GetSprite();
		this->_currentAnimIndex = 0;

		this->_currentFrameTime = 0;
		this->_isAnimationActive = false;
		this->_isRepeating = true;
	}

	void SpriteAnimationSI::Process(float i_deltaTime)
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
			this->_targetSprite->setTexture(*this->_animations[this->_currentAnimIndex]);
		}
	}

	void SpriteAnimationSI::Exit()
	{
		this->_animations.clear();
	}

#pragma endregion
}
