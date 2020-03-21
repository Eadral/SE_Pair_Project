#include "../src/Core/solver.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(CircleCircleIntersectionTest)
	{
	public:

		TEST_METHOD(TwoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.CircleCircleIntersect(
				Circle(1, 0, 1),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 2);
		}

		TEST_METHOD(ExternallyTangent)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.CircleCircleIntersect(
				Circle(2, 0, 1),
				Circle(0, 0, 1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(InternallTangent)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.CircleCircleIntersect(
				Circle(1, 0, 1),
				Circle(0, 0, 2)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.CircleCircleIntersect(
				Circle(5, 0, 1),
				Circle(0, 0, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

	

	};
}
