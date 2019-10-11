#include "stdafx.h"
#include "Engine.h"
#include <iostream>

namespace Engine
{
	void Init()
	{
		std::cout << "Engine Initialized" << std::endl;
	}

	void ShutDown()
	{
		std::cout << "Engine ShutDown" << std::endl;
	}
}
