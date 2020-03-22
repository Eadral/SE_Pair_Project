#include "../src/Core/solver.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(LineRayIntersectionTest)
	{
	public:

		TEST_METHOD(Cross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineRayIntersect(
				Line(0, 0, 1, 1),
				Ray(-1, 2, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineRayIntersect(
				Line(0, 0, 1, 1),
				Ray(0, 1, -1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(Parallel)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineRayIntersect(
				Line(0, 0, 1, 1),
				Ray(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(InfinietIntersections)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			Assert::ExpectException<CoreException>([&] {solver.LineRayIntersect(
				Line(0, 0, 1, 1),
				Ray(3, 3, 2, 2)
			); });
		}

	};
}
