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
using System.Resources;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace GUI {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();
            
            resman = new ResourceManager(new Resource().GetType());
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

            try
            {
                NativeMethods.Clear();
            }
            catch (ExternalException e)
            {
                try
                {
                    NativeMethods.resetRes();
                    api_type = 1;
                }
                catch (Exception exception) {
                    Console.WriteLine(exception);
                }
               
            }

            adjustGraph();
            

           
        }

        private int api_type = 0;

        ResourceManager resman;

        private int IntParse(string str) {
            return int.Parse(str, CultureInfo.InvariantCulture);
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
                AddLine(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            } else if (selectType.SelectedIndex == 3) {
                AddCircle(IntParse(x1), IntParse(y1), IntParse(r));
            } else if (selectType.SelectedIndex == 1) {
                AddRay(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            } else if (selectType.SelectedIndex == 2) {
                AddSection(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            }
            
            Draw();
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
            int size = GetIntersectionsSize();
            double[] xs = new double[size];
            double[] ys = new double[size];
            GetIntersections(xs, ys, size);
            for (int i = 0; i < size; i++) {
                double x = xs[i], y = ys[i];

                // DrawCircleFill(x, y, 1);
                listView.Items.Add(new ListItem("Intersection", x, y));
                DrawIntersection(x, y);
            }
        }

        private void DrawSections() {
            int size;
            int[] x1s;
            int[] y1s;
            int[] x2s;
            int[] y2s;
            GetSections(out x1s, out y1s, out x2s, out y2s, out size);
            for (int i = 0; i < size; i++) {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];
                listView.Items.Add(new ListItem("Section", x1, y1, x2, y2));
                DrawLine(x1, y1, x2, y2);
            }

        }

        private void DrawRays() {
            int size;
            int[] x1s;
            int[] y1s;
            int[] x2s;
            int[] y2s;
            GetRays(out x1s, out y1s, out x2s, out y2s, out size);
            for (int i = 0; i < size; i++) {
                int x1 = x1s[i], y1 = y1s[i], x2 = x2s[i], y2 = y2s[i];
                listView.Items.Add(new ListItem("Ray", x1, y1, x2, y2));
                DrawRay(x1, y1, x2, y2);
            }

        }

        private void DrawRay(double x1, double y1, double x2, double y2) {
            double dx = x2 - x1;
            double dy = y2 - y1;
            x2 = x1 + 1000 * dx;
            y2 = y1 + 1000 * dy;
            DrawLineBasic(x1, y1, x2, y2, 1, color);
        }

        private void DrawLines() {
            int size;
            int[] x1s;
            int[] y1s;
            int[] x2s;
            int[] y2s;
            GetLines(out x1s, out y1s, out x2s, out y2s, out size);
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

        private void DrawLineBasic(double x1, double y1, double x2, double y2, double thickness, Color linecolor) {
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
            DrawLineBasic(x - 2, y - 2, x + 2, y + 2, 1, Colors.Orange);
            DrawLineBasic(x - 2, y + 2, x + 2, y - 2, 1, Colors.Orange);
        }

        private void DrawCircles() {
            int size = GetCirclesSize();
            int[] xs = new int[size];
            int[] ys = new int[size];
            int[] rs = new int[size];
            GetCircles(xs, ys, rs, size);

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

        private string GetString(string name) {
            return resman.GetString(name, CultureInfo.InvariantCulture);
        }

        private void refrashInput() {
            if (label1 == null)
                return;
            if (selectType.SelectedIndex == 0) {

                label1.Text = GetString("x1");
                label2.Text = GetString("y1");
                label3.Text = GetString("x2");
                label4.Text = GetString("y2");
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 1) {
                label1.Text = GetString("x1");
                label2.Text = GetString("y1");
                label3.Text = GetString("x2");
                label4.Text = GetString("y2");
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 2) {
                label1.Text = GetString("x1");
                label2.Text = GetString("y1");
                label3.Text = GetString("x2");
                label4.Text = GetString("y2");
                label4.Visibility = Visibility.Visible;
                text4.Visibility = Visibility.Visible;
            }
            else if (selectType.SelectedIndex == 3) {
                label1.Text = GetString("x");
                label2.Text = GetString("y");
                label3.Text = GetString("r");
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
                this.x1 = x1.ToString(CultureInfo.InvariantCulture);
                this.y1 = y1.ToString(CultureInfo.InvariantCulture);
                this.x2 = x2.ToString(CultureInfo.InvariantCulture);
                this.y2 = y2.ToString(CultureInfo.InvariantCulture);
            }

            public ListItem(string type, int x, int y, int r) {
                this.type = type;
                x1 = x.ToString(CultureInfo.InvariantCulture);
                y1 = y.ToString(CultureInfo.InvariantCulture);
                this.r = r.ToString(CultureInfo.InvariantCulture);
            }

            public ListItem(string type, double x, double y) {
                this.type = type;
                x1 = $"{x:F2}";
                y1 = $"{y:F2}";
            }
        }

        private void RemoveLine(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.RemoveLine(x1, y1, x2, y2);
                else NativeMethods.delLine('L', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void RemoveRay(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.RemoveRay(x1, y1, x2, y2);
                else NativeMethods.delLine('R', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void RemoveSection(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.RemoveSection(x1, y1, x2, y2);
                else NativeMethods.delLine('S', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void RemoveCircle(int x, int y, int r)
        {
            try {
                if (api_type == 0) NativeMethods.RemoveCircle(x, y, r);
                else NativeMethods.delCircle(x, y, r);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void AddLine(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.AddLine(x1, y1, x2, y2);
                else NativeMethods.addLine('L', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void AddRay(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.AddRay(x1, y1, x2, y2);
                else NativeMethods.addLine('R', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void AddSection(int x1, int y1, int x2, int y2)
        {
            try {
                if (api_type == 0) NativeMethods.AddSection(x1, y1, x2, y2);
                else NativeMethods.addLine('S', x1, y1, x2, y2);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void AddCircle(int x, int y, int r)
        {
            try
            {
                if (api_type == 0) NativeMethods.AddCircle(x, y, r);
                else NativeMethods.addCircle(x, y, r);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
           
        }

        private int GetIntersectionsSize() {
            try {
                if (api_type == 0) return NativeMethods.GetIntersectionsSize();
                else return NativeMethods.getResultOfIntersect();
            }
            catch (Exception e) {
                Console.WriteLine(e);
                return 0;
            }
            
        }

        private void GetIntersections(double[] xs, double[] ys, int size) {
            try
            {
                if (api_type == 0) NativeMethods.GetIntersections(xs, ys, size);
                else NativeMethods.getPoint(xs, ys);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
           
        }

        private int GetCirclesSize() {
            try
            {
                if (api_type == 0) return NativeMethods.GetCirclesSize();
                else return NativeMethods.getNumOfCircles();
            }
            catch (Exception e) {
                Console.WriteLine(e);
                return 0;
            }
           
        }

        private void GetCircles(int[] xs, int[] ys, int[] rs, int size) {
            try {
                if (api_type == 0) NativeMethods.GetCircles(xs, ys, rs, size);
                else NativeMethods.getCircles(xs, ys, rs, size);
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            
        }

        private void GetLines(out int[] x1s, out int[] y1s, out int[] x2s, out int[] y2s, out int size)
        {
            try {
                if (api_type == 0)
                {
                    size = NativeMethods.GetLinesSize();
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    NativeMethods.GetLines(x1s, y1s, x2s, y2s, size);
                }
                else
                {
                    int all_size = NativeMethods.getNumOfLines();
                    char[] all_types = new char[all_size];
                    int[] all_x1s = new int[all_size];
                    int[] all_y1s = new int[all_size];
                    int[] all_x2s = new int[all_size];
                    int[] all_y2s = new int[all_size];
                    size = 0;
                    NativeMethods.getLines(all_types, all_x1s, all_y1s, all_x2s, all_y2s, all_size);
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'L') size++;
                    }
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    int p = 0;
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'L')
                        {
                            x1s[p] = all_x1s[i];
                            y1s[p] = all_y1s[i];
                            x2s[p] = all_x2s[i];
                            y2s[p] = all_y2s[i];
                            p++;
                        }
                    }
                }
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }

            x1s = null;
            x2s = null;
            y1s = null;
            y2s = null;
            size = 0;
        }

        private void GetRays(out int[] x1s, out int[] y1s, out int[] x2s, out int[] y2s, out int size)
        {
            try {
                if (api_type == 0)
                {
                    size = NativeMethods.GetRaysSize();
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    NativeMethods.GetRays(x1s, y1s, x2s, y2s, size);
                }
                else
                {
                    int all_size = NativeMethods.getNumOfLines();
                    char[] all_types = new char[all_size];
                    int[] all_x1s = new int[all_size];
                    int[] all_y1s = new int[all_size];
                    int[] all_x2s = new int[all_size];
                    int[] all_y2s = new int[all_size];
                    size = 0;
                    NativeMethods.getLines(all_types, all_x1s, all_y1s, all_x2s, all_y2s, all_size);
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'R') size++;
                    }
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    int p = 0;
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'R')
                        {
                            x1s[p] = all_x1s[i];
                            y1s[p] = all_y1s[i];
                            x2s[p] = all_x2s[i];
                            y2s[p] = all_y2s[i];
                            p++;
                        }
                    }
                }
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            x1s = null;
            x2s = null;
            y1s = null;
            y2s = null;
            size = 0;
        }

        private void GetSections(out int[] x1s, out int[] y1s, out int[] x2s, out int[] y2s, out int size)
        {
            try
            {
                if (api_type == 0)
                {
                    size = NativeMethods.GetSectionsSize();
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    NativeMethods.GetSections(x1s, y1s, x2s, y2s, size);
                }
                else
                {
                    int all_size = NativeMethods.getNumOfLines();
                    char[] all_types = new char[all_size];
                    int[] all_x1s = new int[all_size];
                    int[] all_y1s = new int[all_size];
                    int[] all_x2s = new int[all_size];
                    int[] all_y2s = new int[all_size];
                    size = 0;
                    NativeMethods.getLines(all_types, all_x1s, all_y1s, all_x2s, all_y2s, all_size);
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'S') size++;
                    }
                    x1s = new int[size];
                    y1s = new int[size];
                    x2s = new int[size];
                    y2s = new int[size];
                    int p = 0;
                    for (int i = 0; i < all_size; i++)
                    {
                        if (all_types[i] == 'S')
                        {
                            x1s[p] = all_x1s[i];
                            y1s[p] = all_y1s[i];
                            x2s[p] = all_x2s[i];
                            y2s[p] = all_y2s[i];
                            p++;
                        }
                    }
                }
            }
            catch (Exception e) {
                Console.WriteLine(e);
            }
            x1s = null;
            x2s = null;
            y1s = null;
            y2s = null;
            size = 0;
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
                RemoveLine(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            }
            else if (selectType.SelectedIndex == 3)
            {
                RemoveCircle(IntParse(x1), IntParse(y1), IntParse(r));
            }
            else if (selectType.SelectedIndex == 1)
            {
                RemoveRay(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            }
            else if (selectType.SelectedIndex == 2)
            {
                RemoveSection(IntParse(x1), IntParse(y1), IntParse(x2), IntParse(y2));
            }
            // IntersectAPI.Clear();
            int size = GetIntersectionsSize();

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
            try {
                NativeMethods.Input(text);
            }
            catch (Exception exception) {
                Console.WriteLine(exception);
            }
            int size = GetIntersectionsSize();
            Draw();
        }
    }
}
