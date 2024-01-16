#include "residue.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <variant>
#include <map>
using namespace std;
const map<string, char> Residue::nameToChar = {
    {"ALA", 'A'}, {"ARG", 'R'}, {"ASN", 'N'}, {"ASP", 'D'}, 
    {"CYS", 'C'}, {"GLN", 'Q'}, {"GLU", 'E'}, {"GLY", 'G'},
    {"HIS", 'H'}, {"ILE", 'I'}, {"LEU", 'L'}, {"LYS", 'K'},
    {"MET", 'M'}, {"PHE", 'F'}, {"PRO", 'P'}, {"SER", 'S'},
    {"THR", 'T'}, {"TRP", 'W'}, {"TYR", 'Y'}, {"VAL", 'V'}
};
Residue::Residue(int atomFirst, const string &residueName, int residueNumber) : atomFirst(atomFirst), residueName(residueName), residueNumber(residueNumber)
{
}

Residue::Residue()
{
}
int Residue::getAtomFirst() const{
    return atomFirst;
}
int Residue::getAtomLast() const{
    return atomLast;

}
void Residue::setAtomFirst(int atomFirst){
    Residue::atomFirst = atomFirst;
}
void Residue::setAtomLast(int atomLast){
    Residue::atomLast = atomLast;
}
string Residue::getResidueName() const{
    return residueName;
}
int Residue::getResidueNumber() const{
    return residueNumber;
}
void Residue::setResidueNumber(int number){
    Residue::residueNumber = number;
}
void Residue::setResidueName(const string &name){
    Residue::residueName = name;
}

char Residue::getResidueChar() const{
    for(auto it = nameToChar.begin();
        it != nameToChar.end(); ++it){
            if (it->first == residueName){
                return it->second;
            }
    }
    return 'X';
}
string Residue::findLineForRgb() const{
    ifstream ifile("rgb_amino.txt");
    string line;
    if (!ifile)
    {
        cout << "Nelze otevrit soubor!\n";
        
    }
    unsigned int curLine = 0;
    string aa = Residue::getResidueName();
    if (ifile.is_open()){
        while(getline(ifile, line)) { 
            curLine++;
            if (line.find(aa, 0) != string::npos) {
                return line;
            }
        }
        return "UNKNOWN 153 153 153";
        ifile.close();
    }
   
    
}

void Residue::getColorRgb(int &r, int &g, int &b){
    string s = Residue::findLineForRgb();
    istringstream sstream(s);
    string aa;
    
    sstream >> aa >> r >> g >> b;
    
}
int Residue::getPosX() const{
    return posX;
}
int Residue::getPosY() const{
    return posY;
}
void Residue::setPosXY(int posX, int posY){
    Residue::posX = posX;
    Residue::posY = posY;
}
int Residue::getAtomCount() const{
    return Residue::atomLast - Residue::atomFirst;
}
