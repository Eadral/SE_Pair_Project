#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(RaySectionIntersectionTest)
	{
	public:

		TEST_METHOD(Cross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RaySectionIntersect(
				Ray(0, 0, 1, 1),
				Section(0, 1, 1, 0)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RaySectionIntersect(
				Ray(0, 0, 1, 1),
				Section(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(InfinietIntersections)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			Assert::ExpectException<CoreException>([&] {solver.RaySectionIntersect(
				Ray(0, 0, 1, 1),
				Section(3, 3, 2, 2)
			); });
		}

	};
}
