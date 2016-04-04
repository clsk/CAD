#include "Scene.h"

#include <QtGui>
#include <QtCore>

Scene::Scene()
{
    QPixmap pixmap(m_GRID_SPACING, m_GRID_SPACING);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.drawPoint(0, 0);
    painter.drawPoint(m_GRID_SPACING, m_GRID_SPACING);

    this->setBackgroundBrush(pixmap);
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    double x = rect.x();
    double y = rect.y();

    QRectF newRect(rect);

    newRect.setTopLeft(QPointF(floor(x/m_GRID_SPACING)*m_GRID_SPACING, floor(y/m_GRID_SPACING)*m_GRID_SPACING));
    painter->drawTiledPixmap(newRect, backgroundBrush().texture());

    // X axis
    painter->setPen(Qt::green);
    painter->drawLine(0, 0, 40, 0);

    // Y axis
    painter->setPen(Qt::red);
    painter->drawLine(0, 0, 0, -40);

    painter->end();
}

