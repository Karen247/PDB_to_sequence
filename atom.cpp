#include "atom.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

string Atom::getAtomName() const{
    return atomName;
}

int Atom::getAtomNumber() const{
    return atomNumber;
}

int Atom::getResidueNumber() const{
    return residueNumber;
}

string Atom::getResidueName() const{
    return residueName;
}
void Atom::writeLine(ostream &os) const{
    if (recordType == RECORD_ATOM){
        os << "ATOM  ";
    }
    else if (recordType == RECORD_HETATM){
        os << "HETATM";
    }
    else return;
    os << right << setw(5) << atomNumber;
    os << ' ';
    os << left << setw(4) << atomName;
    os << alternateLocation;
    os << left << setw(3) << residueName;
    os << ' ';
    os << chainID;
    os << right << setw(4) << residueNumber;
    os << iCode;
    os << "   ";
    os << right << fixed << setprecision(3);
    os << setw(8) << coordX;
    os << setw(8) << coordY;
    os << setw(8) << coordZ;

    if (hasOccupancy){
        os << right << fixed << setprecision(2) << setw(6) << occupancy;
    }
    else {
        os << "      ";
    }
    if (hasTempFactor) // Zapiseme teplotni faktor
        os << right << fixed << setprecision(2) << setw(6) << tempFactor;
    else
        os << "      ";
    os << "          ";
    os << right << setw(2) << elementName;
    os << left << setw(2) << formalCharge;
    os << endl;

}

void Atom::writeLine() const{
    if (recordType == RECORD_ATOM){
        cout << "ATOM  ";
    }
    else if (recordType == RECORD_HETATM){
        cout << "HETATM";
    }
    else return;
    cout << right << setw(5) << atomNumber;
    cout << ' ';
    cout << left << setw(4) << atomName;
    cout << alternateLocation;
    cout << left << setw(3) << residueName;
    cout << ' ';
    cout << chainID;
    cout << right << setw(4) << residueNumber;
    cout << iCode;
    cout << "   ";
    cout << right << fixed << setprecision(3);
    cout << setw(8) << coordX;
    cout << setw(8) << coordY;
    cout << setw(8) << coordZ;

    if (hasOccupancy){
        cout << right << fixed << setprecision(2) << setw(6) << occupancy;
    }
    else {
        cout << "      ";
    }
    if (hasTempFactor) // Zapiseme teplotni faktor
        cout << right << fixed << setprecision(2) << setw(6) << tempFactor;
    else
        cout << "      ";
    cout << "          ";
    cout << right << setw(2) << elementName;
    cout << left << setw(2) << formalCharge;
    cout << endl;

}

bool Atom::readLine(const string &line){
    string recordName, s;
    istringstream sstream;
    if (line.length() < 53){
        cout << "Kratky radek!" << endl;
        return false;
    }
    recordName = line.substr(0, 6);
    if (recordName == "ATOM  "){
        recordType = RECORD_ATOM;
    }
    else if (recordName == "HETATM") recordType = RECORD_HETATM;
    else return false;

    // read atomNum
    s = line.substr(6, 5);
    sstream.str(s);
    sstream.clear();
    sstream >> atomNumber;
    if (sstream.fail()){
        cout << "Nepodarilo nacist cislo atomu" << endl;
        return false;
    }

    //read atom name
    atomName = line.substr(12, 4);

    //read alternate location indicator
    alternateLocation = line[16];

    residueName = line.substr(17, 3);
    chainID = line[21];

    //read residue sequence number
    s = line.substr(22, 4);
    sstream.str(s);
    sstream.clear();
    sstream >> residueNumber;
    if (sstream.fail()){
        cout << "Nepodarilo nacist cislo residua" << endl;
        return false;
    }

    iCode = line[26];

    //read X coodrinates
    s = line.substr(30, 8);
    sstream.str(s);
    sstream.clear();
    sstream >> coordX;
    if (sstream.fail()){
        cout << "Nepodarilo nacist cislo X" << endl;
        return false;
    }

    //read Y coodrinates
    s = line.substr(38, 8);
    sstream.str(s);
    sstream.clear();
    sstream >> coordY;
    if (sstream.fail()){
        cout << "Nepodarilo nacist cislo Y" << endl;
        return false;
    }

    //read Z coodrinates
    s = line.substr(46, 8);
    sstream.str(s);
    sstream.clear();
    sstream >> coordZ;
    if (sstream.fail()){
        cout << "Nepodarilo nacist cislo Z" << endl;
        return false;
    }

    //read occupancy
    if (line.length() >= 60){
        s = line.substr(54, 6);
        sstream.str(s);
        sstream.clear();
        sstream >> occupancy;
        if (sstream.fail()){
            cout << "Nepodarilo nacist occupancy" << endl;
            return false;
        }
        else {hasOccupancy = true;}
    }

    //read factor
    if (line.length()>=66){
        s = line.substr(60, 6);
        sstream.str(s);
        sstream.clear();
        sstream >> tempFactor;
        if (sstream.fail()){
            cout << "Nepodarilo nacist temperature factor" << endl;
            return false;
        }
        else{hasTempFactor = true;}
    }

    if (line.length() >= 78){
        elementName = line.substr(76, 2);

    }

    if (line.length() >= 80){
        formalCharge = line.substr(78, 2);
    }
    return true;
}
