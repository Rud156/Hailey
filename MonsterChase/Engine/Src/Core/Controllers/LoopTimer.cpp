#include "LoopTimer.h"

double Core::Controllers::LoopTimer::DeltaTime;

namespace Core::Controllers
{
	LoopTimer::LoopTimer()
	{
		this->_lastTimePoint = std::chrono::high_resolution_clock::now();
	}

	void LoopTimer::NormalizeAndSetDeltaTime(double i_deltaTime)
	{
		if (i_deltaTime > MaxDeltaAllowed)
		{
			i_deltaTime = MaxDeltaAllowed;
		}

		LoopTimer::DeltaTime = i_deltaTime;
		this->_lastDeltaTime = i_deltaTime;
	}

	double LoopTimer::GetDeltaTime() const
	{
		return this->_lastDeltaTime;
	}

	double LoopTimer::RestartClock()
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto duration = (std::chrono::duration_cast<
				std::chrono::duration<double>>(currentTime - this->_lastTimePoint)
		);

		this->_lastTimePoint = currentTime;

		const auto timeSpan = duration.count();
		this->NormalizeAndSetDeltaTime(timeSpan);
		return this->_lastDeltaTime;
	}
}
