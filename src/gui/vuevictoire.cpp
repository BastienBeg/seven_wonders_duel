#include "vuevictoire.h"
#include <QApplication>

VueVictoireScientifique::VueVictoireScientifique(Joueur* joueur, QWidget *parent)
    : QDialog(parent), message(QString::fromStdString("Le joueur " + joueur->getNom() + " a gagné par victoire scientifique !"))
{
    messageVictoire = new QLabel(message, this);
    fermer = new QPushButton("Quitter", this);
    relancer = new QPushButton("Relancer", this);

    connect(fermer, &QPushButton::clicked, this, &VueVictoireScientifique::quitterPartie);
    connect(relancer, &QPushButton::clicked, this, &VueVictoireScientifique::relancerPartie);

    // Utiliser un layout pour organiser les widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageVictoire);
    layout->addWidget(relancer);
    layout->addWidget(fermer);

    // Appliquer le layout à la boîte de dialogue
    setLayout(layout);
}

VueVictoireMilitaire::VueVictoireMilitaire(Joueur* joueur, QWidget *parent)
    : QDialog(parent), message(QString::fromStdString("Le joueur " + joueur->getNom() + " a gagné par victoire Militaire !"))
{
    messageVictoire = new QLabel(message, this);
    fermer = new QPushButton("Quitter", this);
    relancer = new QPushButton("Relancer", this);

    connect(fermer, &QPushButton::clicked, this, &VueVictoireMilitaire::quitterPartie);
    connect(relancer, &QPushButton::clicked, this, &VueVictoireMilitaire::relancerPartie);

    // Utiliser un layout pour organiser les widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageVictoire);
    layout->addWidget(relancer);
    layout->addWidget(fermer);

    // Appliquer le layout à la boîte de dialogue
    setLayout(layout);
}

VueVictoireNormale::VueVictoireNormale(Joueur* joueur, QWidget *parent)
    : QDialog(parent), message(QString::fromStdString("Le joueur " + joueur->getNom() + " a gagné par points de victoire !"))
{
    messageVictoire = new QLabel(message, this);
    fermer = new QPushButton("Quitter", this);
    relancer = new QPushButton("Relancer", this);

    connect(fermer, &QPushButton::clicked, this, &VueVictoireNormale::quitterPartie);
    connect(relancer, &QPushButton::clicked, this, &VueVictoireNormale::relancerPartie);

    // Utiliser un layout pour organiser les widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageVictoire);
    layout->addWidget(relancer);
    layout->addWidget(fermer);

    // Appliquer le layout à la boîte de dialogue
    setLayout(layout);
}
