#include "partie.h"
#include "joueur.h"
#include "plateau.h"
#include "carte.h"
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

Partie::Partie() {
    j1 = new Joueur(1,"id1");
    j2 = new Joueur(2,"id2");
    j1->setAdversaire(j2);
    j2->setAdversaire(j1);
    std::vector<Joueur*> joueurs = { j1, j2 };
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(joueurs.begin(), joueurs.end(), g);
    actuel = joueurs[0];

    // Initialisation du plateau
    plateau = new Plateau();


    // Vous pouvez ajouter d'autres initialisations ici si nécessaire
}

Partie::~Partie() {
    delete j1;
    delete j2;
    delete plateau;
}

Partie& Partie::getInstance() {
    static Partie instance;
    return instance;
}

void Partie::resetInstance() {
    Partie& instance = getInstance();
    instance.reset();
}

void Partie::reset() {
    // Supprimez les anciens objets
    delete j1;
    delete j2;
    delete plateau;

    // Réinitialisez les attributs de l'instance
    j1 = new Joueur(1, "id1");
    j2 = new Joueur(2, "id2");
    j1->setAdversaire(j2);
    j2->setAdversaire(j1);
    std::vector<Joueur*> joueurs = { j1, j2 };
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(joueurs.begin(), joueurs.end(), g);
    actuel = joueurs[0];

    // Réinitialisation du plateau
    plateau = new Plateau();
}

void Partie::nouvelle_partie(Partie* p){
    /*
    Algo :
    * random pour attribuer le joueur actuel (baton de parole)
    * distribution_merveille()
    * for i=1 in range(3) :  //3 ages
    * while(plateau.end_age(AGE age) != True) :
    *  jouer_tour(Joueur* actuel, AGE age)
    *Calcul_point()
    *actuel = gagnant
              *Afficher actuel et ses stats
*/
}

void Partie::fin_de_partie(Partie* p){
    //fais dans vue plateau et vue victoire
}

int Partie::calcul_point_victoire_militaire(const Joueur* j) const { // a revoir
    int position = getPlateau()->getPlateauMilitaire()->getPosition();
    if (j == j1)
    {
        if (position >= 1) {
            return 2;
        }
        else if (position >= 3) {
            return 5;
        }
        else if (position >= 6) {
            return 10;
        }
    }
    if (j == j2)
    {
        if (position <= -1) {
            return 2;
        }
        else if (position <= -3) {
            return 5;
        }
        else if (position <= -6) {
            return 10;

        }
    }
    return 0;// Retourne 0 si aucun joueur n'a atteint une victoire militaire
}

int Partie::calculer_point(Joueur* j) const{ // Augustin :a finir, ce serait ptetre mieux de passer un seul joueur en argument t de l'appeler pour chaque joueur

    //on compte les points de vicoire des cartes guildes
    std::vector<Carte*> cartesGuilde;
    for (Carte* carte : j->getCartes()) {
        if (carte->getTypeCarte()==Type_Carte::GUILDE) {
            cartesGuilde.push_back(carte);
        }
    }
    for(Carte* carte : cartesGuilde){
        int nb1=j->nbCarteType(carte->getTypeCarte());
        int nb2=j->getAdversaire()->nbCarteType(carte->getTypeCarte());
        if(nb1>nb2){
            j->ajouter_points_victoires(nb1);
        }else{
            j->ajouter_points_victoires(nb2);
        }
        if (carte->getNom()=="guilde_des_batisseurs"){
            if(j->getMerveillesConstruites().size()>j->getAdversaire()->getMerveillesConstruites().size())
                j->ajouter_points_victoires(j->getMerveillesConstruites().size());
            else{
                j->ajouter_points_victoires(j->getAdversaire()->getMerveillesConstruites().size());
            }
        }
    }

    //on vérifie le jeton mathématique
    for (Jeton_Progres* jeton : j->getJetonsAcqui()){
        if(jeton->getNom()=="Mathematique"){
            j->ajouter_points_victoires(j->getJetonsAcqui().size()*3);
        }
        if(jeton->getNom()=="Philosophie"){
            j->ajouter_points_victoires(7);
        }
    }

    int total_Joueur = calcul_point_victoire_militaire(j) + j->getPointsVictoire() + (j->getPiece() / 3);
    return total_Joueur;
}


void Partie::changement_joueur() {
    if (actuel->getPeutRejouer() == false){
        actuel = actuel->getAdversaire();
    }
    else {
        actuel->setPeutRejouer(false);
    }
}

