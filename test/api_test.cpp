#include "../src/Core/solver.h"
#include "CppUnitTest.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(APITest)
	{
	public:
        TEST_METHOD(E2ETest) {
			Clear();
			char buf[] = "2\nL 0 0 1 1\nL0 1 1 0\n";
			Input(buf);
			Assert::AreEqual(1, GetIntersectionsSize());
			double xs[5], ys[5];
			GetIntersections(xs, ys, 1);
			Assert::AreEqual(0.5, xs[0]);
			Assert::AreEqual(0.5, ys[0]);
        }

		TEST_METHOD(LineTest) {
			Clear();
			AddLine(1, 2, 3, 4);
			AddLine(2, 3, 4, 5);
			RemoveLine(2, 3, 4, 5);
			Assert::AreEqual(1, GetLinesSize());
			int x1s[5], y1s[5], x2s[5], y2s[5];
			GetLines(x1s, y1s, x2s, y2s, 1);
			Assert::AreEqual(1, x1s[0]);
			Assert::AreEqual(2, y1s[0]);
			Assert::AreEqual(3, x2s[0]);
			Assert::AreEqual(4, y2s[0]);
		}

		TEST_METHOD(RayTest) {
			Clear();
			AddRay(1, 2, 3, 4);
			AddRay(2, 3, 4, 5);
			RemoveRay(2, 3, 4, 5);
			Assert::AreEqual(1, GetRaysSize());
			int x1s[5], y1s[5], x2s[5], y2s[5];
			GetRays(x1s, y1s, x2s, y2s, 1);
			Assert::AreEqual(1, x1s[0]);
			Assert::AreEqual(2, y1s[0]);
			Assert::AreEqual(3, x2s[0]);
			Assert::AreEqual(4, y2s[0]);
		}

		TEST_METHOD(SectionTest) {
			Clear();
			AddSection(1, 2, 3, 4);
			AddSection(2, 3, 4, 5);
			RemoveSection(2, 3, 4, 5);
			Assert::AreEqual(1, GetSectionsSize());
			int x1s[5], y1s[5], x2s[5], y2s[5];
			GetSections(x1s, y1s, x2s, y2s, 1);
			Assert::AreEqual(1, x1s[0]);
			Assert::AreEqual(2, y1s[0]);
			Assert::AreEqual(3, x2s[0]);
			Assert::AreEqual(4, y2s[0]);
		}

		TEST_METHOD(CircleTest) {
			Clear();
			AddCircle(1, 2, 3);
			AddCircle(2, 3, 4);
			RemoveCircle(2, 3, 4);
			Assert::AreEqual(1, GetCirclesSize());
			int x1s[5], y1s[5], x2s[5];
			GetCircles(x1s, y1s, x2s, 1);
			Assert::AreEqual(1, x1s[0]);
			Assert::AreEqual(2, y1s[0]);
			Assert::AreEqual(3, x2s[0]);
		}


	};
}
