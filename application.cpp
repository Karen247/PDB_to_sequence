#include "application.h"
#include "graphicwidget.h"
#include "atom.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
using namespace std;
Application::Application(int &argc, char *argv[]) : QApplication(argc, argv)
{
}
int Application::run(){
    QWidget window;
    graphicWidget = new GraphicWidget;
    graphicWidget->setMinimumSize(750, 1000);
    QPushButton *hideButton = new QPushButton("HIDE");
    hideButton->setMinimumSize(QSize(50, 50));
    QPushButton *showButton = new QPushButton("SHOW");
    showButton->setMinimumSize(QSize(50, 50));
    QPushButton *fileButton = new QPushButton("FILE");
    fileButton->setMinimumSize(QSize(50, 50));
    QObject::connect(showButton, &QPushButton::clicked, graphicWidget, &GraphicWidget::showLetters);
    QObject::connect(hideButton, &QPushButton::clicked, graphicWidget, &GraphicWidget::hideLetters);
    QObject::connect(fileButton, &QPushButton::clicked, graphicWidget, &GraphicWidget::openFile);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(hideButton);
    rightLayout->addWidget(showButton);
    rightLayout->addWidget(fileButton);
    rightLayout->addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(graphicWidget);
    mainLayout->addLayout(rightLayout);
    window.setLayout(mainLayout);
    window.show();

    return QApplication::exec();
}
