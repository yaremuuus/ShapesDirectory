
#ifndef SHAPES_H
#define SHAPES_H



#include "Head.h"
using namespace std;


static int id = 0;

static int countR = 0;
static int countT = 0;
static int countE = 0;


class ShapeItem : public QGraphicsItem {
public:
    ShapeItem() : isActive(false), color(Qt::gray) , pos_(0, 0){ setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);}
    void setActive(bool active) {
        isActive = active;
        if (isActive) {
            setZValue(getMaxZValue() + 1); // Устанавливаем максимальное значение Z + 1
        }
        update(); // Перерисовать элемент
    }
    void setPos(const QPointF& newPos){
        if (newPos != pos_) {
            prepareGeometryChange();
            pos_ = newPos;
            QGraphicsItem::setPos(newPos);
        }
    }
    QPointF getCenter() const {
        return QPointF(boundingRect().center().x() + pos().x(), boundingRect().center().y() + pos().y());
    }
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) {
        return QGraphicsItem::itemChange(change, value);
    }
    virtual QRectF boundingRect() const override = 0;
    virtual QPainterPath shape() const override = 0;
    virtual int getId() = 0;
    virtual int getType() = 0;
    virtual  int getCount(bool f) = 0;

    bool isActive; // Флаг активности
    //signals:
    //void centerChanged();
    QPointF pos_;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {}

private:
    QColor color; // Цвет заливки


    int getMaxZValue() const {
        // Получаем максимальное значение Z среди всех фигур
        int maxZ = 0;
        for (auto item : scene()->items()) {
            if (auto shape = dynamic_cast<ShapeItem*>(item)) {
                maxZ = max(maxZ, static_cast<int>(shape->zValue()));
            }
        }
        return maxZ;
    }
};

class RectangleItem : public ShapeItem {
public:
    int idR;
    int getId() override{ return idR;}
    int getType() override{ return 1;}
    int getCount(bool f) override{if(f)return  --countR;return countR ;}
    RectangleItem(qreal x, qreal y) : ShapeItem() {
        setPos(QPoint(x,y));
        setZValue(0);
        idR = ++id;
        ++countR;
    }

    QRectF boundingRect() const override {
        return QRectF(-50, -25, 100, 50);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        ShapeItem::paint(painter, option, widget);
        painter->setBrush(Qt::red);
        painter->drawRect(boundingRect());

    }

    QPainterPath shape() const override {
        QPainterPath path;
        path.addRect(boundingRect()); // Определяем форму как прямоугольник
        return path;
    }
};

class EllipseItem : public ShapeItem {
public:
    int idE;
    int getId() override{return idE;}
    int getType() override{ return 3;}
    int getCount(bool f) override{if(f)return --countE;return  countE;}
    EllipseItem(qreal x, qreal y) : ShapeItem() {
        setPos(QPoint(x,y));
        setZValue(0);
        idE= ++id;
        ++countE;
    }

    QRectF boundingRect() const override {
        return QRectF(-50, -25, 100, 50);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        ShapeItem::paint(painter, option, widget);
        painter->setBrush(Qt::blue);
        painter->drawEllipse(boundingRect());

    }

    QPainterPath shape() const override {
        QPainterPath path;
        path.addEllipse(boundingRect()); // Определяем форму как эллипс
        return path;
    }

};

class TriangleItem : public ShapeItem {
public:
    int idT;
    int getId() override{return idT;}
    int getType() override{ return 2;}
    int getCount(bool f) override{if(f)return  --countT;return countE;}
    TriangleItem(QPointF p1, QPointF p2, QPointF p3) : ShapeItem() {
        setZValue(0);
        polygon << p1 << p2 << p3; // Устанавливаем вершины треугольника
        setPos((p1 + p2 + p3) / 3); // Устанавливаем позицию по центру треугольника
        idT = ++id;
        ++countT;
    }

    QRectF boundingRect() const override {
        return QRectF(-50, -50, 100, 100);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        ShapeItem::paint(painter, option, widget);
        QPolygonF triangle;

        triangle << QPointF(0, -50) << QPointF(50, 50) << QPointF(-50, 50);
        painter->setBrush(Qt::green);
        painter->drawPolygon(triangle);
    }

    QPainterPath shape() const override {
        QPainterPath path;
        QPolygonF triangle;
        triangle << QPointF(0, -50) << QPointF(50, 50) << QPointF(-50, 50);
        path.addPolygon(triangle); // Определяем форму как треугольник
        return path;
    }
private:
    QPolygonF polygon;
};

// Helper function to draw a shape in a delegate

class CustomTableCell : public QWidget {
    Q_OBJECT
public:
    int shapeType;
    int shapeCount;
    CustomTableCell(int type, int count, QWidget* parent = nullptr)
        : QWidget(parent), shapeType(type), shapeCount(count) {}

    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter.setPen(pen);
        int width = this->width();
        int height = this->height();
        int shapeWidth = width / 3; // Определяем размер фигур
        int shapeSize = 25 ; // Adjust size as needed
        for (int i = 0; i < shapeCount; ++i) {
            int x = (i % 3) * shapeWidth;
            int y = 10;

            if (shapeType == 1) { // Прямоугольник
                painter.setBrush(Qt::red);
                painter.drawRect(x, y, shapeSize, shapeSize);
            } else if (shapeType == 3) { // Эллипс
                painter.setBrush(Qt::blue);
                painter.drawEllipse(x, y, shapeWidth/1.2, shapeWidth/2);
            } else if (shapeType == 2) { // Треугольник
                painter.setBrush(Qt::green);
                QPolygon triangle;
                triangle << QPoint(x + (shapeWidth-5) / 2, y)
                         << QPoint(x, y + shapeWidth/2)
                         << QPoint(x + shapeWidth-5, y + shapeWidth/2);
                painter.drawPolygon(triangle);
            }
        }
    }

    void setShapeCount(int count) {
        shapeCount = count;
        update(); // Обновляем виджет после изменения количества фигур
    }
};

#endif //SHAPES_H
