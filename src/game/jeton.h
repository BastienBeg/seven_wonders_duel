#pragma once
#include <string>
using namespace std;

class Jeton_Progres {
private:
    string nom;

public:
    Jeton_Progres(string n) :nom(n) {}
    ~Jeton_Progres() = default;
    string getCheminImage() const;
    string getNom() const { return nom; }
};
