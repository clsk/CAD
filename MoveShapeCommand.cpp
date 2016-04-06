#include "MoveShapeCommand.h"

MoveShapeCommand::MoveShapeCommand(QGraphicsScene *graphicsScene, shared_ptr<Shape> shape) :
    ICommand(graphicsScene, shape)
{
}

void MoveShapeCommand::execute()
{
}

void MoveShapeCommand::undo()
{

}

