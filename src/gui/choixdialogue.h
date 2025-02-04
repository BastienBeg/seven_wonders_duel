#ifndef CHOIXDIALOGUE_H
#define CHOIXDIALOGUE_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "carte.h"

class ChoixDialogue : public QDialog {
    Q_OBJECT

public:
    explicit ChoixDialogue(Carte* carte, QWidget *parent = nullptr);

signals:
    void defausserCarte(Carte* carte);
    void construireBatiment(Carte* carte);
    void construireMerveille(Carte* carte);

private slots:
    void handleDefausser();
    void handleConstruireBatiment();
    void handleConstruireMerveille();

private:
    Carte* carte;
};

#endif // CHOIXDIALOGUE_H
