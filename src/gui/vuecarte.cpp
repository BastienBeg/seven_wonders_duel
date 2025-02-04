#include "vuecarte.h"
#include <QString>

VueCarte::VueCarte(Carte* carte, QWidget *parent)
    : QPushButton(QString::fromStdString(carte->getNom()), parent), carte(carte)
{
    connect(this, &QPushButton::clicked, this, &VueCarte::handleButtonClick);
}

void VueCarte::handleButtonClick() {
    emit carteCliquee(carte);
}
