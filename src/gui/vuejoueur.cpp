#include "vuejoueur.h"
#include "vuemerveille.h"

class VueMerveille;

VueJoueur::VueJoueur(Joueur* joueur, QWidget *parent)
    : QWidget(parent), joueur(joueur), vuemescartes(nullptr)
{
    // Création du QLabel avec le texte du nom du joueur
    QLabel *label = new QLabel(QString::fromStdString(joueur->getNom()), this);
    label->setAlignment(Qt::AlignCenter);

    // Création du QPushButton avec le texte "Voir mes cartes"
    QPushButton *button = new QPushButton("Voir mes cartes", this);
    connect(button, &QPushButton::clicked, this, &VueJoueur::ouvrirVueMesCartes);

    // Création du QPushButton avec le texte "Voir mes merveilles"
    QPushButton *buttonMerveilles = new QPushButton("Voir mes merveilles", this);
    connect(buttonMerveilles, &QPushButton::clicked, this, &VueJoueur::ouvrirVueMesMerveilles);

    pieces = new QLabel("Pièces", this);
    nbpiece = new QLCDNumber(this);
    nbpiece->display(joueur->getPiece());

    ptvictoire = new QLabel("Points victoire", this);
    nbptvictoire = new QLCDNumber(this);
    QHBoxLayout* victoireLayout = new QHBoxLayout;
    victoireLayout->addWidget(ptvictoire);
    victoireLayout->addWidget(nbptvictoire);
    // Création du QLabel pour le titre "Ressources"
    ressourcesLabel = new QLabel("Ressources", this);
    ressourcesLabel->setAlignment(Qt::AlignCenter);

    // Création des QLCDNumber et des QLabel pour les descriptions
    argileLCD = new QLCDNumber(this);
    pierreLCD = new QLCDNumber(this);
    boisLCD = new QLCDNumber(this);
    verreLCD = new QLCDNumber(this);
    papyrusLCD = new QLCDNumber(this);


    argileLabel = new QLabel("Argile", this);
    pierreLabel = new QLabel("Pierre", this);
    boisLabel = new QLabel("Bois", this);
    verreLabel = new QLabel("Verre", this);
    papyrusLabel = new QLabel("Papyrus", this);

    // Création d'un layout pour chaque ressource (label + LCD)
    QHBoxLayout *argileLayout = new QHBoxLayout;
    argileLayout->addWidget(argileLabel);
    argileLayout->addWidget(argileLCD);

    QHBoxLayout *pierreLayout = new QHBoxLayout;
    pierreLayout->addWidget(pierreLabel);
    pierreLayout->addWidget(pierreLCD);

    QHBoxLayout *boisLayout = new QHBoxLayout;
    boisLayout->addWidget(boisLabel);
    boisLayout->addWidget(boisLCD);

    QHBoxLayout *verreLayout = new QHBoxLayout;
    verreLayout->addWidget(verreLabel);
    verreLayout->addWidget(verreLCD);

    QHBoxLayout *papyrusLayout = new QHBoxLayout;
    papyrusLayout->addWidget(papyrusLabel);
    papyrusLayout->addWidget(papyrusLCD);

    // Ajout du QLabel au layout de VueJoueur
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(buttonMerveilles);
    layout->addWidget(button);
    layout->addWidget(ressourcesLabel);
    layout->addLayout(argileLayout);
    layout->addLayout(pierreLayout);
    layout->addLayout(boisLayout);
    layout->addLayout(verreLayout);
    layout->addLayout(papyrusLayout);
    layout->addWidget(pieces);
    layout->addWidget(nbpiece);
    layout->addLayout(victoireLayout);
    setLayout(layout);

    vuemescartes = new QDialog(this);
    vuemescartes->setWindowTitle("Mes Cartes");

    // Créez une QScrollArea
    QScrollArea* scrollArea = new QScrollArea(vuemescartes);
    scrollArea->setWidgetResizable(true);

    // Créez un widget de contenu pour la zone de défilement
    QWidget* contenu = new QWidget();
    contenu->setMinimumSize(contenu->sizeHint()); // Ajuster la taille minimale du contenu
    cartesLayout = new QVBoxLayout(contenu);

    // Ajoutez le layout au widget de contenu
    contenu->setLayout(cartesLayout);

    // Définissez le widget de contenu comme le widget de la zone de défilement
    scrollArea->setWidget(contenu);

    // Créez un layout principal pour le QDialog et ajoutez la QScrollArea
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(vuemescartes);
    layoutPrincipal->addWidget(scrollArea);

    vuemescartes->setLayout(layoutPrincipal);

    // Mise à jour automatique de la vue des cartes
    updateVueMesCartes();
}

