#include "Shapes.h"

class CustomTableCell;


void addShapesToTableCell(QTableWidget* tableWidget, int rowIndex,
    int columnIndex, int shapeType, int count) {
    if (columnIndex < 0 || columnIndex >= tableWidget->columnCount()) {
        return;
    }

    int ShapeCount = 0;

    if (count <= 3 ) {
        ShapeCount = 1;
    } else if (count < 10) {
        ShapeCount = 2;
    } else {
        ShapeCount = 3;
    }
    for (int rowIndex = 0; rowIndex < tableWidget->rowCount(); ++rowIndex) {
        QWidget* cellWidget = tableWidget->cellWidget(rowIndex, columnIndex);
        if (cellWidget && dynamic_cast<CustomTableCell*>(cellWidget)) {
            CustomTableCell* customCell = static_cast<CustomTableCell*>(cellWidget);
            if (customCell-> shapeType == shapeType) {
                customCell->setShapeCount(ShapeCount); // Обновляем количество фигур
            }
        }
    }
        CustomTableCell* widget = new CustomTableCell(shapeType, ShapeCount);
        tableWidget->setCellWidget(rowIndex, columnIndex, widget);

}

