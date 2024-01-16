#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H
#include "atom.h" 
#include "residue.h"
#include <QApplication>
#include <vector>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include<iostream>
class GraphicWidget : public QWidget
{
 Q_OBJECT
 public:
    bool readPdbFile(QString pdbFile);
    void findResidues();
 public slots:
    void hideLetters();
    void showLetters();

    void openFile();
 protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent* event);

 private: 
    QString fileName;
    bool displayLetters = true, displayFile = false;
    int lastPosX = 0, lastPosY = 0;
    Residue *selectedResidue = nullptr;
    vector<Atom> atoms;
    vector<Residue> residues;
};
#endif // GRAPHICWIDGET_H
