using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
using System.IO;

namespace Paint
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //Shapes to add to the canvas when created
        Polyline _pencil;
        Polyline _brush;
        Rectangle _rectangle = null;
        Ellipse _ellipse = null;
        Line _line = null;

        //Variables used to draw the select box
        Rectangle _select = null;
        CroppedBitmap _selectBitmap = null;
        CroppedBitmap _editedBitmap = null;
        Image _selectImage = null;
        TransformGroup transformGroup = null;
        bool _isSelected = false;
        bool _isDragging = false;

        //Variables used to draw polygons
        Polygon _polygon = null;
        Point _currentPoint;

        //Variables used to draw textboxes
        TextBlock _text = null;
        Point _textInputPoint;

        //Variables used while drawing bezier curves
        PathFigure _bezier = null;
        BezierSegment _bezierSegment = null;
        int _bezierPointCounter = 0;

        //Point used to store the starting position of the object to be drawn
        Point startPoint;

        //Brush to store the border color, fill color, and text color
        SolidColorBrush colorBrush = Brushes.Black;
        SolidColorBrush fillBrush = Brushes.WhiteSmoke;
        SolidColorBrush textColor = Brushes.Black;

        //Boolean objects used to handle text settings, color settings, and size settings
        bool fillObject = false;
        bool bold = false;
        bool italic = false;
        bool underline = false;
        bool setToolColor = false;
        bool setBorderColor = false;
        bool setTextColor = false;
        int borderSize = 5;
        int textSize = 12;

        public MainWindow()
        {
            InitializeComponent();
        }

        #region Menu bar logic
        //Wipes the canvas clean of all children elements
        private void ClearCanvas()
        {
            DrawingCanvas.Children.Clear();
        }

        //Called when the user selects the Status Bar option in the view menu
        private void mnuStatusBar_Click(object sender, RoutedEventArgs e)
        {
            //If the status bar option is checked
            if (mnuStatusBar.IsChecked)
            {
                //Sets the status bar as visible
                statusBar.Visibility = System.Windows.Visibility.Visible;

                //changes height of canvas when color box is shown
                Thickness drawingMargin = DrawingCanvas.Margin;
                drawingMargin.Bottom += statusBar.Height;
                DrawingCanvas.Margin = drawingMargin;
            }
            else
            {
                //Hides the status bar
                statusBar.Visibility = System.Windows.Visibility.Hidden;

                //changes height of canvas when color box is hidden
                Thickness drawingMargin = DrawingCanvas.Margin;
                drawingMargin.Bottom -= statusBar.Height;
                DrawingCanvas.Margin = drawingMargin;
            }
        }

        //Called when the user selects the Tool Box option in the view menu
        private void mnuToolBox_Click(object sender, RoutedEventArgs e)
        {
            if (mnuToolBox.IsChecked)
            {
                toolBox.Visibility = System.Windows.Visibility.Visible;

                //changes height of canvas when tool box is not hidden
                Thickness canvasMargin = DrawingCanvas.Margin;
                canvasMargin.Top += toolBox.Height;
                DrawingCanvas.Margin = canvasMargin;
            }
            else
            {
                toolBox.Visibility = System.Windows.Visibility.Hidden;

                //changes height of canvas when tool box is hidden
                Thickness canvasMargin = DrawingCanvas.Margin;
                canvasMargin.Top -= toolBox.Height;
                DrawingCanvas.Margin = canvasMargin;
            }
                
        }
        #endregion

        #region Tool button event switching logic

        /// <summary>
        /// Default tool, doesn't do anything
        /// </summary>
        private void btnPointer_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Pointer";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();
        }

        /// <summary>
        /// Allows the user to select a portion of the drawing canvas
        /// </summary>
        private void btnSelect_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Rectangular Select";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_SelectClick;
            DrawingCanvas.MouseMove += Canvas_SelectMouseMove;
        }

        /// <summary>
        /// Allows user to draw with a paintbrush like tool
        /// </summary>
        private void btnBrush_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Brush";

            //Removes all current OnClick/OnMouseMove delegates from DrawingCanvas
            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            //Adds the delegates relevant to this tool to the DrawingCanvas
            DrawingCanvas.MouseLeftButtonDown += Canvas_BrushClick;
            DrawingCanvas.MouseMove += Canvas_BrushMouseMove;
        }

        /// <summary>
        /// Allows user to draw with a pencil like tool
        /// </summary>
        private void btnPencil_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Pencil";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_PencilClick;
            DrawingCanvas.MouseMove += Canvas_PencilMouseMove;
        }

        /// <summary>
        /// Allows user to draw squares
        /// </summary>
        private void btnSquare_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Square";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_RectClick;
            DrawingCanvas.MouseMove += Canvas_RectMouseMove;
        }

        /// <summary>
        /// Allows user to draw ellipses
        /// </summary>
        private void btnEllipse_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Ellipse";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_EllipseClick;
            DrawingCanvas.MouseMove += Canvas_EllipseMouseMove;
        }

        /// <summary>
        /// Allows user to draw text
        /// </summary>
        private void btnText_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Text";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_TextBlockClick;
        }

        /// <summary>
        /// Allows user to draw polygons
        /// </summary>
        private void btnPolygon_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Polygon";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_PolygonClick;
        }

        /// <summary>
        /// Allows user to draw bezier curves
        /// </summary>
        private void btnBezier_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Bezier";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_BezierClick;
            DrawingCanvas.MouseMove += Canvas_BezierMouseMove;
        }

        /// <summary>
        /// Allows user to draw lines
        /// </summary>
        private void btnLine_Click(object sender, RoutedEventArgs e)
        {
            //Updates status bar to show current tool being used
            lblCurrentTool.Text = "Line";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_LineClick;
            DrawingCanvas.MouseMove += Canvas_LineMouseMove;
        }

        /// <summary>
        /// Allows user to "erase" drawings
        /// </summary>
        private void btnEraser_Click(object sender, RoutedEventArgs e)
        {
            lblCurrentTool.Text = "Eraser";

            RemoveEventHandlersFromCanvas();
            RemoveUnwantedUIObjects();

            DrawingCanvas.MouseLeftButtonDown += Canvas_EraserClick;
            DrawingCanvas.MouseMove += Canvas_EraserMouseMove;
        }


        /// <summary>
        /// Removes all OnClick/OnMouseMove event handler delegates from the DrawingCanvas
        /// </summary>
        private void RemoveEventHandlersFromCanvas()
        {
            DrawingCanvas.MouseLeftButtonDown -= Canvas_SelectClick;
            DrawingCanvas.MouseMove -= Canvas_SelectMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_RectClick;
            DrawingCanvas.MouseMove -= Canvas_RectMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_EllipseClick;
            DrawingCanvas.MouseMove -= Canvas_EllipseMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_LineClick;
            DrawingCanvas.MouseMove -= Canvas_LineMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_BrushClick;
            DrawingCanvas.MouseMove -= Canvas_BrushMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_PencilClick;
            DrawingCanvas.MouseMove -= Canvas_PencilMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_BezierClick;
            DrawingCanvas.MouseMove -= Canvas_BezierMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_EraserClick;
            DrawingCanvas.MouseMove -= Canvas_EraserMouseMove;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_PolygonClick;

            DrawingCanvas.MouseLeftButtonDown -= Canvas_TextBlockClick;

            DrawingCanvas.MouseLeftButtonDown -= SelectEscape_Click;
        }

        /// <summary>
        /// Goes through all the special UIObject flags as well as 
        /// all the stored UIObjects and ensures that if the user cancels the drawing
        /// that the objects are reset to null and if needed, removed from the canvas.
        /// </summary>
        private void RemoveUnwantedUIObjects()
        {
            if (_pencil != null)
            {
                _pencil = null;
            }

            if (_brush != null)
            {
                _brush = null;
            }

            if (_rectangle != null)
            {
                DrawingCanvas.Children.Remove(_rectangle);
                _rectangle = null;
            }

            if (_ellipse != null)
            {
                DrawingCanvas.Children.Remove(_rectangle);
                _ellipse = null;
            }

            if (_line != null)
            {
                DrawingCanvas.Children.Remove(_line);
                _line = null;
            }

            if (_polygon != null)
            {
                DrawingCanvas.Children.Remove(_polygon);
                _polygon = null;
            }

            if (_text != null)
            {
                DrawingCanvas.Children.Remove(_text);
                _text = null;
            }

            if (_select != null)
            {
                DrawingCanvas.Children.Remove(_select);
                _select = null;
            }

            if (transformGroup != null)
            {
                transformGroup = null;
            }

            if (_selectImage != null)
            {
                _selectImage.MouseLeftButtonDown -= Select_Click;
                _selectImage.MouseMove -= Select_MouseMove;
                _selectImage.Source = _editedBitmap;
                _selectImage = null;
            }

            if (_editedBitmap != null)
            {
                _editedBitmap = null;
            }

            if (_selectBitmap != null)
            {
                _selectBitmap = null;
            }

            _isSelected = false;
            _isDragging = false;

            if (_bezier != null)
            {
                DrawingCanvas.Children.RemoveAt(DrawingCanvas.Children.Count);
                _bezier = null;
            }

            _bezierSegment = null;
            _bezierPointCounter = 0;
        }

        /// <summary>
        /// When the user presses escape, calls RemoveUnwantedUIObjects
        /// </summary>
        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                RemoveUnwantedUIObjects();
            }
        }
        #endregion

        /// <summary>
        /// Displays the text shown in the status bar
        /// </summary>
        /// <param name="e">MouseEventArgs used to retrieve mouse position</param>
        private void PrintStatusBar(MouseEventArgs e)
        {
            lblCursorPosition.Text = "X: " + Mouse.GetPosition(Application.Current.MainWindow).X + ", Y: " + Mouse.GetPosition(Application.Current.MainWindow).Y;
        }

        #region Select tool magic

        /// <summary>
        /// When the mouse is clicked, and the select box has not been set, dynamically draws the select box
        /// </summary>
        private void Canvas_SelectMouseMove(object sender, MouseEventArgs e)
        {
            //Updates the status bar
            PrintStatusBar(e);

            //if the mouse is released, adds events to the select box and then releases it from modification
            if (e.LeftButton == MouseButtonState.Released)
            {
                if (!_isSelected && _selectImage == null && _select != null)
                {
                    ConvertRectangleToBitMap();
                    _isSelected = true;
                }

                return;
            }

            //Gets the mouses current position
            Point point = e.GetPosition(DrawingCanvas);

            //Sets the end points
            double x = Math.Min(point.X, startPoint.X);
            double y = Math.Min(point.Y, startPoint.Y);

            //Sets the height and width
            _select.Width = Math.Max(point.X, startPoint.X) - x;
            _select.Height = Math.Max(point.Y, startPoint.Y) - y;

            //Updates the position based on position relative to the canvas
            Canvas.SetLeft(_select, x);
            Canvas.SetTop(_select, y);
        }

        /// <summary>
        /// When the mouse is clicked, creates a new rectangle object and adds it 
        /// to the drawing canvas
        /// </summary>
        private void Canvas_SelectClick(object sender, MouseButtonEventArgs e)
        {
            //Gets the current mouse position
            startPoint = e.GetPosition(DrawingCanvas);

            //Creates a new rectangle to be used for the select box
            _select = new Rectangle
            {
                Stroke = Brushes.Gray,
                StrokeThickness = 1,
                StrokeDashArray = {4, 3}
            };

            //Sets the position relative to the canvas
            Canvas.SetLeft(_select, startPoint.X);
            Canvas.SetTop(_select, startPoint.Y);

            //Adds the rectangle as a child to the drawing canvas
            DrawingCanvas.Children.Add(_select);
        }

        /// <summary>
        /// While the mouse is clicked on the selected image, moves the image to the mouses position
        /// </summary>
        private void Select_MouseMove(object sender, MouseEventArgs e)
        {
            //Updates the status bar
            PrintStatusBar(e);

            //if the mouse is released, doesnt do anything
            if (e.LeftButton == MouseButtonState.Released)
            {
                _isDragging = false;
                return;
            }
            
            //While the dragging flag is set, repositions the selected image on the screen
            if (_isDragging)
            {
                Point point = e.GetPosition(DrawingCanvas);

                Canvas.SetLeft(_selectImage, point.X - (_selectImage.ActualWidth / 2));
                Canvas.SetTop(_selectImage, point.Y - (_selectImage.ActualHeight / 2));
            }
        }

        /// <summary>
        /// Used to escape out of the selection tool
        /// </summary>
        private void SelectEscape_Click(object sender, MouseButtonEventArgs e)
        {
            if (!_isDragging && _isSelected)
            {
                _selectImage.MouseLeftButtonDown -= Select_Click;
                _selectImage.MouseMove -= Select_MouseMove;
                _selectImage.Source = _editedBitmap;
                _isSelected = false;
                _selectImage = null;
                _select = null;
            }
        }


        /// <summary>
        /// When the mouse is clicked, creates a new rectangle object and adds it 
        /// to the drawing canvas
        /// </summary>
        private void Select_Click(object sender, MouseButtonEventArgs e)
        {
            Point point = e.GetPosition(DrawingCanvas);

            double newX = point.X - (_selectImage.ActualWidth / 2);
            double newY = point.Y - (_selectImage.ActualHeight / 2);

            Canvas.SetLeft(_selectImage, newX);
            Canvas.SetTop(_selectImage, newY);
            _isDragging = true;
        }

        /// <summary>
        /// Creates two bitmaps from the selection rectangle, one with the border to be used while editing
        /// and the second without the border which will be set in place after editing of the selection is finished.
        /// Sets the background of the selection rectangle to white and sets it in place.
        /// </summary>
        private void ConvertRectangleToBitMap()
        {
            //Used to retrieve the native dpi for the bitmaps
            PresentationSource source = PresentationSource.FromVisual(this);

            //Creates a new bitmap from the canvas and renders it
            RenderTargetBitmap bmp = new RenderTargetBitmap((int)DrawingCanvas.ActualWidth, (int)DrawingCanvas.ActualHeight, 96 * source.CompositionTarget.TransformToDevice.M11, 96 * source.CompositionTarget.TransformToDevice.M22, PixelFormats.Default);
            bmp.Render(DrawingCanvas);

            //Crops the bitmap to contain only the select box
            _selectBitmap = new CroppedBitmap(bmp, new Int32Rect((int)Canvas.GetLeft(_select), (int)Canvas.GetTop(_select) + (int)DrawingCanvas.Margin.Top, (int)_select.ActualWidth, (int)_select.ActualHeight));

            //Creates a copy of the same bitmap, but without the border from the select box
            //will be used to set the image in place
            _editedBitmap = new CroppedBitmap(bmp, new Int32Rect((int)Canvas.GetLeft(_select) + 1, (int)Canvas.GetTop(_select) + (int)DrawingCanvas.Margin.Top + 1, (int)_select.ActualWidth - 2, (int)_select.ActualHeight - 2));
            
            //Sets the fill on the select box to be the bitmap
            _selectImage = new Image();
            _selectImage.Width = _select.ActualWidth;
            _selectImage.Height = _select.ActualHeight;
            _selectImage.Source = _selectBitmap;

            //Creates a new transform group and adds it to the image
            transformGroup = new TransformGroup();
            _selectImage.RenderTransformOrigin = new Point(0.5, 0.5);
            _selectImage.RenderTransform = transformGroup;

            Canvas.SetLeft(_selectImage, Canvas.GetLeft(_select));
            Canvas.SetTop(_selectImage, Canvas.GetTop(_select));

            DrawingCanvas.Children.Add(_selectImage);

            //Fills the selected rectangle with white and unsets it so that it cannot be moved
            _select.Fill = Brushes.White;
            _select.StrokeThickness = 0;
            _select = null;

            //Removes and adds the appropriate event handlers for the UI elements
            RemoveEventHandlersFromCanvas();
            _selectImage.MouseLeftButtonDown += Select_Click;
            _selectImage.MouseMove += Select_MouseMove;
            DrawingCanvas.MouseLeftButtonDown += SelectEscape_Click;
        }

        #endregion

        #region Rectangle logic
        /// <summary>
        /// When the mouse is clicked, dyanimcally draws the rectangles end point to be
        /// wherever the mouse currently is on the drawing canvas
        /// </summary>
        private void Canvas_RectMouseMove(object sender, MouseEventArgs e)
        {
            //Updates the status bar
            PrintStatusBar(e);

            //If the mouse is released, sets the reference to the rectangle to null so that it
            //is set on the canvas and exits the function. If the rectangle is null, exits the function
            if (e.LeftButton == MouseButtonState.Released || _rectangle == null)
            {
                _rectangle = null;
                return;
            }
                
            //Gets the mouses current position
            Point point = e.GetPosition(DrawingCanvas);

            //Sets the end points
            double x = Math.Min(point.X, startPoint.X);
            double y = Math.Min(point.Y, startPoint.Y);

            //Sets the height and width
            _rectangle.Width = Math.Max(point.X, startPoint.X) - x;
            _rectangle.Height = Math.Max(point.Y, startPoint.Y) - y;

            //Updates the position based on position relative to the canvas
            Canvas.SetLeft(_rectangle, x);
            Canvas.SetTop(_rectangle, y);
        }

        /// <summary>
        /// When the mouse is clicked, creates a new rectangle object and adds it 
        /// to the drawing canvas
        /// </summary>
        private void Canvas_RectClick(object sender, MouseButtonEventArgs e)
        {
            //Gets the current mouse position
            startPoint = e.GetPosition(DrawingCanvas);

            //If the fill object flag is true
            if (fillObject)
            {
                //Creates a new rectangle with the fill property set
                _rectangle = new Rectangle
                {
                    Stroke = colorBrush,
                    Fill = fillBrush,
                    StrokeThickness = borderSize
                };
            }
            //Otherwise creates a rectangle with no fill
            else
            {
                _rectangle = new Rectangle
                {
                    Stroke = colorBrush,
                    StrokeThickness = borderSize
                };
            }

            //Sets the position relative to the canvas
            Canvas.SetLeft(_rectangle, startPoint.X);
            Canvas.SetTop(_rectangle, startPoint.Y);

            //Adds the rectangle as a child to the drawing canvas
            DrawingCanvas.Children.Add(_rectangle);
        }
        #endregion```

        #region Ellipse logic
        /// <summary>
        /// When an ellipse has been created, dynamically draws the ellipse so that
        /// the endpoint is always where the mouse currently is on the canvas
        /// </summary>
        private void Canvas_EllipseMouseMove(object sender, MouseEventArgs e)
        {
            //Updates the status bar
            PrintStatusBar(e);

            //If the mouse button is released, sets the ellipse in place by removing the reference to it
            //jumps out of function
            if (e.LeftButton == MouseButtonState.Released || _ellipse == null)
            {
                _ellipse = null;
                return;
            }
            
            //Gets the current position
            Point point = e.GetPosition(DrawingCanvas);

            //Gets the ending points
            double x = Math.Min(point.X, startPoint.X);
            double y = Math.Min(point.Y, startPoint.Y);

            //Sets the height and width of the ellipse
            _ellipse.Width = Math.Max(point.X, startPoint.X) - x;
            _ellipse.Height= Math.Max(point.Y, startPoint.Y) - y;

            //Sets the position of the ellips based on its position relative to the canvas
            Canvas.SetLeft(_ellipse, x);
            Canvas.SetTop(_ellipse, y);
        }

        /// <summary>
        /// When the user clicks, creates a new ellipse and draws it to the canvas
        /// </summary>
        private void Canvas_EllipseClick(object sender, MouseButtonEventArgs e)
        {
            //Gets the point of the mouse click
            startPoint = e.GetPosition(DrawingCanvas);

            //If the fill object flag is set to true
            if (fillObject)
            {
                //Creates an ellipse with the fill property set
                _ellipse = new Ellipse
                {
                    Stroke = colorBrush,
                    Fill = fillBrush,
                    StrokeThickness = borderSize
                };
            }
            //Otherwise creates an ellipse with no fill
            else
            {
                _ellipse = new Ellipse
                {
                    Stroke = colorBrush,
                    StrokeThickness = borderSize
                };
            }

            //Sets the ellipse's position relative to the canvas position
            Canvas.SetLeft(_ellipse, startPoint.X);
            Canvas.SetTop(_ellipse, startPoint.Y);

            //Draws the ellipse to the canvas
            DrawingCanvas.Children.Add(_ellipse);
        }
        #endregion

        #region Line logic
        /// <summary>
        /// If a line object is available, dynamically draws it with the endpoints being
        /// wherever the mouse currently is on the canvas
        /// </summary>
        private void Canvas_LineMouseMove(object sender, MouseEventArgs e)
        {
            //Updates the status bar
            PrintStatusBar(e);

            //If the mouse button is released, sets the line object in  place
            //jumps out of function
            if (e.LeftButton == MouseButtonState.Released || _line == null)
            {
                _line = null;
                return;
            }

            //Gets the current location of the mouse
            Point point = e.GetPosition(DrawingCanvas);

            //Sets the ending points to be the mouse's current point
            _line.X2 = point.X;
            _line.Y2 = point.Y;
        }

        /// <summary>
        /// When the mouse is clicked, creates a new line object and adds it to the canvas
        /// </summary>
        private void Canvas_LineClick(object sender, MouseButtonEventArgs e)
        {
            //Gets the position of the mouse click
            startPoint = e.GetPosition(DrawingCanvas);

            //Creates a new line
            _line = new Line
            {
                Stroke = colorBrush,
                StrokeThickness = borderSize
            };

            //Sets all points to be point of the click
            _line.X1 = startPoint.X;
            _line.Y1 = startPoint.Y;

            _line.X2 = startPoint.X;
            _line.Y2 = startPoint.Y;

            //Adds the line to the canvas
            DrawingCanvas.Children.Add(_line);
        }
        #endregion

        #region Brush Logic (Includes Pencil)

        /// <summary>
        /// Draws a polyline that follows the mouse around the drawing canvas
        /// </summary>
        private void Canvas_BrushClick(object sender, MouseButtonEventArgs e)
        {
            //Gets the current mouse position
            startPoint = e.GetPosition(DrawingCanvas);

            //Creates the new polyline that will be drawn
            _brush = new Polyline()
            {
                Stroke = colorBrush,
                StrokeThickness = borderSize,
                StrokeStartLineCap = PenLineCap.Round,
                StrokeEndLineCap = PenLineCap.Round,
                StrokeLineJoin = PenLineJoin.Round
            };

            //Adds the initial point to the polyline (where the user clicked)
            _brush.Points.Add(startPoint);

            //Adds the polyline to the canvas
            DrawingCanvas.Children.Add(_brush);
        }

        /// <summary>
        /// Continues to add points to the brush polyline so long as the mouse is in the 
        /// drawing canvas and the left mouse button is held down
        /// </summary>
        private void Canvas_BrushMouseMove(object sender, MouseEventArgs e)
        {
            //prints current state to the status bar
            PrintStatusBar(e);

            //So long as the left mouse button is pressed
            if (e.LeftButton == MouseButtonState.Released || _brush == null)
            {
                _brush = null;
                return;
            }

            //Gets the current mouse position
            startPoint = e.GetPosition(DrawingCanvas);

            //If the position is valid, adds to the polyline
            if (CheckBrushPointPosition(startPoint.Y))
                _brush.Points.Add(startPoint);
        }

        /// <summary>
        /// Same as the brush tool, other than the strokethickness which is set to the constant 2
        /// </summary>
        private void Canvas_PencilClick(object sender, MouseButtonEventArgs e)
        {
            startPoint = e.GetPosition(DrawingCanvas);

            _pencil = new Polyline()
            {
                Stroke = colorBrush,
                StrokeThickness = 2,
                StrokeStartLineCap = PenLineCap.Flat,
                StrokeEndLineCap = PenLineCap.Triangle,
                StrokeLineJoin = PenLineJoin.Bevel
            };

            _pencil.Points.Add(startPoint);

            DrawingCanvas.Children.Add(_pencil);
        }

        /// <summary>
        /// Same functionality as the brush tool 
        /// </summary>
        private void Canvas_PencilMouseMove(object sender, MouseEventArgs e)
        {
            PrintStatusBar(e);

            if (e.LeftButton == MouseButtonState.Released || _pencil == null)
            {
                _pencil = null;
                return;
            }

            startPoint = e.GetPosition(DrawingCanvas);

            if (CheckBrushPointPosition(startPoint.Y))
                _pencil.Points.Add(startPoint);
        }

        /// <summary>
        /// Checks to ensure that all brush objects (brush, pencil, and eraser) don't draw
        /// outside the bounds of the canvas
        /// </summary>
        private bool CheckBrushPointPosition(double y)
        {
            bool draw = true;

            if (toolBox.IsVisible)
            {
                if (y < DrawingCanvas.Margin.Top - toolBox.Margin.Top - toolBox.Height + (borderSize / 2))
                    draw = false;
            }
            else
            {
                if (y < DrawingCanvas.Margin.Top - toolBox.Margin.Top + (borderSize / 2))
                    draw = false;
            }

            return draw;
        }
        #endregion

        #region Bezier Curve Logic
        /// <summary>
        /// Begins the logic for drawing a bezier curve
        /// </summary>
        private void Canvas_BezierClick(object sender, MouseButtonEventArgs e)
        {
            //The starting position that will be used for all points on the curve
            startPoint = e.GetPosition(DrawingCanvas);

            //So long as the bezier path has not been started yet
            if (_bezier == null)
            {
                //Creates a new path to store the bezier curve
                _bezier = new PathFigure();
                _bezier.StartPoint = startPoint;

                //Creates a new BezierSegment object to store the points that will create the path
                _bezierSegment = new BezierSegment();

                //Initializes the points to a default value (where the mouse is clicked)
                _bezierSegment.Point1 = startPoint;
                _bezierSegment.Point2 = startPoint;
                _bezierSegment.Point3 = startPoint;

                //Creates a new path segment collection, adds the bezier segment to it
                PathSegmentCollection myPathSegmentCollection = new PathSegmentCollection();
                myPathSegmentCollection.Add(_bezierSegment);

                //Adds the path segment collection to the path that stores the bezier curve
                _bezier.Segments = myPathSegmentCollection;

                //Creates a new path figure collection and adds the bezier path to it
                PathFigureCollection pthFigureCollection = new PathFigureCollection();
                pthFigureCollection.Add(_bezier);

                //Creates a new path geometry object, adds the figure collection to it
                PathGeometry pthGeometry = new PathGeometry();
                pthGeometry.Figures = pthFigureCollection;

                //Finally, creates a path based on the path geometry object
                System.Windows.Shapes.Path arcPath = new System.Windows.Shapes.Path();
                arcPath.Stroke = colorBrush;
                arcPath.StrokeThickness = borderSize;
                arcPath.Data = pthGeometry;

                if (fillObject)
                    arcPath.Fill = fillBrush;

                //Adds the path to the drawing canvas
                DrawingCanvas.Children.Add(arcPath);
            }

            //If this is the second click on the curve, sets the second point
            else if (_bezierPointCounter < 3)
            {
                if (_bezierPointCounter == 0)
                {
                    _bezierSegment.Point1 = e.GetPosition(DrawingCanvas);
                    _bezierPointCounter++;
                }
                else if (_bezierPointCounter == 1)
                {
                    _bezierSegment.Point2 = e.GetPosition(DrawingCanvas);
                    _bezierPointCounter++;
                }
                else if (_bezierPointCounter == 2)
                {
                    _bezierSegment.Point3 = e.GetPosition(DrawingCanvas);
                    _bezierPointCounter = 0;
                    _bezier = null;
                    _bezierSegment = null;
                }
                    
            }
        }

        /// <summary>
        /// Sets the second and third points for the bezier curve
        /// </summary>
        private void Canvas_BezierMouseMove(object sender, MouseEventArgs e)
        {
            //Prints the appropriate text to the status bar
            PrintStatusBar(e);

            //If the bezier object is null, then we don't care about this event
            if (_bezier == null)
            {
                return;
            }

            //Dynamically draws the bezier curve
            if (_bezierPointCounter == 0)
            {
                _bezierSegment.Point1 = e.GetPosition(DrawingCanvas);
            }
            if (_bezierPointCounter == 1)
            {
                _bezierSegment.Point2 = e.GetPosition(DrawingCanvas);
            }
            else
            {
                _bezierSegment.Point3 = e.GetPosition(DrawingCanvas);
            }
        }
        #endregion

        #region Polygon Logic
        /// <summary>
        /// Draws a Polygon
        /// </summary>
        private void Canvas_PolygonClick(object sender, MouseButtonEventArgs e)
        {
            //Gets current position
            startPoint = e.GetPosition(DrawingCanvas);

            //If the polygon has not been created, creates a new polygon
            if (_polygon == null)
            {
                _polygon = new Polygon()
                {
                    Stroke = colorBrush,
                    StrokeThickness = borderSize
                };

                //If the fill flag is true, sets the fill
                if (fillObject)
                    _polygon.Fill = fillBrush;

                //Adds the current point to the polygon
                _currentPoint = startPoint;
                _polygon.Points.Add(_currentPoint);

                //Draws the polygon on the canvas
                DrawingCanvas.Children.Add(_polygon);
            }
            //If the polygon has already been created
            else
            {
                //If the user double clicks, finallizes the polygon
                if (startPoint == _currentPoint)
                    _polygon = null;
                //Regular clicks will add more points to the polygon
                else
                {
                    _currentPoint = startPoint;
                    _polygon.Points.Add(_currentPoint);
                }
            }
        }
        #endregion

        #region Text Block Logic
        /// <summary>
        /// Unhides the input box that will get a string from the user
        /// Creates a new text block and adds it to the canvas
        /// </summary>
        private void Canvas_TextBlockClick(object sender, MouseButtonEventArgs e)
        {
            //Shows the input box
            InputBox.Visibility = System.Windows.Visibility.Visible;

            //Gets mouse's current position
            _textInputPoint = e.GetPosition(DrawingCanvas);

            //Creates the new text block
            _text = new TextBlock()
            {
                FontSize = textSize,
                FontFamily = new FontFamily(TextFontChooser.Text),
                Foreground = textColor
            };

            if (bold)
                _text.FontWeight = FontWeights.Bold;

            if (italic)
                _text.FontStyle = FontStyles.Italic;

            if (underline)
                _text.TextDecorations = TextDecorations.Underline;

            //Sets the text blocks position based on the input point
            Canvas.SetLeft(_text, _textInputPoint.X);
            Canvas.SetTop(_text, _textInputPoint.Y);

            //Adds text block to the drawing canvas
            DrawingCanvas.Children.Add(_text);
        }

        /// <summary>
        /// When user hits submit, adds the provided text to the already created text block
        /// Re-hides the input box
        /// </summary>
        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            //Re-hides the text block
            InputBox.Visibility = System.Windows.Visibility.Collapsed;

            //Adds the given text to the text block
            _text.Text = InputTextBox.Text;

            //Clear InputBox, resets _text
            InputTextBox.Text = String.Empty;
            _text = null;
        }

        /// <summary>
        /// When user hits cancel, hides the input box and resets _text
        /// </summary>
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            //Re-hides the input box
            InputBox.Visibility = System.Windows.Visibility.Collapsed;

            //Clears the input text box
            InputTextBox.Text = String.Empty;
            _text = null;
        }
        #endregion

        #region Eraser Logic
        /// <summary>
        /// Mimicks an eraser. Basically it draws over all the children of the canvas with a white
        /// brush stroke
        /// </summary>
        private void Canvas_EraserClick(object sender, MouseButtonEventArgs e)
        {
            startPoint = e.GetPosition(DrawingCanvas);

            //Creates a new polyline, sets its color to white, all other settings are just like the brush tool
            _brush = new Polyline()
            {
                Stroke = Brushes.White,
                StrokeThickness = borderSize,
                StrokeStartLineCap = PenLineCap.Round,
                StrokeEndLineCap = PenLineCap.Round,
                StrokeLineJoin = PenLineJoin.Round
            };

            //Adds the initial point of the 
            _brush.Points.Add(startPoint);

            //adds the brush to the drawing canvas
            DrawingCanvas.Children.Add(_brush);
        }

        /// <summary>
        /// While the house button has not been released, adds wherever the mouse has been to the
        /// list of points stored in _brush
        /// </summary>
        private void Canvas_EraserMouseMove(object sender, MouseEventArgs e)
        {
            PrintStatusBar(e);

            //If the mouse button has been released, or if the brush hasn't been initialized yet,
            //we don't want to take any action
            if (e.LeftButton == MouseButtonState.Released || _brush == null)
            {
                _brush = null;
                return;
            }

            //If the mouse button is held down, gets the current point of the mouse and add it to the
            //points stored in the brush
            startPoint = e.GetPosition(DrawingCanvas);

            if (CheckBrushPointPosition(startPoint.Y))
                _brush.Points.Add(startPoint);
        }
        #endregion

        #region File Menu Controls
        //This region holds the events used in the File menu

        /// <summary>
        /// Calls the function to clear the canvas after prompting the user if they want to save
        /// </summary>
        private void mnuNew_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Save before creating new picture?", "Save File", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.No)
            {
                ClearCanvas();
            }
            else
            {
                mnuSave_Click(sender, e);
            }
            
        }
        /// <summary>
        /// Closes the window after prompting the user if they want to save
        /// </summary>
        private void mnuExit_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Save before creating new picture?", "Save File", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.No)
            {
                this.Close();
            }
            else
            {
                mnuSave_Click(sender, e);
            }
        }
        /// <summary>
        /// Saves the file
        /// </summary>
        private void mnuSave_Click(object sender, RoutedEventArgs e)
        {
            //Sets up the save file dialog box
            System.Windows.Forms.SaveFileDialog dialog = new System.Windows.Forms.SaveFileDialog();
            dialog.InitialDirectory = "C:\\";
            dialog.AddExtension = true;
            dialog.DefaultExt = ".png";
            dialog.Filter = "PNG Image (.png)|*.png";

            //displays the dialog box
            System.Windows.Forms.DialogResult result = dialog.ShowDialog();
            //If the user selects okay
            if (result.ToString() == "OK")
            {
                //stores their specified filename to fileName
                string fileName = dialog.FileName;

                //Used to retrieve the native dpi for the bitmaps
                PresentationSource source = PresentationSource.FromVisual(this);

                //Copies the entire DrawingCanvas to a bitmap object
                RenderTargetBitmap bmp = new RenderTargetBitmap((int)DrawingCanvas.ActualWidth, (int)DrawingCanvas.ActualHeight + (int)DrawingCanvas.Margin.Top, 96 * source.CompositionTarget.TransformToDevice.M11, 96 * source.CompositionTarget.TransformToDevice.M22, PixelFormats.Default);
                bmp.Render(DrawingCanvas);

                //Creates a new png encoder, and adds the DrawingCanvas bitmap to it
                PngBitmapEncoder png = new PngBitmapEncoder();
                png.Frames.Add(BitmapFrame.Create(bmp));

                //Saves the data from the png encoder to the destination file
                using (Stream stm = File.Create(fileName))
                {
                    png.Save(stm);
                }
            }
            //If the user presses Cancel, does not save         
        }
        #endregion

        #region Tool Size Picker
        //This region has the events which pick the border size or thickness of the drawing tools

        /// <summary>
        /// Sets the size to 2px
        /// </summary>
        private void size2Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size2Ellipse.ToolTip.ToString());
        }
        /// <summary>
        /// Sets the size to 5px
        /// </summary>
        private void size5Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size5Ellipse.ToolTip.ToString());
        }
        /// <summary>
        /// Sets the size to 7px
        /// </summary>
        private void size7Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size7Ellipse.ToolTip.ToString());
        }
        /// <summary>
        /// Sets the size to 10px
        /// </summary>
        private void size10Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size10Ellipse.ToolTip.ToString());
        }
        /// <summary>
        /// Sets the size to 15px
        /// </summary>
        private void size15Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size15Ellipse.ToolTip.ToString());
        }
        /// <summary>
        /// Sets the size to 20px
        /// </summary>
        private void size20Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            borderSize = Convert.ToInt32(size20Ellipse.ToolTip.ToString());
        }
        #endregion

        #region Text Options
        //Contains controls that change the properties of the text that will be added to the drawing canvas

        /// <summary>
        /// Selects the text size based on the TextSizeChooser combo box
        /// </summary>
        private void TextSizeChooser_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //Converts the selected item to a combo box item
            ComboBoxItem typeItem = (ComboBoxItem)TextSizeChooser.SelectedItem;
            string temp = typeItem.Content.ToString();

            //So long as the combo box item text is not empty
            if (temp != "")
            {
                //Converts that text to an int value and stores it in textSize
                temp = temp.Substring(0, 2);
                textSize = Convert.ToInt32(temp);
            }
        }

        /// <summary>
        /// Sets the bold flag to true or false, sets the highlighting on the button
        /// </summary>
        private void btnBold_Click(object sender, RoutedEventArgs e)
        {
            if (bold)
            {
                bold = false;
                btnBold.Background = Brushes.Transparent;
            }
            else
            {
                bold = true;
                btnBold.Background = Brushes.Gainsboro;
            }
        }

        /// <summary>
        /// Sets the italic flag to true or false, sets the highlighting on the button
        /// </summary>
        private void btnItalic_Click(object sender, RoutedEventArgs e)
        {
            if (italic)
            {
                italic = false;
                btnItalic.Background = Brushes.Transparent;
            }
            else
            {
                italic = true;
                btnItalic.Background = Brushes.Gainsboro;

            }
        }

        /// <summary>
        /// Sets the underline flag to true or false, sets the highlighting on the button
        /// </summary>
        private void btnUnderline_Click(object sender, RoutedEventArgs e)
        {
            if (underline)
            {
                underline = false;
                btnUnderline.Background = Brushes.Transparent;
            }
            else
            {
                underline = true;
                btnUnderline.Background = Brushes.Gainsboro;
            }
        }
        #endregion

        #region Color Picker
        /// <summary>
        /// Retrieves the color from the ColorRectangle at the point where the mouse is in the rectangle
        /// </summary>
        /// <returns>Returns the color in an Argb format</returns>
        private Color GetColorFromColorRectangle()
        {
            PresentationSource source = PresentationSource.FromVisual(this);

            //Gets the mouses current position relative to the color rectangle
            Point point = Mouse.GetPosition(ColorRectangle);

            //Creates a bitmap of the color rectangle and renders it
            RenderTargetBitmap bmp = new RenderTargetBitmap((int)ColorRectangle.Width, (int)ColorRectangle.Height, 96 * source.CompositionTarget.TransformToDevice.M11, 96 * source.CompositionTarget.TransformToDevice.M22, PixelFormats.Default);
            bmp.Render(ColorRectangle);

            //If the mouse position is within the color rectangle
            if ((point.X < bmp.PixelWidth) && (point.Y < bmp.PixelHeight))
            {
                //Create a cropped bitmap with the dimensions of height, width = 1, at the mouses position
                CroppedBitmap croppedBitmap = new CroppedBitmap(bmp, new Int32Rect((int)point.X, (int)point.Y, 1, 1));

                //Copies the pixel stored in the cropped bitmap to a byte array
                byte[] pixels = new byte[4];
                croppedBitmap.CopyPixels(pixels, 4, 0);

                //Returns the color generated from the byte array to the calling function
                return Color.FromArgb(255, pixels[2], pixels[1], pixels[0]);
            }
            //IF the mouse is out of bounds of the ColorRectangle, returns a default color
            else
                return Color.FromArgb(0, 0, 0, 0);
        }

        /// <summary>
        /// When the user clicks inside the ColorRectangle, sets whatever option is selected
        /// to be that of the color wherever the mouse was clicked
        /// </summary>
        private void ColorChooser_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            //If the BorderColor option was selected
            if (setBorderColor)
            {
                colorBrush = new SolidColorBrush(GetColorFromColorRectangle());
                setBorderColor = false;
                btnToolColor.Background = Brushes.Transparent;
                ColorRectangle.Visibility = Visibility.Collapsed;
            } 
            //If the FillColor option was selected
            else if (setToolColor && fillCheckBox.IsChecked.Value)
            {
                fillBrush = new SolidColorBrush(GetColorFromColorRectangle());
                setToolColor = false;
                fillObject = true;
                btnFillColor.Background = Brushes.Transparent;
                ColorRectangle.Visibility = Visibility.Collapsed;
            }
            //If the TextColor option was selected
            else if (setTextColor)
            {
                textColor = new SolidColorBrush(GetColorFromColorRectangle());
                setTextColor = false;
                btnTextColor.Background = Brushes.Transparent;
                ColorRectangle.Visibility = Visibility.Collapsed;
            }
        }

        /// <summary>
        /// When the mouse is moved in the color rectangle, sets the color of whatever control is
        /// selected to be that of the ColorRectangle where the mouse is 
        /// </summary>
        private void ColorRectangle_MouseMove(object sender, MouseEventArgs e)
        {
            if (setBorderColor)
                ToolColor.Stroke = new SolidColorBrush(GetColorFromColorRectangle());
            else if (setToolColor)
                FillColor.Fill = new SolidColorBrush(GetColorFromColorRectangle());
            else if (setTextColor)
                TextColor.Foreground = new SolidColorBrush(GetColorFromColorRectangle());
        }
        
        /// <summary>
        /// When the TextColor button is clicked, sets the setTextColor flag to true
        /// Shows the ColorRectangle
        /// </summary>
        private void btnTextColor_Click(object sender, RoutedEventArgs e)
        {
            setTextColor = true;
            btnTextColor.Background = Brushes.Gainsboro;

            ColorRectangle.Visibility = Visibility.Visible;
            ColorRectangle.Focus();
        }

        /// <summary>
        /// When the FillColor button is clicked, sets the setToolColor flag to true
        /// Shows the ColorRectangle
        /// </summary>
        private void btnFillColor_LeftClick(object sender, RoutedEventArgs e)
        {
            if (fillCheckBox.IsChecked.Value)
            {
                setToolColor = true;
                btnFillColor.Background = Brushes.Gainsboro;

                ColorRectangle.Visibility = Visibility.Visible;
                ColorRectangle.Focus();
            }
        }

        /// <summary>
        /// When the ToolColor button is clicked, sets the setBorderColor flag to true
        /// Shows the ColorRectangle
        /// </summary>
        private void btnToolColor_Click(object sender, RoutedEventArgs e)
        {
            setBorderColor = true;
            btnToolColor.Background = Brushes.Gainsboro;

            ColorRectangle.Visibility = Visibility.Visible;
            ColorRectangle.Focus();
        }

        /// <summary>
        /// If checkbox for the fill color is selected, sets the fill flag to true and
        /// calls the fill color button click event
        /// If checkbox is unselected, sets the fill flag to false
        /// </summary>
        private void fillCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            if (fillCheckBox.IsChecked.Value)
            {
                fillObject = true;
                btnFillColor_LeftClick(sender, e);
                fillCheckBox.Background = Brushes.Gainsboro;
            }
            else
            {
                fillObject = false;
                fillCheckBox.Background = Brushes.Transparent;
            }  
        }
        #endregion

        #region Image manipulation logic
        /// <summary>
        /// Flips the selected image vertically
        /// </summary>
        private void mnuFlipV_Click(object sender, RoutedEventArgs e)
        {
            if (_isSelected)
            {
                ScaleTransform transform = new ScaleTransform();
                transform.ScaleY = -1;

                transformGroup.Children.Add(transform);
            }
        }

        /// <summary>
        /// Flips the selected image horizontally
        /// </summary>
        private void mnuFlipH_Click(object sender, RoutedEventArgs e)
        {
            if (_isSelected)
            {
                ScaleTransform transform = new ScaleTransform();
                transform.ScaleX = -1;

                transformGroup.Children.Add(transform);
            }
        }

        /// <summary>
        /// Rotates the selected image by 90 degrees
        /// </summary>
        private void mnuRotate90_Click(object sender, RoutedEventArgs e)
        {
            if (_selectImage != null)
            {
                RotateTransform transform = new RotateTransform(90);

                transformGroup.Children.Add(transform);
            }
        }

        /// <summary>
        /// Stretches the selected image by a factor of 5 in all directions
        /// </summary>
        private void mnuStretch_Click(object sender, RoutedEventArgs e)
        {
            if (_isSelected)
            {
                ScaleTransform transform = new ScaleTransform();
                transform.ScaleX = 5;
                transform.ScaleY = 5;

                transformGroup.Children.Add(transform);
            }
        }

        /// <summary>
        /// Skews the image by 45, 0, -50, 50 
        /// </summary>
        private void mnuSkew_Click(object sender, RoutedEventArgs e)
        {
            if (_isSelected)
            {
                SkewTransform transform = new SkewTransform(45, 0, -50, 50);

                transformGroup.Children.Add(transform);
            }
        }
        #endregion

        //If user clicks the red exit button, makes sure to prompt them in case they want to save their picture
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (MessageBox.Show("Save before creating new picture?", "Save File", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.Yes)
            {
                mnuSave_Click(sender, new RoutedEventArgs());
            }
        }
    }
}
