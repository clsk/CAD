#include "CreateShapeCommand.h"

#include <QGraphicsView>

#include <iostream>

using std::cout;
using std::endl;

CreateShapeCommand::CreateShapeCommand(QGraphicsScene* scene, Shape::Type type, const QPointF& pos, const QPointF& size, const QColor& color) :
    ICommand(scene), m_type(type), m_pos(pos), m_size(size), m_color(color)
{
}

void CreateShapeCommand::execute()
{
    auto sceneRect = m_scene->views().first()->sceneRect();

    QGraphicsItem* item = nullptr;

    if (m_type == Shape::LINE) {
        cout << "x: " << m_pos.x() << ", y: " << m_pos.y() << endl;
        item = m_scene->addLine(m_pos.x(), m_pos.y(), m_pos.x()+m_size.x(), m_pos.y()-10);
        m_scene->views().first()->setSceneRect(sceneRect);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setFlag(QGraphicsItem::ItemIsSelectable);

    } else if (m_type == Shape::RECTANGLE) {
        cout << "x: " << m_pos.x() << ", y: " << m_pos.y() << endl;
        item = m_scene->addRect(m_pos.x(), m_pos.y(), m_size.x(), m_size.y());
        m_scene->views().first()->setSceneRect(sceneRect);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setFlag(QGraphicsItem::ItemIsSelectable);

    } else if (m_type == Shape::CIRCLE) {
        cout << "x: " << m_pos.x() << ", y: " << m_pos.y() << endl;
        auto item = m_scene->addEllipse(m_pos.x(), m_pos.y(), m_size.x(), m_size.y());
        m_scene->views().first()->setSceneRect(sceneRect);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
    }

    m_shape = shared_ptr<Shape>(new Shape {m_type, m_pos, m_size, m_color, unique_ptr<QGraphicsItem>(item)});
}

void CreateShapeCommand::undo()
{

}



