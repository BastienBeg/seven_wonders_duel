#include "joueur.h"

class Exception;
//-----------------------------------------

Joueur::Joueur(int id, string n) : id_joueur(id), nom(n), pointsVictoire(0), ressource(new Ressource()), piece(7), adversaire(nullptr) {
    // Initialisation des ressources
    ressource->setBois(0);
    ressource->setFer(0);
    ressource->setArgile(0);
    ressource->setVerre(0);
    ressource->setPapyrus(0);
}

Joueur::~Joueur() {
    delete ressource; // Libérez la mémoire allouée à ressource
    for (auto& carte : cartes) {
        delete carte; // Assurez-vous de libérer toutes les cartes
    }
    for (auto& merveille : merveilles_construites) {
        delete merveille; // Assurez-vous de libérer toutes les merveilles construites
    }
    // rajouter pour les pièces aussi
}

void Joueur::ajouter_points_victoires(int points){
    pointsVictoire+= points;
}

void Joueur::ajouterCarte(Carte* carte) {
    cartes.push_back(carte);
}

void Joueur::ajouterSymbolScientifique(Symbol_Scientifique symbol) {
    symbol_scientifique.push_back(symbol);
}

void Joueur::ajouter_jeton_progres(Jeton_Progres* jeton) {
   jetons_progres_acquis.push_back(jeton);
}

void Joueur::ajouter_ressources_partielles(Ressource* ressource){
    ressources_partielles.push_back(ressource);
}

void Joueur::retirer_carte(Carte* c) {
    auto it = std::find(cartes.begin(), cartes.end(), c);
    if (it != getCartes().end())
    {
        cartes.erase(it);
    }
    else
    {
        throw Exception("carte pas dans la main du joueur");
    }
        
}

void Joueur::ajouterChainage(Chainage c) {
    chainage.push_back(c);
}

bool Joueur::possede_symbole_scientifique(Symbol_Scientifique symbole) const {
    for (const Symbol_Scientifique& sym : symbol_scientifique) {
        if (sym == symbole) {
            return true;
        }
    }
    return false;
}

bool Joueur::possede_jeton_progres(string nomJeton) const {
    for (Jeton_Progres* j : jetons_progres_acquis) {
        if (j->getNom() == nomJeton) {
            return true;
        }
    }
    return false;
}


