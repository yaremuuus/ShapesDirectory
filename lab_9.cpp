
#include "lab_9.h"


MainWindow::MainWindow() {
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::vUpdate);
    timer->start(10);
    QPushButton *addRectangleButton = new QPushButton("Добавить Прямоугольник",this);
    QPushButton *addEllipseButton = new QPushButton("Добавить Эллипс",this);
    QPushButton *addTriangleButton = new QPushButton("Добавить треугольник",this);
    QPushButton *removeShapeButton = new QPushButton("Удалить фигуру",this);
    QPushButton *choose1 = new QPushButton("Выбрать 1 фигуру",this);
    QPushButton *choose2 = new QPushButton("Выбрать 2 фигуру",this);
    hideShape = new QComboBox(this);
    hideShape->addItems({"Все прямоугольники", "Все треугольники", "Все эллипсы"});
    QPushButton *hideShapeButton = new QPushButton("Фильтровать",this);
    QPushButton *showShapeButton = new QPushButton("Показать все",this);

    QPushButton *linkShapes = new QPushButton("Соединить фигуры",this);
    QPushButton *nolinkShapes = new QPushButton("Разъединить фигуры",this);
QPushButton* updateButton = new QPushButton("ОБновить соединения",this);

    connect(addRectangleButton, &QPushButton::clicked, this, &MainWindow::addRectangle);
    connect(addEllipseButton, &QPushButton::clicked, this, &MainWindow::addEllipse);
    connect(addTriangleButton, &QPushButton::clicked, this, &MainWindow::addTriangle);
    connect(removeShapeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedShape);
    connect(hideShapeButton,&QPushButton::clicked,this,&MainWindow::hideShapesVoid);
    connect(showShapeButton,&QPushButton::clicked,this,&MainWindow::showShapesVoid);
    connect(choose1,&QPushButton::clicked,this,&MainWindow::choose1Shape);
    connect(choose2,&QPushButton::clicked,this,&MainWindow::choose2Shape);
    connect(linkShapes,&QPushButton::clicked,this,&MainWindow::connectShapes);
    connect(nolinkShapes,&QPushButton::clicked,this,&MainWindow::removeConnectVoid);
    connect(updateButton,&QPushButton::clicked,this,&MainWindow::vUpdate);


    connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::updateActiveShape);

    tableWidget = new QTableWidget(0, 4); // Изначально 0 строк
    QStringList headers;
    headers << "id"  << "Тип фигуры"<<"связаны"<< "количество";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setColumnWidth(0,1);

    QHBoxLayout *addButtonlayout = new QHBoxLayout;
    addButtonlayout->addWidget(addRectangleButton);
    addButtonlayout->addWidget(addTriangleButton);
    addButtonlayout->addWidget(addEllipseButton);

    QWidget *addbuttonsWidget = new QWidget(this);
    addbuttonsWidget->setLayout(addButtonlayout);

    QHBoxLayout *chooseButtonlayout = new QHBoxLayout;
    chooseButtonlayout->addWidget(choose1);
    chooseButtonlayout->addWidget(choose2);
    QWidget *choosebuttonsWidget = new QWidget(this);
    choosebuttonsWidget->setLayout(chooseButtonlayout);

    QVBoxLayout *Buttonlayout = new QVBoxLayout;
    Buttonlayout->addWidget(addbuttonsWidget);
    Buttonlayout->addWidget(removeShapeButton);
    Buttonlayout->addWidget(hideShape);
    Buttonlayout->addWidget(hideShapeButton);
    Buttonlayout->addWidget(showShapeButton);
    Buttonlayout->addWidget(choosebuttonsWidget);
    Buttonlayout->addWidget(linkShapes);
    Buttonlayout->addWidget(nolinkShapes);
    Buttonlayout->addWidget(updateButton);
    Buttonlayout->addWidget(tableWidget);

    QWidget *buttonsWidget = new QWidget(this);
    buttonsWidget->setLayout(Buttonlayout);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(buttonsWidget);
    mainLayout->addWidget(view);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    scene->setSceneRect(-300,-300,600,600); // Установка границ сцены
}

