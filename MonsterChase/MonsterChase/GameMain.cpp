#include "GameMain.h"
#include "Random.h"
#include "Node2D.h"
#include <ctime>
#include <conio.h>

#define KeyUp 72
#define KeyDown 80
#define KeyLeft 75
#define KeyRight 77
#define Escape 27
#define NewLine 224

namespace Game
{
	// Constructor and Destructor

	GameMain::GameMain(): _player(nullptr), _monsters(nullptr), _monsterBaseName(nullptr), _gameState(),
	                      _quitGame(false)
	{
	}

	GameMain::~GameMain()
	{
		delete this->_player;

		delete[] this->_monsterBaseName;
		for (int i = 0; i < MaxMonsters; i++)
		{
			delete this->_monsters[i];
		}
		delete this->_monsters;
	}

	// Constructor and Destructor

	// Initialization

	void GameMain::InitializeData()
	{
		// Player
		printf_s("Enter You Name: ");
		char* input = static_cast<char*>(malloc(sizeof(char)));
		int inputLength = 0;
		int inputCharacter;
		while ((inputCharacter = getchar()) != '\n' && inputCharacter != EOF)
		{
			input = static_cast<char*>(realloc(input, sizeof(char) * (inputLength + 1)));
			input[inputLength] = static_cast<char>(inputCharacter);
			inputLength += 1;
		}
		input = static_cast<char*>(realloc(input, sizeof(char) * (inputLength + 1)));
		input[inputLength] = '\0';

		const size_t maxStringLength = strlen(input) > MaxStringSize - 1 ? MaxStringSize - 1 : strlen(input);
		char* playerName = new char[maxStringLength + 1];
		for (size_t i = 0; i < maxStringLength; i++)
		{
			playerName[i] = input[i];
		}
		playerName[maxStringLength] = '\0';
		free(input);

		this->_player = new GridActorController();
		this->_player->SetActorName(playerName);
		this->_player->SetActorHealth(1);
		Math::Point2D* randomPlayerGridPosition = this->GetRandomEmptyGridPosition();
		const auto playerPositionComponent = this->_player->GetGameObject()->
		                                           GetComponent<Core::Components::Transform::Node2D>();
		playerPositionComponent->GetPosition()->set(*randomPlayerGridPosition);
		delete randomPlayerGridPosition;

		// Player

		// Initial Monsters

		printf_s("Enter the initial number of monsters: ");
		int initialMonsterCount = 0;
		scanf_s("%d", &initialMonsterCount);
		if (initialMonsterCount >= MaxMonsters)
		{
			initialMonsterCount = MaxMonsters;
		}
		getchar();

		// Input Monster Base Name
		printf_s("Enter starting characters of Monster Name: ");
		input = static_cast<char*>(malloc(sizeof(char)));
		inputLength = 0;
		while ((inputCharacter = getchar()) != '\n' && inputCharacter != EOF)
		{
			input = static_cast<char*>(realloc(input, sizeof(char) * (inputLength + 1)));
			input[inputLength] = static_cast<char>(inputCharacter);
			inputLength += 1;
		}
		input = static_cast<char*>(realloc(input, sizeof(char) * (inputLength + 1)));
		input[inputLength] = '\0';

		const size_t maxMonsterBaseNameLength = strlen(input) > MaxInputStringSize ? MaxInputStringSize : strlen(input);
		this->_monsterBaseName = new char[maxMonsterBaseNameLength + 1];
		for (size_t i = 0; i < maxMonsterBaseNameLength; i++)
		{
			this->_monsterBaseName[i] = input[i];
		}
		this->_monsterBaseName[maxMonsterBaseNameLength] = '\0'; // Terminate the string after copying
		free(input);

		this->_monsters = new GridActorController*[MaxMonsters];
		for (int i = 0; i < MaxMonsters; i++)
		{
			this->_monsters[i] = new GridActorController();
		}

		this->CreateInitialMonsters(initialMonsterCount);

		// Initial Monsters

		this->SetGameState(GameState::GameRunning);
	}

