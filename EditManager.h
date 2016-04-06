#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include "Shape.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPointF>

#include <memory>
#include <list>
#include <stack>
#include <unordered_map>

#include "ICommand.h"

using std::stack;
using std::list;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_map;

class EditManager
{
public:
    EditManager(QGraphicsScene* scene);

    // Actions
    void createShape(Shape::Type type, const QPointF &pos, const QPointF &size, const QColor& color);
    void deleteShape(QGraphicsItem* item);
    void moveShape(QGraphicsItem* item, const QPointF& newPos);
    void resizeShape(QGraphicsItem* item, const QPointF& newSize);
    void changeShapeColor(QGraphicsItem* item, const QColor& color);

    // Manage QGraphicsItems' pointers
    void addGraphicsItem(QGraphicsItem *graphicsItem, shared_ptr<Shape> shape);
    void removeGraphicsItem(QGraphicsItem* graphicsItem);
    shared_ptr<Shape> getShape(QGraphicsItem* graphicsItem);

    QGraphicsScene* m_scene;
private:
    stack<ICommand> m_undoStack;
    stack<ICommand> m_redoStack;
    unordered_map<QGraphicsItem*, shared_ptr<Shape>> m_graphicsItems;
};

#endif // EDITMANAGER_H
