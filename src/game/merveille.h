#pragma once
#include "joueur.h"
#include "ressources.h"
#include "enum.h"
#include "partie.h"    
#include "enum.h"
#include "partie.h"    

// Déclaration avancé pour eviter les inclusion circulaire
class Joueur;
class Ressource;
class VuePlateau;

using namespace std;

class Bonus_merveille{
private:
    Ressource* offre_ressource;
    int bonus_piece;
    // Malus piece est un nombre positif qui correspond à ce qu'on soustrait au joueur
    int malus_piece;
    int point_de_victoire;
    int point_militaire;
    Couleur supprime_carte;
    bool offre_jeton;
    bool rejouer_tour;
    bool choisis_defausse;

public:
// Constructeur/destructeur
    Bonus_merveille(Ressource* o_r = nullptr, int b_p = 0, int m_p = 0, int p_v = 0, Couleur c = Couleur::AUCUN, bool o_j = false, int p_m = 0, bool r_t = false, bool c_p = false)
        : offre_ressource(o_r), bonus_piece(b_p), malus_piece(m_p),
        point_de_victoire(p_v), supprime_carte(c), offre_jeton(o_j),
        point_militaire(p_m), rejouer_tour(r_t), choisis_defausse(c_p) {}
    
    ~Bonus_merveille();

// Accesseurs

    Ressource* getOffreRessource() const { return offre_ressource; }
    int getBonusPiece() const { return bonus_piece; }
    int getMalusPiece() const { return malus_piece; }
    int getPointDeVictoire() const { return point_de_victoire; }
    Couleur getSupprimeCarte() const { return supprime_carte; }
    bool getOffreJeton() const { return offre_jeton; }
    int getPointMilitaire() const { return point_militaire; }
    bool getRejouerTour() const { return rejouer_tour; }
    bool getChoisisDefausse() const { return choisis_defausse; }

    void setOffreRessource(int bois, int fer, int argile, int verre, int papyrus);
    void setBonusPiece(int bonus) { bonus_piece = bonus; }
    void setMalusPiece(int malus) { malus_piece = malus; }
    void setPointDeVictoire(int points) { point_de_victoire = points; }
    void setSupprimeCarte(Couleur couleur) { supprime_carte = couleur; }
    void setOffreJeton(bool jeton) { offre_jeton = jeton; }
    void setPointMilitaire(int points) { point_militaire = points; }
    void setRejouerTour(bool rejouer) { rejouer_tour = rejouer; }
    void setChoisisDefausse(bool defausse) { choisis_defausse = defausse; }

// Methodes de la classe
private:

    void offre_jeton_progres(Joueur* j, VuePlateau* vp);

public:
    void joue_le_bonus(Joueur* j, VuePlateau* vp);
};


class Merveille{
private:
    string nom;
    Ressource* cout_construction;
    Bonus_merveille* bonus;

public : 
    Merveille(string n,Ressource* c,Bonus_merveille* b):nom(n),cout_construction(c),bonus(b){}
    ~Merveille();

    //Acesseurs
    string getNom() const { return nom; };
    Ressource* getCout() const { return cout_construction; }
    Bonus_merveille* getBonus() const { return bonus; }
    // Renvoie True si il a pu construire la merveille sinon False
    bool construireMerveille(Joueur* j );
    const std::vector<Merveille*>& getMerveillesConstruites() const;
    std::string getCheminImage() const;

};

std::ostream& operator<<(std::ostream& os, const Merveille& merveille);
