#include "plateau.h"
#include "joueur.h"
#include "partie.h"
#include "cartes_data.h" // Inclure le fichier des données de cartes
#include <algorithm>
#include <random>



void Plateau_militaire::test_victoire_militaire(const Plateau_militaire& p)const {
    if (position >= -9)
    {
        Partie::getInstance().fin_de_partie(&Partie::getInstance());// fonction victoire pour associer la victoire au joueur ?
    }
    if (position >= 9)
    {
        Partie::getInstance().fin_de_partie(&Partie::getInstance());// fonction victoire pour associer la victoire au joueur ?
    }

}

void Plateau_militaire::deplacement(int force) {
    int coef;
    if(Partie::getInstance().getActuel() == Partie::getInstance().getJ1()){
        coef = 1;
        cout<<"j1 avance"<<endl;
    }
    else{
        coef = -1;
        cout<<"j2 avance"<<endl;
    }
    int deplacement_pion = coef*force;
    position = position + deplacement_pion; // Ajoute la force militaire à la position actuelle
    // Limite la position pour ne pas dépasser les extrémités de la piste
    if (position > 9) {
        position = 9;
    }
    else if (position < -9){
        position = -9;
    }
    std::cout<< "position : "<< position<< "malus piece : " << malus_piece[1]<< std::endl;
    Joueur* joueur_qui_perd = nullptr;
    // gestion des malus de pièces via le plateau militaire
    if (position < -5 && malus_piece[0] == false ){
        malus_piece[0] = true;
        joueur_qui_perd = Partie::getInstance().getJ1();
        joueur_qui_perd -> setPiece(joueur_qui_perd->getPiece() - 5);
    }
    else if (position < -2 && malus_piece[1] == false){
        std::cout<< "Plateau militaire" << std::endl;
        malus_piece[1] = true;
        joueur_qui_perd = Partie::getInstance().getJ1();
        joueur_qui_perd -> setPiece(joueur_qui_perd->getPiece() - 2);
    }
    else if (position > 2 && malus_piece[2] == false) {
        malus_piece[2] = true;
        joueur_qui_perd = Partie::getInstance().getJ2();
        joueur_qui_perd -> setPiece(joueur_qui_perd->getPiece() - 2);
    }
    else if (position > 5 && malus_piece[3] == false) {
        malus_piece[3] = true;
        joueur_qui_perd = Partie::getInstance().getJ2();
        joueur_qui_perd -> setPiece(joueur_qui_perd->getPiece() - 5);
    }
    if (joueur_qui_perd != nullptr){
        if (joueur_qui_perd->getPiece() < 0){
            joueur_qui_perd->setPiece(0);
        }
    }
}

void Plateau::initialiserCartes() {
    cartes_age_I = initialiserCartesAgeI();
    cartes_age_II = initialiserCartesAgeII();
    cartes_age_III = initialiserCartesAgeIII();
    carte_invisible = initcarte_invisible();
}

void Plateau::initialiserJetons() {
    jeton_prog_total = initialiserJetonProgres();

    jeton_prog_en_jeu.push_back(jeton_prog_total[1]);
    jeton_prog_en_jeu.push_back(jeton_prog_total[2]);
    jeton_prog_en_jeu.push_back(jeton_prog_total[3]);
    jeton_prog_en_jeu.push_back(jeton_prog_total[4]);
    jeton_prog_en_jeu.push_back(jeton_prog_total[5]);

    jeton_prog_defausse.push_back(jeton_prog_total[6]);
    jeton_prog_defausse.push_back(jeton_prog_total[7]);
    jeton_prog_defausse.push_back(jeton_prog_total[8]);
    jeton_prog_defausse.push_back(jeton_prog_total[9]);
    jeton_prog_defausse.push_back(jeton_prog_total[10]);
}

void Plateau::initialiserMerveilles(){
    liste_merveilles = initialiserMerveillesData();
}

Plateau::Plateau() {
    initialiserCartes();
    initialiserMerveilles();
    initialiserJetons();
    age = AGE::AGE1;
    plateau_militaire = new Plateau_militaire();
}

void Plateau::afficherCartes(AGE age) const {
    const std::vector<Carte*>* cartes = nullptr;
    if (age == AGE::AGE1) {
        cartes = &cartes_age_I;
    } else if (age == AGE::AGE2) {
        cartes = &cartes_age_II;
    } else if (age == AGE::AGE3) {
        cartes = &cartes_age_III;
    }

    if (cartes) {
        for (const auto& carte : *cartes) {
            std::cout << *carte << std::endl;
        }
    } else {
        std::cout << "Âge invalide!" << std::endl;   //Faire une exception
    }
}


void Plateau::retirer_jeton_defausse(Jeton_Progres* j){
    auto it = std::find(jeton_prog_defausse.begin(), jeton_prog_defausse.end(), j);
    if (it != jeton_prog_defausse.end()){
        jeton_prog_defausse.erase(it);
    }
    else{
        throw Exception("Le jeton a retirer de la defausse n'est pas dans la defausse");
    }
}
    
void Plateau::retirer_carte_defausse(Carte* c){   
    auto it = std::find(defausse.begin(), defausse.end(), c);
    if (it != defausse.end()){
        defausse.erase(it);
    }
    else{
        throw Exception("La carte a retirer de la defausse n'est pas dans la defausse");
    }
}

