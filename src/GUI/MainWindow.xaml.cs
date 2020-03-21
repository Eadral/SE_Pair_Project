using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using System.Globalization;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            canvas.Focusable = true;
            canvas.HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch;
            canvas.VerticalAlignment = System.Windows.VerticalAlignment.Stretch;
            canvas.Background = Brushes.WhiteSmoke;
            totalTranslate.X = this.Width / 4;
            totalTranslate.Y = this.Height / 2;
            tempTranslate.X = totalTranslate.X;
            tempTranslate.Y = totalTranslate.Y;
            adjustGraph();
            IntersectAPI.Clear();
        }

        private void ButtonAdd(object sender, RoutedEventArgs e)
        {
            // listView.Items.Add(new { });
            string type = text_type.Text;
            string x1 = text_x1.Text;
            string y1 = text_y1.Text;
            string x2 = text_x2.Text;
            string y2 = text_y2.Text;
            string r = text_r.Text;

            if (type == "Line") {
                IntersectAPI.AddLine(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            } else if (type == "Circle") {
                IntersectAPI.AddCircle(int.Parse(x1), int.Parse(y1), int.Parse(r));
            } else if (type == "Ray") {
                IntersectAPI.AddRay(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            } else if (type == "Section") {
                IntersectAPI.AddSection(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            }

            Draw();
        }

        private void ButtonDebug(object sender, RoutedEventArgs e)
        {
            // IntersectAPI.Clear();
            // Trace.WriteLine("test");
            // Draw();
            // Trace.WriteLine("test end");
            Trace.WriteLine($"lines: {IntersectAPI.GetLinesSize()}");
            Trace.WriteLine($"intersections: {IntersectAPI.GetIntersectionsSize()}");
            int size = IntersectAPI.GetLinesSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetLines(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++) {
                Trace.WriteLine($"Line({x1s[i]}, {y1s[i]}, {x2s[i]}, {y2s[i]})");
            }
            
        }

        bool isMoving = false;
        Point startMovePosition;

        TranslateTransform totalTranslate = new TranslateTransform();
        TranslateTransform tempTranslate = new TranslateTransform();
        ScaleTransform totalScale = new ScaleTransform();
        Double scaleLevel = 3;
        private Color color = Colors.CornflowerBlue;


        private void Canvas_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            startMovePosition = e.GetPosition((Canvas)sender);
            isMoving = true;
        }

        private void Canvas_OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            isMoving = false;
            Point endMovePosition = e.GetPosition((Canvas)sender);

            totalTranslate.X += (endMovePosition.X - startMovePosition.X) / scaleLevel;
            totalTranslate.Y += (endMovePosition.Y - startMovePosition.Y) / scaleLevel;
        }

        private void Canvas_OnMouseMove(object sender, MouseEventArgs e)
        {
            if (isMoving)
            {
                Point currentMousePosition = e.GetPosition((Canvas)sender);

                Point deltaPt = new Point(0, 0);
                deltaPt.X = (currentMousePosition.X - startMovePosition.X) / scaleLevel;
                deltaPt.Y = (currentMousePosition.Y - startMovePosition.Y) / scaleLevel;

                tempTranslate.X = totalTranslate.X + deltaPt.X;
                tempTranslate.Y = totalTranslate.Y + deltaPt.Y;

                adjustGraph();
            }
        }

        private void Canvas_OnMouseWheel(object sender, MouseWheelEventArgs e)
        {
            Point scaleCenter = e.GetPosition((Canvas)sender);

            if (e.Delta > 0)
            {
                scaleLevel *= 1.08;
            }
            else
            {
                scaleLevel /= 1.08;
            }
            //Console.WriteLine("scaleLevel: {0}", scaleLevel);

            totalScale.ScaleX = scaleLevel;
            totalScale.ScaleY = scaleLevel;
            totalScale.CenterX = scaleCenter.X;
            totalScale.CenterY = scaleCenter.Y;

            adjustGraph();
        }

        private void adjustGraph()
        {
            DrawCircles();
            DrawLines();
            DrawRays();
            DrawSections();
            DrawIntersections();

            TransformGroup tfGroup = new TransformGroup();
            tfGroup.Children.Add(tempTranslate);
            tfGroup.Children.Add(totalScale);

            foreach (UIElement ue in canvas.Children)
            {
                ue.RenderTransform = tfGroup;
            }
        }

        private void Draw()
        {
            canvas.Children.Clear();

        

            adjustGraph();
        }

        private void DrawIntersections()
        {
            int size = IntersectAPI.GetIntersectionsSize();
            float[] xs = new float[size];
            float[] ys = new float[size];
            IntersectAPI.GetIntersections(xs, ys, size);
            for (int i = 0; i < size; i++)
            {
                float x = xs[i], y = ys[i];

                // DrawCircleFill(x, y, 1);
                DrawIntersection(x, y);
            }
        }

        private void DrawSections() {
            int size = IntersectAPI.GetSectionsSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetSections(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++) {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];
                
                DrawLine(x1, y1, x2, y2);
            }
            
        }

        private void DrawRays()
        {
            int size = IntersectAPI.GetRaysSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetRays(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++)
            {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];

                DrawLine(x1, y1, x2, y2);
            }

        }

        private void DrawLines() {
            int size = IntersectAPI.GetLinesSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetLines(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++)
            {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];

                DrawLine(x1, y1, x2, y2);
            }
        }

        private void DrawLine(double x1, double y1, double x2, double y2) {
            DrawLineBasic(x1, y1, x2, y2, 1, color, 1);
        }

        private void DrawLineBasic(double x1, double y1, double x2, double y2, double thickness, Color linecolor, double yindex) {
            y1 = -y1;
            y2 = -y2;
            Line l = new Line();
            l.Stroke = new SolidColorBrush(linecolor);
            l.StrokeThickness = thickness;
            l.X1 = x1;
            l.Y1 = y1;
            l.X2 = x2;
            l.Y2 = y2;

            canvas.Children.Add(l);
        }

        private void DrawIntersection(double x, double y)
        {
            DrawLineBasic(x - 1, y - 1, x + 1, y + 1, 0.5, Colors.Orange, 10);
            DrawLineBasic(x - 1, y + 1, x + 1, y - 1, 0.5, Colors.Orange, 10);
        }

        private void DrawCircles() {
            int size = IntersectAPI.GetCirclesSize();
            int[] xs = new int[size];
            int[] ys = new int[size];
            int[] rs = new int[size];
            IntersectAPI.GetCircles(xs, ys, rs, size);

            for (int i = 0; i < size; i++) {
               
                int x = xs[i];
                int y = ys[i];
                int r = rs[i];

                DrawCircle(x, y, r);
            }
            
        }

        private void DrawCircle(double x, double y, double r) {
            y = -y;

            // Path path = new Path();
            // PathGeometry pathGeometry = new PathGeometry();
            // ArcSegment arc = new ArcSegment(new Point(100, 200), new Size(50, 100), 0, false, SweepDirection.Counterclockwise, true);
            // PathFigure figure = new PathFigure();
            // figure.StartPoint = new Point(100, 0);
            // figure.Segments.Add(arc);
            // pathGeometry.Figures.Add(figure);
            // path.Data = pathGeometry;
            // path.Stroke = Brushes.Orange;
            // canvas.Children.Add(path);
            // Ellipse el = new Ellipse();
            // Trace.WriteLine($"Circle({x}, {y}, {r})");
            // el.Width = 2 * r;
            // el.Height = 2 * r;
            // el.SetValue(Canvas.LeftProperty, (double)x - r);
            // el.SetValue(Canvas.TopProperty, (double)y - r);
            // el.Stroke = new SolidColorBrush(color);
            // el.StrokeThickness = 1;
            // canvas.Children.Add(el);
        }

        private void DrawCircleFill(double x, double y, double r)
        {
            y = -y;
            Ellipse el = new Ellipse();
            Trace.WriteLine($"Circle({x}, {y}, {r})");
            el.Width = 2 * r;
            el.Height = 2 * r;
            
            el.SetValue(Canvas.LeftProperty, (double)x - r);
            el.SetValue(Canvas.TopProperty, (double)y - r);
            el.Fill = new SolidColorBrush(color);
            el.Stroke = new SolidColorBrush(color);
            el.StrokeThickness = 1;
            canvas.Children.Add(el);
        }

        private void ButtonDraw(object sender, RoutedEventArgs e) {
            Draw();
        }

       
    }
}
