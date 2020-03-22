#include "../src/Core/solver.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(SectionCircleIntersectionTest)
	{
	public:

		TEST_METHOD(OneCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionCircleIntersect(
				Section(0, 0, 0, 1),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(TwoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionCircleIntersect(
				Section(0, -10, 0, 10),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 2);
		}

		TEST_METHOD(Tangent)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionCircleIntersect(
				Section(1, -1, 1, 1),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionCircleIntersect(
				Section(3, 0, 3, 1),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

	};
}
