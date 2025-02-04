#ifndef CONSTRUCTIONMERVEILLEDIALOGUE_H
#define CONSTRUCTIONMERVEILLEDIALOGUE_H

#include <QDialog>
#include <QVBoxLayout>
#include "joueur.h"
#include "partie.h"
#include "clickablelabel.h"

class ConstructionMerveilleDialogue : public QDialog {
    Q_OBJECT

public:
    ConstructionMerveilleDialogue(Joueur* joueur, QWidget *parent = nullptr);

private slots:
    void handleConstruireMerveille(Merveille* merveille);

private:
    void afficherMerveillesNonConstruites();
    Joueur* joueur;
    QVBoxLayout* layoutMerveilles;
};

#endif // CONSTRUCTIONMERVEILLEDIALOGUE_H
