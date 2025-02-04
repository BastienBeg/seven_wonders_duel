#ifndef VUEPLATEAU_H
#define VUEPLATEAU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <vector>
#include <QSlider>
#include <QPainter>
#include <QStyle>

#include "plateau.h"
#include "vuecarte.h"
#include "vuejoueur.h"
#include "vuedefausse.h"
#include "choixdialogue.h"
#include "ConstructionMerveilleDialogue.h"
#include "clickablelabel.h"

class CustomSlider : public QSlider
{
    Q_OBJECT

public:
    explicit CustomSlider(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

class VuePlateau : public QWidget {
    Q_OBJECT

public:
    explicit VuePlateau(Plateau* plateau, QWidget *parent = nullptr);
    void afficherCartesAge(Plateau* plateau, AGE age);
    void afficherJetons(Plateau* plateau);
    void victoire();
    QHBoxLayout* layoutChoixCartes = nullptr;
    QHBoxLayout* layoutChoixJetons = nullptr;
    QHBoxLayout* layoutChoixJoueur = nullptr;
    QDialog* vueChoixCartes = nullptr;
    QDialog* vueChoixJetons = nullptr;
    QDialog* vueChoixJoueur = nullptr;
    VueJoueur* getvueJoueur1(){return vueJoueur1;}
    VueJoueur* getvueJoueur2(){return vueJoueur1;}
    void afficherDefausse(const std::vector<Carte*>& cartes);
    Carte* afficherChoixCartes(std::vector<Carte *> cartes);
    Joueur* afficherChoixJoueur(Joueur* joueur);
    Jeton_Progres* afficherChoixJeton(std::vector<Jeton_Progres *> jetons);
public slots:
    void restartGame();
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void handleCarteCliquee(Carte* carte);
    void handleDefausser(Carte* carte);
    void handleConstruireBatiment(Carte* carte);
    void handleConstruireMerveille(Carte* carte);
    void handleChoixCarte(Carte* carte);
    void handleChoixJeton(Jeton_Progres* jeton);
    void handleChoixJoueur(Joueur* joueur);
    void ouvrirDefausse();
    void refreshCartes();
    void updateDefausse();


private:
    VueJoueur* vueJoueur1;
    VueJoueur* vueJoueur2;
    QGridLayout* layoutCartes;
    QHBoxLayout* layoutJetons = nullptr;
    QDialog* vuedefausse = nullptr;
    QVBoxLayout* defausseLayout = nullptr;
    Plateau* plateau;
    CustomSlider *plateauMilitaire;
    QHBoxLayout* layoutJetonsProgres = nullptr;
    Carte* carteSelectionnee = nullptr;
    Jeton_Progres* jetonSelectionnee = nullptr;
    Joueur* joueurSelectionnee = nullptr;
    void refreshJoueurs();
    void updateJetons();
    void updatePlateauMilitaire();
    void tour_joueur_debut_age();
    void afficherJetonsProgres();
};

#endif // VUEPLATEAU_H



