#include "vuemerveille.h"
#include <QDebug>

VueMerveille::VueMerveille(Joueur* joueur, QWidget *parent)
    : QDialog(parent), joueur(joueur)
{
    setWindowTitle("Mes Merveilles");

    layoutMerveilles = new QVBoxLayout(this);

    afficherMerveilles();
    setLayout(layoutMerveilles);
}

void VueMerveille::refresh() {
    // Clear the existing layout
    QLayoutItem* item;
    while ((item = layoutMerveilles->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Re-add the merveilles
    afficherMerveilles();
}

void VueMerveille::afficherMerveilles() {
    for (Merveille* merveille : joueur->getMerveillesPossede()) {
        if (!joueur->estConstruite(merveille)) {
            QHBoxLayout* merveilleLayout = new QHBoxLayout;

            // Ajouter le nom de la merveille
            QLabel* merveilleLabel = new QLabel(QString::fromStdString(merveille->getNom()), this);
            merveilleLayout->addWidget(merveilleLabel);

            // Ajouter l'image de la merveille
            QPixmap pixmap(QString::fromStdString(merveille->getCheminImage()));
            if (!pixmap.isNull()) {
                QLabel* imageLabel = new QLabel(this);
                imageLabel->setPixmap(pixmap.scaled(100, 150)); // Redimensionnez l'image si nécessaire
                merveilleLayout->addWidget(imageLabel);
            }

            layoutMerveilles->addLayout(merveilleLayout);
        }
    }
}
