#ifndef ATOM_H
#define ATOM_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
class Atom
{
    public:
        static const int RECORD_UNKNOWN = 0;
        static const int RECORD_ATOM = 1;
        static const int RECORD_HETATM = 2;
        bool readLine(const string &line);
        void writeLine() const;
        void writeLine(ostream &os) const;
        int getAtomNumber() const;
        string getAtomName() const;
        string getResidueName() const;
        int getResidueNumber() const;
    private:
        int recordType = RECORD_UNKNOWN;
        int atomNumber = 0;
        string atomName = "    ";
        char alternateLocation = ' ';
        string residueName = "   ";
        char chainID = ' ';
        int residueNumber = 0;
        char iCode = ' ';
        double coordX = 0, coordY = 0, coordZ = 0;
        double occupancy = 0;
        double tempFactor = 0;
        string elementName = "  ";
        string formalCharge;
        bool hasOccupancy = false;
        bool hasTempFactor = false;

};
#endif // ATOM_H
