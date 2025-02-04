#pragma once

#include <iostream>
#include "joueur.h"
class Joueur;
class Carte;
class Ressource {
public:
    Ressource(int b = 0, int f = 0, int a = 0, int v = 0, int p = 0) : bois(b), fer(f), argile(a), verre(v), papyrus(p) {}
    ~Ressource() = default;
    Ressource(const Ressource& r) = default;
    Ressource& operator=(const Ressource& r) = default;

    // méthode pour accéder à chaque ressource
    inline int getBois() const { return bois; }
    inline int getFer() const { return fer; }
    inline int getArgile() const { return argile; }
    inline int getVerre() const { return verre; }
    inline int getPapyrus() const { return papyrus; }

    // Méthode pour associer une valeur à chaque ressources
    inline void setBois(int b) { bois = b; }
    inline void setFer(int f) { fer = f; }
    inline void setArgile(int a) { argile = a; }
    inline void setVerre(int v) { verre = v; }
    inline void setPapyrus(int p) { papyrus = p; }

    void ajouterRessources(const Ressource& gain);
    void retirerRessources(const Ressource& perte);
        // Cette methode doit etre appele sur l'objet ressource du joueur qui veut acheter la carte ou la merveille
        // le cout à payer correspond a l'objet ressource qui represente le cout de la carte/merveille
        // On donne la possibilité de donner une carte pour gérer le cas du chainage
    int calculerCoutTotal(const Ressource& cout_a_payer, Joueur& j, Carte* c = nullptr) const;


    friend inline std::ostream& operator<<(std::ostream& os, const Ressource& res) {
        os << "B: " << res.bois << ", "
           << "F: " << res.fer << ", "
           << "A: " << res.argile << ", "
           << "V: " << res.verre << ", "
           << "P: " << res.papyrus;
        return os;
    }

private:
    int bois, fer, argile, verre, papyrus;
};