int Joueur::nbCarteType(Type_Carte type)const{
    int count = 0;
    for (Carte* carte : cartes) {
        switch (type) {
        case Type_Carte::MILITAIRE:
            if (dynamic_cast<Carte_militaire*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::SCIENTIFIQUE:
            if (dynamic_cast<Carte_scientifique*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::CIVIL:
            if (dynamic_cast<Carte_civil*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::COMMERCIAL:
            if (dynamic_cast<Carte_commerciales*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::RESSOURCES_MAN:
            if (dynamic_cast<Carte_manufacture*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::RESSOURCES_PRE:
            if (dynamic_cast<Carte_matiere_premiere*>(carte) != nullptr) {
                count++;
            }
            break;
        case Type_Carte::RESSOURCES:
            if (dynamic_cast<Carte_matiere_premiere*>(carte) != nullptr||dynamic_cast<Carte_manufacture*>(carte) != nullptr) {
                count++;
            }
            break;

        case Type_Carte::GUILDE:
            if (dynamic_cast<Carte_guilde*>(carte) != nullptr) {
                count++;
            }
            break;

        case Type_Carte::MERVEILLE:
            count=merveilles_construites.size();
            break;

        case Type_Carte::AUCUN:
            count=piece/3;
            break;
        }
    }
    return count;
}


void Joueur::piece_de_defausse(Carte* c){
    int nb_carte_jaune = nbCarteType(Type_Carte::COMMERCIAL);
    setPiece(getPiece() + 2 + nb_carte_jaune);
}

void Joueur::ajouter_merveille(Merveille* m){
    merveilles_construites.push_back(m);
}

void Joueur::distribuer_merveille(Merveille* m){
    merveilles_possede.push_back(m);
}

bool Joueur::construire_merveille_console(){
    // Verifier qu'il n'y a pas deja 7 merveilles construites
    size_t nb_merveille_construite_total = getMerveillesConstruites().size() + getAdversaire()->getMerveillesConstruites().size();
    if (nb_merveille_construite_total < 7){
        // Verifier qu'il n'a pas deja construit ses 4 merveilles
        if(getMerveillesConstruites().size() < 4){
            // Afficher les merveilles qu'il a pas construit dans la console et lui en faire choisir une 

            std::vector<Merveille*> merveilles_construites_tmp = getMerveillesConstruites();
            std::vector<Merveille*> merveilles_possede_tmp = getMerveillesPossede();
            std::vector<Merveille*> merveilles_non_construites;

            // On trie les copies vecteur temporaires pour pouvoir utiliser "set difference"
            std::sort(merveilles_construites_tmp.begin(), merveilles_construites_tmp.end());
            std::sort(merveilles_possede_tmp.begin(), merveilles_possede_tmp.end());

            // set difference va comparer les deu vecteurs et ajouter dans le troisième les elements qui different
            std::set_difference(merveilles_possede_tmp.begin(), merveilles_possede_tmp.end(),
                merveilles_construites_tmp.begin(), merveilles_construites_tmp.end(),
                std::inserter(merveilles_non_construites, merveilles_non_construites.end()));
            
            // Maintenant qu'on a les merveilles non construite, on les affiches dans la console pour l'utilisateur 
            for (size_t i = 0; i < merveilles_non_construites.size(); ++i) {
                std::cout << i + 1 << ". \n" << *merveilles_non_construites[i] << std::endl;
            }

            // On lui demande d'en choisir une
            int choix;
            std::cout << getNom()<<", choisissez une merveille (1-" << merveilles_non_construites.size() <<"): ";
            std::cin >> choix;
            while (choix < 1 || choix > merveilles_non_construites.size() ) {
                std::cout << "Choix invalide. Veuillez choisir une merveille disponible (1-" << merveilles_non_construites.size() <<"): ";
                std::cin >> choix;
            }
            Merveille* merveille_choisie = merveilles_non_construites[choix - 1];

            // Appeler la methode de construction sur la merveille choisis, et on renvoie le resultat de la methode
            // Si il a bien pu la constuire la verif est a true, sinon false
            bool verif_construction = merveille_choisie->construireMerveille(this);
            //cout << "verif_construction : " << verif_construction << endl;
            return verif_construction;
        } 
        else{
            return false;
        }
    }
    else {
        return false;
    }
}
bool Joueur::construire_merveille_gui(Merveille* merveille_choisie){
    // Verifier qu'il n'y a pas deja 7 merveilles construites
    size_t nb_merveille_construite_total = getMerveillesConstruites().size() + getAdversaire()->getMerveillesConstruites().size();
    if (nb_merveille_construite_total < 7){
        // Verifier qu'il n'a pas deja construit ses 4 merveilles
        if(getMerveillesConstruites().size() < 4){
            // Appeler la methode de construction sur la merveille choisis, et on renvoie le resultat de la methode
            // Si il a bien pu la constuire la verif est a true, sinon false
            Ressource* rTemp1 = nullptr;
            Ressource* rTemp2 = nullptr;
            if (possede_jeton_progres("Architecture")){
                Ressource* rTemp1 = new Ressource(1, 1, 1, 1, 1);
                Ressource* rTemp2 = new Ressource(1, 1, 1, 1, 1);
                this->ajouter_ressources_partielles(rTemp1);
                this->ajouter_ressources_partielles(rTemp2);
            }
            bool verif_construction = merveille_choisie->construireMerveille(this);
            if (possede_jeton_progres("Architecture")) {
                ressources_partielles.pop_back();
                ressources_partielles.pop_back();
                delete rTemp1;
                delete rTemp2;
            }
            //cout << "verif_construction : " << verif_construction << endl;
            return verif_construction;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}

//Set Adversaire
void Joueur::setAdversaire(Joueur* adv) {
    adversaire = adv;
}

void Joueur::setPeutRejouer(bool rejoue){
    peut_rejouer = rejoue;
}

std::vector<Merveille*> Joueur::getPlayableWonders() {
    std::vector<Merveille*> playableWonders;
    std::vector<Merveille*> allWonders = this->getMerveillesPossede();
    std::vector<Merveille*> builtWonders = this->getMerveillesConstruites();

    for (auto& wonder : allWonders) {
        if (std::find(builtWonders.begin(), builtWonders.end(), wonder) == builtWonders.end()) {
            playableWonders.push_back(wonder);
        }
    }

    return playableWonders;
}

bool Joueur::estConstruite(const Merveille* merveille) const {
    for (const auto& m : merveilles_construites) {
        if (m == merveille) {
            return true;
        }
    }
    return false;
}

void Joueur::retirerMerveille(Merveille* merveille) {
    auto it = std::find(merveilles_possede.begin(), merveilles_possede.end(), merveille);
    if (it != merveilles_possede.end()) {
        merveilles_possede.erase(it);
    }
}

void Joueur::retirerChainage(Chainage c){
    auto it = std::find(chainage.begin(), chainage.end(), c);
    if (it != chainage.end()) {
        chainage.erase(it);
    }
}
