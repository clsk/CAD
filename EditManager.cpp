#include "EditManager.h"

#include "CreateShapeCommand.h"
#include "DeleteShapeCommand.h"

#include <QDebug>

using std::make_shared;

EditManager::EditManager(QGraphicsScene* scene) : m_scene(scene)
{

}


void EditManager::removeGraphicsItem(QGraphicsItem *graphicsItem)
{
    m_graphicsItems.erase(graphicsItem);
}

shared_ptr<Shape> EditManager::getShape(QGraphicsItem *graphicsItem)
{
    auto shapeIter = m_graphicsItems.find(graphicsItem);
    if (shapeIter != m_graphicsItems.end()) {
        return shapeIter->second;
    } else {
        return nullptr;
    }
}

void EditManager::addGraphicsItem(QGraphicsItem *graphicsItem, shared_ptr<Shape> shape)
{
    m_graphicsItems.insert(unordered_map<QGraphicsItem*, shared_ptr<Shape>>::value_type(graphicsItem, shape));
}


void EditManager::createShape(Shape::Type type, const QPointF &pos, const QPointF &size, const QColor& color)
{
    shared_ptr<CreateShapeCommand> createCommand = make_shared<CreateShapeCommand>(m_scene, type, pos, size, color);
    createCommand->execute();
    auto shape = createCommand->getShape();
    addGraphicsItem(shape->qItem.get(), shape);
}


void EditManager::deleteShape(QGraphicsItem *item)
{
    auto shape = getShape(item);
    shared_ptr<DeleteShapeCommand> deleteCommand = make_shared<DeleteShapeCommand>(m_scene, shape);
    deleteCommand->execute();
    removeGraphicsItem(item);
}

// TODO: When redo stack is reset, make sure shape objects are deleted for CreateCommands
