#pragma once
#include "game/carte.h" //Changer le include

#include "game/joueur.h" // Make sure this path is correct
#include <iostream>

#include <QApplication>

/*int main() {
    // Create resources for the cards
    Ressource ressource(5, 3, 2, 1, 0);

    // Create various types of cards
    Carte_militaire maCarte("Ecurie", 0, 1, 0, 0, 0, 0, 1, Chainage::FER, Chainage::AUCUN);
    Carte_civil carte_civil("Temple", 0, 0, 0, 0, 0, 0, 3, Chainage::TEMPLE, Chainage::AUCUN);
    Carte_manufacture carte_man("Soufflerie", 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
    Carte_matiere_premiere carte_mat_pre("Scierie", 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);

    // --- Test jouer_carte() ---
    // std::cout<< "Test / Debug" << std::endl;
    // Joueur* j_test = new Joueur(1, "Joueur test");
    // std::cout<< "Creation joueur" << std::endl;
    // carte_civil.jouer_carte(j_test);
    // std::cout<< "FIN ----- Test / Debug" << std::endl;


    // Cartes information, ça affiche toute la carte mtn, on peut aussi demander d'afficher une ressource

    /*std::cout << "infos de la carte: " << "\n" << maCarte << std::endl;
    std::cout << "infos de la carte: " << "\n" << carte_civil << std::endl;
    std::cout << "infos de la carte: " << "\n" << carte_man << std::endl;
     */
/*
    std::cout << "Coût en pièces: " << maCarte.getCoutPiece() << std::endl;
    std::cout << "Ressources nécessaires pour la construction:" << std::endl;
    std::cout << "  Bois: " << maCarte.getCoutConstruction()->getBois() << std::endl;
    std::cout << "  Fer: " << maCarte.getCoutConstruction()->getFer() << std::endl;
    std::cout << "  Argile: " << maCarte.getCoutConstruction()->getArgile() << std::endl;
    std::cout << "  Verre: " << maCarte.getCoutConstruction()->getVerre() << std::endl;
    std::cout << "  Papyrus: " << maCarte.getCoutConstruction()->getPapyrus() << std::endl;
    std::cout << "Chainage offert: " << static_cast<int>(maCarte.getChainageMilOffert()) << std::endl;
    std::cout << "Chainage coût: " << static_cast<int>(maCarte.getChainageMilCout()) << std::endl;
    std::cout << "Verre offert par Soufflerie: " << carte_man.getRessource_offerte()->getVerre() << std::endl;
    std::cout << "Bois offert par la Scierie: " << carte_mat_pre.getRessource_offerte()->getBois() << std::endl;*/

/*

    // Initialiser un joueur
    Joueur joueur1("Player One", 1);

    // Assigner une carte à un joueur
    joueur1.addCard(&maCarte);
    joueur1.addCard(&carte_civil);
    joueur1.addCard(&carte_man);
    joueur1.addCard(&carte_mat_pre);

    // On simule le jeu d'une carte
    maCarte.jouer_carte(joueur1);
    carte_civil.jouer_carte(joueur1);
    carte_man.jouer_carte(joueur1);
    carte_mat_pre.jouer_carte(joueur1);

    // Infos sur le joueur
    std::cout << "Player: " << joueur1.getNom() << std::endl;
    std::cout << "Total victory points: " << joueur1.getPointsVictoire() << std::endl;
    std::cout << "Resources held by the player:" << std::endl;
    std::cout << "  Bois: " << joueur1.getRessources()->getBois() << std::endl;
    std::cout << "  Fer: " << joueur1.getRessources()->getFer() << std::endl;
    std::cout << "  Argile: " << joueur1.getRessources()->getArgile() << std::endl;
    std::cout << "  Verre: " << joueur1.getRessources()->getVerre() << std::endl;
    std::cout << "  Papyrus: " << joueur1.getRessources()->getPapyrus() << std::endl;



    //Plateau plateau;
    //plateau.afficherCartes(AGE::AGE1); // Afficher les cartes de l'âge I

    Partie partie;
    partie.boucle_partie();

    return 0;


} */

#include <QApplication>
#include "vuepartie.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Créer une instance de Partie
    Partie &partie = Partie::getInstance(); // Utiliser l'instance unique

    // Créer une instance de VuePartie
    VuePartie vuePartie(partie);

    vuePartie.showMaximized();

    // Démarrer la boucle d'événements
    return app.exec();
}