	void GameMain::CreateInitialMonsters(const int initialMonsterCount)
	{
		for (int i = 0; i < MaxMonsters; i++)
		{
			auto monster = this->_monsters[i];

			if (i < initialMonsterCount)
			{
				Math::Point2D* randomPosition = this->GetRandomEmptyGridPosition();

				monster->SetActorHealth(InitialMonsterHealth);
				const auto monsterPositionComponent = monster->GetGameObject()->
				                                               GetComponent<Core::Components::Transform::Node2D>();
				monsterPositionComponent->GetPosition()->set(*randomPosition);

				const int totalCharSize = (static_cast<int>(ceil(log10(_currentMonsterIndex))) + 2) * sizeof(char);
				char* stringInt = new char[totalCharSize];
				_itoa_s(_currentMonsterIndex, stringInt, totalCharSize, 10);
				_currentMonsterIndex += 1;

				char* monsterName = new char[MaxStringSize];
				strcpy_s(monsterName, MaxStringSize, this->_monsterBaseName);
				strcat_s(monsterName, MaxStringSize, stringInt);

				monster->SetActorName(monsterName);

				delete[] stringInt;
				delete randomPosition;
			}
			else
			{
				const auto monsterPositionComponent = monster->GetGameObject()->
				                                               GetComponent<Core::Components::Transform::Node2D>();
				monsterPositionComponent->GetPosition()->set(-1, -1);
			}
		}
	}

	// Initialization

	// Draw and Update

	void GameMain::Update()
	{
		do
		{
			CheckPlayerMonsterCollision();

			printf_s("Awaiting Input: ");
			const int input = _getch();

			switch (input)
			{
			case KeyUp:
			case KeyDown:
			case KeyLeft:
			case KeyRight:
				MovePlayer(input);
				break;

			case Escape:
				CheckAndQuitGame();
				break;

			case NewLine:
				break;

			default:
				printf_s("Invalid Input Entered: %d\n", input);
				break;
			}

			if (!this->_quitGame)
			{
				switch (this->_gameState)
				{
				case GameRunning:
					UpdateMonsters();
					Draw();
					break;

				case PlayerDead:
					CheckAndDisplayGameOver();
					break;

				default: break;
				}
			}
		}
		while (!this->_quitGame);
	}


	void GameMain::Draw() const
	{
		system("cls");

		printf_s("\n\n");

		for (int i = 0; i < BoardRows; i++)
		{
			for (int j = 0; j < BoardColumns; j++)
			{
				if (IsBoardTileEmpty(i, j))
				{
					printf_s("|");
					for (size_t k = 0; k < MaxStringSize + 5; k++)
					{
						printf_s(" ");
					}
					printf_s("|");
				}
				else
				{
					const int monsterIndex = this->GetGridMonsterIndex(i, j);
					if (monsterIndex == -1)
					{
						printf_s("|%s", _player->GetActorName());
						const size_t spacesLeft = 5 + MaxStringSize - static_cast<int>(strlen(_player->GetActorName()));
						for (size_t k = 0; k < spacesLeft; k++)
						{
							printf_s(" ");
						}
						printf_s("|");
					}
					else
					{
						const auto monster = this->_monsters[monsterIndex];

						printf_s("|%s", monster->GetActorName());
						const size_t spacesLeft = 5 + MaxStringSize - static_cast<int>(strlen(_player->GetActorName()));
						for (size_t k = 0; k < spacesLeft; k++)
						{
							printf_s(" ");
						}
						printf_s("|");
					}
				}
			}

			printf_s("\n");
		}
	}

	// Draw and Update

	// Player Helpers

	void GameMain::MovePlayer(const int direction) const
	{
		if (_gameState == GameState::PlayerDead)
		{
			return;
		}

		const auto playerPositionComponent = this->_player->GetGameObject()->
		                                           GetComponent<Core::Components::Transform::Node2D>();
		Math::Point2D* playerPosition = playerPositionComponent->GetPosition();
		int playerRow = static_cast<int>(playerPosition->X());
		int playerColumn = static_cast<int>(playerPosition->Y());

		switch (direction)
		{
		case KeyUp:
			{
				playerRow -= 1;
				if (IsValidBoardIndex(playerRow, playerColumn))
				{
					playerPosition->set(playerRow, playerColumn);
				}
			}
			break;

		case KeyDown:
			{
				playerRow += 1;
				if (IsValidBoardIndex(playerRow, playerColumn))
				{
					playerPosition->set(playerRow, playerColumn);
				}
			}
			break;

		case KeyLeft:
			{
				playerColumn -= 1;
				if (IsValidBoardIndex(playerRow, playerColumn))
				{
					playerPosition->set(playerRow, playerColumn);
				}
			}
			break;

		case KeyRight:
			{
				playerColumn += 1;
				if (IsValidBoardIndex(playerRow, playerColumn))
				{
					playerPosition->set(playerRow, playerColumn);
				}
			}
			break;

		default:
			break;
		}
	}

