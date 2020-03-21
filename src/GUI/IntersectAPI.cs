using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Media;

namespace GUI
{
    class IntersectAPI
    {
        [DllImport("intersect_core.dll")]
        public static extern void Clear();

        [DllImport("intersect_core.dll")]
        public static extern void Input([MarshalAs(UnmanagedType.LPStr)]string input);

        [DllImport("intersect_core.dll")]
        public static extern void AddLine(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern void RemoveLine(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern int GetLinesSize();

        [DllImport("intersect_core.dll")]
        public static extern void GetLines(int[] x1s, int[] y1s, int[] x2s, int[] y2s, int size);

        [DllImport("intersect_core.dll")]
        public static extern void AddCircle(int x, int y, int r);

        [DllImport("intersect_core.dll")]
        public static extern void RemoveCircle(int x, int y, int r);

        [DllImport("intersect_core.dll")]
        public static extern int GetCirclesSize();

        [DllImport("intersect_core.dll")]
        public static extern void GetCircles(int[] xs, int[] ys, int[] rs, int size);

        [DllImport("intersect_core.dll")]
        public static extern void AddRay(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern void RemoveRay(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern int GetRaysSize();

        [DllImport("intersect_core.dll")]
        public static extern void GetRays(int[] x1s, int[] y1s, int[] x2s, int[] y2s, int size);

        [DllImport("intersect_core.dll")]
        public static extern void AddSection(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern void RemoveSection(int x1, int y1, int x2, int y2);

        [DllImport("intersect_core.dll")]
        public static extern int GetSectionsSize();

        [DllImport("intersect_core.dll")]
        public static extern void GetSections(int[] x1s, int[] y1s, int[] x2s, int[] y2s, int size);

        [DllImport("intersect_core.dll")]
        public static extern int GetIntersectionsSize();

        [DllImport("intersect_core.dll")]
        public static extern void GetIntersections(float[] xs, float[] ys, int size);
    }
}
