#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(SectionSectionIntersectionTest)
	{
	public:

		TEST_METHOD(Cross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionSectionIntersect(
				Section(0, 0, 1, 1),
				Section(1, 1, 2, 0)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(NoCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.SectionSectionIntersect(
				Section(0, 0, 1, 1),
				Section(2, 2, 3, 3)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(InfinietIntersections)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			Assert::ExpectException<CoreException>([&] {solver.SectionSectionIntersect(
				Section(0, 0, 2, 2),
				Section(1, 1, 3, 3)
			); });
		}
	};
}
