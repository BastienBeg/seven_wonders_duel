#pragma once
#include "carte.h"
#include <algorithm> // Pour std::find
#include "ressources.h"
#include "choixjetondialogue.h"
// -- Carte --

// Constructeur classique
Carte::Carte(std::string n, int piece, int bois, int fer, int argile, int verre, int papyrus, string png)
    : nom(n),
    cout_piece(piece),
    cout_construction(new Ressource(bois, fer, argile, verre, papyrus))
{}

// Constructeur de recopie //Eliot : J'ai modifié, on recopiait sur le même pointeur de ressources //Bastien : Pas de necessité d'un constructeur de recopie ?
Carte::Carte(const std::string& n, const Ressource* r, int p)
    : nom(n), cout_piece(p) {
    if (r != nullptr) {
        cout_construction = new Ressource(*r);  // Crée une copie de l'objet Ressource
    }
    else {
        cout_construction = nullptr;  // Gère le cas où r est nullptr, peut-être mettre une erreur ici? 
    }
}

// Destructeur virtuel
Carte::~Carte() {
    delete cout_construction; //Pas sur pour le & dans le delete // effctivement, pas besoin 
}

// Accesseurs
std::string Carte::getCheminImage() const {
       return R"(../../ressources/)" + nom + ".png";

}

//methode verification du cout de construction
//les return sont temporaire il faut finir cout_construction
int Carte::cout(Joueur* j, Carte* c) {
    return j->getRessources()->calculerCoutTotal(*c->getCoutConstruction(), *j, c);
}

void Carte::afficherFils() const {
    for (const auto& carte : fils) {
        //si pas detenu : afficher nom
        if (!carte->detenu) {
            std::cout << carte->getNom() << ", ";
        }
    }
}


// -- Carte militaire --

bool Carte_militaire::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        if (joueur_qui_joue_carte->possede_jeton_progres("Strategie")) {
            Partie::getInstance().getPlateau()->getPlateauMilitaire()->deplacement(point_militaire + 1);
        }
        else {
            Partie::getInstance().getPlateau()->getPlateauMilitaire()->deplacement(point_militaire);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageMilOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageMilOffert());
        }
        return true;
    }
    else{
        return false;
    }
}


// Accesseurs
Chainage Carte_militaire::getChainageMilOffert() const { return chainage_offert; }

Chainage Carte_militaire::getChainageMilCout() const { return chainage_cout; }

Type_Carte Carte_militaire::getTypeCarte()const { return Type_Carte::MILITAIRE; }

// -- Carte Ressource --


// Accesseurs
Ressource* Carte_ressource::getRessource_offerte() {
    return ressource_offerte;
}

Type_Carte Carte_manufacture::getTypeCarte()const { return Type_Carte::RESSOURCES_MAN; }
Type_Carte Carte_matiere_premiere::getTypeCarte()const { return Type_Carte::RESSOURCES_PRE; }



Carte_ressource::Carte_ressource(string n, int piece, int bois, int fer, int argile, int verre, int papyrus,
        int bois_offert, int fer_offert, int argile_offert, int verre_offert, int papyrus_offert, string png ="") :
        Carte(n, piece, bois, fer, argile, verre, papyrus, png),
        ressource_offerte(new Ressource(bois_offert, fer_offert, argile_offert, verre_offert, papyrus_offert)) {}

string Carte_ressource::details() const {
        stringstream ss;
        ss << Carte::details();
        ss << "/ " << "Type: Ressource" << "\n";
        if (ressource_offerte) {
            ss << "/ " << *ressource_offerte << "\n";
        }
        return ss.str();
    }

// -- Carte manufacture --


bool Carte_manufacture::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()){
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        joueur_qui_joue_carte->getRessources()->ajouterRessources(*ressource_offerte);
        return true;
    }
    else{
        return false;
    }
}

// -- Carte matière_première --

bool Carte_matiere_premiere::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()){
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        joueur_qui_joue_carte->getRessources()->ajouterRessources(*ressource_offerte);
        return true;
    }
    return false;
}

