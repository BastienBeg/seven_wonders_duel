#pragma once
#include <iostream>
#include <string>

// Symboles scientifiques pour les cartes scientifiques
enum class Symbol_Scientifique {
    GLOBE,
    BALANCE,
    CADRAN,
    BOL,
    COMPAS,
    PLUME,
    ROUE
};

// Symboles pour le chaînage
enum class Chainage {
    AUCUN,
    AMPHORE,
    TAMBOUR,

    MASQUE,
    TEMPLE,
    SOLEIL,
    GOUTTE,
    PILLIER,
    LUNE,

    CIBLE,
    CASQUE,
    FER,
    EPEE,
    TOUR,

    HARPE,
    ENGRENAGE,
    LIVRE,
    LAMPE
};


//types de cartes 
enum class Type_Carte {
    AUCUN,
    RESSOURCES,
    RESSOURCES_PRE,
    RESSOURCES_MAN,
    MILITAIRE,
    SCIENTIFIQUE,
    CIVIL,
    COMMERCIAL,
    GUILDE,
    MERVEILLE
};


// Couleurs des cartes pour les différentes matières premières ou produits manufacturés
enum class Couleur {
    AUCUN,
    MARRON,  // Matières premières
    GRIS    // Produits manufacturés
};

// Énumération pour gérer les différentes époques ou âges du jeu
enum class AGE {
    AGE1,
    AGE2,
    AGE3,
    FIN
};

// Surcharge des operateur << pour les enums


// -- Chainage -- : 

std::ostream& operator<<(std::ostream& flux, const Chainage& chainage);
bool operator==(Chainage c1, Chainage c2);
bool operator!=(Chainage c1, Chainage c2);




// -- Symbol scientifique -- :
std::ostream& operator<<(std::ostream& os, Symbol_Scientifique symbol) ;
