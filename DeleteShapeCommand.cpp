#include "DeleteShapeCommand.h"

DeleteShapeCommand::DeleteShapeCommand(QGraphicsScene *graphicsScene, shared_ptr<Shape> shape) :
    ICommand(graphicsScene, shape)
{
}

void DeleteShapeCommand::execute()
{
    if (m_shape) {
        m_scene->removeItem(m_shape->qItem.get());
        m_shape->qItem.reset();
    }
}

void DeleteShapeCommand::undo()
{

}
