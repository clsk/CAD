#include "DeleteShapeCommand.h"
#include "CreateShapeCommand.h"

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
    CreateShapeCommand createCommand(m_scene, m_shape->type, m_shape->pos, m_shape->size, m_shape->color);
    createCommand.execute();
    m_shape->qItem.reset(createCommand.getShape()->qItem.release());
    // TODO:

}