void MainWindow::addRectangle() {

    // Генерация случайных координат
    int x = QRandomGenerator::global()->bounded(-250, 250); // Ограничиваем по X
    int y = QRandomGenerator::global()->bounded(-250, 250); // Ограничиваем по Y
    RectangleItem* rectItem = new RectangleItem(x, y);
    scene->addItem(rectItem);

    hideShape->addItem(QString("Прямоугольник id %1").arg(rectItem->getId()));
    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rectItem->idR)));
    tableWidget->setItem(rowCount, 1, new QTableWidgetItem("Прямоугольник"));
    addShapesToTableCell(tableWidget, rowCount, 3,1,countR);

}

    void MainWindow::addEllipse() {

    // Генерация случайных координат
    int x = QRandomGenerator::global()->bounded(-250, 250); // Ограничиваем по X
    int y = QRandomGenerator::global()->bounded(-250, 250); // Ограничиваем по Y
    EllipseItem* ellipseItem = new EllipseItem(x, y);
    scene->addItem(ellipseItem);
    hideShape->addItem(QString("Эллипс id %1").arg(ellipseItem->getId()));

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(ellipseItem->idE)));
    tableWidget->setItem(rowCount, 1, new QTableWidgetItem("Эллипс"));
    addShapesToTableCell(tableWidget, rowCount, 3, 3,countE);

}

    void MainWindow::addTriangle() {

    // Генерация случайных координат для треугольника
    QPointF p1(QRandomGenerator::global()->bounded(-250, 250), QRandomGenerator::global()->bounded(-250, 250));
    QPointF p2(QRandomGenerator::global()->bounded(-250, 250), QRandomGenerator::global()->bounded(-250, 250));
    QPointF p3(QRandomGenerator::global()->bounded(-250, 250), QRandomGenerator::global()->bounded(-250, 250));

    TriangleItem* trinagleItem = new TriangleItem(p1, p2, p3);
    scene->addItem(trinagleItem);
    hideShape->addItem(QString("Треугольник id %1").arg(trinagleItem->getId()));

    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow(rowCount);
    tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(trinagleItem->idT)));
    tableWidget->setItem(rowCount, 1, new QTableWidgetItem("Треугольник"));
    addShapesToTableCell(tableWidget, rowCount, 3, 2,countT);

}

void MainWindow::removeSelectedShape() {
    int removeId;
    int removeType;
    int removeCount;
    if( scene->selectedItems().size()){
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();
        for (auto item : selectedItems) {
            ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
            removeId = shapeItem->getId();
            removeType = shapeItem->getType();
            removeCount = shapeItem->getCount(1);
            scene->removeItem(item);
            delete item;
        }
        for(int i = 0; i < tableWidget->rowCount(); ++i){
            int removeRow = tableWidget->item(i,0)->text().toInt();
            if(removeRow == removeId){
                tableWidget->removeRow(i);
                addShapesToTableCell(tableWidget, removeRow, 3, removeType,removeCount);
            }
        }
        for (int i = 0; i < hideShape->count(); ++i) {
            QString currentText = hideShape->itemText(i);
            if (currentText.contains(QString::number(removeId))) {
                hideShape->removeItem(i);
                break; // Exit the loop after removing the item
            }
        }
    }
}


void MainWindow::updateActiveShape() {
    // Сначала сбрасываем активные состояния всех фигур
    for (auto item : scene->items()) {
        if (auto shape = dynamic_cast<ShapeItem*>(item)) {
            shape->setActive(false); // Деактивируем все фигуры
        }
    }

    // Затем активируем только выбранные и поднимаем их на передний план
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();

    for (auto item : selectedItems) {
        auto shape = dynamic_cast<ShapeItem*>(item);
            shape->setActive(true); // Активируем выбранные фигуры
            active_id = shape->getId();
        }

    // Перерисовываем сцену для обновления отображения
    scene->update();
}

