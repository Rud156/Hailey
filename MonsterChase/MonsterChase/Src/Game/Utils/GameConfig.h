#pragma once

#include <cstdint>

namespace Game::Utils
{
	class GameConfig
	{
	public:
		inline static const __int16 PlayerGroup = -1;
		inline static const __int16 EnemyGroup = -2;

		inline static const uint16_t PlayerCat = 0x0001;
		inline static const uint16_t EnemyCat = 0x0002;

		inline static const uint16_t PlayerProjectileCat = 0x0004;
		inline static const uint16_t EnemyProjectileCat = 0x0008;

		// TODO: Update these values...
		inline static const float EnemyProjectileDamage = 10;
		inline static const float EnemyLargeProjectileDamage = 10;
		inline static const float PlayerProjectileDamage = 10;
		inline static const float EnemyDPS = 10;

		inline static const char* const PlayerTag = "Player";
		inline static const char* const EnemyTag = "Enemy";
		inline static const char* const PlayerProjTag = "PlayerProj";
		inline static const char* const EnemyProjTag = "EnemyProj";
	};
}
