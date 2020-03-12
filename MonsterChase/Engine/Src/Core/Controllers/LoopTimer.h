#pragma once

#include <chrono>

namespace Core
{
	namespace Controllers
	{
		class LoopTimer
		{
		private:
			const float MaxDeltaAllowed = 0.04167f;

			std::chrono::time_point<std::chrono::steady_clock> _lastTimePoint;
			double _lastDeltaTime{};

			void NormalizeAndSetDeltaTime(double i_deltaTime);

		public:
			// Constructor
			LoopTimer();

			static double DeltaTime;

			[[nodiscard]] double GetDeltaTime() const;
			double RestartClock();
		};
	}
}
