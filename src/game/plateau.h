#pragma once
#include "carte.h"
#include "partie.h"
#include "enum.h"
#include "jeton.h"
#include "joueur.h"
#include "merveille.h"
#include <vector>
using namespace std;

// Déclaration avance
class Joueur;
class Partie;
class Carte;
class Merveille;

class Plateau_militaire {
private:
    int position; // Position du pion sur la piste militaire, initialement à 0
    bool malus_piece[4] = {false, false, false, false};
public:
    Plateau_militaire() : position(0) {}
    // Méthode pour déplacer le pion sur la piste militaire
    void deplacement(int force);
    void test_victoire_militaire(const Plateau_militaire& p) const;

    int getPosition() const { return position; }
};


class Plateau {
private:
    AGE age;
    std::vector<Carte*> cartesDisponibles;
    int positionConflit{}; // Position du pion Conflit sur la piste militaire
    std::vector<Carte*> defausse;
    int nb_carte_en_jeu{};

    Plateau_militaire* plateau_militaire;
    std::vector<Jeton_Progres*> jeton_prog_total;
    std::vector<Jeton_Progres*> jeton_prog_en_jeu;
    std::vector<Jeton_Progres*> jeton_prog_defausse;

    //Cartes disposition
    std::vector<Carte*> cartes_age_I;
    std::vector<Carte*> cartes_age_II;
    std::vector<Carte*> cartes_age_III;
    Carte* carte_invisible;

    std::vector<Merveille*> liste_merveilles;


    // Méthode pour initialiser les cartes
    void initialiserCartes();
    // Methode pour initialiser les merveilles
    void initialiserMerveilles();
    //Methode pour initialiser les jetons progres
    void initialiserJetons();

    friend class VuePlateau;

public:
    // ----- Constructeur et destructeur à définir !!! -----
    Plateau();
    ~Plateau() = default;
    Plateau(const Plateau &p) = delete;
    Plateau &operator=(const Plateau &p) = default;
    struct disposition { // comment on pourrait l'organiser ? 3 dispositions en fonction de l'AGE ? if (age == 1) disposition[1];
        std::vector<Carte*> cartes;
        int nb_carte;
    };
// Accesseurs
    std::vector<Jeton_Progres*> getJetonsProgresdefausse() const {return jeton_prog_defausse; }
    std::vector<Jeton_Progres*> getJetonsProgresEnJeu() const {return jeton_prog_en_jeu; }
    std::vector<Jeton_Progres*> getJetonsProgresTotal() const {return jeton_prog_total; }
    Plateau_militaire* getPlateauMilitaire() const {return plateau_militaire; }
    std::vector<Carte*> getDefausse() const { return defausse; }
    std::vector<Merveille*> getListe_merveilles() const {return liste_merveilles;}

    
// Methodes
    // Méthode pour afficher les cartes d'un âge
    void afficherCartes(AGE age) const;

    void retirer_jeton_defausse(Jeton_Progres* j);
    void retirer_carte_defausse(Carte* c);

private:
    void distribuer_set_4_merveilles(std::vector<Merveille*> set_a_distribuer, Joueur* joueur_1er_choix);
public:
    void distribuer_merveille(Joueur* premier_joueur);
    
    bool end_age(AGE age); //Renvoie true quand l'age x est finit (plus de carte dans le vecteur cartes_age_x)

    // Getter for age
    AGE getAge() const {
        return age;
    }

    // Getter cartes_age_I
    std::vector<Carte*> getCartesAgeI() const {
        return cartes_age_I;
    }

    // Getter cartes_age_II
    std::vector<Carte*> getCartesAgeII() const {
        return cartes_age_II;
    }

    // Getter cartes_age_III
    std::vector<Carte*> getCartesAgeIII() const {
        return cartes_age_III;
    }

    void retirer_carte(AGE age, Carte* carte);

    void ajouter_carte_defausse(Carte* c);

    void retirerJetonProgres(Jeton_Progres* jeton);

    void afficherDefausse() const;


};
