#include "graphicwidget.h"
#include "atom.h"
#include "residue.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QMouseEvent>
using namespace std;

void GraphicWidget::showLetters()
{
 cout << "Bylo stisknuto tlacitko Show" << endl;
 displayLetters = true;
 update();
}

void GraphicWidget::hideLetters()
{
 cout << "Bylo stisknuto tlacitko Hide" << endl;
 displayLetters = false;
 update();
}

bool GraphicWidget::readPdbFile(QString pdbFile){
    string x = pdbFile.toStdString();
    int line_num = 1;
    ifstream ifile(x);
    if (ifile.fail()){
        cout << "Nelze otevrit soubor!\n";
        return false;
    }
    string line, recordName;
    while (getline(ifile, line)) {
        if (line.length() >= 6) {
                    recordName = line.substr(0, 6);
                }
        if (recordName == "ATOM  " || recordName == "HETATM") {
                    Atom atom;

            if (!atom.readLine(line)){
                cout << "error on line number: " << line_num << endl;
                cout << line << endl;
                return false;
            }

            atoms.push_back(atom);
        }
        line_num+=1;

    }
    return true;
}

void GraphicWidget::openFile()
{
     residues.clear();
     atoms.clear();
     fileName = QFileDialog::getOpenFileName(this, "Vyber soubor", ".");
     if (fileName.isEmpty()) return;
     cout << "Jmeno souboru: " << fileName.toStdString() << endl;
     fileName.toStdString();
     if (readPdbFile(fileName)){
         findResidues();
     }
     for (auto &res : residues){
                
                cout << "Residuum: " <<  res.getResidueNumber() << " " << res.getResidueName() << " " << res.getResidueChar()  
                     << ", atomy: " << res.getAtomFirst() << " " << res.getAtomLast() << endl;
     }
     
     displayFile = true;
     update();

     

}

void GraphicWidget::findResidues(){
    int counter = 0;
    int size = atoms.size();
    for (int i = 0; i < size; i++){
         if (i == 0 || atoms[i].getResidueNumber() != atoms[i-1].getResidueNumber()){

             Residue residue(atoms[i].getAtomNumber(), atoms[i].getResidueName(), atoms[i].getResidueNumber());
             residues.push_back(residue);
         }

         else if(atoms[i+1].getResidueNumber() != atoms[i].getResidueNumber()){
             residues[counter].setAtomLast(atoms[i].getAtomNumber());
             counter++;
         }
    }


}
void GraphicWidget::mousePressEvent(QMouseEvent *event)
{
    cout << "Stisknuto tlacitko mysi!" << endl;
    lastPosX = event->x();
    lastPosY = event->y();
    for (auto &res : residues){
        if ((lastPosX < res.getPosX() + 20 & lastPosX >= res.getPosX()) 
            & (lastPosY >= res.getPosY() & lastPosY < res.getPosY() + 20)){
                selectedResidue = &res;
            }
        update();    
    }

    
}

void GraphicWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    int count = 0;
    int x = 20;
    int y = 90;
    int r = 153, g = 153, b = 153;
    if (displayFile == true){
        QPen pen0(Qt::black);
        painter.setPen(pen0);
        QFont font("Helvetica", 14, QFont::Bold);
        painter.setFont(font);
        fileName.toStdString();
        painter.drawText(20, 30, "File:" );
        painter.drawText(20, 70, fileName);
        QPen pen1(Qt::black);
        QBrush brush1(Qt::transparent);
        painter.setPen(pen1);
        painter.setBrush(brush1);
        painter.drawRect(10, 10, 600, 980); 
    }
    
    for (auto &res : residues){
        char aa = res.getResidueChar();
        res.getColorRgb(r, g, b);
        QPen pen2(Qt::transparent);
        QBrush brush2(QColor(r, g, b));
        painter.setPen(pen2);
        painter.setBrush(brush2);
        painter.drawRect(x, y, 22, 30); 
        res.setPosXY(x, y);
        if (displayLetters == true){
            QPen pen3(Qt::black, 3);
            painter.setPen(pen3);
            QFont font("Helvetica", 14, QFont::Bold);
            painter.setFont(font);
            painter.drawText(x+3, y+20, QString(aa));
        }
        x += 22;
        count++;
        if (count == 20){
            y += 50;
            x = 20;
            count = 0;
           
        }
    }
    if (selectedResidue != nullptr){
            ostringstream ss;
            QPen pen4(Qt::red, 5);
            QBrush brush4(Qt::transparent);
            painter.setBrush(brush4);
            painter.setPen(pen4);
            painter.drawRect(selectedResidue->getPosX(), selectedResidue->getPosY() - 1, 20 + 1, 30 + 1);
            QPen pen5(Qt::black);
            painter.setPen(pen5);
            QFont font("Helvetica", 14, QFont::Bold);
            painter.setFont(font);
            ss << "Residuum: ";
            ss << selectedResidue->getResidueName();
            ss << selectedResidue->getResidueNumber();
            ss << " Pocet atomu: ";
            ss << selectedResidue->getAtomCount();
            painter.drawText(20, height() - 70, ss.str().c_str());
            selectedResidue = nullptr; 
    }


}
