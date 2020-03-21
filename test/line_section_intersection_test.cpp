#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(LineLineIntersectionTest)
	{
	public:

		TEST_METHOD(Cross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineSectionIntersect(
				Line(0, 0, 1, 1),
				Section(0, 1, 1, 0)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineSectionIntersect(
				Line(0, 0, 1, 1),
				Section(1, 0, 2, -1)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(Parallel)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineSectionIntersect(
				Line(0, 0, 1, 1),
				Section(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(InfiniteIntersections)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			Assert::ExpectException<CoreException>([&] {solver.LineSectionIntersect(
				Line(0, 0, 1, 1),
				Section(3, 3, 2, 2)
			); });
		}
	};
}
