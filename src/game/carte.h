#pragma once
#include "enum.h"
#include <iostream>
#include <sstream>
#include <vector>

class Ressource;
class Joueur;

using namespace std;

//CLASSE MERE : CARTE 
class Carte {

protected:
    string pngPath;
    string nom;
    Ressource* cout_construction;
    int cout_piece;

    //Disposition pour le plateau
    bool cachee;
    std::vector<Carte*> fils; //Si fils vide alors la carte est jouable
    bool detenu = false;

    // permet de calculer le cout d'une carte pour un joueur
    int cout(Joueur* j, Carte* c);

public:
    Carte(string n, int piece, int bois, int fer, int argile, int verre, int papyrus, string png);
    // Constructeur surchargé qui prend un objet ressource
    Carte(const std::string& n, const Ressource* r, int p);
    // Destructeur virtuel
    virtual ~Carte(); //On alloue dynamiquement pour les ressources, il faut le modifier pour libérer la mémoire cout_construction

    // Accesseurs
    string getCheminImage() const;
    std::string getNom() const { return nom; }
    Ressource* getCoutConstruction() const { return cout_construction; }
    int getCoutPiece() const { return cout_piece; }
    bool getDetenu() const { return detenu; }
    virtual Ressource* getRessource_offerte(){ return nullptr; };

    // affichage d'une carte dans la console
    virtual string details() const {
        stringstream ss;
        if (cout_construction) {
            ss << &cout_construction << "\n";
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Carte& carte) {
        os << "-------------------------\n";
        os << "/ " << carte.nom << "\n";
        carte.afficherFils();
        os << "/ " << "Coût en pièces: " << carte.cout_piece << "\n";
        if (carte.estCachee()) {
            os << "/ " << "Cette carte est cachée\n";
        }
        if (carte.estJouable()) {
            os << "/ " << "Cette carte est jouable\n";
        } else {
            os << "/ " << "Cette carte n'est pas jouable\n";
        }
        if (!carte.estCachee()) {
            os << "/ " << carte.details(); 
        }
        os << "-------------------------\n";
        return os;
    }

    // Méthode virtuelle pure qui doit être surcharge dans toute les classes filles ! 
    virtual Type_Carte getTypeCarte()const = 0;
    virtual bool jouer_carte(Joueur* joueur_qui_joue_carte) = 0;

    //Disposition pour le plateau
    void ajouterFils(Carte* carte);
    void retirerFils(Carte* carte);
    void setCachee(bool estCachee);
    void setDetenu(bool estDetenu) { this->detenu = estDetenu; }
    bool estCachee() const;
    bool estJouable() const;

    void afficherFils() const;
};



// Classe carte Militaire (Bastien)
class Carte_militaire : public Carte {
    using Carte::Carte;

private:
    int point_militaire;
    Chainage chainage_offert;
    Chainage chainage_cout;

public:
    Carte_militaire(string n, int piece, int bois, int fer, int argile, int verre, int papyrus, int pt_militaire, Chainage offert, Chainage cout,string png) :
        Carte(n, piece, bois, fer, argile, verre, papyrus, png),
        point_militaire(pt_militaire),
        chainage_offert(offert),
        chainage_cout(cout) {}

    Chainage getChainageMilOffert() const;
    Chainage getChainageMilCout() const;

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override;

    string details() const override {
        stringstream ss;
        ss << Carte::details();
        ss <<"/ " << "Type: Militaire" << "\n";
        ss <<"/ " << "P_M: " << point_militaire << "\n";
        ss <<"/ " << "C_O: " << chainage_offert << "\n";
        ss <<"/ " << "C_C: " << chainage_cout << "\n";
        return ss.str();
    }
};


// Class carte civil
class Carte_civil : public Carte {
    using Carte::Carte;

private:
    int points_victoire;
    Chainage chainage_offert;
    Chainage chainage_cout;

public:
    Carte_civil(string n, int piece, int bois, int fer, int argile, int verre, int papyrus, int pt_victoire, Chainage offert, Chainage cout, string png) :
        Carte(n, piece, bois, fer, argile, verre, papyrus, png),
        points_victoire(pt_victoire),
        chainage_offert(offert),
        chainage_cout(cout) {}

