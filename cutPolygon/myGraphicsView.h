#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include "myGraphicsScene.h"

class myGraphicsView : public QGraphicsView
{
public:
    myGraphicsView(QWidget *parent = nullptr);
    void        reDraw();

private:
    void                drawGrids(QPainter& painter);
    virtual void        resizeEvent(QResizeEvent*) override;
    virtual void        wheelEvent(QWheelEvent* ) override;

private:
    QRect               _drawBox;
    myGraphicsScene*    _scene;
};

#endif // MYGRAPHICSVIEW_H