void MainWindow::hideShapesVoid() {
    QString choise = hideShape->currentText();
    QString typec;
    int hideType=0;
    if(choise=="Все прямоугольники"){hideType = 1; typec = "Прямоугольник";}
    else if(choise =="Все треугольники"){hideType =2;typec = "Треугольник";}
    else if(choise== "Все эллипсы"){hideType =3;typec = "Эллипс";}
    else {
        int lastSpace = choise.lastIndexOf(' ');
        int number = choise.mid(lastSpace + 1).toInt();
        for (QGraphicsItem* item : scene->items()) {
            if (ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item)) {
                if (shapeItem->getId() == number) {
                    item->setVisible(false);
                    break;
                }
            }
        }
        for(auto pair : connectedPairs) {
            if(pair.first == number || pair.second ==number) {
                std::pair<int, int> connection = {std::min(pair.first, min(pair.second,number)), std::max(pair.first, max(pair.second,number))};
                if(connectedPairs.count(connection) == 0) {
                    return;
                }

                ShapeItem* shape1 = nullptr;
                ShapeItem* shape2 = nullptr;

                // Find the shape items
                for (QGraphicsItem* item : scene->items()) {
                    if(item){
                        ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
                        if(shapeItem) {
                            if (shapeItem->getId() == connection.first) {cout<<6;shape1 = shapeItem;}
                            if(shapeItem->getId() == connection.second){cout<<7; shape2 = shapeItem;}
                        }
                    }
                }
                if (!shape1||!shape2) return;
                // Iterate through scene items to find the line connecting those shapes.

                QPointF center1 = shape1->getCenter();
                QPointF center2 = shape2->getCenter();
                for(QGraphicsItem* item : scene->items()) {
                    QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);
                    if(lineItem) {
                        QLineF line = lineItem->line();
                        if ((line.p1() == center1 && line.p2() == center2) || (line.p1() == center2 && line.p2() == center1)) {
                            lineItem->setVisible(false);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            QTableWidgetItem* item = tableWidget->item(i, 0);
            if (item && item->text().toInt() == number) {
                tableWidget->setRowHidden(i, true);
                break;
            }
        }
        return;
    }
    for (QGraphicsItem* item : scene->items()) {
        if (ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item)) {
            if (shapeItem->getType() == hideType) {
                for(auto pair : connectedPairs) {
                    if(pair.first == shapeItem->getId() || pair.second == shapeItem->getId()) {
                        std::pair<int, int> connection = {std::min(pair.first, min(pair.second,shapeItem->getId())), std::max(pair.first, max(pair.second,shapeItem->getId()))};
                        if(connectedPairs.count(connection) == 0) {
                            return;
                        }

                        ShapeItem* shape1 = nullptr;
                        ShapeItem* shape2 = nullptr;

                        // Find the shape items
                        for (QGraphicsItem* item : scene->items()) {
                            if(item){
                                ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
                                if(shapeItem) {
                                    if (shapeItem->getId() == connection.first) {cout<<6;shape1 = shapeItem;}
                                    if(shapeItem->getId() == connection.second){cout<<7; shape2 = shapeItem;}
                                }
                            }
                        }
                        if (!shape1||!shape2) return;
                        // Iterate through scene items to find the line connecting those shapes.

                        QPointF center1 = shape1->getCenter();
                        QPointF center2 = shape2->getCenter();
                        for(QGraphicsItem* item : scene->items()) {
                            QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);
                            if(lineItem) {
                                QLineF line = lineItem->line();
                                if ((line.p1() == center1 && line.p2() == center2) || (line.p1() == center2 && line.p2() == center1)) {
                                    lineItem->setVisible(false);
                                }
                            }
                        }
                    }
                }
                item->setVisible(false);
            }
        }
    }


    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        QTableWidgetItem* item = tableWidget->item(i, 1);
        if (item && item->text() == typec) {
            tableWidget->setRowHidden(i, true);
        }
    }

}

