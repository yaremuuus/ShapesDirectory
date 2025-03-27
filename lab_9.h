

#ifndef LAB_9_H
#define LAB_9_H



using namespace std;
#include "Head.h"
#include "Shapes.h"

void addShapesToTableCell(QTableWidget* tableWidget, int rowIndex, int columnIndex, int shapeType, int count);

static int id_1;
static int id_2;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow() ;
    set<pair<int, int>> connectedPairs;
    std::map<std::pair<int, int>, QGraphicsLineItem*> connectedLines;
private slots:
    void addRectangle() ;           //добавить Rect
    void addEllipse() ;             //добавть элипс
    void addTriangle() ;            //добавть треуг
    void removeSelectedShape() ;    //удалить фигуру
    void updateActiveShape() ;      //обновить актуальную фигуру
    void hideShapesVoid();
    void showShapesVoid();
    void choose1Shape();
    void choose2Shape();
    void connectShapes();
    void removeConnectVoid();
    void vUpdate();




private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QComboBox* hideShape;
    int id = 1;
    int active_id;

    QTableWidget* tableWidget;
};
#endif //LAB_9_H
