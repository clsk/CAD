#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QGraphicsScene>

#include <memory>

#include "Shape.h"

using std::weak_ptr;
using std::shared_ptr;

class ICommand {
public:
    ICommand(QGraphicsScene* graphicsScene, shared_ptr<Shape> shape = shared_ptr<Shape>()) : m_scene(graphicsScene), m_shape(shape) {}
    virtual ~ICommand() {}

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual shared_ptr<Shape> getShape() const { return m_shape; }

protected:
    QGraphicsScene* m_scene;
    shared_ptr<Shape> m_shape;
};

#endif // ICOMMAND_H
