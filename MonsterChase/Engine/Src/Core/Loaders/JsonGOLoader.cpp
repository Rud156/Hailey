#include "JsonGOLoader.h"
#include "FileLoader.h"
#include "../BaseComponents/Node.h"
#include "../Components/Physics/Rigidbody2D.h"
#include "../Components/Rendering/SpriteRenderer.h"
#include "../Components/Transform/Node2D.h"
#include "../Components/Transform/Rotate2D.h"
#include "../Components/Transform/Scale2D.h"
#include "../../Utils/Debug.h"
#include "../../Maths/Point2D.h"
#include "../Controllers/GameObjectUpdater_Extern.h"
#include "../../Utils/Random.h"
#include "../Controllers/CoreLoop.h"

#include <string>

using namespace nlohmann;

// TODO: Remove this later on
#define DEBUG

#ifdef DEBUG
#include <SFML/Graphics.hpp>
#endif

// Define the static data here to create instance...
std::mutex Core::Loaders::JsonGOLoader::JsonMutex;
std::vector<std::future<void>> Core::Loaders::JsonGOLoader::FutureList;

namespace Core::Loaders
{
	void JsonGOLoader::LoadGoFileDeferred(const std::string i_filePath)
	{
		const std::string jsonDataString = FileLoader::LoadFileAsString(i_filePath);

		JsonGOLoader::JsonMutex.lock();
		const auto jsonData = json::parse(jsonDataString);
		JsonGOLoader::JsonMutex.unlock();

		const bool hasGameObjects = jsonData.contains(JsonGOLoader::GameObjectStr);
		if (hasGameObjects)
		{
			auto gameObjectData = jsonData[JsonGOLoader::GameObjectStr];
			for (auto& element : gameObjectData.items())
			{
				JsonGOLoader::FutureList.push_back(std::async(std::launch::async,
				                                              JsonGOLoader::LoadGameObjectDeferred,
				                                              element.value()
					)
				);


				Utils::Debug::LogOutputToWindow("Loading Json\n");
			}
		}
		else
		{
			Utils::Debug::LogOutputToWindow("No GameObjects Found");
		}
	}

	void JsonGOLoader::LoadGameObjectDeferred(basic_json<> i_value)
	{
		const auto name = std::string(i_value[JsonGOLoader::NameStr].get<std::string>());
		auto gameObject = new BaseComponents::Node(name, false);

		gameObject->AddComponent<Components::Transform::Rotate2D>();
		gameObject->AddComponent<Components::Transform::Scale2D>();
		const auto gameObjectPosition = gameObject->AddComponent<Components::Transform::Node2D>();

		if (i_value.contains(JsonGOLoader::InitialPositionStr))
		{
			auto position = i_value[JsonGOLoader::InitialPositionStr].get<std::vector<float>>();
#ifdef DEBUG
			const auto windowSize = Controllers::CoreLoop::Window->getSize();
			position[0] = static_cast<float>(Utils::Random::RandomInRange(0, windowSize.x));
			position[1] = static_cast<float>(Utils::Random::RandomInRange(0, windowSize.y));
#endif

			gameObjectPosition->GetPosition()->set(position[0], position[1]);
		}

		if (i_value.contains(JsonGOLoader::RenderDataStr))
		{
			const auto rendererData = i_value[JsonGOLoader::RenderDataStr];
			const auto renderer = gameObject->AddComponent<Components::Rendering::SpriteRenderer>();

			const auto texturePath = rendererData[JsonGOLoader::SpriteStr].get<std::string>();
			const auto assetsDir = FileLoader::Assets;

			std::string finalTexturePath = assetsDir;
			finalTexturePath += texturePath;

			renderer->LoadTexture(finalTexturePath);

			if (rendererData.contains(JsonGOLoader::RenderOrderStr))
			{
				const auto spriteDepth = rendererData[JsonGOLoader::RenderOrderStr].get<float>();
				renderer->SetSpriteDepth(spriteDepth);
			}
		}

		if (i_value.contains(JsonGOLoader::ComponentsStr))
		{
			// TODO: Do something here. Maybe when there are more components
		}

		if (i_value.contains(JsonGOLoader::RigidbodyDataStr))
		{
			const auto rigidbodyData = i_value[JsonGOLoader::RigidbodyDataStr];
			const auto rigidbody = gameObject->AddComponent<Components::Physics::Rigidbody2D>();

			if (rigidbodyData.contains(JsonGOLoader::MassStr))
			{
				rigidbody->SetMass(rigidbodyData[JsonGOLoader::MassStr].get<float>());
			}

			if (rigidbodyData.contains(JsonGOLoader::GravityScaleStr))
			{
				rigidbody->SetGravityScale(rigidbodyData[JsonGOLoader::GravityScaleStr].get<float>());
			}

			if (rigidbodyData.contains(JsonGOLoader::AngularDragStr))
			{
				rigidbody->SetAngularDrag(rigidbodyData[JsonGOLoader::AngularDragStr].get<float>());
			}

			if (rigidbodyData.contains(JsonGOLoader::AngularVelocityStr))
			{
				rigidbody->SetAngularVelocity(rigidbodyData[JsonGOLoader::AngularVelocityStr].get<float>());
			}
		}


		gameObjectUpdater->AddGameObject(gameObject);
		Utils::Debug::LogOutputToWindow("GameObject Loaded\n");
	}

