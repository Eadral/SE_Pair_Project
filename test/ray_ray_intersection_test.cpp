#include "../src/Core/solver.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(RayRayIntersectionTest)
	{
	public:

		TEST_METHOD(OnRay)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			
			Assert::IsTrue(solver.PointOnRay(
				0.5, 0.5,
				Ray(-1, 2, 0, 1)
			));
		}

		TEST_METHOD(OnVerticalRay)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);


			Assert::IsTrue(solver.PointOnRay(
				0, 1.9,
				Ray(0, 0, 0, 1)
			));
		}

		TEST_METHOD(NotOnRay)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);


			Assert::IsFalse(solver.PointOnRay(
				0.5, 0.5,
				Ray(0, 1, -1, 2)
			));
		}

		TEST_METHOD(NotOnVerticalRay)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);


			Assert::IsFalse(solver.PointOnRay(
				0, 1.9,
				Ray(0, 1, 0, 0)
			));
		}

		TEST_METHOD(Cross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 1),
				Ray(0, 1, 1, 0)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(SameLineNotCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 1),
				Ray(-1, -1, -2, -2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(SameLineCross)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 1),
				Ray(0, 0, -1, -1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

		TEST_METHOD(InfinietIntersections)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			Assert::ExpectException<CoreException>([&] {solver.RayRayIntersect(
				Ray(0, 0, 1, 1),
				Ray(3, 3, 2, 2)
			);});
		}
		TEST_METHOD(Parallel)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 1),
				Ray(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 0);
		}

		TEST_METHOD(FourRays)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 0),
				Ray(0, 0, 0, 1)
			);

			solver.RayRayIntersect(
				Ray(0, 1, 1, 1),
				Ray(0, 1, 1, 2)
			);

			Assert::AreEqual(solver.GetAns(), 2);
		}

		TEST_METHOD(PointOnRay) {
			Assert::AreEqual(false, Solver::PointOnRay(0, 0, Ray(1, 1, 1, 1)));
			Assert::AreEqual(true, Solver::PointOnRay(1, 0, Ray(1, 1, 1, 0)));
		}

		TEST_METHOD(PointOnSection) {
			Assert::AreEqual(true, Solver::PointOnSection(1.5, 1.5, Section(2, 2, 1, 1)));
			Assert::AreEqual(false, Solver::PointOnSection(-1.5, 1.5, Section(2, 2, 1, 1)));
			Assert::AreEqual(true, Solver::PointOnSection(1, 1.5, Section(1, 2, 1, 1)));
			Assert::AreEqual(false, Solver::PointOnSection(-1, -1.5, Section(1, 2, 1, 1)));
			Assert::AreEqual(false, Solver::PointOnSection(-1.5, 1.5, Section(1, 1, 1, 1)));
		}

		TEST_METHOD(RayRayIntersectX)
		{
			stringstream sin;
			stringstream sout;

			Solver solver(sin, sout);

			solver.RayRayIntersect(
				Ray(0, 0, 1, 0),
				Ray(0, 0, -1, 0)
			);

			solver.RayRayIntersect(
				Ray(0, 0, 0, 1),
				Ray(0, 0, 0, -1)
			);

			Assert::AreEqual(solver.GetAns(), 1);
		}

	};
}