void MainWindow::showShapesVoid() {
    for (QGraphicsItem* item : scene->items()) {
        item->setVisible(true);
    }
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        tableWidget->setRowHidden(i, false);
    }
}

void MainWindow::choose1Shape() {
    id_1 = active_id;
    cout<<id_1<<endl;
}
void MainWindow::choose2Shape() {
    id_2 = active_id;
    cout<<id_2<<endl;
}

void MainWindow::connectShapes() {
    ShapeItem* shape1;
    ShapeItem* shape2;

    for (QGraphicsItem* item : scene->items()) {
        if(item){
            ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
            if(shapeItem) {

                if (shapeItem->getId() == id_1) shape1 = shapeItem;
                if(shapeItem->getId() == id_2) shape2 = shapeItem;
            }
        }
    }
    if (!scene|| !shape1||!shape2 || shape1 ==shape2 ) {
        return;
    }
    // Check for duplicate connections (to avoid multiple lines between the same two shapes)
    if (connectedPairs.size() && connectedPairs.count({std::min(id_1, id_2), std::max(id_1, id_2)})) {
        return; // Already connected
    }
    // Get center coordinates of the shapes
    QPointF center1 = shape1->getCenter();
    QPointF center2 = shape2->getCenter();

    // Create a line item
    QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(center1, center2));
    // Add the line to the scene
    scene->addItem(lineItem);

    // Add the pair of shapes to the connectedPairs set
    connectedPairs.insert({std::min(id_1, id_2), std::max(id_1, id_2)});
}

void MainWindow::removeConnectVoid() {
    std::pair<int, int> connection = {std::min(id_1, id_2), std::max(id_1, id_2)};

    if(connectedPairs.count(connection) == 0)
        return;


    ShapeItem* shape1 = nullptr;
    ShapeItem* shape2 = nullptr;

    // Find the shape items
    for (QGraphicsItem* item : scene->items()) {
        if(item){
            ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
            if(shapeItem) {
                if (shapeItem->getId() == id_1) shape1 = shapeItem;
                if(shapeItem->getId() == id_2) shape2 = shapeItem;
            }
        }
    }
    if (!shape1||!shape2) return;

    // Iterate through scene items to find the line connecting those shapes.

    QPointF center1 = shape1->getCenter();
    QPointF center2 = shape2->getCenter();


    for(QGraphicsItem* item : scene->items()) {
        QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);
        if(lineItem) {
            QLineF line = lineItem->line();
            if ((line.p1() == center1 && line.p2() == center2) || (line.p1() == center2 && line.p2() == center1)){
                scene->removeItem(lineItem);
                delete lineItem;
                connectedPairs.erase(connection);
                break; // Assuming there's only one line between these shapes
            }
        }
    }
}



void MainWindow::vUpdate() {
    std::vector<QGraphicsLineItem*> linesToRemove;
    for (QGraphicsItem* item : scene->items()) {
        QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);
        if (lineItem) {
            linesToRemove.push_back(lineItem);
        }
    }
    for (QGraphicsLineItem* lineItem : linesToRemove) {
        scene->removeItem(lineItem);
        delete lineItem;
    }
    for (const auto& pair : connectedPairs) {
        int id1 = pair.first;
        int id2 = pair.second;
        ShapeItem* shape1;
        ShapeItem* shape2;
        for (QGraphicsItem* item : scene->items()) {
            if(item){
                ShapeItem* shapeItem = dynamic_cast<ShapeItem*>(item);
                if(shapeItem) {
                    if (shapeItem->getId() == id1) shape1 = shapeItem;
                    if(shapeItem->getId() == id2) shape2 = shapeItem;
                }
            }
        }
        if (!scene|| !shape1||!shape2 || shape1 ==shape2 ) {
            return;
        }
        QPointF center1 = shape1->getCenter();
        QPointF center2 = shape2->getCenter();

        // Create a line item
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(center1, center2));
        // Add the line to the scene
        scene->addItem(lineItem);
    }
}

