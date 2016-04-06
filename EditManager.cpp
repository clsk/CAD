#include "EditManager.h"

#include "CreateShapeCommand.h"
#include "DeleteShapeCommand.h"

#include <QDebug>

using std::make_shared;

EditManager::EditManager(QGraphicsScene* scene) : m_scene(scene)
{

}

void EditManager::undo()
{
    if (m_undoStack.size() < 1) {
        return;
    }

    m_undoStack.top()->undo();

    CreateShapeCommand* createCommand = dynamic_cast<CreateShapeCommand*>(m_undoStack.top().get());
    if (createCommand != nullptr) { // If this was a create command, (undo = delete), remove QGraphicsItem
        qDebug() << "This is a Create command";
        removeGraphicsItem(createCommand->getShape()->qItem.get());
    } else {
        qDebug() << "This is NOT a Create command";
        DeleteShapeCommand* deleteCommand = dynamic_cast<DeleteShapeCommand*>(m_undoStack.top().get());
        if (deleteCommand != nullptr) { // if this was a delete command, (undo = create), add QGraphicsItem
            qDebug() << "This is a Delete command";
            auto shape = deleteCommand->getShape();
            addGraphicsItem(shape->qItem.get(), shape);
        } else {
            qDebug() << "This is NOT a Delete command";
        }
    }

    m_redoStack.push(m_undoStack.top());
    m_undoStack.pop();
}

void EditManager::redo()
{
    if (m_redoStack.size() < 1) {
        return;
    }

    m_redoStack.top()->execute();

    CreateShapeCommand* createCommand = dynamic_cast<CreateShapeCommand*>(m_undoStack.top().get());
    if (createCommand != nullptr) { // If this was a create command, add QGraphicsItem
        qDebug() << "This is a Create command";

        auto shape = createCommand->getShape();
        addGraphicsItem(shape->qItem.get(), shape);

    } else {
        qDebug() << "This is NOT a Create command";
        DeleteShapeCommand* deleteCommand = dynamic_cast<DeleteShapeCommand*>(m_undoStack.top().get());
        if (deleteCommand != nullptr) { // if this was a delete command, remove QGraphicsItem
            qDebug() << "This is a Delete command";
            removeGraphicsItem(deleteCommand->getShape()->qItem.get());
        } else {
            qDebug() << "This is NOT a Delete command";
        }

    }

    m_undoStack.push(m_undoStack.top());
    m_redoStack.pop();
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

void EditManager::resetRedoStack()
{
    // TODO: make sure shape objects are deleted for CreateCommands
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
    m_undoStack.push(createCommand);
}


void EditManager::deleteShape(QGraphicsItem *item)
{
    auto shape = getShape(item);
    shared_ptr<DeleteShapeCommand> deleteCommand = make_shared<DeleteShapeCommand>(m_scene, shape);
    deleteCommand->execute();
    removeGraphicsItem(item);
    m_undoStack.push(deleteCommand);
}

