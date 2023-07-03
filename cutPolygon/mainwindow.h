#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "myGraphicsView.h"

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myMainWindow(QWidget *parent = nullptr);
    ~myMainWindow();

    void        init();

private:
    void        resizeEvent(QResizeEvent *) override;

private:
    myGraphicsView*     _view;

};
#endif // MAINWINDOW_H