void VueJoueur::ouvrirVueMesMerveilles() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Mes Merveilles");

    QHBoxLayout* layoutMerveilles = new QHBoxLayout(dialog);

    // Afficher les noms des merveilles possédées non construites avec images
    for (Merveille* merveille : joueur->getMerveillesPossede()) {
        if (!joueur->estConstruite(merveille)) {
            QLabel* label = new QLabel(dialog);
            label->setText(QString::fromStdString(merveille->getNom()));
            layoutMerveilles->addWidget(label);
            QPixmap pixmap(QString::fromStdString(merveille->getCheminImage()));
            if (pixmap.isNull()) {
                qDebug() << "Erreur : Impossible de charger l'image pour la merveille : " << QString::fromStdString(merveille->getCheminImage());
            } else {
                QLabel* imageLabel = new QLabel(dialog);
                imageLabel->setPixmap(pixmap.scaled(400, 250)); // Redimensionner l'image si nécessaire
                layoutMerveilles->addWidget(imageLabel);
            }


        }
    }

    dialog->setLayout(layoutMerveilles);
    dialog->exec();
}
void VueJoueur::ouvrirVueMesCartes() {
    if (!vuemescartes) {
        vuemescartes = new QDialog(this);
        vuemescartes->setWindowTitle("Mes Cartes");
    }
    vuemescartes->exec();
}

void VueJoueur::updateVueMesCartes() {
    if (!cartesLayout) {
        qWarning() << "cartesLayout is null";
        return;
    }

    // Clear previous cards
    QLayoutItem* item;
    while ((item = cartesLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Add current cards
    const std::vector<Carte*>& cartes = joueur->getCartes();
    afficherCartes(cartes);
}

void VueJoueur::afficherCartes(const std::vector<Carte*>& cartes) {
    for (Carte* carte : cartes) {
        if (!carte) {
            qWarning() << "carte is null";
            continue;
        }

        // Créez un QLabel pour afficher l'illustration de la carte
        QLabel* label = new QLabel(this);
        QPixmap pixmap(QString::fromStdString(carte->getCheminImage()));
        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image pour la carte : " << QString::fromStdString(carte->getCheminImage());
        } else {
            label->setPixmap(pixmap.scaled(100, 150)); // Redimensionnez l'image si nécessaire
        }

        // Ajoutez le QLabel au layout
        cartesLayout->addWidget(label);
    }
}

std::string VueJoueur::getnomJoueur() const {
    return joueur->getNom();
}

void VueJoueur::setActif(bool actif) {
    if (actif) {
        setStyleSheet("background-color: lightgreen;");
    } else {
        setStyleSheet("");
    }
}

void VueJoueur::refresh() {
    Partie& partie = Partie::getInstance();

    // Mettre à jour les pièces
    nbpiece->display(joueur->getPiece());

    // Mettre à jour les ressources
    Ressource* ressources = joueur->getRessources();
    argileLCD->display(ressources->getArgile());
    pierreLCD->display(ressources->getFer());
    boisLCD->display(ressources->getBois());
    verreLCD->display(ressources->getVerre());
    papyrusLCD->display(ressources->getPapyrus());
    nbptvictoire->display(joueur->getPointsVictoire());
    setActif(joueur == partie.getActuel());
    updateVueMesCartes();
}

void VueJoueur::testAfficherMerveillesNonConstruites() {
    qDebug() << "Merveilles possédées mais non construites pour le joueur :" << QString::fromStdString(joueur->getNom());
    for (Merveille* merveille : joueur->getMerveillesPossede()) {
        if (!joueur->estConstruite(merveille)) {
            qDebug() << "Merveille :" << QString::fromStdString(merveille->getNom());
        }
    }
}
