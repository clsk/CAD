#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QtCore>
#include <QtGui>

#include <iostream>

#include "Shape.h"

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), currentlySelectedTool(SELECT), m_scene(new Scene()), m_editManager(m_scene)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    ui->actionSelect->setChecked(true);
    ui->graphicsView->installEventFilter(this);
    cout << sizeof(QGraphicsItem) << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Filtered MousePress from QGraphicsView
    if (event->type() == QEvent::MouseButtonPress) {

        if (currentlySelectedTool == LINE || currentlySelectedTool == CIRCLE || currentlySelectedTool == RECTANGLE) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            auto pos = ui->graphicsView->mapToScene(mouseEvent->pos());
            QPointF size = QPointF(100, 100);

            Shape::Type shapeType = Shape::LINE;

            switch(currentlySelectedTool) {
            case CIRCLE:
                shapeType = Shape::CIRCLE;
                size = QPointF(100, 100);
                break;
            case RECTANGLE:
                shapeType = Shape::RECTANGLE;
                size = QPointF(150, 100);
                break;
            }

            m_editManager.createShape(shapeType, pos, size, QColor("black"));
            return true;
        }

    }

    return false;
}

void MainWindow::on_actionLine_triggered(bool checked)
{
    changeCurrentlySelectedTool(currentlySelectedTool, LINE, ui->actionLine);
}

void MainWindow::on_actionRectangle_triggered(bool checked)
{
    changeCurrentlySelectedTool(currentlySelectedTool, RECTANGLE, ui->actionRectangle);
}

void MainWindow::on_actionCircle_triggered(bool checked)
{
    changeCurrentlySelectedTool(currentlySelectedTool, CIRCLE, ui->actionCircle);
}

void MainWindow::on_actionSelect_triggered(bool checked)
{
    changeCurrentlySelectedTool(currentlySelectedTool, SELECT, ui->actionSelect);
}

void MainWindow::on_actionPan_triggered(bool checked)
{
    changeCurrentlySelectedTool(currentlySelectedTool, PAN, ui->actionPan);
}


void MainWindow::changeCurrentlySelectedTool(CheckableTool oldTool, CheckableTool newTool, QAction* newToolAction)
{
    if (oldTool == newTool) {
        newToolAction->setChecked(true);
        return;
    }

    QAction* action = nullptr;
    switch(oldTool) {
    case SELECT:
        action = ui->actionSelect;
        break;
    case PAN:
        action = ui->actionPan;
        break;
    case LINE:
        action = ui->actionLine;
        break;
    case RECTANGLE:
        action = ui->actionRectangle;
        break;
    case CIRCLE:
        action = ui->actionCircle;
        break;
    }

    if (action != nullptr) {
        action->setChecked(false);
    }

    newToolAction->setChecked(true);
    currentlySelectedTool = newTool;

}


void MainWindow::on_actionZoom_In_triggered()
{

}

void MainWindow::on_actionZoom_Out_triggered()
{

}

void MainWindow::on_actionZoom_All_triggered()
{

}



void MainWindow::on_actionDelete_triggered()
{
    auto items = m_scene->selectedItems();
    for (auto item : items) {
        m_editManager.deleteShape(item);
    }
}

void MainWindow::on_actionUndo_triggered()
{
    m_editManager.undo();
}

void MainWindow::on_actionRedo_triggered()
{
    m_editManager.redo();
}
