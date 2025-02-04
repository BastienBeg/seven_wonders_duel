#pragma once
#include <iostream>
#include <vector>
#include "joueur.h"
#include "carte.h"
#include "plateau.h"

// Déclaration avance
class Merveille;
class Joueur;
class Carte;
enum class AGE;
class Plateau;
class Plateau_militaire;

class Partie {
private:
	// attributs priv�e
	Joueur* j1;
	Joueur* j2;
    Joueur* actuel; //Joueur dont c'est le tour (baton de parole)
	//  id partie � faire plus tard si syst�me de sauvegarde
    Plateau* plateau; // Composition entre plateau et partie
    bool victoire_militaire;
    bool victoire_scientifique;
    void reset();

public:
    Partie();
    ~Partie();
    Partie(const Partie& p) = delete;
    Partie& operator=(const Partie& p) = delete;
	[[nodiscard]] Plateau* getPlateau() const {return plateau;}
	static Partie& getInstance();
    static void resetInstance();
	void nouvelle_partie(Partie* p);
	void fin_de_partie(Partie* p);
    int calculer_point( Joueur* j) const;
	// Calcule les points de victoire militaire en fin de partie
	int calcul_point_victoire_militaire(const Joueur* j) const;

    void jouer_tour();
    void changement_joueur();

    void boucle_partie();

    Joueur*& getActuel() {return actuel;}
    Joueur* getJ1() {return j1;}
    Joueur* getJ2() {return j2;}
    bool getVictoireScientifique() const { return victoire_scientifique; }
    bool getVictoireMilitaire() const { return victoire_militaire; }

    void setActuel(Joueur* j) { actuel = j; }
    void setVictoireScientifique () {victoire_scientifique = true; } 
    void setVictoireMilitaire () {victoire_militaire = true; } 
};
