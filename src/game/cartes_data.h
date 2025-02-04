#ifndef SEVENWONDERSDUEL_CARTES_DATA_H
#define SEVENWONDERSDUEL_CARTES_DATA_H

#ifndef CARTES_DATA_H
#define CARTES_DATA_H

#include <vector>
#include "Carte.h"
#include "merveille.h"

// Déclaration des fonctions pour initialiser les cartes de chaque âge
std::vector<Carte*> initialiserCartesAgeI();
std::vector<Carte*> initialiserCartesAgeII();
std::vector<Carte*> initialiserCartesAgeIII();
std::vector<Jeton_Progres*> initialiserJetonProgres();
Carte* initcarte_invisible();

std::vector<Merveille*> initialiserMerveillesData();

string getCheminImage();

#endif // CARTES_DATA_H


#endif //SEVENWONDERSDUEL_CARTES_DATA_H


