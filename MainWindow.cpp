#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), currentlySelectedTool(SELECT)
{
    ui->setupUi(this);
    scene = new Scene();
    ui->graphicsView->setScene(scene);
//    ui->actionSelect->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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

