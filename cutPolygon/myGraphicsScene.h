#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

class myGraphicsScene : public QGraphicsScene
{
public:
    explicit myGraphicsScene(QObject *parent = nullptr);
};

#endif // MYGRAPHICSSCENE_H
