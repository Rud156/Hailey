#include "PointerTest.h"
#include "../SmartPtr.h"
#include "../WeakPtr.h"
#include "../../Utils/Debug.h"

namespace Containers::Tests
{
	void PointerTest::MockParent::SayHello()
	{
		Utils::Debug::LogOutputToWindow("Hello From Parent\n");
		Utils::Debug::LogToFile("Hello From Parent\n");
	}

	void PointerTest::MockChild::SayHello()
	{
		Utils::Debug::LogOutputToWindow("Hello From Child\n");
		Utils::Debug::LogToFile("Hello From Child\n");
	}

	PointerTest::MockChild::~MockChild() = default;

	void PointerTest::RunPointerUnitTest()
	{
		WeakPtr<MockParent> weakPtr;

		{
			SmartPtr<MockParent> smParent(new MockParent());
			smParent->SayHello();

			SmartPtr<MockParent> smParent_1 = smParent;
			weakPtr = smParent;

			if (auto smParent_2 = weakPtr.Lock())
			{
				smParent_2->SayHello();
			}

			const bool isParentValid = smParent.IsValid();
			Utils::Debug::LogOutputToWindow("Is Valid: %d\n", isParentValid);
		}

		{
			SmartPtr<MockParent> smChildParent(new MockChild());
			smChildParent->SayHello();

			WeakPtr<MockParent> parentPtr(smChildParent);
		}
	}
}