    Chainage getChainageCivOffert() const;
    Chainage getChainageCivCout() const;
    int getPointVictoire() { return points_victoire; }

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override;

    string details() const override {
        stringstream ss;
        ss << Carte::details();
        ss << "/ " << "Type: Civil" << "\n";
        ss << "/ " << "Pts Victoire: " << points_victoire << "\n";
        ss << "/ " << "C_O: " << chainage_offert << "\n";
        ss << "/ " << "C_C: " << chainage_cout << "\n";
        return ss.str();
    }
};


// Classe Carte Ressource (classe mère abstraite pour manufacture et matière première)
class Carte_ressource : public Carte {
    using Carte::Carte;

protected:
    Ressource* ressource_offerte;

    // Peut etre pas le bon constructeur
    Carte_ressource(string n, int piece, int bois, int fer, int argile, int verre, int papyrus,
        int bois_offert, int fer_offert, int argile_offert, int verre_offert, int papyrus_offert,string png);
    virtual bool jouer_carte(Joueur* joueur_qui_joue_carte)override = 0;

public:
    Ressource* getRessource_offerte() override;
    string details() const override;
};

// class Carte_manufacture
class Carte_manufacture : public Carte_ressource {
    using Carte_ressource::Carte_ressource;

public:
    Carte_manufacture(string n, int piece, int bois, int fer, int argile, int verre, int papyrus,
        int bois_offert, int fer_offert, int argile_offert, int verre_offert, int papyrus_offert,string png) :
        Carte_ressource(n, piece, bois, fer, argile, verre, papyrus,
            bois_offert, fer_offert, argile_offert, verre_offert, papyrus_offert, png) {}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override;

    string details() const override {
        stringstream ss;
        ss << Carte_ressource::details();  // Appel à la méthode de base pour inclure les informations de base des ressources
        ss << "/ " << "Type: Manufacture" << "\n";
        // Ajouter des détails supplémentaires si nécessaire, par exemple un bonus spécifique à la manufacture
        return ss.str();
    }
};


// class Carte_matiere_premiere
class Carte_matiere_premiere : public Carte_ressource {
    using Carte_ressource::Carte_ressource;

public:
    Carte_matiere_premiere(string n, int piece, int bois, int fer, int argile, int verre, int papyrus,
        int bois_offert, int fer_offert, int argile_offert, int verre_offert, int papyrus_offert,string png) :
        Carte_ressource(n, piece, bois, fer, argile, verre, papyrus,
            bois_offert, fer_offert, argile_offert, verre_offert, papyrus_offert, png) {}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override;
};


//class Carte_Scientifique
class Carte_scientifique : public Carte {
private:
    Symbol_Scientifique symbol_scientifique;
    int points_victoire;
    Chainage chainage_offert;
    Chainage chainage_cout;

public:
    Carte_scientifique(std::string n, int piece, int bois, int fer, int argile, int verre, int papyrus,
                       Symbol_Scientifique symbol, int pts, Chainage offert, Chainage cout,string png)
            : Carte(n, piece, bois, fer, argile, verre, papyrus, png), symbol_scientifique(symbol), points_victoire(pts),
              chainage_offert(offert), chainage_cout(cout) {}
    ~Carte_scientifique() override = default;

    Chainage getChainageScientifiqueOffert() const;
    Chainage getChainageScientifiqueCout() const;

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override;

    string details() const override {
        stringstream ss;
        ss << Carte::details();
        ss << "/ " << "Type: Scientifique" << "\n";
        ss << "/ " << "Symbole: " << symbol_scientifique << "\n";
        ss << "/ " << "Pts Victoire: " << points_victoire << "\n";
        ss << "/ " << "C_O: " << chainage_offert << "\n";
        ss << "/ " << "C_C: " << chainage_cout << "\n";
        return ss.str();
    }
};

//class mere Carte_commerciales --> classes filles piece/prix/ressource/bonus
class Carte_commerciales : public Carte {
protected:
    int points_victoire;
    Chainage chainage_offert;
    Chainage chainage_cout;

public:
    Carte_commerciales(string n, int piece, int bois, int fer, int argile, int verre, int papyrus, int pt_victoire, Chainage offert, Chainage cout, string png) :
            Carte(n, piece, bois, fer, argile, verre, papyrus, png),
            chainage_offert(offert),
            chainage_cout(cout), points_victoire(pt_victoire) {}

