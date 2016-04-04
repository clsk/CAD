#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum CheckableTool {
        SELECT,
        PAN,
        RECTANGLE,
        LINE,
        CIRCLE
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLine_triggered(bool checked);

    void on_actionRectangle_triggered(bool checked);

    void on_actionCircle_triggered(bool checked);

    void on_actionSelect_triggered(bool checked);

    void on_actionPan_triggered(bool checked);

private:
    void changeCurrentlySelectedTool(CheckableTool oldTool, CheckableTool newTool, QAction* newToolAction);

    Ui::MainWindow *ui;
    Scene* scene;
    CheckableTool currentlySelectedTool;
};

#endif // MAINWINDOW_H
