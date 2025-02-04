#include "ConstructionMerveilleDialogue.h"
#include <QMessageBox>
#include <QDebug>

ConstructionMerveilleDialogue::ConstructionMerveilleDialogue(Joueur* joueur, QWidget *parent)
    : QDialog(parent), joueur(joueur) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Choisissez une merveille à construire:", this);
    mainLayout->addWidget(label);

    layoutMerveilles = new QVBoxLayout;
    mainLayout->addLayout(layoutMerveilles);

    afficherMerveillesNonConstruites();

    setLayout(mainLayout);
}

void ConstructionMerveilleDialogue::afficherMerveillesNonConstruites() {
    // Nettoyer les widgets précédents
    QLayoutItem* item;
    while ((item = layoutMerveilles->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Afficher les illustrations des merveilles non construites
    for (Merveille* merveille : joueur->getMerveillesPossede()) {
        if (!joueur->estConstruite(merveille)) {
            ClickableLabel* merveilleLabel = new ClickableLabel(this);

            QString cheminImage = QString::fromStdString(merveille->getCheminImage());
            QPixmap pixmap(cheminImage);
            if (pixmap.isNull()) {
                qDebug() << "Erreur : Impossible de charger l'image pour la merveille : " << cheminImage;
            } else {
                qDebug() << "Chargement de l'image pour la merveille : " << cheminImage;
                merveilleLabel->setPixmap(pixmap.scaled(400, 250)); // Simplification du redimensionnement
                merveilleLabel->setScaledContents(true); // Assure que le QLabel redimensionne l'image pour remplir le label
            }

            connect(merveilleLabel, &ClickableLabel::clicked, [this, merveille]() {
                handleConstruireMerveille(merveille);
            });

            layoutMerveilles->addWidget(merveilleLabel);
        }
    }
}

void ConstructionMerveilleDialogue::handleConstruireMerveille(Merveille* merveille) {
    Partie& partie = Partie::getInstance();
    if (merveille->construireMerveille(partie.getActuel())) {
        QMessageBox::information(this, "Succès", "La merveille a été construite !");
        joueur->retirerMerveille(merveille); // Retirer la merveille construite de la liste des merveilles possédées
    } else {
        QMessageBox::warning(this, "Échec", "Vous n'avez pas assez de ressources pour construire cette merveille.");
    }
    accept(); // Fermer le dialogue après tentative de construction
}
