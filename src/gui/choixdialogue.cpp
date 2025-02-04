#include "choixdialogue.h"

ChoixDialogue::ChoixDialogue(Carte* carte, QWidget *parent)
    : QDialog(parent), carte(carte)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* defausserButton = new QPushButton("Défausser", this);
    QPushButton* construireBatimentButton = new QPushButton("Construire Bâtiment", this);
    QPushButton* construireMerveilleButton = new QPushButton("Construire Merveille", this);

    layout->addWidget(defausserButton);
    layout->addWidget(construireBatimentButton);
    layout->addWidget(construireMerveilleButton);

    connect(defausserButton, &QPushButton::clicked, this, &ChoixDialogue::handleDefausser);
    connect(construireBatimentButton, &QPushButton::clicked, this, &ChoixDialogue::handleConstruireBatiment);
    connect(construireMerveilleButton, &QPushButton::clicked, this, &ChoixDialogue::handleConstruireMerveille);

    setLayout(layout);
}

void ChoixDialogue::handleDefausser() {
    emit defausserCarte(carte);
    accept();
}

void ChoixDialogue::handleConstruireBatiment() {
    emit construireBatiment(carte);
    accept();
}

void ChoixDialogue::handleConstruireMerveille() {
    emit construireMerveille(carte);
    accept();
}
