#ifndef VUECARTE_H
#define VUECARTE_H

#include <QPushButton>
#include "carte.h"

class VueCarte : public QPushButton {
    Q_OBJECT

public:
    explicit VueCarte(Carte* carte, QWidget *parent = nullptr);

signals:
    void carteCliquee(Carte* carte);  // Déclaration du signal

private slots:
    void handleButtonClick();  // Déclaration du slot

private:
    Carte* carte;
};

#endif // VUECARTE_H
