#ifndef MOVESHAPECOMMAND_H
#define MOVESHAPECOMMAND_H

#include <QGraphicsItem>
#include <memory>

#include "ICommand.h"
#include "Shape.h"

using std::shared_ptr;

class MoveShapeCommand : public ICommand
{
public:
    MoveShapeCommand(QGraphicsScene* graphicsScene, shared_ptr<Shape> shape = shared_ptr<Shape>());
    void execute();
    void undo();
};

#endif // MOVESHAPECOMMAND_H
