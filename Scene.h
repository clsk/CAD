#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
public slots:
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    const int m_GRID_SPACING = 20;
};

#endif // MAINSCENE_H
