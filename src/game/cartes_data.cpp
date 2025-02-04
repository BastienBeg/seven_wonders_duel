#include "cartes_data.h"
#include <algorithm>
#include <random>

std::string getCheminImage(const std::string& nomCarte) {
    return "src/ressources/" + nomCarte + ".png";
}

// Create resources for the cards
Ressource ressource(5, 3, 2, 1, 0);

std::vector<Jeton_Progres*> initialiserJetonProgres() {
    
    std::vector<Jeton_Progres*> Jetons;

    Jeton_Progres* j1 = new Jeton_Progres("Mathematiques");
    Jeton_Progres* j2 = new Jeton_Progres("Philosophie");
    Jeton_Progres* j3 = new Jeton_Progres("Urbanisme");
    Jeton_Progres* j4 = new Jeton_Progres("Maconnerie");
    Jeton_Progres* j5 = new Jeton_Progres("Agriculture");
    Jeton_Progres* j6 = new Jeton_Progres("Strategie");
    Jeton_Progres* j7 = new Jeton_Progres("Theologie");
    Jeton_Progres* j8 = new Jeton_Progres("economie");
    Jeton_Progres* j9 = new Jeton_Progres("Loi");
    Jeton_Progres* j10 = new Jeton_Progres("Architecture");

    Jetons.push_back(j1);
    Jetons.push_back(j2);
    Jetons.push_back(j3);
    Jetons.push_back(j4);
    Jetons.push_back(j5);
    Jetons.push_back(j6);
    Jetons.push_back(j7);
    Jetons.push_back(j8);
    Jetons.push_back(j9);
    Jetons.push_back(j10);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(Jetons.begin(), Jetons.end(), g);

    return Jetons;

    
}

