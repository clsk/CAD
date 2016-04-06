#ifndef DELETESHAPECOMMAND_H
#define DELETESHAPECOMMAND_H

#include "ICommand.h"

class DeleteShapeCommand : public ICommand
{
public:
    DeleteShapeCommand(QGraphicsScene* graphicsScene, shared_ptr<Shape> shape = shared_ptr<Shape>());
    void execute();
    void undo();
};

#endif // DELETESHAPECOMMAND_H
