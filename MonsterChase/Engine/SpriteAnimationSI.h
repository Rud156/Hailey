#pragma once

#include "Component.h"

#include <vector>

namespace Core
{
	namespace Components
	{
		namespace Rendering
		{
			class SpriteRenderer;
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
			class SpriteAnimationSI final : BaseComponents::Component // Sprite Animation Single Image
			{
			private:
				sf::Sprite* _targetSprite{};

				std::vector<sf::Texture*> _animations;
				size_t _currentAnimIndex{};

				float _currentFrameTime{};
				float _frameTime{};

				bool _isAnimationActive{};
				bool _isRepeating{};

			public:
				// Constructor and Destructor
				SpriteAnimationSI();
				~SpriteAnimationSI();

				// Frame Control
				void AddFrame(sf::Texture* i_texture);
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