// -- Carte commerciales --


//Accesseurs
int Carte_commerciales::getPointsVictoire() const {
    return points_victoire;
}
Chainage Carte_commerciales::getChainageOffert() const {
    return chainage_offert;
}
Chainage Carte_commerciales::getChainageCout() const {
    return chainage_cout;
}


// bool Carte_commerciales::jouer_carte(Joueur* joueur_qui_joue_carte) {}

//Accesseurs des differents type de cartes commerciales
int Carte_commerciales_piece::getPiece() const { return pieces; }
Ressource* Carte_commerciales_prix::getDiscount() const { return discount; }
Ressource* Carte_commerciales_ressources::getRessource() const { return ressource; }


//jouer_carte pour les type de cartes commerciales

bool Carte_commerciales_piece::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()){
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageOffert());
        }
        joueur_qui_joue_carte->ajouter_piece(pieces);
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        return true;
    }
    else{
        return false;
    }
}

bool Carte_commerciales_prix::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageOffert());
        }
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        return true;
    }
    else{
        return false;
    }
}

bool Carte_commerciales_ressources::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageOffert());
        }
        joueur_qui_joue_carte->ajouter_ressources_partielles(getRessource());
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        return true;
    }
    else{
        return false;
    }
}

bool Carte_commerciales_bonus::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageOffert());
        }
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        joueur_qui_joue_carte->ajouter_piece(joueur_qui_joue_carte->nbCarteType(this->type));
        return true;
    }
    else {
        return false;
    }
}

Type_Carte Carte_commerciales_bonus::getTypeCarte() const{
    return type;
}

// -- Carte civil --

bool Carte_civil::jouer_carte(Joueur* joueur_qui_joue_carte) {
    Ressource* rTemp1 = nullptr;
    Ressource* rTemp2 = nullptr;
    if (joueur_qui_joue_carte->possede_jeton_progres("Maconnerie")) {
        Ressource* rTemp1 = new Ressource(1, 1, 1, 1, 1);
        Ressource* rTemp2 = new Ressource(1, 1, 1, 1, 1);
        joueur_qui_joue_carte->ajouter_ressources_partielles(rTemp1);
        joueur_qui_joue_carte->ajouter_ressources_partielles(rTemp2);

    }
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageCivOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageCivOffert());
        }
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        if (joueur_qui_joue_carte->possede_jeton_progres("Maconnerie")) {
            joueur_qui_joue_carte->getRessourcesPartielles().pop_back();
            joueur_qui_joue_carte->getRessourcesPartielles().pop_back();
            delete rTemp1;
            delete rTemp2;
        }
        return true;
    }
    else{
        return false;
    }
}

// Accesseurs
Chainage Carte_civil::getChainageCivOffert() const { return chainage_offert; }

Chainage Carte_civil::getChainageCivCout() const { return chainage_cout; }

Type_Carte Carte_civil::getTypeCarte()const { return Type_Carte::CIVIL; }

// Carte scientifique

