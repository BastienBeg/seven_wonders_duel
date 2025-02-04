#include "merveillesdialogue.h"
#include <random>

MerveillesDialogue::MerveillesDialogue(const std::vector<Merveille*>& merveilles, QWidget *parent)
    : QDialog(parent), merveilles(merveilles), choixRestants(4), choixTotal(0), setActuel(1)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    Partie& partie = Partie::getInstance(); // Utiliser l'instance unique

    labelJoueur1 = new QLabel(QString::fromStdString(partie.getJ1()->getNom()), this);
    layoutJoueur1 = new QVBoxLayout;
    layoutJoueur1->addWidget(labelJoueur1);

    labelJoueur2 = new QLabel(QString::fromStdString(partie.getJ2()->getNom()), this);
    layoutJoueur2 = new QVBoxLayout;
    layoutJoueur2->addWidget(labelJoueur2);

    layoutMerveilles = new QHBoxLayout;
    mainLayout->addLayout(layoutJoueur1);
    mainLayout->addLayout(layoutJoueur2);
    mainLayout->addLayout(layoutMerveilles);

    setLayout(mainLayout);

    // Initialisation des sets de merveilles
    initialiserSetsMerveilles();
    afficherSetMerveilles(set_1_merveille);
}

void MerveillesDialogue::initialiserSetsMerveilles() {
    // Mélanger les 12 merveilles
    std::vector<Merveille*> merveille_a_distribuer = merveilles;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(merveille_a_distribuer.begin(), merveille_a_distribuer.end(), g);

    if (merveille_a_distribuer.size() >= 8) {
        // Split en 2 sets de 4 merveilles
        set_1_merveille.assign(merveille_a_distribuer.begin(), merveille_a_distribuer.begin() + 4);
        set_2_merveille.assign(merveille_a_distribuer.begin() + 4, merveille_a_distribuer.begin() + 8);
    } else {
        std::cerr << "Erreur : liste_merveilles doit contenir au moins 8 éléments." << std::endl;
    }
}

void MerveillesDialogue::afficherSetMerveilles(const std::vector<Merveille*>& set) {
    // Nettoyer les widgets précédents
    QLayoutItem* item;
    while ((item = layoutMerveilles->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Ajouter les nouvelles étiquettes clicables pour le set actuel
    for (Merveille* merveille : set) {
        ClickableLabel* label = new ClickableLabel(this); // Ajout de l'argument manquant
        label->setText(QString::fromStdString(merveille->getNom())); // Ajout du texte de l'étiquette
        QPixmap pixmap(QString::fromStdString(merveille->getCheminImage()));
        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image pour la carte : " << QString::fromStdString(merveille->getCheminImage());
        } else {
            label->setPixmap(pixmap.scaled(300, 175)); // Redimensionnez l'image si nécessaire
        }
        connect(label, &ClickableLabel::clicked, [this, merveille, label]() {
            handleChoisirMerveille(merveille, label);
        });
        layoutMerveilles->addWidget(label);
    }
}

void MerveillesDialogue::handleChoisirMerveille(Merveille* merveille, ClickableLabel* label) {
    Partie& partie = Partie::getInstance(); // Utiliser l'instance unique
    Joueur* joueur1 = partie.getJ1();
    Joueur* joueur2 = partie.getJ2();
    static Joueur* joueurActuel = joueur1;

    joueurActuel->distribuer_merveille(merveille);
    label->setDisabled(true);

    // Mettre à jour les layouts des joueurs
    mettreAJourLayoutMerveilles();

    --choixRestants;
    ++choixTotal;

    // Définir la séquence des choix
    if (setActuel == 1) {
        if (choixTotal == 1) joueurActuel = joueur2;       // j1 -> j2
        else if (choixTotal == 2) joueurActuel = joueur2;  // j2 -> j2
        else if (choixTotal == 3) joueurActuel = joueur1;  // j2 -> j1
        else if (choixTotal == 4) joueurActuel = joueur1;  // j1 -> j1
    } else if (setActuel == 2) {
        if (choixTotal == 1) joueurActuel = joueur1;       // j2 -> j1
        else if (choixTotal == 2) joueurActuel = joueur1;  // j1 -> j1
        else if (choixTotal == 3) joueurActuel = joueur2;  // j1 -> j2
        else if (choixTotal == 4) joueurActuel = joueur2;  // j2 -> j2
    }

    if (choixRestants == 0) {
        // Réinitialiser pour le prochain set de merveilles
        choixRestants = 4;
        choixTotal = 0;
        ++setActuel;
        joueurActuel = (setActuel == 2) ? joueur2 : joueur1;

        if (setActuel == 2) {
            afficherSetMerveilles(set_2_merveille);
        } else {
            accept(); // Fermer le dialogue après avoir distribué les deux sets
        }
    }
}





void MerveillesDialogue::mettreAJourLayoutMerveilles() {
    Partie& partie = Partie::getInstance();
    // Nettoyer les layouts des merveilles des joueurs
    QLayoutItem* item;
    while ((item = layoutJoueur1->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }
    while ((item = layoutJoueur2->takeAt(1)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Ajouter les merveilles de chaque joueur à leur layout respectif
    for (Merveille* merveille : partie.getJ1()->getMerveillesPossede()) {
        QLabel* merveilleLabel = new QLabel(QString::fromStdString(merveille->getNom()), this);
        layoutJoueur1->addWidget(merveilleLabel);
    }

    for (Merveille* merveille : partie.getJ2()->getMerveillesPossede()) {
        QLabel* merveilleLabel = new QLabel(QString::fromStdString(merveille->getNom()), this);
        layoutJoueur2->addWidget(merveilleLabel);
    }
}
