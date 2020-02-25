#pragma once

namespace Utils
{
	class Utilities
	{
	private:
		Utilities();
		~Utilities();

	public:
		[[nodiscard]] static size_t GetRoundNextMultiple(size_t i_number, unsigned int i_multiple);
	};
}
