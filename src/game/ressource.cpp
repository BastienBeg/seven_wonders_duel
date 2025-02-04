#pragma once
#include "ressources.h"
#include "joueur.h"
#include "carte.h"

void Ressource::ajouterRessources(const Ressource& gain) {
    int n_bois = getBois() + gain.getBois();
    setBois(n_bois);
    int n_fer = getFer() + gain.getFer();
    setFer(n_fer);
    int n_argile = getArgile() + gain.getArgile();
    setArgile(n_argile);
    int n_verre = getVerre() + gain.getVerre();
    setVerre(n_verre);
    int n_papyrus = getPapyrus() + gain.getPapyrus();
    setPapyrus(n_papyrus);
}

void Ressource::retirerRessources(const Ressource& perte) {
    int n_bois = getBois() - perte.getBois();
    if (n_bois > 0) { setBois(n_bois); }
    else { setBois(0); }

    int n_fer = getFer() - perte.getFer();
    if (n_fer > 0) { setFer(n_fer); }
    else { setFer(0); }

    int n_argile = getArgile() - perte.getArgile();
    if (n_argile > 0) { setArgile(n_argile); }
    else { setArgile(0); }

    int n_verre = getVerre() - perte.getVerre();
    if (n_verre > 0) { setVerre(n_verre); }
    else { setVerre(0); }

    int n_papyrus = getPapyrus() - perte.getPapyrus();
    if (n_papyrus > 0) { setPapyrus(n_papyrus); }
    else { setPapyrus(0); }
}

