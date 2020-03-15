#pragma once
#include "../../Externals/json.hpp"

#include <future>
#include <vector>
#include <mutex>
#include <string_view>

namespace Core::Loaders
{
	class JsonGOLoader
	{
	private:
		static inline const char* const GameObjectStr = "GOs";
		static inline const char* const NameStr = "Name";
		static inline const char* const InitialPositionStr = "IniPos";

		static inline const char* const RigidbodyDataStr = "RB";
		static inline const char* const MassStr = "Mass";
		static inline const char* const GravityScaleStr = "GraSc";
		static inline const char* const AngularDragStr = "AngDrg";
		static inline const char* const AngularVelocityStr = "AngVel";

		static inline const char* const ComponentsStr = "Comp";

		static inline const char* const RenderDataStr = "Ren";
		static inline const char* const SpriteStr = "Spr";
		static inline const char* const RenderOrderStr = "Ord";

		static std::mutex JsonMutex;
		static std::vector<std::future<void>> FutureList;

		static void LoadGoFileDeferred(std::string i_filePath);
		static void LoadGameObjectDeferred(nlohmann::basic_json<> i_value);

	public:
		static void LoadJsonGameObjectAsync(std::string_view i_filePath);
		static void LoadJsonGameObjectSync(std::string_view i_filePath);
	};
}
