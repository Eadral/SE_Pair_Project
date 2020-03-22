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
using System.Runtime.CompilerServices;
using Microsoft.Win32;

namespace GUI {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
            canvas.Focusable = true;
            canvas.HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch;
            canvas.VerticalAlignment = System.Windows.VerticalAlignment.Stretch;
            canvas.Background = Brushes.WhiteSmoke;
            totalTranslate.X = this.Width / 4;
            totalTranslate.Y = this.Height / 2;
            tempTranslate.X = totalTranslate.X;
            tempTranslate.Y = totalTranslate.Y;

            scaleLevel = 1;
            //Console.WriteLine("scaleLevel: {0}", scaleLevel);

            totalScale.ScaleX = scaleLevel;
            totalScale.ScaleY = scaleLevel;
            totalScale.CenterX = this.Width / 4;
            totalScale.CenterY = this.Height / 2;

            adjustGraph();
            IntersectAPI.Clear();
        }

        private void ButtonAdd(object sender, RoutedEventArgs e) {
            // listView.Items.Add(new { });
            string x1 = text1.Text;
            string y1 = text2.Text;
            string x2 = text3.Text;
            string y2 = text4.Text;
            string r = text3.Text;
            //
            if (selectType.SelectedIndex == 0) {
                IntersectAPI.AddLine(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            } else if (selectType.SelectedIndex == 3) {
                IntersectAPI.AddCircle(int.Parse(x1), int.Parse(y1), int.Parse(r));
            } else if (selectType.SelectedIndex == 1) {
                IntersectAPI.AddRay(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            } else if (selectType.SelectedIndex == 2) {
                IntersectAPI.AddSection(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            }
            
            Draw();
        }

        private void ButtonDebug(object sender, RoutedEventArgs e) {
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
        Double scaleLevel = 1;
        private Color color = Colors.CornflowerBlue;


        private void Canvas_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
            startMovePosition = e.GetPosition((Canvas) sender);
            isMoving = true;
        }

        private void Canvas_OnMouseLeftButtonUp(object sender, MouseButtonEventArgs e) {
            isMoving = false;
            Point endMovePosition = e.GetPosition((Canvas) sender);

            totalTranslate.X += (endMovePosition.X - startMovePosition.X) / scaleLevel;
            totalTranslate.Y += (endMovePosition.Y - startMovePosition.Y) / scaleLevel;
        }

        private void Canvas_OnMouseMove(object sender, MouseEventArgs e) {
            if (isMoving) {
                Point currentMousePosition = e.GetPosition((Canvas) sender);

                Point deltaPt = new Point(0, 0);
                deltaPt.X = (currentMousePosition.X - startMovePosition.X) / scaleLevel;
                deltaPt.Y = (currentMousePosition.Y - startMovePosition.Y) / scaleLevel;

                tempTranslate.X = totalTranslate.X + deltaPt.X;
                tempTranslate.Y = totalTranslate.Y + deltaPt.Y;

                adjustGraph();
            }
        }

        private void Canvas_OnMouseWheel(object sender, MouseWheelEventArgs e) {
            Point scaleCenter = e.GetPosition((Canvas) sender);

            if (e.Delta > 0) {
                scaleLevel *= 1.08;
            }
            else {
                scaleLevel /= 1.08;
            }
            //Console.WriteLine("scaleLevel: {0}", scaleLevel);

            totalScale.ScaleX = scaleLevel;
            totalScale.ScaleY = scaleLevel;
            // totalScale.CenterX = scaleCenter.X;
            // totalScale.CenterY = scaleCenter.Y;
            totalScale.CenterX = this.Width / 4;
            totalScale.CenterY = this.Height / 2;

            adjustGraph();
        }

        private void adjustGraph() {
            listView.Items.Clear();

            DrawCircles();
            DrawLines();
            DrawRays();
            DrawSections();
            DrawIntersections();

            TransformGroup tfGroup = new TransformGroup();
            tfGroup.Children.Add(tempTranslate);
            tfGroup.Children.Add(totalScale);

            foreach (UIElement ue in canvas.Children) {
                ue.RenderTransform = tfGroup;
            }
        }

        private void Draw() {
            canvas.Children.Clear();

            adjustGraph();
        }

        private void DrawIntersections() {
            int size = IntersectAPI.GetIntersectionsSize();
            float[] xs = new float[size];
            float[] ys = new float[size];
            IntersectAPI.GetIntersections(xs, ys, size);
            for (int i = 0; i < size; i++) {
                float x = xs[i], y = ys[i];

                // DrawCircleFill(x, y, 1);
                listView.Items.Add(new ListItem("Intersection", x, y));
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
                listView.Items.Add(new ListItem("Section", x1, y1, x2, y2));
                DrawLine(x1, y1, x2, y2);
            }

        }

        private void DrawRays() {
            int size = IntersectAPI.GetRaysSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetRays(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++) {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];
                listView.Items.Add(new ListItem("Ray", x1, y1, x2, y2));
                DrawRay(x1, y1, x2, y2);
            }

        }

        private void DrawRay(double x1, double y1, double x2, double y2) {
            double dx = x2 - x1;
            double dy = y2 - y1;
            x2 = x1 + 1000000 * dx;
            y2 = y1 + 1000000 * dy;
            DrawLineBasic(x1, y1, x2, y2, 1, color, 1);
        }

        private void DrawLines() {
            int size = IntersectAPI.GetLinesSize();
            int[] x1s = new int[size];
            int[] y1s = new int[size];
            int[] x2s = new int[size];
            int[] y2s = new int[size];
            IntersectAPI.GetLines(x1s, y1s, x2s, y2s, size);
            for (int i = 0; i < size; i++) {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];

                listView.Items.Add(new ListItem("Line", x1, y1, x2, y2));
                DrawLine(x1, y1, x2, y2);
            }
        }

        private void DrawLine(double x1, double y1, double x2, double y2) {
            DrawRay(x1, y1, x2, y2);
            DrawRay(x2, y2, x1, y1);
        }

        private void DrawLineBasic(double x1, double y1, double x2, double y2, double thickness, Color linecolor,
            double yindex) {
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

        private void DrawIntersection(double x, double y) {
            DrawLineBasic(x - 2, y - 2, x + 2, y + 2, 1, Colors.Orange, 10);
            DrawLineBasic(x - 2, y + 2, x + 2, y - 2, 1, Colors.Orange, 10);
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

                listView.Items.Add(new ListItem("Circle", x, y, r));
                // listView.Items.Add(new {})
                DrawCircle(x, y, r);
            }

        }

        private void DrawCircle(double x, double y, double r) {
            y = -y;

            Path path = new Path();
            PathGeometry pathGeometry = new PathGeometry();
            ArcSegment arc = new ArcSegment(new Point(x, y + r), new Size(r, r), 0, false,
                SweepDirection.Counterclockwise, true);
            PathFigure figure = new PathFigure();
            figure.StartPoint = new Point(x, y - r);
            figure.Segments.Add(arc);
            pathGeometry.Figures.Add(figure);
            path.Data = pathGeometry;
            path.Stroke = new SolidColorBrush(color);
            canvas.Children.Add(path);

            Path path2 = new Path();
            PathGeometry pathGeometry2 = new PathGeometry();
            ArcSegment arc2 = new ArcSegment(new Point(x, y + r), new Size(r, r), 0, false, SweepDirection.Clockwise,
                true);
            PathFigure figure2 = new PathFigure();
            figure2.StartPoint = new Point(x, y - r);
            figure2.Segments.Add(arc2);
            pathGeometry2.Figures.Add(figure2);
            path2.Data = pathGeometry2;
            path2.Stroke = new SolidColorBrush(color);
            canvas.Children.Add(path2);

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

        private void DrawCircleFill(double x, double y, double r) {
            y = -y;
            Ellipse el = new Ellipse();
            Trace.WriteLine($"Circle({x}, {y}, {r})");
            el.Width = 2 * r;
            el.Height = 2 * r;

            el.SetValue(Canvas.LeftProperty, (double) x - r);
            el.SetValue(Canvas.TopProperty, (double) y - r);
            el.Fill = new SolidColorBrush(color);
            el.Stroke = new SolidColorBrush(color);
            el.StrokeThickness = 1;
            canvas.Children.Add(el);
        }

        private void ButtonDraw(object sender, RoutedEventArgs e) {
            Draw();
        }


        private void ListView_OnSelected(object sender, RoutedEventArgs e) {

            ListItem item = listView.SelectedItem as ListItem;
            if (item == null) return;
            if (item.type == "Line") {
                selectType.SelectedIndex = 0;
                text1.Text = item.x1;
                text2.Text = item.y1;
                text3.Text = item.x2;
                text4.Text = item.y2;
            }

            if (item.type == "Ray") {
                selectType.SelectedIndex = 1;
                text1.Text = item.x1;
                text2.Text = item.y1;
                text3.Text = item.x2;
                text4.Text = item.y2;
            }

            if (item.type == "Section") {
                selectType.SelectedIndex = 2;
                text1.Text = item.x1;
                text2.Text = item.y1;
                text3.Text = item.x2;
                text4.Text = item.y2;
            }

            if (item.type == "Circle") {
                selectType.SelectedIndex = 3;
                text1.Text = item.x1;
                text2.Text = item.y1;
                text3.Text = item.r;
            }
        }

        private void refrashInput() {
            if (label1 == null)
                return;
            if (selectType.SelectedIndex == 0) {
                label1.Text = "x1";
                label2.Text = "y1";
                label3.Text = "x2";
                label4.Text = "y2";
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 1) {
                label1.Text = "x1";
                label2.Text = "y1";
                label3.Text = "x2";
                label4.Text = "y2";
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 2) {
                label1.Text = "x1";
                label2.Text = "y1";
                label3.Text = "x2";
                label4.Text = "y2";
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 3) {
                label1.Text = "x";
                label2.Text = "y";
                label3.Text = "r";
                // label4.Content = "y2";
                label4.Visibility = Visibility.Hidden;
                text4.Visibility = Visibility.Hidden;
            }
        }

        // private void SetInput(int type, int t1, int t2, int t3, int t4) {
        //     selectType.SelectedIndex = type;
        //     text1.Text = t1.ToString();
        //     text2.Text = t2.ToString();
        //     text3.Text = t3.ToString();
        //     text4.Text = t4.ToString();
        // }

        private void selectType_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            refrashInput();
        }

        class ListItem {
            public string type { set; get; }
            public string x1 { set; get; }
            public string y1 { set; get; }
            public string x2 { set; get; }
            public string y2 { set; get; }
            public string r { set; get; }

            public ListItem(string type, int x1, int y1, int x2, int y2) {
                this.type = type;
                this.x1 = x1.ToString();
                this.y1 = y1.ToString();
                this.x2 = x2.ToString();
                this.y2 = y2.ToString();
            }

            public ListItem(string type, int x, int y, int r) {
                this.type = type;
                x1 = x.ToString();
                y1 = y.ToString();
                this.r = r.ToString();
            }

            public ListItem(string type, double x, double y) {
                this.type = type;
                x1 = $"{x:F2}";
                y1 = $"{y:F2}";
            }
        }

        private void ButtonRemove(object sender, RoutedEventArgs e) {
            string x1 = text1.Text;
            string y1 = text2.Text;
            string x2 = text3.Text;
            string y2 = text4.Text;
            string r = text3.Text;
            //
            if (selectType.SelectedIndex == 0)
            {
                IntersectAPI.RemoveLine(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            }
            else if (selectType.SelectedIndex == 3)
            {
                IntersectAPI.RemoveCircle(int.Parse(x1), int.Parse(y1), int.Parse(r));
            }
            else if (selectType.SelectedIndex == 1)
            {
                IntersectAPI.RemoveRay(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            }
            else if (selectType.SelectedIndex == 2)
            {
                IntersectAPI.RemoveSection(int.Parse(x1), int.Parse(y1), int.Parse(x2), int.Parse(y2));
            }
            // IntersectAPI.Clear();
            int size = IntersectAPI.GetIntersectionsSize();

            Draw();
        }

        private void ButtonImport(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "Import";
            openFileDialog.Filter = "Text file(*.txt)|*.txt";
            openFileDialog.FileName = string.Empty;
            openFileDialog.FilterIndex = 1;
            openFileDialog.Multiselect = false;
            openFileDialog.RestoreDirectory = true;
            openFileDialog.DefaultExt = "txt";
            if (openFileDialog.ShowDialog() == false)
            {
                return;
            }
            string txtFile = openFileDialog.FileName;
            string text = System.IO.File.ReadAllText(txtFile);
            IntersectAPI.Input(text);
            Draw();
        }
    }
}
