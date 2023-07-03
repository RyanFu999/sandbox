#include "myGraphicsView.h"
#include <QPolygonF>
#include <iostream>
using namespace  std;

myGraphicsView::myGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    _scene = new myGraphicsScene(this);
    _scene->setSceneRect(this->rect());
    setScene(_scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void myGraphicsView::reDraw()
{
    QSize viewSize = size();
    int viewWidth = viewSize.width();
    int viewHeight = viewSize.height();
    _drawBox = QRect(0, 0, viewWidth, viewHeight);
    QPixmap pm(_drawBox.width(), _drawBox.height());
    pm.fill(Qt::black);
    QPainter painter(&pm);
    drawGrids(painter);
    setBackgroundBrush(pm);
}

void myGraphicsView::drawGrids(QPainter &painter)
{
    if (_drawBox.width() > 10000 || _drawBox.height() > 10000)
        return;

    int xDigit = (int)log10(_drawBox.width()) - 1;
    int yDigit = (int)log10(_drawBox.height()) - 1;
    int digit = xDigit > yDigit ? xDigit : yDigit;
    int space = digit < 0 ? 1 : pow(10, digit);

    QPolygon pointBuf;
    int x = _drawBox.left() - (_drawBox.left() % space);
    int y = _drawBox.top() - (_drawBox.top() % space);
    for (int i = x; i < _drawBox.right(); i+= space) {
        for (int j = y; j < _drawBox.bottom(); j += space) {
            pointBuf.push_back(QPoint(i, j));
        }
    }
    painter.setPen(Qt::white);
    painter.setBrush(QBrush());
    painter.drawPoints(pointBuf);
}

void myGraphicsView::resizeEvent(QResizeEvent *)
{
    int w = width();
    int h = height();
    _scene->setSceneRect(0, 0, w, h);
}

void myGraphicsView::wheelEvent(QWheelEvent *)
{

}

