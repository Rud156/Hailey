#pragma once
#include "Node.h"

namespace Game
{
	class GridActorController
	{
	private:
		char* _gridActorName;
		int _gridActorHealth;
		Core::BaseComponents::Node* _gridGameObject;

	public:
		// Constructor And Destructor
		GridActorController();
		~GridActorController();

		// Name
		void SetActorName(char* name);
		char* GetActorName() const;
		void DeleteActorName() const;

		// Health
		void SetActorHealth(int healthAmount);
		void DecrementHealth(int amount);
		void IncrementHealth(int amount);
		int GetActorHealth() const;

		// GameObject
		Core::BaseComponents::Node* GetGameObject() const;
	};
}