	void GameMain::CheckPlayerMonsterCollision()
	{
		for (size_t i = 0; i < MaxMonsters; i++)
		{
			const auto monster = this->_monsters[i];
			Math::Point2D* monsterPosition = monster->GetGameObject()->
			                                          GetComponent<Core::Components::Transform::Node2D>()->
			                                          GetPosition();

			if (monsterPosition->X() == -1 && monsterPosition->Y() == -1)
			{
				continue;
			}

			Math::Point2D* playerPosition = this->_player->GetGameObject()->
			                                      GetComponent<Core::Components::Transform::Node2D>()->GetPosition();

			if (*playerPosition == *monsterPosition)
			{
				SetGameState(GameState::PlayerDead);
				break;
			}
		}
	}

	// Player Helpers

	// Monster Helpers

	void GameMain::UpdateMonsters()
	{
		for (size_t i = 0; i < MaxMonsters; i++)
		{
			const auto monster = this->_monsters[i];
			const auto monsterPositionComponent = monster->GetGameObject()->
			                                               GetComponent<Core::Components::Transform::Node2D>();
			Math::Point2D* monsterPosition = monsterPositionComponent->GetPosition();

			// This means that array index has a valid monster
			if (monsterPosition->X() != -1 && monsterPosition->Y() != -1)
			{
				monster->DecrementHealth(1);

				if (monster->GetActorHealth() <= 0)
				{
					monsterPosition->set(-1, -1);
					monster->DeleteActorName();
				}
				else
				{
					const int direction = Utils::Random::RandomInRange(0, 4);
					float monsterRow = monsterPosition->X();
					float monsterColumn = monsterPosition->Y();

					switch (direction)
					{
					case 0:
						monsterRow -= 1;
						break;

					case 1:
						monsterRow += 1;
						break;

					case 2:
						monsterColumn -= 1;
						break;

					case 3:
						monsterColumn += 1;
						break;

					default:
						break;
					}

					monsterPosition->set(monsterRow, monsterColumn);
				}
			}
		}

		// Check if Monsters Collided Among Each Other
		for (int i = 0; i < MaxMonsters; i++)
		{
			for (int j = i + 1; j < MaxMonsters; j++)
			{
				const auto monster_1 = this->_monsters[i];
				const auto monster_2 = this->_monsters[j];
				const auto monsterPositionComponent_1 = monster_1->GetGameObject()->
				                                                   GetComponent<Core::Components::Transform::Node2D>();
				const auto monsterPositionComponent_2 = monster_2->GetGameObject()->
				                                                   GetComponent<Core::Components::Transform::Node2D>();

				Math::Point2D* monsterPosition_1 = monsterPositionComponent_1->GetPosition();
				Math::Point2D* monsterPosition_2 = monsterPositionComponent_2->GetPosition();

				if (monsterPosition_1->X() != -1 && monsterPosition_1->Y() != -1 &&
					monsterPosition_2->X() != -1 && monsterPosition_2->Y() != -1 &&
					*monsterPosition_1 == *monsterPosition_2)
				{
					const int firstMonsterHealth = monster_1->GetActorHealth();
					const int secondMonsterHealth = monster_2->GetActorHealth();

					if (firstMonsterHealth > secondMonsterHealth)
					{
						monster_1->DecrementHealth(firstMonsterHealth - secondMonsterHealth);

						monster_2->SetActorHealth(0);
						monsterPosition_2->set(-1, -1);
						monster_2->DeleteActorName();
					}
					else if (secondMonsterHealth > firstMonsterHealth)
					{
						monster_2->DecrementHealth(secondMonsterHealth - firstMonsterHealth);

						monster_1->SetActorHealth(0);
						monsterPosition_1->set(-1, -1);
						monster_1->DeleteActorName();
					}
					else
					{
						monster_1->SetActorHealth(0);
						monsterPosition_1->set(-1, -1);
						monster_1->DeleteActorName();

						monster_2->SetActorHealth(0);
						monsterPosition_2->set(-1, -1);
						monster_2->DeleteActorName();
					}
				}
			}
		}

		_currentMonsterTurnTimer -= 1;
		if (_currentMonsterTurnTimer <= 0)
		{
			_currentMonsterTurnTimer = MonsterTurnTimer;
			CheckAndSpawnNewMonster();
		}
	}