	void JsonGOLoader::LoadJsonGameObjectAsync(std::string_view i_filePath)
	{
		// Just clear the older Future List
		for (size_t i = 0; i < JsonGOLoader::FutureList.size(); i++)
		{
			if (JsonGOLoader::FutureList[i]._Is_ready())
			{
				Utils::Debug::LogOutputToWindow("Future Removed\n");
				JsonGOLoader::FutureList.erase(JsonGOLoader::FutureList.begin() + i);
				i -= 1;
			}
		}

		// Create a copy of the string as it maybe destroyed before the function runs
		const std::string filePath = std::string(i_filePath);

		JsonGOLoader::FutureList.push_back(std::async(std::launch::async,
		                                              JsonGOLoader::LoadGoFileDeferred,
		                                              filePath
			)
		);
	}

	void JsonGOLoader::LoadJsonGameObjectSync(std::string_view i_filePath)
	{
		const std::string jsonDataString = FileLoader::LoadFileAsString(i_filePath);
		const auto jsonData = json::parse(jsonDataString);

		const bool hasGameObjects = jsonData.contains(JsonGOLoader::GameObjectStr);
		if (hasGameObjects)
		{
			auto gameObjectData = jsonData[JsonGOLoader::GameObjectStr];
			for (auto& [key, value] : gameObjectData.items())
			{
				const auto name = value[JsonGOLoader::NameStr].get<std::string>();
				auto gameObject = new BaseComponents::Node(name);

				gameObject->AddComponent<Components::Transform::Rotate2D>();
				gameObject->AddComponent<Components::Transform::Scale2D>();
				const auto gameObjectPosition = gameObject->AddComponent<Components::Transform::Node2D>();

				if (value.contains(JsonGOLoader::InitialPositionStr))
				{
					auto position = value[JsonGOLoader::InitialPositionStr].get<std::vector<float>>();
					gameObjectPosition->GetPosition()->set(position[0], position[1]);
				}

				if (value.contains(JsonGOLoader::RenderDataStr))
				{
					const auto rendererData = value[JsonGOLoader::RenderDataStr];
					const auto renderer = gameObject->AddComponent<Components::Rendering::SpriteRenderer>();

					const auto texturePath = rendererData[JsonGOLoader::SpriteStr].get<std::string>();
					const auto assetsDir = FileLoader::Assets;

					std::string finalTexturePath = assetsDir;
					finalTexturePath += texturePath;

					renderer->LoadTexture(finalTexturePath);

					if (rendererData.contains(JsonGOLoader::RenderOrderStr))
					{
						const auto spriteDepth = rendererData[JsonGOLoader::RenderOrderStr].get<float>();
						renderer->SetSpriteDepth(spriteDepth);
					}
				}

				if (value.contains(JsonGOLoader::ComponentsStr))
				{
					// TODO: Do something here. Maybe when there are more components
				}

				if (value.contains(JsonGOLoader::RigidbodyDataStr))
				{
					const auto rigidbodyData = value[JsonGOLoader::RigidbodyDataStr];
					const auto rigidbody = gameObject->AddComponent<Components::Physics::Rigidbody2D>();

					if (rigidbodyData.contains(JsonGOLoader::MassStr))
					{
						rigidbody->SetMass(rigidbodyData[JsonGOLoader::MassStr].get<float>());
					}

					if (rigidbodyData.contains(JsonGOLoader::GravityScaleStr))
					{
						rigidbody->SetGravityScale(rigidbodyData[JsonGOLoader::GravityScaleStr].get<float>());
					}

					if (rigidbodyData.contains(JsonGOLoader::AngularDragStr))
					{
						rigidbody->SetAngularDrag(rigidbodyData[JsonGOLoader::AngularDragStr].get<float>());
					}

					if (rigidbodyData.contains(JsonGOLoader::AngularVelocityStr))
					{
						rigidbody->SetAngularVelocity(rigidbodyData[JsonGOLoader::AngularVelocityStr].get<float>());
					}
				}
			}
		}
		else
		{
			Utils::Debug::LogOutputToWindow("No GameObjects Found");
		}

		// If anything fails the entire operation fails
	}
}
