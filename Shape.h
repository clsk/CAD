#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QPointF>
#include <QGraphicsItem>

#include <memory>

using std::unique_ptr;

struct Shape {
    enum Type {
        CIRCLE,
        LINE,
        RECTANGLE
    };

//    Shape(QPointF _pos, QPointF _size, Type _type, QColor _color, unique_ptr<QGraphicsItem> _qItem) :
//        pos(_pos), size(_size), type(_type), color(_color), qItem(_qItem)
//    {}

    Type type;
    QPointF pos;
    QPointF size;
    QColor color;
    unique_ptr<QGraphicsItem> qItem;
};

#endif // SHAPE_H