void Partie::jouer_tour() {
    plateau->afficherCartes(plateau->getAge()); // Display playable cards

    std::cout << "Cartes jouables :" << std::endl;
    int index = 0;
    std::vector<Carte*> cartesJouables;
    if (plateau->getAge() == AGE::AGE1) {
        cout << "Age: 1" << endl;
        for (auto& carte : plateau->getCartesAgeI()) {
            if (carte->estJouable()) {
                std::cout << index << ": " << carte->getNom() <<  std::endl;
                cartesJouables.push_back(carte);
                ++index;
            }
        }
    } else if (plateau->getAge() == AGE::AGE2) {
        cout << "Age: 2" << endl;
        for (auto& carte : plateau->getCartesAgeII()) {
            if (carte->estJouable()) {
                std::cout << index << ": " << carte->getNom() << std::endl;
                cartesJouables.push_back(carte);
                ++index;
            }
        }
    } else if (plateau->getAge()  == AGE::AGE3) {
        for (auto& carte : plateau->getCartesAgeIII()) {
            if (carte->estJouable()) {
                std::cout << index << ": " << carte->getNom() << std::endl;
                cartesJouables.push_back(carte);
                ++index;
            }
        }
    }

    int i=0;
    std::cout << "Joueur 1, merveilles jouables:\n";
    for (auto& wonder : j1->getPlayableWonders()) {
        std::cout <<i<<": "<< wonder->getNom() << "\n";
        ++i;
    }

    std::cout << "Joueur 2, merveilles jouables:\n";
    i=0;
    for (auto& wonder : j2->getPlayableWonders()) {
        std::cout <<i<<": "<< wonder->getNom() << "\n";
        ++i;
    }

    std::cout  << actuel->getNom() << " : Choisissez une carte à jouer (par indice) : " << std::endl;
    int choix;
    std::cin >> choix;

    if (choix < 0 || choix >= cartesJouables.size()) {
        std::cout << "Indice invalide. Veuillez réessayer." << std::endl;
        return;
    }

    std::cout << actuel->getNom() << " : Que voulez-vous faire avec cette carte ? (1) Défausser, (2) Construire, (3) Construire merveille" << std::endl;
    int choix2;
    std::cin >> choix2;

    // Choi de la defausse
    if (choix2 == 1) {
        actuel->piece_de_defausse(cartesJouables[choix]);
        getPlateau()->ajouter_carte_defausse(cartesJouables[choix]);
        cout << "Carte Defaussee !" << endl;
        //On retire la carte du plateau, elle ne sera plus jamais jouable (c'est plus simple comme ça) et on dit qu'elle est detenu
        // On la set detenu pour verifier que la carte du dessus est jouable
        cartesJouables[choix]->setDetenu(true);
        plateau->retirer_carte(plateau->getAge(), cartesJouables[choix]);

    // Choi construction de la carte
    } else if (choix2 == 2) {
        bool test = cartesJouables[choix]->jouer_carte(actuel);
        if (test){
            cout << "Carte Construite !" << endl;
            //On retire la carte du plateau,comme dans la defausse
            cartesJouables[choix]->setDetenu(true);
            plateau->retirer_carte(plateau->getAge(), cartesJouables[choix]);
        }
        else{
            actuel->setPeutRejouer(true);
            std::cout << "Pas assez de ressources/piece pour la construire, veuillez rejouer." << std::endl;
        }

    // Choi construire une merveille avec la carte (on rapelle que la carte ne va pas a la defausse lors de la creation d'une merveille)
    } else if (choix2 == 3) {
        bool test = actuel->construire_merveille_console();
        if(test){
            cout << "Merveille construite" << endl;
            //On retire la carte du plateau,comme dans la defausse
            cartesJouables[choix]->setDetenu(true);
            plateau->retirer_carte(plateau->getAge(), cartesJouables[choix]);
        }
        else {
            actuel->setPeutRejouer(true);
            std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    }
    else {
        actuel->setPeutRejouer(true);
        std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
    }

    changement_joueur();
}

void Partie::boucle_partie() {
    // Distribuer Merveille
    plateau->distribuer_merveille(actuel);
    // Afficher les cartes de l'âge actuel
    plateau->afficherCartes(plateau->getAge());

    // Boucle pour faire toute la partie
    while (!plateau->end_age(AGE::AGE3) && !getVictoireMilitaire() && !getVictoireScientifique()) {
        // Jouer un tour pour chaque joueur
        jouer_tour();
                //  Vérifier si le joueur a atteint une victoire militaire ou scientifique
                /*if (joueur->victoire_militaire() || joueur->victoire_scientifique()) {
                    // Si oui, annoncer le joueur gagnant et sortir de la boucle de la partie
                    std::cout << joueur->getNom() << " a gagné la partie par une victoire "
                              << (joueur->victoire_militaire() ? "militaire" : "scientifique") << "!" << std::endl;
                    return;
                }*/
    }

    // Calculer les points à la fin de l'âge
    int points_j1 = calculer_point(j1);
    int points_j2 = calculer_point(j2);
    // Afficher les points de chaque joueur
    std::cout << "Points de " << j1->getNom() << ": " << points_j1 << std::endl;
    std::cout << "Points de " << j2->getNom() << ": " << points_j2 << std::endl;
    if (getVictoireMilitaire()){
        std::cout << actuel->getNom() << " a gagné la partie par victoire militaire!" << std::endl;
    }
    else if (getVictoireScientifique()){
        std::cout << actuel->getNom() << " a gagné la partie par victoire scientifique!" << std::endl;
    }
    else if (points_j1 > points_j2) {
        std::cout << j1->getNom() << " a gagné la partie!" << std::endl;
    } else if (points_j2 > points_j1) {
        std::cout << j2->getNom() << " a gagné la partie!" << std::endl;
    } else {
        std::cout << "La partie est un match nul!" << std::endl;
    }
}
