#ifndef VUEJOUEUR_H
#define VUEJOUEUR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QScrollArea>
#include "joueur.h"
#include "vuecarte.h"
#include "vuemerveille.h"
#include "partie.h"

class VueJoueur : public QWidget {
    Q_OBJECT

public:
    VueJoueur(Joueur* joueur, QWidget *parent = nullptr);
    std::string getnomJoueur() const;
    void setActif(bool actif);
    void refresh();

    void ouvrirVueMesCartes();
    void afficherCartes(const std::vector<Carte*>& cartes);

    void ouvrirVueMesMerveilles();
    void ouvrirMerveilles(const std::vector<Merveille*>& merveilles);

    void testAfficherMerveillesNonConstruites();

private:
    QDialog* vuemerveilles = nullptr;
    Joueur* joueur;
    QLabel* pieces;
    QLCDNumber* nbpiece;
    QLabel* ptvictoire;
    QLCDNumber* nbptvictoire;
    QLabel* ressourcesLabel;
    QLCDNumber* argileLCD;
    QLCDNumber* pierreLCD;
    QLCDNumber* boisLCD;
    QLCDNumber* verreLCD;
    QLCDNumber* papyrusLCD;
    QLabel* argileLabel;
    QLabel* pierreLabel;
    QLabel* boisLabel;
    QLabel* verreLabel;
    QLabel* papyrusLabel;
    QDialog* vuemescartes = nullptr;
    QVBoxLayout* cartesLayout = nullptr;

    void updateVueMesCartes();
};

#endif // VUEJOUEUR_H
