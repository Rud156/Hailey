#include "MainScene.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Maths/Point2D.h"
#include "Src/Containers/PointerIncludes.cpp"

namespace Game::Scenes
{
#pragma region Constructor and Destructor

	MainScene::MainScene()
	{
		const Containers::SmartPtr<GameObjects::Player::Player> player(new GameObjects::Player::Player());
		this->_player = player;

		auto* const testCollider = new Core::BaseComponents::Node("TestCollider");
		testCollider->AddComponent<Core::Components::Transform::Node2D>().Lock()->GetPosition()->set(300, 200);
		testCollider->AddComponent<Core::Components::Transform::Rotate2D>();

		auto collider = testCollider->AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		collider.Lock()->SetColliderExtents(50, 50);
		collider.Lock()->AddToWorld();
	}

	MainScene::~MainScene() = default;


#pragma endregion

#pragma region LifeCycle Functions

	void MainScene::Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler)
	{
		this->_player->Init(i_inputHandler);
	}

	void MainScene::Update(float i_deltaTime)
	{
		this->_player->Update(i_deltaTime);
	}

	void MainScene::SwitchSceneLoad()
	{
	}

	void MainScene::SwitchSceneUnload()
	{
	}

	void MainScene::RemoveSceneElements()
	{
	}

#pragma endregion
}
