#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "ressources.h"
#include "carte.h"
#include "enum.h"
#include "merveille.h"
#include "jeton.h"
#include "exception.h"

// Déclaration avancé

class Merveille;
class Carte;

class Joueur {
private:
    int id_joueur;
    std::string nom;
    int pointsVictoire;
    int pointMilitaire;
    Ressource* ressource;
    std::vector<Jeton_Progres*> jetons_progres_acquis;
    std::vector<Merveille*> merveilles_possede;
    std::vector<Merveille*> merveilles_construites;
    int piece;
    std::vector<Carte*> cartes;
    Joueur* adversaire;
    std::vector<Symbol_Scientifique> symbol_scientifique;
    std::vector<Chainage> chainage;
    // ressources_partielles represente les ressources dit "un parmi plusieur" 
    // soit les cartes qui donnent une ressource parmis plusieurs proposé
    std::vector<Ressource*> ressources_partielles;
    // Flag pour check si le joueur peut rejouer après son tour
    bool peut_rejouer = false;

public:
    Joueur(int id, std::string n);
    ~Joueur();

    // Accesseurs
    std::string getNom() const { return nom; }
    int getPointsVictoire() const { return pointsVictoire; }
    // getRessource n'est pas const car on doit pouvoir appeler la methode de ressource qui la modifie
    Ressource* getRessources() { return ressource; }
    int getPiece() const { return piece; }
    Joueur* getAdversaire() { return adversaire; }
    const std::vector<Carte*>& getCartes() const { return cartes; }
    const std::vector<Chainage>& getChainage() const { return chainage; }
    const std::vector<Symbol_Scientifique>& getSymbolScientifique() const { return symbol_scientifique; }
    const std::vector<Merveille*>& getMerveillesConstruites() const { return merveilles_construites; }
    const std::vector<Merveille*>& getMerveillesPossede() const { return merveilles_possede; }
    std::vector<Ressource*>& getRessourcesPartielles() { return ressources_partielles; }
    const bool getPeutRejouer() const { return peut_rejouer; }
    const std::vector<Jeton_Progres*>& getJetonsAcqui() {return jetons_progres_acquis;}

    void setPointsVictoire(int p) {pointsVictoire = p;}
    void setPiece(int p) {piece = p;}
    void ajouter_merveille(Merveille* m);
    void distribuer_merveille(Merveille* m);
    void setAdversaire(Joueur* adv);
    void setPeutRejouer(bool peuu_rejouer);
    void setNom(std::string& s ){nom = s;}
    // Méthodes
    void ajouter_points_victoires(int points);
    void ajouterCarte(Carte* carte);
    void ajouterChainage(Chainage chainage);
    void ajouter_jeton_progres(Jeton_Progres* jeton);
    void ajouter_ressources_partielles(Ressource* ressource);
    void retirer_carte(Carte* c);
    void retirerMerveille(Merveille* merveille);
    void retirerChainage(Chainage c);
    void ajouter_piece(int prix) { piece += prix; };
    void ajouterSymbolScientifique(Symbol_Scientifique symbol);
    bool possede_symbole_scientifique(Symbol_Scientifique symbole) const;
    bool possede_jeton_progres(string nomJeton) const;
    // S'occupe uniquement de donner les piece lors de la defausse
    void piece_de_defausse(Carte* c);
    int nbCarteType(Type_Carte type)const;
    // Permet au joueur qui appelle la methode de choisir un merveille parmi celles qu'il n'a pas 
    // construite, pour la construire si il a les ressources
    bool construire_merveille_console();
    bool construire_merveille_gui(Merveille* merveille_choisie);
    bool estConstruite(const Merveille* merveille) const;
    std::vector<Merveille*> getPlayableWonders();
};

