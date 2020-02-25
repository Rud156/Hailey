#pragma once

#include "Component.h"
#include <vector>
#include <SFML/Graphics/Rect.hpp>

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
			class SpriteAnimationSS : BaseComponents::Component
			{
			private:
				sf::Sprite* _targetSprite{};

				sf::Texture* _baseTexture{};
				std::vector<sf::IntRect*> _animations;
				size_t _currentAnimIndex{};

				float _currentFrameTime{};
				float _frameTime{};

				bool _isAnimationActive{};
				bool _isRepeating{};

			public:
				// Constructor and Destructor
				SpriteAnimationSS();
				~SpriteAnimationSS();

				// Frame Control
				void SetTexture(sf::Texture* i_texture);
				void AddFrame(int i_x, int i_y, int i_width, int i_height);
				void ClearFrames();
				void SetFrameTime(float i_value);

				// Animation Control
				void StartAnimation();
				void StopAnimation(bool i_reset = true);
				void ResetAnimation();
				void SetIsRepeating(bool i_value);

				// LifeCycle Functions
				void Ready(BaseComponents::Node* i_node) override;
				void Process(float i_deltaTime) override;
				void Exit() override;
			};
		}
	}
}
