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

			solver.LineLineIntersect(
				Line(0, 0, 1, 1),
				Line(0, 1, 1, 0)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.LineLineIntersect(
				Line(0, 0, 1, 1),
				Line(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}
		
	};
}
