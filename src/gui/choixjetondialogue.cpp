#include "choixjetondialogue.h"

ChoixJetonDialogue::ChoixJetonDialogue(const std::vector<Jeton_Progres*>& jetons, QWidget* parent)
    : QDialog(parent), jetons(jetons), jetonChoisi(nullptr) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    labelInstructions = new QLabel("Choisissez un jeton progrès :", this);
    mainLayout->addWidget(labelInstructions);

    layoutJetons = new QVBoxLayout;
    mainLayout->addLayout(layoutJetons);

    for (size_t i = 0; i < jetons.size(); ++i) {
        QPushButton* button = new QPushButton(QString::fromStdString(jetons[i]->getNom()), this);
        layoutJetons->addWidget(button);
        connect(button, &QPushButton::clicked, [this, i]() {
            handleChoisirJeton(i);
        });
    }

    setLayout(mainLayout);
}

Jeton_Progres* ChoixJetonDialogue::getJetonChoisi() const {
    return jetonChoisi;
}

void ChoixJetonDialogue::handleChoisirJeton(int index) {
    if (index >= 0 && index < static_cast<int>(jetons.size())) {
        jetonChoisi = jetons[index];
        accept(); // Fermer le dialogue
    }
}
