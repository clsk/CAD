#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "EditManager.h"
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
    CheckableTool currentlySelectedTool;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_actionLine_triggered(bool checked);
    void on_actionRectangle_triggered(bool checked);
    void on_actionCircle_triggered(bool checked);
    void on_actionSelect_triggered(bool checked);
    void on_actionPan_triggered(bool checked);
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionZoom_All_triggered();

    void on_actionDelete_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    void changeCurrentlySelectedTool(CheckableTool oldTool, CheckableTool newTool, QAction* newToolAction);

    Ui::MainWindow *ui;
    Scene* m_scene;
    EditManager m_editManager;

};

#endif // MAINWINDOW_H
