# **ShapeSimulator – Interactive Geometric Shapes Simulator**  

A Qt/C++ application for visualizing and managing geometric shapes with connection capabilities, counting, and tabular display.  

## **Key Features**  

### **1. Shape Management**  
- **Add shapes** of different types:  
  - Rectangles (red)  
  - Triangles (green)  
  - Ellipses (blue)  
- **Delete selected shapes**  
- **Set active shape** (Z-order adjustment)  
- **Connect shapes with lines** (visualizing relationships)  
- **Hide/show shapes** by type  

### **2. Visualization & Statistics**  
- **Graphics scene** (QGraphicsScene) for shape rendering  
- **Table with shape counts** (QTableWidget)  
  - Displays the number of each shape type  
  - Renders shapes directly in table cells  
- **Drag-and-drop support** for moving shapes  

### **3. Shape Connections**  
- Select two shapes to connect with a line  
- Remove existing connections  
- Automatic line updates when shapes are moved  

## **Implemented Algorithms**  
- Z-order management for proper rendering  
- Custom shape rendering in table cells  
- Shape connection mechanism with line visualization  
- Real-time shape counting and statistics updates  

## **Interface (MainWindow Class)**  
### **UI Controls**  
- **Graphics scene** (QGraphicsView + QGraphicsScene)  
- **Statistics table** (QTableWidget)  
- **Control buttons**:  
  - `addRectangle()` – Add a rectangle  
  - `addEllipse()` – Add an ellipse  
  - `addTriangle()` – Add a triangle  
  - `removeSelectedShape()` – Delete selected shape  
  - `connectShapes()` – Connect two selected shapes  
  - `removeConnectVoid()` – Remove a connection  
  - `hideShapesVoid()` / `showShapesVoid()` – Hide/show shapes  

### **Logic**  
- Unique ID system for each shape  
- Multi-selection support  
- Automatic table updates on changes  
- Connection system with visual lines  

## **Shape Classes**  
1. **ShapeItem** (base class)  
   - Abstract class with common logic  
   - Supports moving and selection  
   - Virtual methods for type identification and counting  

2. **RectangleItem**  
   - Red rectangles  
   - Implements `boundingRect()` and `paint()`  

3. **EllipseItem**  
   - Blue ellipses  
   - Custom rendering  

4. **TriangleItem**  
   - Green triangles  
   - Custom shape and rendering  

5. **CustomTableCell**  
   - Custom widget for displaying shapes in table cells  
   - Supports different shape types and counts  

## **Dependencies**  
- Qt 5.x/6.x (Widgets, Core, GraphicsView)  
- C++17 (STL)  

## **Build & Run**  
```bash
git clone <repository>  
cd ShapeSimulator  
cmake -B build && cmake --build build  
./build/ShapeSimulator  
```

The project demonstrates:  
- Working with **QGraphicsView/QGraphicsScene**  
- **Custom painting** of graphical elements  
- **Complex interactions** between visual objects  
- **Dynamic UI updates** based on user actions

## **How it looks:**