// Fonction pour initialiser les cartes de l'âge I
std::vector<Carte*> initialiserCartesAgeI() {
    std::vector<Carte*> cartes;

    // age1
    Carte* c1 = new Carte_militaire("Caserne", 0, 0, 0, 1, 0, 0, 1, Chainage::EPEE, Chainage::AUCUN, getCheminImage("Caserne"));
    Carte* c2 = new Carte_militaire("tour_de_garde", 0, 0, 0, 0, 0, 0, 1, Chainage::AUCUN, Chainage::AUCUN,"src/ressources/tour_de_garde.png");
    Carte* c3 = new Carte_militaire("Palissade", 2, 0, 0, 0, 0, 0, 1, Chainage::TOUR, Chainage::AUCUN, getCheminImage("Palissade"));
    Carte* c4 = new Carte_militaire("ecurie", 0, 1, 0, 0, 0, 0, 1, Chainage::FER, Chainage::AUCUN, getCheminImage("Écurie"));

    // Cartes Civiles
    Carte* c5 = new Carte_civil("Theatre", 0, 0, 0, 0, 0, 0, 3, Chainage::MASQUE, Chainage::AUCUN, getCheminImage("theatre"));
    Carte* c6 = new Carte_civil("Autel", 0, 0, 0, 0, 0, 0, 3, Chainage::LUNE, Chainage::AUCUN, getCheminImage("autel"));
    Carte* c7 = new Carte_civil("Bains", 0, 0, 1, 0, 0, 0, 3, Chainage::GOUTTE, Chainage::AUCUN, getCheminImage("Bains"));

    // Cartes Matière Première
    Carte* c8 = new Carte_matiere_premiere("Bassin_argileux", 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, getCheminImage("Bassin argileux"));
    Carte* c9 = new Carte_matiere_premiere("Exploitation", 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, getCheminImage("Exploitation"));
    Carte* c10 = new Carte_matiere_premiere("Chantier", 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, getCheminImage("Chantier"));
    Carte* c11 = new Carte_matiere_premiere("Cavite", 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, getCheminImage("Cavité"));
    Carte* c12 = new Carte_matiere_premiere("Gisement", 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, getCheminImage("Gisement"));
    Carte* c13 = new Carte_matiere_premiere("Mine", 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, getCheminImage("Mine"));

    // Cartes Manufacture
    Carte* c14 = new Carte_manufacture("Presse", 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, getCheminImage("presse"));
    Carte* c15 = new Carte_manufacture("Verrerie", 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, getCheminImage("Verrerie"));

    // Cartes Scientifiques
    Carte* c16 = new Carte_scientifique("Scriptorium", 2, 0, 0, 0, 0, 0, Symbol_Scientifique::PLUME, 0, Chainage::LIVRE, Chainage::AUCUN, getCheminImage("Scriptorium"));
    Carte* c17 = new Carte_scientifique("Officine", 2, 0, 0, 0, 0, 0, Symbol_Scientifique::BOL, 0, Chainage::ENGRENAGE, Chainage::AUCUN, getCheminImage("Officine"));
    Carte* c18 = new Carte_scientifique("Atelier", 0, 0, 0, 0, 0, 1, Symbol_Scientifique::COMPAS, 1, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("atelier"));
    Carte* c19 = new Carte_scientifique("Apothicaire", 0, 0, 0, 0, 1, 0, Symbol_Scientifique::ROUE, 1, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Apoticaire"));

    // Cartes commerciales
    Carte* c20 = new Carte_commerciales_piece("Taverne", 4, Chainage::AMPHORE, Chainage::AUCUN, getCheminImage("Taverne"));
    Carte* c21 = new Carte_commerciales_prix("Depot_de_pierre", new Ressource(0, 1, 0, 0, 0), Chainage::AUCUN, Chainage::AUCUN, 3, getCheminImage("Dépôt de pierre"));
    Carte* c22 = new Carte_commerciales_prix("Depot_de_bois", new Ressource(1, 0, 0, 0, 0), Chainage::AUCUN, Chainage::AUCUN, 3, getCheminImage("Dépôt de bois"));
    Carte* c23 = new Carte_commerciales_prix("Depot_argile", new Ressource(0, 0, 1, 0, 0), Chainage::AUCUN, Chainage::AUCUN, 3, getCheminImage("Dépôt d'argile"));

    // Ajouter les cartes au vecteur
    cartes.push_back(c1);
    cartes.push_back(c2);
    cartes.push_back(c3);
    cartes.push_back(c4);
    cartes.push_back(c5);
    cartes.push_back(c6);
    cartes.push_back(c7);
    cartes.push_back(c8);
    cartes.push_back(c9);
    cartes.push_back(c10);
    cartes.push_back(c11);
    cartes.push_back(c12);
    cartes.push_back(c13);
    cartes.push_back(c14);
    cartes.push_back(c15);
    cartes.push_back(c16);
    cartes.push_back(c17);
    cartes.push_back(c18);
    cartes.push_back(c19);
    cartes.push_back(c20);
    cartes.push_back(c21);
    cartes.push_back(c22);
    cartes.push_back(c23);

    // Mélanger les cartes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);

    //On veut 20 cartes pour l'âge 1, on enlève les 3 dernières du vecteur après mélange.
    cartes.resize(20);

    // Attribue les relations de parenté en fonction de leur position après le mélange
    cartes[0]->ajouterFils(cartes[2]);
    cartes[0]->ajouterFils(cartes[3]);
    cartes[1]->ajouterFils(cartes[3]);
    cartes[1]->ajouterFils(cartes[4]);
    cartes[2]->ajouterFils(cartes[5]);
    cartes[2]->ajouterFils(cartes[6]);
    cartes[3]->ajouterFils(cartes[6]);
    cartes[3]->ajouterFils(cartes[7]);
    cartes[4]->ajouterFils(cartes[7]);
    cartes[4]->ajouterFils(cartes[8]);
    cartes[5]->ajouterFils(cartes[9]);
    cartes[5]->ajouterFils(cartes[10]);
    cartes[6]->ajouterFils(cartes[10]);
    cartes[6]->ajouterFils(cartes[11]);
    cartes[7]->ajouterFils(cartes[11]);
    cartes[7]->ajouterFils(cartes[12]);
    cartes[8]->ajouterFils(cartes[12]);
    cartes[8]->ajouterFils(cartes[13]);
    cartes[9]->ajouterFils(cartes[14]);
    cartes[9]->ajouterFils(cartes[15]);
    cartes[10]->ajouterFils(cartes[15]);
    cartes[10]->ajouterFils(cartes[16]);
    cartes[11]->ajouterFils(cartes[16]);
    cartes[11]->ajouterFils(cartes[17]);
    cartes[12]->ajouterFils(cartes[17]);
    cartes[12]->ajouterFils(cartes[18]);
    cartes[13]->ajouterFils(cartes[18]);
    cartes[13]->ajouterFils(cartes[19]);

    //On cache les cartes cachées lors du début de l'âge1:

    cartes[0]->setCachee(false);
    cartes[1]->setCachee(false);

    cartes[2]->setCachee(true);
    cartes[3]->setCachee(true);
    cartes[4]->setCachee(true);

    cartes[5]->setCachee(false);
    cartes[6]->setCachee(false);
    cartes[7]->setCachee(false);
    cartes[8]->setCachee(false);

    cartes[9]->setCachee(true);
    cartes[10]->setCachee(true);
    cartes[11]->setCachee(true);
    cartes[12]->setCachee(true);
    cartes[13]->setCachee(true);




    return cartes;
}

// Fonction pour initialiser les cartes de l'âge II
std::vector<Carte*> initialiserCartesAgeII() {
    std::vector<Carte*> cartes;

    Carte* c1 = new Carte_militaire("Haras", 0, 1, 0, 1, 0, 0, 1, Chainage::AUCUN, Chainage::FER, getCheminImage("Haras"));
    Carte* c2 = new Carte_militaire("Place d'armes", 0, 0, 0, 2, 1, 0, 2, Chainage::CASQUE, Chainage::AUCUN, getCheminImage("Place d'armes"));
    Carte* c3 = new Carte_militaire("Baraquements", 3, 0, 0, 0, 0, 0, 1, Chainage::AUCUN, Chainage::EPEE, getCheminImage("Baraquements"));
    Carte* c4 = new Carte_militaire("Muraille", 0, 0, 2, 0, 0, 0, 2, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Muraille"));
    Carte* c5 = new Carte_militaire("Champs de tir", 0, 1, 1, 0, 0, 1, 2, Chainage::CIBLE, Chainage::AUCUN, getCheminImage("Champs de tir"));

    Carte* c6 = new Carte_civil("Aqueduc", 0, 0, 3, 0, 0, 0, 5, Chainage::AUCUN, Chainage::GOUTTE, getCheminImage("Aqueduc"));
    Carte* c7 = new Carte_civil("Temple", 0, 1, 0, 0, 0, 1, 4, Chainage::SOLEIL, Chainage::LUNE, getCheminImage("Temple"));
    Carte* c8 = new Carte_civil("Tribunal", 0, 2, 0, 0, 1, 0, 5, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Tribunal"));
    Carte* c9 = new Carte_civil("Rostres", 0, 1, 1, 0, 0, 0, 4, Chainage::TEMPLE, Chainage::AUCUN, getCheminImage("Rostres"));
    Carte* c10 = new Carte_civil("Statue", 0, 0, 0, 2, 0, 0, 4, Chainage::PILLIER, Chainage::MASQUE, getCheminImage("Statue"));

    Carte* c11 = new Carte_matiere_premiere("Briqueterie", 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, getCheminImage("Briqueterie"));
    Carte* c12 = new Carte_matiere_premiere("Scierie", 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, getCheminImage("Scierie"));
    Carte* c13 = new Carte_matiere_premiere("Carriere", 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, getCheminImage("Carrière"));
    Carte* c14 = new Carte_manufacture("Soufflerie", 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, getCheminImage("Soufflerie"));
    Carte* c15 = new Carte_manufacture("sechoir", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, getCheminImage("Séchoir"));

    Carte* c16 = new Carte_scientifique("Dispensaire", 0, 0, 1, 2, 0, 0, Symbol_Scientifique::BOL, 2, Chainage::AUCUN, Chainage::ENGRENAGE, getCheminImage("Dispensaire"));
    Carte* c17 = new Carte_scientifique("ecole", 0, 1, 0, 0, 0, 2, Symbol_Scientifique::ROUE, 1, Chainage::HARPE, Chainage::AUCUN, getCheminImage("École"));
    Carte* c18 = new Carte_scientifique("Laboratoire", 0, 1, 0, 0, 2, 0, Symbol_Scientifique::COMPAS, 0, Chainage::LAMPE, Chainage::AUCUN, getCheminImage("Laboratoire"));
    Carte* c19 = new Carte_scientifique("Bibliotheque", 0, 1, 1, 0, 1, 0, Symbol_Scientifique::PLUME, 2, Chainage::AUCUN, Chainage::LIVRE, getCheminImage("Bibliothèque"));


    Carte* c20 = new Carte_commerciales_piece("Brasserie", 0, Chainage::TAMBOUR, Chainage::AUCUN, getCheminImage("Brasserie"));
    Carte* c21 = new Carte_commerciales_ressources("Caravanserail", new Ressource(1, 1, 1, 0, 0), Chainage::AUCUN, Chainage::AUCUN, 2, 0, 0, 0, 1, 1, 0, getCheminImage("Caravansérail"));
    Carte* c22 = new Carte_commerciales_ressources("Forum", new Ressource(0, 0, 0, 1, 1), Chainage::AUCUN, Chainage::AUCUN, 3, 0, 0, 1, 0, 0, 0, getCheminImage("Forum"));
    Carte* c23 = new Carte_commerciales_prix("Douane", new Ressource(0, 0, 0, 1, 1), Chainage::AUCUN, Chainage::AUCUN, 4, getCheminImage("Douane"));



    // Ajouter les cartes au vecteur
    cartes.push_back(c2);
    cartes.push_back(c1);
    cartes.push_back(c3);
    cartes.push_back(c4);
    cartes.push_back(c5);
    cartes.push_back(c6);
    cartes.push_back(c7);
    cartes.push_back(c8);
    cartes.push_back(c9);
    cartes.push_back(c10);
    cartes.push_back(c11);
    cartes.push_back(c12);
    cartes.push_back(c13);
    cartes.push_back(c14);
    cartes.push_back(c15);
    cartes.push_back(c16);
    cartes.push_back(c17);
    cartes.push_back(c18);
    cartes.push_back(c19);
    cartes.push_back(c20);
    cartes.push_back(c21);
    cartes.push_back(c22);
    cartes.push_back(c23);


    // Mélanger les cartes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);

    //On veut 20 cartes pour l'âge 2, on enlève les 3 dernières du vecteur après mélange.
    cartes.resize(20);

    // Attribue les relations de parenté en fonction de leur position après le mélange
    cartes[0]->ajouterFils(cartes[6]);
    cartes[1]->ajouterFils(cartes[6]);
    cartes[1]->ajouterFils(cartes[7]);
    cartes[2]->ajouterFils(cartes[7]);
    cartes[2]->ajouterFils(cartes[8]);
    cartes[3]->ajouterFils(cartes[8]);
    cartes[3]->ajouterFils(cartes[9]);
    cartes[4]->ajouterFils(cartes[9]);
    cartes[4]->ajouterFils(cartes[10]);
    cartes[5]->ajouterFils(cartes[10]);
    cartes[6]->ajouterFils(cartes[11]);
    cartes[7]->ajouterFils(cartes[11]);
    cartes[7]->ajouterFils(cartes[12]);
    cartes[8]->ajouterFils(cartes[12]);
    cartes[8]->ajouterFils(cartes[13]);
    cartes[9]->ajouterFils(cartes[13]);
    cartes[9]->ajouterFils(cartes[14]);
    cartes[10]->ajouterFils(cartes[14]);
    cartes[11]->ajouterFils(cartes[15]);
    cartes[12]->ajouterFils(cartes[15]);
    cartes[12]->ajouterFils(cartes[16]);
    cartes[13]->ajouterFils(cartes[16]);
    cartes[13]->ajouterFils(cartes[17]);
    cartes[14]->ajouterFils(cartes[17]);
    cartes[15]->ajouterFils(cartes[18]);
    cartes[16]->ajouterFils(cartes[18]);
    cartes[16]->ajouterFils(cartes[19]);
    cartes[17]->ajouterFils(cartes[19]);

    //On cache les cartes cachées lors du début de l'âge1:
    cartes[0]->setCachee(false);
    cartes[1]->setCachee(false);
    cartes[2]->setCachee(false);
    cartes[3]->setCachee(false);
    cartes[4]->setCachee(false);
    cartes[5]->setCachee(false);

    cartes[6]->setCachee(true);
    cartes[7]->setCachee(true);
    cartes[8]->setCachee(true);
    cartes[9]->setCachee(true);
    cartes[10]->setCachee(true);

    cartes[11]->setCachee(false);
    cartes[12]->setCachee(false);
    cartes[13]->setCachee(false);
    cartes[14]->setCachee(false);

    cartes[15]->setCachee(true);
    cartes[16]->setCachee(true);
    cartes[17]->setCachee(true);
  
    return cartes;
}


// Fonction pour initialiser les cartes de l'âge III
std::vector<Carte*> initialiserCartesAgeIII() {
    std::vector<Carte*> cartes;
    std::vector<Carte*> guildes;

    Carte* c1 = new Carte_militaire("Cirque", 0, 0, 2, 2, 0, 0, 2, Chainage::AUCUN, Chainage::CASQUE, getCheminImage("Cirque"));
    Carte* c2 = new Carte_militaire("Arsenal", 0, 2, 0, 3, 0, 0, 3, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Arsenal"));
    Carte* c3 = new Carte_militaire("pretoire", 8, 0, 0, 0, 0, 0, 3, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Prétoire"));
    Carte* c4 = new Carte_militaire("fortifications", 0, 0, 2, 1, 0, 1, 2, Chainage::AUCUN, Chainage::TOUR, getCheminImage("Fortification"));
    Carte* c5 = new Carte_militaire("atelier_de_siege", 0, 3, 0, 0, 1, 0, 2, Chainage::AUCUN, Chainage::CIBLE, getCheminImage("Atelier de siège"));

    Carte* c6 = new Carte_civil("Jardins", 0, 2, 0, 2, 0, 0, 6, Chainage::AUCUN, Chainage::PILLIER, getCheminImage("Jardins"));
    Carte* c7 = new Carte_civil("pantheon", 0, 1, 0, 1, 0, 2, 6, Chainage::AUCUN, Chainage::SOLEIL, getCheminImage("Panthéon"));
    Carte* c8 = new Carte_civil("senat", 0, 0, 1, 2, 0, 1, 5, Chainage::AUCUN, Chainage::TEMPLE, getCheminImage("Sénat"));
    Carte* c9 = new Carte_civil("hotel_de_ville", 0, 2, 3, 0, 0, 0, 7, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Hôtel de ville"));
    Carte* c10 = new Carte_civil("Palace", 0, 1, 1, 1, 2, 0, 7, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Palace"));
    Carte* c11 = new Carte_civil("obelisque", 0, 0, 2, 0, 1, 0, 5, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Obélisque"));

    Carte* c12 = new Carte_scientifique("Observatoire", 0, 0, 1, 0, 0, 2, Symbol_Scientifique::GLOBE, 2, Chainage::AUCUN, Chainage::LAMPE, getCheminImage("Observatoire"));
    Carte* c13 = new Carte_scientifique("universite", 0, 0, 0, 1, 1, 1, Symbol_Scientifique::GLOBE, 2, Chainage::AUCUN, Chainage::HARPE, getCheminImage("Université"));
    Carte* c14 = new Carte_scientifique("academie", 0, 1, 1, 0, 2, 0, Symbol_Scientifique::CADRAN, 3, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Académie"));
    Carte* c15 = new Carte_scientifique("etude", 0, 2, 0, 0, 1, 1, Symbol_Scientifique::CADRAN, 3, Chainage::AUCUN, Chainage::AUCUN, getCheminImage("Étude"));

    Carte* c16 = new Carte_commerciales_bonus("Phare", Type_Carte::COMMERCIAL, Chainage::AUCUN, Chainage::AMPHORE, 0, 0, 0, 2, 1, 0, 3, getCheminImage("Phare"));
    Carte* c17 = new Carte_commerciales_bonus("arene", Type_Carte::MERVEILLE, Chainage::AUCUN, Chainage::TAMBOUR, 0, 1, 1, 1, 0, 0, 3, getCheminImage("Arène"));
    Carte* c18 = new Carte_commerciales_bonus("Port", Type_Carte::RESSOURCES_PRE, Chainage::AUCUN, Chainage::AUCUN, 0, 1, 0, 0, 1, 1, 3, getCheminImage("Port"));
    Carte* c19 = new Carte_commerciales_bonus("Armurerie", Type_Carte::MILITAIRE, Chainage::AUCUN, Chainage::AUCUN, 0, 0, 2, 0, 1, 0, 3, getCheminImage("Armurerie"));
    Carte* c20 = new Carte_commerciales_bonus("chambre_de_commerce", Type_Carte::RESSOURCES_MAN, Chainage::AUCUN, Chainage::AUCUN, 0, 0, 0, 0, 0, 2, 3, getCheminImage("Chambre de commerce"));

    Carte* g1 = new Carte_guilde("guilde_des_usuries", Type_Carte::AUCUN, 0, 2, 2, 0, 0, 0, getCheminImage("Guilde des Usuriers"));
    Carte* g2 = new Carte_guilde("guilde_des_batisseurs", Type_Carte::MERVEILLE, 0, 1, 2, 1, 1, 0, getCheminImage("Guilde des Batisseurs"));
    Carte* g3 = new Carte_guilde("guilde_des_tacticiens", Type_Carte::MILITAIRE, 0, 0, 2, 1, 0, 1, getCheminImage("Guilde des Tacticiens"));
    Carte* g4 = new Carte_guilde("guilde_des_armateurs", Type_Carte::RESSOURCES, 0, 0, 1, 1, 1, 1, getCheminImage("Guilde des Armateurs"));
    Carte* g5 = new Carte_guilde("guilde_des_commerçants", Type_Carte::COMMERCIAL, 0, 1, 0, 1, 1, 1, getCheminImage("Guilde des Commercants"));
    Carte* g6 = new Carte_guilde("guilde_des_scientifiques", Type_Carte::SCIENTIFIQUE, 0, 2, 0, 2, 0, 0, getCheminImage("Guilde des Scientifiques"));
    Carte* g7 = new Carte_guilde("guilde_des_magistrats", Type_Carte::CIVIL, 0, 2, 0, 1, 0, 1, getCheminImage("Guilde des Magistrats"));



    cartes.push_back(c2);
    cartes.push_back(c1);
    cartes.push_back(c3);
    cartes.push_back(c4);
    cartes.push_back(c5);
    cartes.push_back(c6);
    cartes.push_back(c7);
    cartes.push_back(c8);
    cartes.push_back(c9);
    cartes.push_back(c10);
    cartes.push_back(c11);
    cartes.push_back(c12);
    cartes.push_back(c13);
    cartes.push_back(c14);
    cartes.push_back(c15);
    cartes.push_back(c16);
    cartes.push_back(c17);
    cartes.push_back(c18);
    cartes.push_back(c19);
    cartes.push_back(c20);


    guildes.push_back(g1);
    guildes.push_back(g2);
    guildes.push_back(g3);
    guildes.push_back(g4);
    guildes.push_back(g5);
    guildes.push_back(g6);
    guildes.push_back(g7);


 // Mélanger les cartes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);
    std::shuffle(guildes.begin(), guildes.end(), g);

    // On veut 17 cartes + 3 guildes pour l'âge 3:
    cartes.resize(17);
    cartes.push_back(guildes[0]);
    cartes.push_back(guildes[1]);
    cartes.push_back(guildes[2]);

    // Re-mélanger les cartes
    std::shuffle(cartes.begin(), cartes.end(), g);

    // Attribue les relations de parenté en fonction de leur position après le mélange
    cartes[0]->ajouterFils(cartes[2]);
    cartes[0]->ajouterFils(cartes[3]);
    cartes[1]->ajouterFils(cartes[3]);
    cartes[1]->ajouterFils(cartes[4]);
    cartes[2]->ajouterFils(cartes[5]);
    cartes[2]->ajouterFils(cartes[6]);
    cartes[3]->ajouterFils(cartes[6]);
    cartes[3]->ajouterFils(cartes[7]);
    cartes[4]->ajouterFils(cartes[7]);
    cartes[4]->ajouterFils(cartes[8]);
    cartes[5]->ajouterFils(cartes[9]);
    cartes[6]->ajouterFils(cartes[9]);
    cartes[7]->ajouterFils(cartes[10]);
    cartes[8]->ajouterFils(cartes[10]);
    cartes[9]->ajouterFils(cartes[11]);
    cartes[9]->ajouterFils(cartes[12]);
    cartes[10]->ajouterFils(cartes[13]);
    cartes[10]->ajouterFils(cartes[14]);
    cartes[11]->ajouterFils(cartes[15]);
    cartes[12]->ajouterFils(cartes[15]);
    cartes[12]->ajouterFils(cartes[16]);
    cartes[13]->ajouterFils(cartes[16]);
    cartes[13]->ajouterFils(cartes[17]);
    cartes[14]->ajouterFils(cartes[17]);
    cartes[15]->ajouterFils(cartes[18]);
    cartes[16]->ajouterFils(cartes[18]);
    cartes[16]->ajouterFils(cartes[19]);
    cartes[17]->ajouterFils(cartes[19]);

    //On cache les cartes cachées lors du début de l'âge1:
    cartes[0]->setCachee(false);
    cartes[1]->setCachee(false);

    cartes[2]->setCachee(true);
    cartes[3]->setCachee(true);
    cartes[4]->setCachee(true);

    cartes[5]->setCachee(false);
    cartes[6]->setCachee(false);
    cartes[7]->setCachee(false);
    cartes[8]->setCachee(false);

    cartes[9]->setCachee(true);
    cartes[10]->setCachee(true);

    cartes[11]->setCachee(false);
    cartes[12]->setCachee(false);
    cartes[13]->setCachee(false);
    cartes[14]->setCachee(false);

    cartes[15]->setCachee(true);
    cartes[16]->setCachee(true);
    cartes[17]->setCachee(true);

    return cartes;
}

std::vector<Merveille*> initialiserMerveillesData(){
    std::vector<Merveille*> listeMerveilles;
    listeMerveilles.push_back(new Merveille("Le Circus Maximus",
     new Ressource(1, 2, 0, 1, 0),
      new Bonus_merveille(nullptr, 0, 0, 3, Couleur::GRIS, false, 1, false)));

    listeMerveilles.push_back(new Merveille("Le Colosse",
     new Ressource(0, 0, 3, 1, 0),
      new Bonus_merveille(nullptr, 0, 0, 3, Couleur::AUCUN, false, 2, false)));

    listeMerveilles.push_back(new Merveille("Le Grand Phare",
     new Ressource(1, 1, 0, 0, 2),
      new Bonus_merveille(new Ressource(1, 1, 1), 0, 0, 4, Couleur::AUCUN, false, 0, false)));

    listeMerveilles.push_back(new Merveille("Les Jardins Suspendus",
     new Ressource(2, 0, 0, 1, 1),
      new Bonus_merveille(nullptr, 6, 0, 3, Couleur::AUCUN, false, 0, true)));


    // La grande bibliothèque est en commentaire car la fenêtre Qt qui doit afficher les jeton progrès à choisir
    // Fait crash l'application

    /*
    listeMerveilles.push_back(new Merveille("La Grande Bibliotheque",
     new Ressource(3, 0, 0, 1, 1),
      new Bonus_merveille(nullptr, 0, 0, 4, Couleur::AUCUN, true, 0, false)));
    */

    listeMerveilles.push_back(new Merveille("Le Mausolée",
     new Ressource(0, 0, 2, 2, 1),
      new Bonus_merveille(nullptr, 0, 0, 2, Couleur::AUCUN, false, 0, false, true)));

    listeMerveilles.push_back(new Merveille("Piree",
     new Ressource(2, 1, 1, 0, 0),
      new Bonus_merveille(new Ressource(0,0,0,1,1), 0, 0, 2, Couleur::AUCUN, false, 0, true, false)));

    listeMerveilles.push_back(new Merveille("Les pyramides",
     new Ressource(0, 3, 0, 0, 1),
      new Bonus_merveille(nullptr, 0, 0, 9, Couleur::AUCUN, false, 0)));

    listeMerveilles.push_back(new Merveille("Le Sphinx",
     new Ressource(0, 1, 1, 2, 0),
      new Bonus_merveille(nullptr, 0, 0, 6, Couleur::AUCUN, false, 0, true)));

    listeMerveilles.push_back(new Merveille("La Statue de Zeus",
     new Ressource(1, 1, 1, 0, 2),
      new Bonus_merveille(nullptr, 0, 0, 3, Couleur::MARRON, false, 1)));

    listeMerveilles.push_back(new Merveille("Le Temple d'Artemis",
     new Ressource(1, 1, 0, 1, 1),
      new Bonus_merveille(nullptr, 12, 0, 0, Couleur::AUCUN, false, 0, true)));

    listeMerveilles.push_back(new Merveille("La Via Apia",
     new Ressource(0, 2, 2, 0, 1),
      new Bonus_merveille(nullptr, 3, 3, 3, Couleur::AUCUN, false, 0, true)));
    
    return listeMerveilles;
}

Carte* initcarte_invisible(){
    return new Carte_militaire("carte_invisible", 0, 0, 0, 0, 0, 0, 0, Chainage::AUCUN, Chainage::AUCUN,"test");
}

