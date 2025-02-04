#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <iostream>
#include <algorithm>
#include <random>
#include "merveille.h"
#include "partie.h"
#include "joueur.h"
#include "jeton.h"
#include "carte.h"
#include "enum.h"
#include "vueplateau.h"


Bonus_merveille::~Bonus_merveille() {
        delete offre_ressource;
    }

void Bonus_merveille::setOffreRessource(int bois, int fer, int argile, int verre, int papyrus) {
        delete offre_ressource;
        offre_ressource = new Ressource(bois, fer, argile, verre, papyrus);
    }

// Permet de d&clancher le bonus pour attribuer un jeton de la défausse au joueur
void Bonus_merveille::offre_jeton_progres(Joueur* j, VuePlateau* vp) {
	// parcourir les jeton non choisis
    Plateau *plateau = Partie::getInstance().getPlateau();

    // ----- Methode getjetondefausse a def, elle doit renvoyer un vecteur qui contient 
    // les jetons de la defausses -----
    std::vector<Jeton_Progres*> jetons_defausee = plateau->getJetonsProgresdefausse();

    // Mélanger les jetons, mt19937 est un generateur de nombre aléatoire
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(jetons_defausee.begin(), jetons_defausee.end(), g);

    // On prend les trois premiers jeton de la liste melange
    std::vector<Jeton_Progres*> jeton_tirer_au_sort(jetons_defausee.begin(), jetons_defausee.begin() + 3);

    // On affiche les jeton au joueur et on lui demande d'en choisir un
    /*
    std::cout << "Choisissez un jeton de progrès parmi les suivants :" << std::endl;
    for (size_t i = 0; i < jeton_tirer_au_sort.size(); ++i) {
        // ----- Methode getnom a definir !!! -----
        std::cout << i + 1 << ". " << jeton_tirer_au_sort[i]->getNom() << std::endl; 
    }


    int choix;
    std::cin >> choix;

    // On verifie le choix de l'utilisateur, (utilisation de la class exeption ?)
    if (choix < 1 || choix > 3) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }
*/
    Jeton_Progres* jeton_choisis = vp->afficherChoixJeton(jeton_tirer_au_sort);//[choix - 1];
    j->ajouter_jeton_progres(jeton_choisis);


    // On retire le jeton de la défausse pour ne plus pourvoir le recuperer
    plateau->retirer_jeton_defausse(jeton_choisis);
}


// Permet de jouer le bonus de la merveille
void Bonus_merveille::joue_le_bonus(Joueur* j, VuePlateau* vp){
    // vérifie chaque attribut du bonus et les donnes au joueur qui appelle la fonction
    
    //      Offre_ressource : (on attend de modeliser le un parmi plusieur)
    if (getOffreRessource() != nullptr) {
        j->ajouter_ressources_partielles(getOffreRessource());
    }

    //      Bonus piece
    if (bonus_piece > 0){
        j->setPiece(j->getPiece()+bonus_piece);
    }

    // Malus piece
    if (malus_piece > 0){
        Joueur* adverseaire = j->getAdversaire();
        int nb_piece_joueur = adverseaire->getPiece() - malus_piece;
        if (nb_piece_joueur < 0){
            nb_piece_joueur = 0;
        }
        adverseaire->setPiece(nb_piece_joueur);
    }

    // Points de victoire
    if (point_de_victoire > 0){
        j->setPointsVictoire(j->getPointsVictoire()+point_de_victoire);
    }

    // Points militaire

    if (point_militaire > 0){
        Plateau_militaire* plateau_militaire = Partie::getInstance().getPlateau()->getPlateauMilitaire();
        plateau_militaire->deplacement(getPointMilitaire());
    }

    // Supprimer Une carte de l'adversaire
    if (supprime_carte != Couleur::AUCUN){
        // On recupere les cartes de l'adversaire pour pouvoir les parcourir
        std::vector<Carte*> cartes = j->getAdversaire()->getCartes();
        std::vector<Carte*> cartes_supprimable;

        // On ajoute toute les cartes du type qu'on peut supprimer a un vecteur
        for (Carte* carte : cartes) {
            // On utilise le dynamic cast pour verif que la carte est bien de la classe file souhaité
            if (supprime_carte == Couleur::GRIS){
                if(Carte_manufacture* c = dynamic_cast<Carte_manufacture*>(carte)){
                    cartes_supprimable.push_back(c);
                }
            }
            else if (supprime_carte == Couleur::MARRON) {
                if(Carte_matiere_premiere* c = dynamic_cast<Carte_matiere_premiere*>(carte)){
                    cartes_supprimable.push_back(c);
                }
            }
        }
        // On verifie qu'il y a bien des cartes a supprimer puis on propose au joueur d'en choisir une
        if (cartes_supprimable.size() != 0){
           /* std::cout << "Choisissez une carte parmi les suivantes : " << std::endl;
            // tant que l'utilisateur de ne choisi pas de carte valide on lui demande de choisir une carte
            bool verif = false;
            int choix;
            while (verif == false){
                // On parcours les carte de l'adversaire que le joueur peut choisir de retirer en lui donnant le choi d'en prendre une
                for (size_t i = 0; i < cartes_supprimable.size(); i++){
                    std::cout << i + 1 << ". " << cartes_supprimable[i]->getNom() << std::endl;
                }
                std::cin >> choix;

                if (choix < 1 || choix > cartes_supprimable.size()) {
                    std::cout << "Choix invalide." << std::endl;
                }
                else {
                    verif = true;
                }
            }*/
            Carte* carte_choisi = vp->afficherChoixCartes(cartes_supprimable);//cartes_supprimable[choix-1];
            // ----- Faire la methode retirerCarte dans joueur !!! -----
            // La méthode doit placer la carte dans la défausse
            Ressource* ressource = carte_choisi->getRessource_offerte();
            j->getAdversaire()->getRessources()->retirerRessources(*ressource);
            j->getAdversaire()->retirer_carte(carte_choisi);
        }
        else {
            std::cout << "L'adversaire n'a aucune carte de ce type vous ne pouvez pas lui en enlever" << std::endl;
        }
    }

    // Offre jeton :
    if (offre_jeton == true){
        offre_jeton_progres(j, vp);
    }

    // Permet de rejouer le tour
    if (rejouer_tour == true){
        j->setPeutRejouer(true);
    }

    // Permet au joueur de choisir une carte de la defausse et de la construire
    if (choisis_defausse == true) {
        std::vector<Carte*> defausse = Partie::getInstance().getPlateau()->getDefausse();
        /*std::cout << "Cartes disponibles dans la defausse : " << std::endl;
        for (size_t i = 0; i < defausse.size(); ++i) {
            std::cout << i + 1 << ". \n" << *defausse[i] << std::endl;
        }

        // Choi d'une des carte de la defausse
        int choix;
        std::cout << j->getNom()<<", choisissez une des cartes ci-dessus (1-"<< defausse.size() <<"): ";
        std::cin >> choix;
        while (choix < 1 || choix > 4 ) {
            std::cout << "Choix invalide. Veuillez choisir une carte disponible (1-"<< defausse.size() <<"): ";
            std::cin >> choix;
        }*/
        // On ajoute la carte au joueur sans regarder son cout
        // Pour ce faire on lui ajoute 10 de chaques ressources pour qu'il puisse la construire puis on lui enleve
        if (defausse.size() != 0){
            Carte* carte_choisie = vp->afficherChoixCartes(defausse);//defausse[choix - 1];
            Ressource* permet_acheter = new Ressource(10, 10, 10, 10, 10);
            j->getRessources()->ajouterRessources(*permet_acheter);
            carte_choisie->jouer_carte(j);
            j->getRessources()->retirerRessources(*permet_acheter);
            delete permet_acheter;
        }
    }
}

