#pragma once

namespace Containers::Tests
{
	class PointerTest
	{
	public:

		class MockParent
		{
		public:
			virtual ~MockParent() = default;
			virtual void SayHello();
		};

		class MockChild final : public MockParent
		{
		public:
			void SayHello() override;
			~MockChild() override;
		};

		static void RunPointerUnitTest();
	};
}
