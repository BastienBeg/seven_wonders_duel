#ifndef MERVEILLESDIALOGUE_H
#define MERVEILLESDIALOGUE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "joueur.h"
#include "merveille.h"
#include "partie.h"
#include "clickablelabel.h"

class MerveillesDialogue : public QDialog {
    Q_OBJECT

public:
    MerveillesDialogue(const std::vector<Merveille*>& merveilles, QWidget *parent = nullptr);

private slots:
    void handleChoisirMerveille(Merveille* merveille, ClickableLabel* label);

private:
    void initialiserSetsMerveilles();
    void afficherSetMerveilles(const std::vector<Merveille*>& set);
    void mettreAJourLayoutMerveilles();

    std::vector<Merveille*> merveilles;
    std::vector<Merveille*> set_1_merveille;
    std::vector<Merveille*> set_2_merveille;
    int choixRestants;
    int choixTotal;
    int setActuel;

    QVBoxLayout* layoutJoueur1;
    QVBoxLayout* layoutJoueur2;
    QHBoxLayout* layoutMerveilles;
    QLabel* labelJoueur1;
    QLabel* labelJoueur2;
};

#endif // MERVEILLESDIALOGUE_H