Merveille::~Merveille(){
        delete cout_construction;
        delete bonus;
    }

bool Merveille::construireMerveille(Joueur* j){
    int cout_en_piece = j->getRessources()->calculerCoutTotal(*cout_construction, *j);
    if (j->getPiece() >= cout_en_piece) {
        j->setPiece(j->getPiece()-cout_en_piece);
        j->ajouter_merveille(this);
        return true;
    }
    else{
        std::cout << "Vous n'avez pas assez de piece pour construire cette merveille" << std::endl<< std::endl;
        return false;
    }

}

std::ostream& operator<<(std::ostream& os, const Merveille& merveille) {
        os<< "-------------------------\n";
        os << "/ "<< merveille.getNom() << "\n";
        os << "/ Cout de construction "<< *merveille.getCout() << "\n";
        if (merveille.getBonus()->getBonusPiece()>0){
            os << "/ "<< "Bonus de piece : " << merveille.getBonus()->getBonusPiece() << "\n";
        }
        if (merveille.getBonus()->getMalusPiece() > 0){
            os << "/ "<< "Malus de piece : " << merveille.getBonus()->getMalusPiece() << "\n";
        }
        if (merveille.getBonus()->getPointDeVictoire() > 0){
            os << "/ "<< "Point de victoire : " << merveille.getBonus()->getPointDeVictoire() << "\n";
        }
        if (merveille.getBonus()->getPointMilitaire()>0){
            os << "/ "<< "Point militaire : " <<merveille.getBonus()->getPointMilitaire() << "\n";
        }
        if (merveille.getBonus()->getOffreJeton() == true){
            os << "/ "<< "Offre un jeton progres : " << merveille.getBonus()->getOffreJeton() << "\n";
        }
        if (merveille.getBonus()->getOffreRessource() != nullptr){
            os << "/ "<< "Offre une ressource parmis les suivante : " << *merveille.getBonus()->getOffreRessource() << "\n";
        }
        if (merveille.getBonus()->getSupprimeCarte() == Couleur::MARRON ){
             os << "/ "<< "Permet de supprimer une carte marron de l'adverssaire" << "\n";
        }
        if (merveille.getBonus()->getSupprimeCarte() == Couleur::GRIS ){
             os << "/ "<< "Permet de supprimer une carte gris de l'adverssaire" << "\n";
        }   
        os << "-------------------------\n";
        return os;
    }

std::string Merveille::getCheminImage() const {
    return R"(../../ressources/)" + nom + ".png"; // Génère le chemin de l'image en fonction du nom
}