	void GameMain::CheckAndSpawnNewMonster()
	{
		const int emptyMonsterIndex = this->GetEmptyMonsterIndex();
		if (emptyMonsterIndex != -1)
		{
			const auto monster = this->_monsters[emptyMonsterIndex];
			Math::Point2D* randomPosition = GetRandomEmptyGridPosition();

			const int totalCharSize = (static_cast<int>(ceil(log10(_currentMonsterIndex))) + 2) * sizeof(char);
			char* stringInt = new char[totalCharSize];
			_itoa_s(_currentMonsterIndex, stringInt, totalCharSize, 10);
			_currentMonsterIndex += 1;

			char* monsterName = new char[MaxStringSize];
			strcpy_s(monsterName, MaxStringSize, this->_monsterBaseName);
			strcat_s(monsterName, MaxStringSize, stringInt);

			monster->SetActorName(monsterName);
			monster->SetActorHealth(InitialMonsterHealth);

			const auto monsterPositionComponent = monster->
			                                      GetGameObject()->GetComponent<Core::Components::Transform::Node2D>();
			monsterPositionComponent->GetPosition()->set(*randomPosition);

			delete[] stringInt;
			delete randomPosition;
		}
	}

	int GameMain::GetEmptyMonsterIndex() const
	{
		for (int i = 0; i < MaxMonsters; i++)
		{
			const auto monster = this->_monsters[i];
			Math::Point2D* monsterPosition = monster->GetGameObject()->
			                                          GetComponent<Core::Components::Transform::Node2D>()->
			                                          GetPosition();

			if (monsterPosition->X() == -1 && monsterPosition->Y() == -1)
			{
				return i;
			}
		}

		return -1;
	}

	int GameMain::GetGridMonsterIndex(const int row, const int column) const
	{
		for (int i = 0; i < MaxMonsters; i++)
		{
			const auto monster = this->_monsters[i];
			Math::Point2D* monsterPosition = monster->GetGameObject()->
			                                          GetComponent<Core::Components::Transform::Node2D>()->
			                                          GetPosition();
			if (monsterPosition->X() == row && monsterPosition->Y() == column)
			{
				return i;
			}
		}

		return -1;
	}

	// Monster Helpers

	// Game End Helpers

	void GameMain::CheckAndDisplayGameOver() const
	{
		if (this->_gameState != GameState::PlayerDead)
		{
			return;
		}

		system("cls");
		printf_s("\n\nYou Died!!! Game Over. Press Esc to Close\n\n");
	}

	void GameMain::CheckAndQuitGame()
	{
		system("cls");

		this->_quitGame = true;
	}

	// Game End Helpers

	// Game Helpers

	Math::Point2D* GameMain::GetRandomEmptyGridPosition() const
	{
		auto position = new Math::Point2D();

		// Definitely will not work when the entire board is full
		while (true)
		{
			const int randomX = Utils::Random::RandomInRange(0, BoardRows);
			const int randomY = Utils::Random::RandomInRange(0, BoardColumns);

			if (this->IsBoardTileEmpty(randomX, randomY))
			{
				position->set(static_cast<float>(randomX), static_cast<float>(randomY));
				break;
			}
		}

		return position;
	}

	bool GameMain::IsBoardTileEmpty(const int row, const int column) const
	{
		if (!IsValidBoardIndex(row, column))
		{
			return false;
		}

		if (this->_monsters != nullptr)
		{
			for (int i = 0; i < MaxMonsters; i++)
			{
				const auto monster = this->_monsters[i];
				Math::Point2D* monsterPosition = monster->GetGameObject()->
				                                          GetComponent<Core::Components::Transform::Node2D>()->
				                                          GetPosition();

				if (monsterPosition->X() == row && monsterPosition->Y() == column &&
					monsterPosition->X() != -1 && monsterPosition->Y() != -1)
				{
					return false;
				}
			}
		}

		if (this->_player != nullptr)
		{
			Math::Point2D* playerPosition = this->_player->GetGameObject()->
			                                      GetComponent<Core::Components::Transform::Node2D>()->GetPosition();
			if (playerPosition->X() == row && playerPosition->Y() == column &&
				playerPosition->X() != -1 && playerPosition->Y() != -1)
			{
				return false;
			}
		}

		return true;
	}

	bool GameMain::IsValidBoardIndex(const int row, const int column)
	{
		if (row < 0 || row >= BoardRows)
		{
			return false;
		}

		if (column < 0 || column >= BoardColumns)
		{
			return false;
		}

		return true;
	}

	void GameMain::SetGameState(GameState gameState)
	{
		this->_gameState = gameState;
	}


	// Game Helpers

	// External Functions

	void GameMain::InitializeAndRun()
	{
		printf_s("MONSTER CHASE\n\n");
		printf_s("Welcome to Monster Chase a Grid Based world where you try to escape monsters\n\n");
		printf_s("Use Arrow Keys to move around the world\n\n");
		printf_s("P.S. Run the Game in Full Screen\n\n");

		Utils::Random::SetSeed(static_cast<unsigned int>(time(nullptr)));

		this->InitializeData();
		this->Draw();
		this->Update();
	}

	// External Functions
}
