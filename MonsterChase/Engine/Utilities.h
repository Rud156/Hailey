#pragma once

namespace Utils
{
	class Utilities
	{
	private:
		Utilities();
		~Utilities();

	public:
		static size_t GetRoundNextMultiple(size_t number, unsigned int multiple);
		
	};
}
