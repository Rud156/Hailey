#pragma once

namespace Containers::Tests
{
	class PointerTest
	{
	public:

		class MockParent
		{
		public:
			virtual void SayHello();
		};

		class MockChild : public MockParent
		{
		public:
			void SayHello() override;
		};

		static void RunPointerUnitTest();
	};
}
