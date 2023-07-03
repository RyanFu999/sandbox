#include "mainwindow.h"
#include <QVBoxLayout>

myMainWindow::myMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);
    init();
}

myMainWindow::~myMainWindow()
{

}

void myMainWindow::init()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    centralWidget->resize(size());

    _view = new myGraphicsView(this);
    layout->addWidget(_view);
}

void myMainWindow::resizeEvent(QResizeEvent *)
{
    _view->reDraw();
}

