#ifndef APPLICATION_H
#define APPLICATION_H
#include "graphicwidget.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char *argv[]);

    int run();


private:
    QWidget window;
    GraphicWidget *graphicWidget;

};
#endif // APPLICATION_H
