#include "vuepartie.h"
#include "merveillesdialogue.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QResizeEvent>
#include "partie.h"

VuePartie::VuePartie(Partie& partie, QWidget *parent)
    : QWidget(parent), partie(partie)
{
    // Initialisation de l'image de fond
    backgroundPixmap = QPixmap("../../ressources/demarrage.png");
    if (backgroundPixmap.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image de fond";
    }

    // Afficher l'écran de démarrage
    afficherEcranDemarrage();

    // Configuration du layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
}

void VuePartie::nouvellePartie2J()
{
    Partie& partie = Partie::getInstance(); // Utiliser l'instance unique
    demanderNomsJoueurs();

    // Distribution des merveilles ----
    std::vector<Merveille*> merveilles = partie.getPlateau()->getListe_merveilles();
    MerveillesDialogue dialogue(merveilles, this);
    dialogue.exec();

    plateau = new VuePlateau(partie.getPlateau(), this);
    plateau->afficherCartesAge(partie.getPlateau(), AGE::AGE1);

    // Create the background widget
    QWidget* backgroundWidget = new QWidget(this);
    backgroundWidget->setStyleSheet("background-color: rgba(245, 222, 179, 128);"); // Beige with 50% transparency
    backgroundWidget->setGeometry(this->rect());
    backgroundWidget->lower(); // Ensure the background is behind other widgets

    // Create a layout for the background widget and add the VuePlateau
    QVBoxLayout* backgroundLayout = new QVBoxLayout(backgroundWidget);
    backgroundLayout->addWidget(plateau);

    // Clear the existing layout and add the new widgets
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(this->layout());
    if (mainLayout) {
        QLayoutItem *item;
        while ((item = mainLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        mainLayout->addWidget(backgroundWidget);
    }
}

void VuePartie::demanderNomsJoueurs()
{
    // Demande id du joueur 1
    bool nomValide = false;

    while (!nomValide) {
        bool ok;
        QString nomJoueurQString = QInputDialog::getText(nullptr, "Entrer le nom du joueur",
                                                         "Veuillez entrer le nom du joueur:", QLineEdit::Normal,
                                                         QString::fromStdString(nomJoueur1), &ok);
        if (!ok) {
            QMessageBox::warning(nullptr, "Aucun nom entré",
                                 "Aucun nom de joueur n'a été entré. L'application va se fermer.");
            exit(EXIT_FAILURE);
        }
        nomJoueur1 = nomJoueurQString.toStdString();
        if (!nomJoueur1.empty()) {
            nomValide = true;
        } else {
            QMessageBox::warning(nullptr, "Nom invalide",
                                 "Le nom du joueur ne peut pas être vide. Veuillez entrer un nom valide.");
        }
    }

    // Demande id du joueur 2
    bool nomValidebis = false;

    while (!nomValidebis) {
        bool ok;
        QString nomJoueurQString = QInputDialog::getText(nullptr, "Entrer le nom du joueur",
                                                         "Veuillez entrer le nom du joueur:", QLineEdit::Normal,
                                                         QString::fromStdString(nomJoueur2), &ok);
        if (!ok) {
            QMessageBox::warning(nullptr, "Aucun nom entré",
                                 "Aucun nom de joueur n'a été entré. L'application va se fermer.");
            exit(EXIT_FAILURE);
        }
        nomJoueur2 = nomJoueurQString.toStdString();
        if (!nomJoueur2.empty()) {
            nomValidebis = true;
        } else {
            QMessageBox::warning(nullptr, "Nom invalide",
                                 "Le nom du joueur ne peut pas être vide. Veuillez entrer un nom valide.");
        }
    }

    partie.getJ1()->setNom(nomJoueur1);
    partie.getJ2()->setNom(nomJoueur2);
}

void VuePartie::demanderNomJoueur()
{
    // Demande id du joueur 1
    bool nomValide = false;

    while (!nomValide) {
        bool ok;
        QString nomJoueurQString = QInputDialog::getText(nullptr, "Entrer le nom du joueur",
                                                         "Veuillez entrer le nom du joueur:", QLineEdit::Normal,
                                                         QString::fromStdString(nomJoueur1), &ok);
        if (!ok) {
            QMessageBox::warning(nullptr, "Aucun nom entré",
                                 "Aucun nom de joueur n'a été entré. L'application va se fermer.");
            exit(EXIT_FAILURE);
        }
        nomJoueur1 = nomJoueurQString.toStdString();
        if (!nomJoueur1.empty()) {
            nomValide = true;
        } else {
            QMessageBox::warning(nullptr, "Nom invalide",
                                 "Le nom du joueur ne peut pas être vide. Veuillez entrer un nom valide.");
        }
    }

    nomJoueur2 = "Bot 7 Wonders";
    partie.getJ1()->setNom(nomJoueur1);
    partie.getJ2()->setNom(nomJoueur2);
}

void VuePartie::afficherEcranDemarrage() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Ajouter un bouton "Jouer"
    QPushButton* buttonJouer = new QPushButton("Jouer", this); // Utiliser un pointeur ici
    buttonJouer->setFixedSize(200, 50); // Taille fixe pour le bouton
    buttonJouer->setStyleSheet("background-color: grey; border: 2px solid black;");
    connect(buttonJouer, &QPushButton::clicked, this, &VuePartie::lancerPartie);
    layout->addWidget(buttonJouer, 0, Qt::AlignCenter);

    setLayout(layout);
}

void VuePartie::lancerPartie() {
    // Logique pour lancer la partie
    nouvellePartie2J();
    qDebug() << "La partie est lancée!";
    // Par exemple, vous pouvez cacher l'écran de démarrage et afficher l'interface principale de la partie
}

void VuePartie::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (!backgroundPixmap.isNull()) {
        painter.drawPixmap(rect(), backgroundPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding));
    }
    QWidget::paintEvent(event);
}