void Plateau::distribuer_set_4_merveilles(std::vector<Merveille*> set_a_distribuer, Joueur* joueur_1er_choix){
    if (set_a_distribuer.size() != 4){
        // exeption ?
        std::cerr << "Erreur : Le set de merveille doit contenir 4 éléments." << std::endl;
    }

    // On affiche les merveilles
    std::cout << "Merveilles disponibles:" << std::endl;
    for (size_t i = 0; i < set_a_distribuer.size(); ++i) {
        std::cout << i + 1 << ". \n" << *set_a_distribuer[i] << std::endl;
    }

    // Choi d'une merveille par le joueur 1
    int choix;
    std::cout << joueur_1er_choix->getNom()<<", choisissez une premiere merveille (1-4): ";
    std::cin >> choix;
    while (choix < 1 || choix > 4 ) {
        std::cout << "Choix invalide. Veuillez choisir une merveille disponible (1-4): ";
        std::cin >> choix;
    }
    // On ajoute la merveille choisis au joueur et on la met a nullptr dans le set pour les futur choi
    Merveille* merveille_choisie = set_a_distribuer[choix - 1];
    joueur_1er_choix->distribuer_merveille(merveille_choisie);
    set_a_distribuer[choix - 1] = nullptr; 

    // le joueur adverse choisit deux merveilles
    Joueur* adversaire = joueur_1er_choix->getAdversaire();
    for (int i = 0; i < 2; ++i) {
        std::cout << adversaire->getNom() <<", choisissez une merveille (1-4): ";
        std::cin >> choix;
        while (choix < 1 || choix > 4 || set_a_distribuer[choix - 1] == nullptr) {
            std::cout << "Choix invalide. Veuillez choisir une merveille disponible (1-4): ";
            std::cin >> choix;
        }
        // On ajoute la merveille choisis au joueur et on la met a nullptr dans le set pour les futur choi
        merveille_choisie = set_a_distribuer[choix - 1];
        adversaire->distribuer_merveille(merveille_choisie);
        set_a_distribuer[choix - 1] = nullptr; 
    }

    // on donne la derniere merveille au premier joueur
    for (Merveille* merveille : set_a_distribuer) {
        if (merveille) {
            merveille_choisie = merveille;
        }
    }
    joueur_1er_choix->distribuer_merveille(merveille_choisie);
}

void Plateau::distribuer_merveille(Joueur* premier_joueur){
    // On melange les 12 merveilles
    std::vector<Merveille*> merveille_a_distribuer = liste_merveilles;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(merveille_a_distribuer.begin(), merveille_a_distribuer.end(), g);

    std::vector<Merveille*> set_1_merveille;
    std::vector<Merveille*> set_2_merveille;
    // On vérif que la liste est assez grande
    if (merveille_a_distribuer.size() >= 8) {
        // On split la liste en 2 set de 4 merveilles
        set_1_merveille.assign(merveille_a_distribuer.begin(), merveille_a_distribuer.begin() + 4);
        set_2_merveille.assign(merveille_a_distribuer.begin() + 4, merveille_a_distribuer.begin() + 8);
    } else {
        // Peut etre utiliser les exeptions ?
        std::cerr << "Erreur : liste_merveilles doit contenir au moins 8 éléments." << std::endl;
    }
    distribuer_set_4_merveilles(set_1_merveille, premier_joueur);
    distribuer_set_4_merveilles(set_2_merveille, premier_joueur->getAdversaire());
}

bool Plateau::end_age(AGE age) {
    if (age == AGE::AGE3) {
        if (cartes_age_III.empty()) {
            return true;
        }
    }
    // Pas sur mais aucune val n'ete retourne
    return false;
}

void Plateau::retirer_carte(AGE age, Carte* carte) {
    auto replace_with_lambda = [this](std::vector<Carte*>& cartes, Carte* carte) {
        auto it = std::find(cartes.begin(), cartes.end(), carte);
        if (it != cartes.end()) {
            *it = carte_invisible;
        }
    };

    auto all_elements_are_lambda = [this](const std::vector<Carte*>& cartes) {
        return std::all_of(cartes.begin(), cartes.end(), [this](Carte* carte) { return carte == carte_invisible; });
    };

    if (age == AGE::AGE1) {
        replace_with_lambda(cartes_age_I, carte);
        // Si toutes les cartes sont des cartes lambda, on passe à l'âge suivant
        if (all_elements_are_lambda(cartes_age_I)) {
            this->age = AGE::AGE2;
        }
    } else if (age == AGE::AGE2) {
        replace_with_lambda(cartes_age_II, carte);
        // Si toutes les cartes sont des cartes lambda, on passe à l'âge suivant
        if (all_elements_are_lambda(cartes_age_II)) {
            this->age = AGE::AGE3;
        }
    } else if (age == AGE::AGE3) {
        replace_with_lambda(cartes_age_III, carte);
        if (all_elements_are_lambda(cartes_age_III)) {
            this->age = AGE::FIN;
        }
    }
}

void Plateau::ajouter_carte_defausse(Carte* c){
    defausse.push_back(c);
}

void Plateau::retirerJetonProgres(Jeton_Progres* jeton) {
    auto it = std::remove(jeton_prog_en_jeu.begin(), jeton_prog_en_jeu.end(), jeton);

    if (it != jeton_prog_en_jeu.end()) {
         Partie::getInstance().getActuel()->ajouter_jeton_progres(jeton);

        jeton_prog_en_jeu.erase(it, jeton_prog_en_jeu.end());
    }
}


void Plateau::afficherDefausse() const {
    if (defausse.empty()) {
        std::cout << "La défausse est vide." << std::endl;
    } else {
        std::cout << "Cartes dans la défausse:" << std::endl;
        for (const auto& carte : defausse) {
            std::cout << *carte << std::endl; // Assurez-vous que l'opérateur << est surchargé pour Carte
        }
    }
}

