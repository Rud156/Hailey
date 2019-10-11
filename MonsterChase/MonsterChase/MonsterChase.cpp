// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Engine.h"
#include "Point2D.h"
#include <conio.h>
#include <iostream>

int main()
{
	{
		Engine::Init();

		Math::Point2D P1(0.0f, 0.0f);
		Math::Point2D P2(0.0f, 0.0f);

		Math::Point2D P3 = P1 + P2;
		P3 = P1 - P2;

		Math::Point2D P4 = P1 * 0.5f;

		Math::Point2D P5 = P1 / 2.0f;

		Math::Point2D P6 = -P4;

		P6 *= 2.0f;
		P5 /= 4.0f;

		P2 += P1;
		P3 -= P1;

		Math::Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

		const bool bArentEqual = P6 != P4;
		std::cout << bArentEqual << std::endl;

		Engine::ShutDown();
	}

	_getch();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
