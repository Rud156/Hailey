#pragma once
#include "GridActorController.h"
#include "Point2D.h"

namespace Game
{
	class GameMain
	{
	private:
		static const int BoardRows = 10;
		static const int BoardColumns = 10;

		static const size_t MaxStringSize = 20;
		static const size_t MaxInputStringSize = MaxStringSize / 2;

		static const int MaxMonsters = 50;
		static const int InitialMonsterHealth = 10;

		static const int MonsterTurnTimer = 1;

		GridActorController* _player;
		GridActorController** _monsters;

		char* _monsterBaseName;
		int _currentMonsterIndex = 1;
		int _currentMonsterTurnTimer = MonsterTurnTimer;

		enum class GameState
		{
			GameRunning,
			PlayerDead
		};

		GameState _gameState;
		bool _quitGame;

		// Initialize
		void InitializeData();
		void CreateInitialMonsters(int initialMonsterCount);

		// Draw and Update
		void Update();
		void Draw() const;

		// Player Helpers
		void MovePlayer(int direction) const;
		void CheckPlayerMonsterCollision();

		// Monster Helpers
		void UpdateMonsters();
		void CheckAndSpawnNewMonster();
		int GetEmptyMonsterIndex() const;
		int GetGridMonsterIndex(int row, int column) const;

		// Game End Helpers
		void CheckAndDisplayGameOver() const;
		void CheckAndQuitGame();

		// Game Helpers
		Math::Point2D* GetRandomEmptyGridPosition() const;
		bool IsBoardTileEmpty(int row, int column) const;
		static bool IsValidBoardIndex(int row, int column);
		void SetGameState(GameState gameState);

	public:
		GameMain();
		~GameMain();

		void InitializeAndRun();
	};
}
