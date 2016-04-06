#ifndef CREATESHAPECOMMAND_H
#define CREATESHAPECOMMAND_H

#include <QPointF>

#include <memory>


#include "ICommand.h"
#include "Shape.h"

class CreateShapeCommand : public ICommand
{
public:
    CreateShapeCommand(QGraphicsScene* scene, Shape::Type type, const QPointF& pos, const QPointF& size, const QColor& color);
    void execute();
    void undo();

private:
    Shape::Type m_type;
    QPointF     m_pos;
    QPointF 	m_size;
    QColor 		m_color;
};

#endif // CREATESHAPECOMMAND_H