int Ressource::calculerCoutTotal(const Ressource& cout_a_payer, Joueur& j, Carte* c) const {
    // On regarde le cout en ressource de la carte/merveille

    // On commence par voir si il eiste un lien de chainage entre la carte à acheter et les cartes du joueur
    if (c != nullptr){
        // ----- A faire une fois que j'aurais le taffe d'amélie  -----
        // On check si la carte "c" est de type "Carte_commercialles" ou "militaire" ou "civil" ou "scientifique"
        Carte_commerciales* c_commerce = dynamic_cast<Carte_commerciales*>(c);
        Carte_civil* c_civil = dynamic_cast<Carte_civil*>(c);
        Carte_militaire* c_miliaire = dynamic_cast<Carte_militaire*>(c);
        Carte_scientifique* c_scientifique = dynamic_cast<Carte_scientifique*>(c);
        Chainage chainage_cout = Chainage::AUCUN;
        if (c_commerce){
            chainage_cout = c_commerce->getChainageCout();
        }
        else if (c_civil){
            chainage_cout = c_civil->getChainageCivCout();
        }
        else if (c_miliaire) {
            chainage_cout = c_miliaire->getChainageMilCout();
        }
        else if (c_scientifique) {
            chainage_cout = c_scientifique->getChainageScientifiqueCout();
        }
        // Si oui, on check si son chainage (getChainage_cout) est différent de Chainage::AUCUN
        if (chainage_cout != Chainage::AUCUN) {
            // Si oui on parcours les chainage du joueur, en verfiant l'egaliste avec le chainage cout
            for (Chainage chainage_joueur : j.getChainage()) {
                // Si == alors on retourne 0 et la carte est gratuite 
                if (chainage_joueur == chainage_cout) {
                    if (j.possede_jeton_progres("Urbanisme")) {
                        j.ajouter_piece(4);
                    }
                    j.retirerChainage(chainage_cout);
                    return 0;
                }
            }
        }
    }

    // On compare au ressource du joueur qui appelle la methode
    Ressource* ressource_joueur = j.getRessources();
    if (ressource_joueur->getArgile()-cout_a_payer.getArgile() < 0 ||
        ressource_joueur->getFer()-cout_a_payer.getFer()< 0 ||
        ressource_joueur->getBois()-cout_a_payer.getBois() < 0 ||
        ressource_joueur->getPapyrus()-cout_a_payer.getPapyrus() < 0 ||
        ressource_joueur->getVerre()-cout_a_payer.getVerre() < 0){

    // s'il reste des ressource à payer, on cree un objet ressource temporaire qui correspond au reste de ce qu'il
    // Faut payer (evidement les ressource ne peuvent etre negatives)
        int reste_bois = cout_a_payer.getBois()-ressource_joueur->getBois();
        if (reste_bois < 0){ reste_bois = 0; }
        int reste_fer = cout_a_payer.getFer()-ressource_joueur->getFer();
        if (reste_fer < 0){ reste_fer = 0; }
        int reste_argile = cout_a_payer.getArgile()-ressource_joueur->getArgile();
        if (reste_argile < 0){ reste_argile = 0; }
        int reste_papyrus = cout_a_payer.getPapyrus()-ressource_joueur->getPapyrus();
        if (reste_papyrus < 0){ reste_papyrus = 0; }
        int reste_verre = cout_a_payer.getVerre()-ressource_joueur->getVerre();
        if (reste_verre < 0){ reste_verre = 0; }

        Ressource* tmp_reste_a_payer = new Ressource(reste_bois, reste_fer, reste_argile, reste_papyrus, reste_verre);

        // si il reste des ressource on cree egalement un objet ressource où les valeurs correspondent au prix
        // individuelle de chaque ressource pour le joueur en question (on prend en compte ses cartes commercialles
        // et le nombre de carte de la ressource en question du joueur adverse)

        int cout_bois = 2;
        int cout_fer = 2;
        int cout_argile = 2;
        int cout_papyrus = 2;
        int cout_verre = 2;

        // Les ressources inscritent dans l'objet "ressource" du joueur correnspondent uniquement a ce qui est produit
        // par les cartes grises et marrons qui servent au calcul du prix des ressources, on peut donc l'utiliser pour ce calcul
        cout_bois = cout_bois + j.getAdversaire()->getRessources()->getBois();
        cout_fer = cout_fer + j.getAdversaire()->getRessources()->getFer();
        cout_argile = cout_argile + j.getAdversaire()->getRessources()->getArgile();
        cout_papyrus = cout_papyrus + j.getAdversaire()->getRessources()->getPapyrus();
        cout_verre = cout_verre + j.getAdversaire()->getRessources()->getVerre();

        // on parcours les cartes commerciales du joueurs,  
        std::vector<Carte_commerciales_prix*> carte_commerciale;
        std::vector<Carte*> cartes_joueur = j.getCartes();

        for (Carte* carte : cartes_joueur){
            if(Carte_commerciales_prix* c_commerce = dynamic_cast<Carte_commerciales_prix*>(carte)){
                carte_commerciale.push_back(c_commerce);
            }
        }

        for (Carte_commerciales_prix* carte : carte_commerciale){
            if (carte->getDiscount()->getBois() != 0) {
                cout_bois = 1;
            }
            if (carte->getDiscount()->getFer() != 0) {
                cout_fer = 1;
            }
            if (carte->getDiscount()->getArgile() != 0) {
                cout_argile = 1;
            }
            if (carte->getDiscount()->getPapyrus() != 0) {
                cout_papyrus = 1;
            }
            if (carte->getDiscount()->getVerre() != 0) {
                cout_verre = 1;
            }
        }

        // On parcours les ressources "un parmis plusieurs" du joueur si elles comportent des ressources necessaires 
        // pour la construction du batiments on en choisis une seule, qu'on soustrait au pri (on priviligie celle au 
        // cout le plus cher)
        std::vector<Ressource*> ressource_partielles_joueur = j.getRessourcesPartielles();
        if (ressource_partielles_joueur.size() != 0){
            // Boucle qui parcours toutes les ressources partielles du joueur
            for (Ressource* ressource_partielle : ressource_partielles_joueur){
                Ressource* tmp_ressource_en_commun = new Ressource();
                int nb_ressource_en_commun = 0;
                // identifier les ressources en commun entre le reste a payer et la ressource partielles
                if(tmp_reste_a_payer->getBois() > 0 && ressource_partielle->getBois() == 1){
                    tmp_ressource_en_commun->setBois(1);
                    nb_ressource_en_commun++;
                }
                if(tmp_reste_a_payer->getFer() > 0 && ressource_partielle->getFer() == 1){
                    tmp_ressource_en_commun->setFer(1);
                    nb_ressource_en_commun++;
                }
                if(tmp_reste_a_payer->getArgile() > 0 && ressource_partielle->getArgile() == 1){
                    tmp_ressource_en_commun->setArgile(1);
                    nb_ressource_en_commun++;
                }
                if(tmp_reste_a_payer->getPapyrus() > 0 && ressource_partielle->getPapyrus() == 1){
                    tmp_ressource_en_commun->setPapyrus(1);
                    nb_ressource_en_commun++;
                }
                if(tmp_reste_a_payer->getVerre() > 0 && ressource_partielle->getVerre() == 1){
                    tmp_ressource_en_commun->setVerre(1);
                    nb_ressource_en_commun++;
                }

                // Si il y en a des ressource en commun entre la ressource partielle et le reste_a_payer, 
                // on prend celle qui coute le plus et on la soustrait au reste_a_payer
                if (nb_ressource_en_commun > 0){
                    int prix_max = -1;
                    std::string ressource_max = "";
                    if (tmp_ressource_en_commun->getBois() == 1 && cout_bois > prix_max){
                        prix_max = cout_bois;
                        ressource_max = "bois";
                    }
                    if (tmp_ressource_en_commun->getFer() == 1 && cout_fer > prix_max){
                        prix_max = cout_fer;
                        ressource_max = "fer";
                    }
                    if (tmp_ressource_en_commun->getArgile() == 1 && cout_argile > prix_max){
                        prix_max = cout_argile;
                        ressource_max = "argile";
                    }
                    if (tmp_ressource_en_commun->getPapyrus() == 1 && cout_papyrus > prix_max){
                        prix_max = cout_papyrus;
                        ressource_max = "papyrus";
                    }
                    if (tmp_ressource_en_commun->getVerre() == 1 && cout_verre > prix_max){
                        prix_max = cout_verre;
                        ressource_max = "verre";
                    }

                    if (prix_max == -1 || ressource_max == ""){
                        // ----- A FAIRE : utilisation de la classe eeption !! pour l'instant on return 0 pour pas faire crash-----
                        std::cout << "Problème dans la foncion calculerCoutTotal dans ressource.cpp" << std::endl;
                        return 0;
                    }
                    // On retire la ressource ayant le pri ma au reste a payer
                    if (ressource_max == "bois"){
                        tmp_reste_a_payer->setBois(tmp_reste_a_payer->getBois()-1); 
                    }
                    else if (ressource_max == "fer"){
                        tmp_reste_a_payer->setFer(tmp_reste_a_payer->getFer()-1); 
                    }
                    else if (ressource_max == "argile"){
                        tmp_reste_a_payer->setArgile(tmp_reste_a_payer->getArgile()-1); 
                    }
                    else if (ressource_max == "papyrus"){
                        tmp_reste_a_payer->setPapyrus(tmp_reste_a_payer->getPapyrus()-1); 
                    }
                    else if (ressource_max == "verre"){
                        tmp_reste_a_payer->setVerre(tmp_reste_a_payer->getVerre()-1); 
                    }
                }
                // Si il y en a aucune, on ne fait rien 
                delete tmp_ressource_en_commun;
            }
        }
        
        // ensuite on calcul le nombre de pièce necessaire en prenant chaques ressources restantes multiplie par son cout
        int piece_a_payer = 0;
        if (tmp_reste_a_payer->getBois() > 0){
            piece_a_payer = piece_a_payer + tmp_reste_a_payer->getBois()*cout_bois;
        }
        if (tmp_reste_a_payer->getFer() > 0){
            piece_a_payer = piece_a_payer + tmp_reste_a_payer->getFer()*cout_fer;
        }
        if (tmp_reste_a_payer->getArgile() > 0){
            piece_a_payer = piece_a_payer + tmp_reste_a_payer->getArgile()*cout_argile;
        }
        if (tmp_reste_a_payer->getPapyrus() > 0){
            piece_a_payer = piece_a_payer + tmp_reste_a_payer->getPapyrus()*cout_papyrus;
        }
        if (tmp_reste_a_payer->getVerre() > 0){
            piece_a_payer = piece_a_payer + tmp_reste_a_payer->getVerre()*cout_verre;
        }
        // On retourne le nombre de piece
        delete tmp_reste_a_payer;
        if (c != nullptr){
            piece_a_payer = piece_a_payer + c->getCoutPiece();
        }
        return piece_a_payer;
    }
    else {
        int piece_a_payer = 0;
        if (c != nullptr){
            piece_a_payer = piece_a_payer + c->getCoutPiece();
        }
        return piece_a_payer;
    }



}