bool Carte_scientifique::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
        joueur_qui_joue_carte->ajouter_piece(-prix);
        if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
            joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
        }
        joueur_qui_joue_carte->ajouter_points_victoires(points_victoire);
        joueur_qui_joue_carte->ajouterCarte(this);
        if (getChainageScientifiqueOffert() != Chainage::AUCUN) {
            joueur_qui_joue_carte->ajouterChainage(getChainageScientifiqueOffert());
        }
        if (joueur_qui_joue_carte->possede_symbole_scientifique(symbol_scientifique)) {
            std::vector<Jeton_Progres*> jetons = Partie::getInstance().getPlateau()->getJetonsProgresEnJeu();
            ChoixJetonDialogue choixDialogue(jetons);
            if (choixDialogue.exec() == QDialog::Accepted) {
                Jeton_Progres* jeton_choisi = choixDialogue.getJetonChoisi();
                if (jeton_choisi) {
                    joueur_qui_joue_carte->ajouter_jeton_progres(jeton_choisi);
                    Partie::getInstance().getPlateau()->retirerJetonProgres(jeton_choisi);

                    if (jeton_choisi->getNom() == "Loi") {
                        joueur_qui_joue_carte->ajouterSymbolScientifique(Symbol_Scientifique::BALANCE);
                    } else if (jeton_choisi->getNom() == "Philosophie") {
                        joueur_qui_joue_carte->ajouter_points_victoires(7);
                    } else if (jeton_choisi->getNom() == "Agriculture") {
                        joueur_qui_joue_carte->ajouter_piece(6);
                        joueur_qui_joue_carte->ajouter_points_victoires(4);
                    } else if (jeton_choisi->getNom() == "Urbanisme") {
                        joueur_qui_joue_carte->ajouter_piece(6);
                    } else if (jeton_choisi->getNom() == "Theologie") {
                        std::vector<Merveille*> merveilles = joueur_qui_joue_carte->getMerveillesPossede();
                        for (Merveille* m : merveilles) {
                            m->getBonus()->setRejouerTour(true);
                        }
                    }
                }
            }
        } else {
            joueur_qui_joue_carte->ajouterSymbolScientifique(symbol_scientifique);
        }
        return true;
    } else {
        return false;
    }
}



//Accesseurs
Chainage Carte_scientifique::getChainageScientifiqueOffert() const {
    return chainage_offert;
}
Chainage Carte_scientifique::getChainageScientifiqueCout() const {
    return chainage_cout;
}
Type_Carte Carte_scientifique::getTypeCarte()const { return Type_Carte::SCIENTIFIQUE; }

//Cartes guildes

//Acesseurs
Type_Carte Carte_guilde::getType()const{return type;}
Type_Carte Carte_guilde::getTypeCarte()const { return Type_Carte::GUILDE; }

bool Carte_guilde::jouer_carte(Joueur* joueur_qui_joue_carte) {
    int prix=cout(joueur_qui_joue_carte, this);
    if (prix<=joueur_qui_joue_carte->getPiece()) {
            joueur_qui_joue_carte->ajouter_piece(-prix);
            if (joueur_qui_joue_carte->getAdversaire()->possede_jeton_progres("Economie")) {
                joueur_qui_joue_carte->getAdversaire()->ajouter_piece(prix);
            }
            joueur_qui_joue_carte->ajouterCarte(this);

            if(type!=Type_Carte::AUCUN && type!=Type_Carte::MERVEILLE){
            if(joueur_qui_joue_carte->nbCarteType(type)>joueur_qui_joue_carte->getAdversaire()->nbCarteType(type)){
            joueur_qui_joue_carte->ajouter_piece(joueur_qui_joue_carte->nbCarteType(type));
            }
            else{
                joueur_qui_joue_carte->ajouter_piece(joueur_qui_joue_carte->getAdversaire()->nbCarteType(type));
            }
        }
        return true;
    }
    else{
        return false;
    }

}





//Disposition plateau 
// Méthode pour ajouter une carte fille
void Carte::ajouterFils(Carte* carte) {
    fils.push_back(carte);
}

// Méthode pour retirer une carte fille
void Carte::retirerFils(Carte* carte) {
    auto it = std::find(fils.begin(), fils.end(), carte); //Iterator de carte
    if (it != fils.end()) { //Si It != fils.end() alors find() a trouvé le fils (à utiliser dans jouer carte)
        fils.erase(it);
    }
}

// Méthode pour définir si une carte est cachée
void Carte::setCachee(bool estCachee) {
    cachee = estCachee;
}

// Méthode pour vérifier si une carte est cachée
bool Carte::estCachee() const {
    return cachee; //Accesseur à l'attribut caché
}

// Méthode pour vérifier si une carte est jouable
bool Carte::estJouable() const {
    //On test si ses fils sont detenu, si les deux sont detenu alors la carte est jouable
    for (Carte* carte : fils) {
        if (!carte->detenu) {
            return false;
        }
    }
    return true;
}


