#ifndef RESIDUE_H
#define RESIDUE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <variant>
#include <unordered_map>
#include <map>
using namespace std;
class Residue
{
    public:
        Residue(int atomFirst, const string &residueName, int residueNumber);
        Residue();
        int getAtomLast() const;
        void setAtomLast(int atomLast);
        int getAtomFirst() const;
        void setAtomFirst(int atomLast);

        string getResidueName() const;
        void setResidueName(const string &name);

        int getResidueNumber() const;
        void setResidueNumber(int number);
        char getResidueChar() const;
        void getColorRgb(int &r, int &g, int&b);
        string findLineForRgb() const;
        int getAtomCount() const;

        int getPosX() const;
        int getPosY() const;
        void setPosXY(int posX, int posY);
    private:
        static const map<string, char> nameToChar;
        int atomFirst;
        int atomLast;
        double posX;
        double posY;
        string residueName = "   ";
        int residueNumber;
};
#endif // RESIDUE_H