    int getPointsVictoire() const;
    Chainage getChainageOffert() const;
    Chainage getChainageCout() const;

    Type_Carte getTypeCarte() const override {
        return Type_Carte::COMMERCIAL;
    }

    string details() const override {
        stringstream ss;
        ss << Carte::details();
        ss << "/ " << "Type: Commerciale" << "\n";
        ss << "/ " << "Pts Victoire: " << points_victoire << "\n";
        ss << "/ " << "C_O: " << chainage_offert << "\n";
        ss << "/ " << "C_C: " << chainage_cout << "\n";
        return ss.str();
    }
};

// Classe pour les cartes commerciales offrante des pieces
class Carte_commerciales_piece : public Carte_commerciales {
private:
    int pieces;
public:
    Carte_commerciales_piece(string n, int piece_offertes, Chainage offert, Chainage cout, string png="", int piece = 0, int bois = 0, int fer = 0, int argile = 0, int verre = 0, int papyrus = 0, int pt_victoire = 0) :
        Carte_commerciales(n, piece, bois, fer, argile, verre, papyrus,pt_victoire,offert,cout, png),
        pieces(piece_offertes) {}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;

    int getPiece() const;
};


// Classe pour les cartes commerciales offrant un discount
class Carte_commerciales_prix : public Carte_commerciales {
private:
    Ressource* discount;
public:
    Carte_commerciales_prix(string n,Ressource* ressource_discount, Chainage offert, Chainage cout, int piece,string png="", int bois = 0, int fer = 0, int argile = 0, int verre = 0, int papyrus = 0, int pt_victoire = 0) :
        Carte_commerciales(n, piece, bois, fer, argile, verre, papyrus, pt_victoire,offert, cout, png),
        discount(ressource_discount){}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;

    Ressource* getDiscount() const;

    Type_Carte getTypeCarte() const override {
        return Type_Carte::COMMERCIAL;
    }


};

// Classe pour les cartes commerciales offant des ressources
class Carte_commerciales_ressources : public Carte_commerciales {
private:
    Ressource* ressource;
public:
    Carte_commerciales_ressources(string n, Ressource* ressource_offertes, Chainage offert, Chainage cout, int piece, int bois, int fer, int argile, int verre, int papyrus, int pt_victoire=0,string png="") :
        Carte_commerciales(n, piece, bois, fer, argile, verre, papyrus, pt_victoire, offert, cout, png),
        ressource(ressource_offertes) {}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte() const override {
        return Type_Carte::COMMERCIAL;
    }

    Ressource* getRessource() const;
};


// Classe pour les cartes commerciales offrant un bonus relatif aux types de cartes
class Carte_commerciales_bonus : public Carte_commerciales {
private:
    Type_Carte type;
public:
    Carte_commerciales_bonus(string n,Type_Carte t, Chainage offert, Chainage cout, int piece, int bois, int fer, int argile, int verre, int papyrus, int pt_victoire, string png) :
        Carte_commerciales(n, piece, bois, fer, argile, verre, papyrus, pt_victoire, offert, cout, png),
        type(t){}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getTypeCarte()const override;
};


// Classe filles pour les cartes guildes
class Carte_guilde:public Carte{
private:
    Type_Carte type;
public:
    Carte_guilde(string n, Type_Carte t,int piece, int bois, int fer, int argile, int verre, int papyrus,string png) :
        Carte(n, piece, bois, fer, argile, verre, papyrus, png),
        type(t){}

    bool jouer_carte(Joueur* joueur_qui_joue_carte) override;
    Type_Carte getType()const;
    Type_Carte getTypeCarte()const override;
};
