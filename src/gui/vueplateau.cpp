#include "vueplateau.h"
#include "partie.h"
#include "vuejoueur.h"
#include "vuepartie.h"
#include <QPixmap>
#include <QDebug>
#include <qmessagebox.h>
#include <QStackedLayout>
#include <QApplication>
#include "vuevictoire.h"

CustomSlider::CustomSlider(QWidget *parent)
    : QSlider(parent)
{
    setStyleSheet(R"(
        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 8px;
            background: #bcbcbc;
            margin: 2px 0;
            border-radius: 4px;
        }
        QSlider::handle:horizontal {
            background: #24445C;
            border: 1px solid #444;
            width: 18px;
            height: 18px;
            border-radius: 9px;
            margin: -2px 0;
        }
        QSlider::sub-page:horizontal {
            background: #b82010;
        }
        QSlider::add-page:horizontal {
            background: #0000FF;
        }
    )");
}

VuePlateau::VuePlateau(Plateau* plateau, QWidget *parent)
    : QWidget(parent), plateau(plateau), vuedefausse(nullptr)
{
    Partie& partie = Partie::getInstance();

    plateauMilitaire = new CustomSlider(this);
    plateauMilitaire->setOrientation(Qt::Horizontal);
    plateauMilitaire->setRange(-9, 9); // Définir la plage de la jauge de -9 à 9
    plateauMilitaire->setValue(0);
    plateauMilitaire->setTickPosition(QSlider::TicksBelow); // Afficher les graduations en dessous
    plateauMilitaire->setTickInterval(1); // Intervalle entre les graduations
    plateauMilitaire->setEnabled(false); // Rendre le slider non interactif

    // Création des vues des joueurs
    vueJoueur1 = new VueJoueur(partie.getJ1(), this);
    vueJoueur2 = new VueJoueur(partie.getJ2(), this);

    // Création des cadres des joueurs
    QFrame *frameJoueur1 = new QFrame(this);
    frameJoueur1->setFrameStyle(QFrame::Box | QFrame::Raised);
    frameJoueur1->setMaximumSize(600, 500);
    QVBoxLayout *layoutJoueur1 = new QVBoxLayout(frameJoueur1);
    layoutJoueur1->addWidget(vueJoueur1);

    QFrame *frameJoueur2 = new QFrame(this);
    frameJoueur2->setFrameStyle(QFrame::Box | QFrame::Raised);
    frameJoueur2->setMaximumSize(600, 500);
    QVBoxLayout *layoutJoueur2 = new QVBoxLayout(frameJoueur2);
    layoutJoueur2->addWidget(vueJoueur2);

    // Création du cadre pour le plateau militaire
    QFrame *framePlateauMilitaire = new QFrame(this);
    framePlateauMilitaire->setMaximumSize(1150, 100);
    framePlateauMilitaire->setFrameStyle(QFrame::Box | QFrame::Raised);
    QVBoxLayout *layoutPlateauMilitaire = new QVBoxLayout(framePlateauMilitaire);
    QLabel *nomMilitaire = new QLabel("Plateau Militaire", this);
    nomMilitaire->setAlignment(Qt::AlignCenter); // Alignement du texte au centre
    layoutPlateauMilitaire->addWidget(nomMilitaire);
    layoutPlateauMilitaire->addWidget(plateauMilitaire);

    // Création du layout pour la partie droite
    QVBoxLayout* joueursLayout = new QVBoxLayout;
    joueursLayout->addWidget(framePlateauMilitaire);

    // Création de la QGridLayout pour afficher les cartes
    layoutCartes = new QGridLayout;
    joueursLayout->addLayout(layoutCartes);

    QPushButton *button = new QPushButton("Voir la défausse", this);
    connect(button, &QPushButton::clicked, this, &VuePlateau::ouvrirDefausse);
    joueursLayout->addWidget(button);

    vuedefausse = new QDialog(this);
    vuedefausse->setWindowTitle("Defausse");

    // Créez une QScrollArea
    QScrollArea* scrollArea = new QScrollArea(vuedefausse);
    scrollArea->setWidgetResizable(true);

    // Créez un widget de contenu pour la zone de défilement
    QWidget* contenu = new QWidget();
    contenu->setMinimumSize(contenu->sizeHint()); // Ajuste la taille minimale du contenu
    defausseLayout = new QVBoxLayout(contenu);

    // Ajoutez le layout au widget de contenu
    contenu->setLayout(defausseLayout);

    // Définissez le widget de contenu comme le widget de la zone de défilement
    scrollArea->setWidget(contenu);

    // Créez un layout principal pour le QDialog et ajoutez la QScrollArea
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(vuedefausse);
    layoutPrincipal->addWidget(scrollArea);

    vuedefausse->setLayout(layoutPrincipal);

    // Mise à jour automatique de la vue des cartes
    updateDefausse();


    // Création du layout pour les vues des joueurs
    QVBoxLayout* playerLayout = new QVBoxLayout;
    playerLayout->addWidget(frameJoueur1);
    playerLayout->addWidget(frameJoueur2);

    // Ajout du layout des jetons de progrès
    layoutJetonsProgres = new QHBoxLayout;
    afficherJetonsProgres();
    joueursLayout->addLayout(layoutJetonsProgres);

    // Création du layout principal
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(playerLayout);
    mainLayout->addLayout(joueursLayout);

    setLayout(mainLayout);
    refreshJoueurs();
}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    QSlider::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::white); // Couleur des graduations

    int interval = tickInterval();
    if (interval <= 0) return;

    for (int i = minimum(); i <= maximum(); i += interval) {
        int x = QStyle::sliderPositionFromValue(minimum(), maximum(), i, width());
        painter.drawText(QPointF(x, height() - 10), QString::number(i));
    }
}

void VuePlateau::afficherJetonsProgres() {
    // Nettoyer les widgets précédents
    QLayoutItem* item;
    while ((item = layoutJetonsProgres->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    layoutJetonsProgres->addWidget(new QLabel("Jetons progrès:", this));
    std::vector<Jeton_Progres*> jetons = plateau->getJetonsProgresEnJeu();
    for (Jeton_Progres* jeton : jetons) {
        QLabel* label = new QLabel(this);

        QPixmap pixmap(QString::fromStdString(jeton->getCheminImage()));
        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image pour le jeton de progrès : " << QString::fromStdString(jeton->getCheminImage());
            label->setText(QString::fromStdString(jeton->getNom())); // Afficher le nom si l'image ne peut pas être chargée
        } else {
            label->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio)); // Redimensionner l'image si nécessaire
            label->setScaledContents(true); // Assure que le QLabel redimensionne l'image pour remplir le label
            label->setMaximumSize(150, 150);
        }

        layoutJetonsProgres->addWidget(label);
    }
}
Carte* VuePlateau::afficherChoixCartes(std::vector<Carte *> cartes) {
    vueChoixCartes = new QDialog(this);
    vueChoixCartes->setWindowTitle("Choix carte");

    layoutChoixCartes = new QHBoxLayout(vueChoixCartes);
    layoutChoixCartes->addWidget(new QLabel("Choississez une carte :", vueChoixCartes));
    for (Carte* carte : cartes) {
        ClickableLabel* label = new ClickableLabel(vueChoixCartes);

        QPixmap pixmap(QString::fromStdString(carte->getCheminImage()));
        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image pour le jeton de progrès : " << QString::fromStdString(carte->getCheminImage());
            label->setText(QString::fromStdString(carte->getNom()));
        } else {
            label->setPixmap(pixmap.scaled(150, 100, Qt::KeepAspectRatio));
            label->setScaledContents(true);
        }

        // Utilisation de [=] pour capturer 'carte' par valeur dans le lambda
        connect(label, &ClickableLabel::clicked, [=]() {
            handleChoixCarte(carte);
        });

        layoutChoixCartes->addWidget(label);
    }


    carteSelectionnee = nullptr;  // Réinitialiser la carte sélectionnée
    vueChoixCartes->exec();

    return carteSelectionnee;
}
void VuePlateau::handleChoixCarte(Carte* carte){
    carteSelectionnee = carte;
    vueChoixCartes->accept();
}


Jeton_Progres* VuePlateau::afficherChoixJeton(std::vector<Jeton_Progres *> jetons) {
    std::cout<< "checkpoint 1" << std::endl;
    vueChoixJetons = new QDialog(this);
    vueChoixJetons->setWindowTitle("Choix Jeton");

    layoutChoixJetons = new QHBoxLayout(vueChoixJetons);
    layoutChoixJetons->addWidget(new QLabel("Choisissez un jeton :", vueChoixJetons));
    std::cout<< "chekpoint 2" << std::endl;
    for (Jeton_Progres* jeton : jetons) {
        ClickableLabel* label = new ClickableLabel(vueChoixJetons);

        QPixmap pixmap(QString::fromStdString(jeton->getCheminImage()));
        if (pixmap.isNull()) {
            std::cout<< "checkpoint 3" << std::endl;
            qDebug() << "Erreur : Impossible de charger l'image pour le jeton de progrès : " << QString::fromStdString(jeton->getCheminImage());
            label->setText(QString::fromStdString(jeton->getNom()));
        } else {
            std::cout<< "checkpoint 4" << std::endl;
            label->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
            label->setScaledContents(true);
        }

        connect(label, &ClickableLabel::clicked, [=]() {
            handleChoixJeton(jeton);
        });
        layoutChoixJetons->addWidget(label);
    }
    jetonSelectionnee = nullptr;  // Réinitialiser le jeton sélectionné
    vueChoixJetons->exec();
    return jetonSelectionnee;
}
void VuePlateau::handleChoixJeton(Jeton_Progres* jeton){
    jetonSelectionnee = jeton;
    vueChoixJetons->accept();
}

Joueur* VuePlateau::afficherChoixJoueur(Joueur* joueur) {
    vueChoixJoueur = new QDialog(this);
    vueChoixJoueur->setWindowTitle("choix joueur");

    layoutChoixJoueur = new QHBoxLayout(vueChoixJoueur);
    QString message = "Le joueur " + QString::fromStdString(joueur->getNom()) + " doit choisir qui commence le prochain âge :";

    layoutChoixJoueur->addWidget(new QLabel(message));

    ClickableLabel* labeljoueur1 = new ClickableLabel(vueChoixJoueur);
    labeljoueur1->setText(QString::fromStdString(joueur->getNom()));
    connect(labeljoueur1, &ClickableLabel::clicked, [=]() {
        handleChoixJoueur(joueur);
    });
    labeljoueur1->setMinimumSize(50,150);
    ClickableLabel* labeljoueur2 = new ClickableLabel(vueChoixJoueur);
    labeljoueur2->setText(QString::fromStdString(joueur->getAdversaire()->getNom()));
    connect(labeljoueur2, &ClickableLabel::clicked, [=]() {
        handleChoixJoueur(joueur->getAdversaire());
    });
    labeljoueur2->setMinimumSize(50,150);
    layoutChoixJoueur->addWidget(labeljoueur1);
    layoutChoixJoueur->addWidget(labeljoueur2);
    joueurSelectionnee = nullptr;  // Réinitialiser le jeton sélectionné
    vueChoixJoueur->exec();

    return joueurSelectionnee;
}
void VuePlateau::handleChoixJoueur(Joueur* joueur){
    joueurSelectionnee = joueur;
    vueChoixJoueur->accept();
}
void VuePlateau::updateJetons(){
    // Suppression des widgets existants dans layoutJetonsProgres
    QLayoutItem* child;
    while ((child = layoutJetonsProgres->takeAt(0)) != nullptr) {
        delete child->widget(); // Supprime le widget associé
        delete child; // Supprime l'élément de layout
    }

    // Appel de la méthode pour afficher les nouveaux jetons
    afficherJetonsProgres();
}

void VuePlateau::afficherCartesAge(Plateau* plateau, AGE age) {
    this->plateau = plateau;

    // Clear previous cards
    while (QLayoutItem* item = layoutCartes->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    // Get the cards for the specified age
    std::vector<Carte*> cartes;
    if (age == AGE::AGE1) {
        cartes = plateau->getCartesAgeI();
    } else if (age == AGE::AGE2) {
        cartes = plateau->getCartesAgeII();
    } else if (age == AGE::AGE3) {
        cartes = plateau->getCartesAgeIII();
    }

    // Define positions for each age
    std::vector<std::pair<int, int>> positions;
    if (age == AGE::AGE1) {
        positions = {{0, 5}, {0, 7}, {1, 4}, {1, 6}, {1, 8}, {2, 3}, {2, 5}, {2, 7}, {2, 9}, {3, 2}, {3, 4}, {3, 6}, {3, 8}, {3, 10}, {4, 1}, {4, 3}, {4, 5}, {4, 7}, {4, 9}, {4, 11}};
    } else if (age == AGE::AGE2) {
        positions = {{0, 0}, {0, 2}, {0, 4}, {0, 6}, {0, 8}, {0, 10}, {1, 1}, {1, 3}, {1, 5}, {1, 7}, {1, 9}, {2, 2}, {2, 4}, {2, 6}, {2, 8}, {3, 3}, {3, 5}, {3, 7}, {4, 4}, {4, 6}};
    } else if (age == AGE::AGE3) {
        positions = {{0, 5}, {0, 7}, {1, 4}, {1, 6}, {1, 8}, {2, 3}, {2, 5}, {2, 7}, {2, 9}, {3, 4}, {3, 8}, {4, 3}, {4, 5}, {4, 7}, {4, 9}, {5, 4}, {5, 6}, {5, 8}, {6, 5}, {6, 7}};
    }

    // Display the cards in the predefined positions
    for (size_t i = 0; i < cartes.size(); ++i) {
        Carte* carte = cartes[i];
        ClickableLabel* label = new ClickableLabel(this);

        QPixmap pixmap;
        if (age == AGE::AGE1) {
            pixmap = QPixmap(carte->estCachee() && !carte->estJouable() ? "../../ressources/dos_age_un.png" : QString::fromStdString(carte->getCheminImage()));
        } else if (age == AGE::AGE2) {
            pixmap = QPixmap(carte->estCachee() && !carte->estJouable() ? "../../ressources/dos_age_deux.png" : QString::fromStdString(carte->getCheminImage()));
        } else if (age == AGE::AGE3) {
            pixmap = QPixmap(carte->estCachee() && !carte->estJouable() ? "../../ressources/dos_age_trois.png" : QString::fromStdString(carte->getCheminImage()));
        }

        if (pixmap.isNull()) {
            qDebug() << "Erreur : Impossible de charger l'image pour la carte : " << QString::fromStdString(carte->getCheminImage());
        } else {
            label->setPixmap(pixmap.scaled(75, 100)); // Redimensionnez l'image si nécessaire
        }
        connect(label, &ClickableLabel::clicked, [this, carte]() {
            handleCarteCliquee(carte);
        });
        layoutCartes->addWidget(label, positions[i].first, positions[i].second);
    }
}


void VuePlateau::refreshCartes() {
    afficherCartesAge(plateau, plateau->getAge());
}

void VuePlateau::handleCarteCliquee(Carte* carte) {

    if(carte->estJouable()){
        ChoixDialogue* dialogue = new ChoixDialogue(carte, this);
        connect(dialogue, &ChoixDialogue::defausserCarte, this, &VuePlateau::handleDefausser);
        connect(dialogue, &ChoixDialogue::construireBatiment, this, &VuePlateau::handleConstruireBatiment);
        connect(dialogue, &ChoixDialogue::construireMerveille, this, &VuePlateau::handleConstruireMerveille);
        dialogue->exec();}
    else{QMessageBox::warning(this, "Échec", "Carte non jouable !");}

}

void VuePlateau::handleDefausser(Carte* carte) {
    Partie& partie = Partie::getInstance();
    partie.getActuel()->setPeutRejouer(false);
    partie.getActuel()->piece_de_defausse(carte);
    partie.getPlateau()->ajouter_carte_defausse(carte);
    const std::vector<Carte*>& defausse = partie.getPlateau()->defausse;

    std::cout << "Cartes dans la défausse :" << std::endl;
    for (const Carte* carte : defausse) {
        std::cout << " - " << carte->getNom() << std::endl;
    }

    cout << "Carte Defaussee !" << endl;
    // On retire la carte du plateau, comme dans la défausse
    carte->setDetenu(true);
    // On check l'age avant de jouer pour pouvoir choisir qui commence au prochain tour si l'age se finit
    AGE age_avant_tour = plateau->getAge();
    plateau->retirer_carte(plateau->getAge(), carte);
    updateDefausse();
    if(age_avant_tour != plateau->getAge() && plateau->getAge() != AGE::FIN){
        tour_joueur_debut_age();
    }
    else{
        partie.changement_joueur();
    }   
    refreshJoueurs();
    refreshCartes();
    victoire();
}

void VuePlateau::handleConstruireBatiment(Carte* carte) {
    Partie& partie = Partie::getInstance();

    bool test = carte->jouer_carte(partie.getActuel());
    if (test) {
        cout << "Carte Construite !" << endl;
        // On retire la carte du plateau, comme dans la défausse
        carte->setDetenu(true);
        // On check l'age avant de jouer pour pouvoir choisir qui commence au prochain tour si l'age se finit
        AGE age_avant_tour = plateau->getAge();
        plateau->retirer_carte(plateau->getAge(), carte);
        if(age_avant_tour != plateau->getAge() && plateau->getAge() != AGE::FIN){
            tour_joueur_debut_age();
        }
        else{
            partie.changement_joueur();
        }
        refreshJoueurs();
    } else {
        partie.getActuel()->setPeutRejouer(true);
        std::cout << "Pas assez de ressources/pièces pour la construire, veuillez rejouer." << std::endl;
    }
    refreshCartes();
    updatePlateauMilitaire();
    updateJetons();
    victoire();

}

void VuePlateau::handleConstruireMerveille(Carte* carte) {
    Partie& partie = Partie::getInstance();
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Construire une merveille");

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QLabel* label = new QLabel("Choisissez une merveille à construire:", dialog);
    layout->addWidget(label);

    QVBoxLayout* layoutMerveilles = new QVBoxLayout;
    layout->addLayout(layoutMerveilles);

    int row = 0;
    for (Merveille* merveille : partie.getActuel()->getMerveillesPossede()) {
        if (!partie.getActuel()->estConstruite(merveille)) {
            QPushButton* button = new QPushButton(QString::fromStdString(merveille->getNom()), dialog);
            connect(button, &QPushButton::clicked, [this, merveille, carte, dialog, &partie]() {
                if (partie.getActuel()->construire_merveille_gui(merveille)) {
                    QMessageBox::information(this, "Succès", "La merveille a été construite !");
                    carte->setDetenu(true);
                    // On check l'age avant de jouer pour pouvoir choisir qui commence au prochain tour si l'age se finit
                    AGE age_avant_tour = plateau->getAge();
                    plateau->retirer_carte(plateau->getAge(), carte);
                    merveille->getBonus()->joue_le_bonus(partie.getActuel(), this);
                    if(age_avant_tour != plateau->getAge() && plateau->getAge() != AGE::FIN){
                        tour_joueur_debut_age();
                    }
                    else{
                        partie.changement_joueur();
                    }
                    refreshJoueurs();
                } else {
                    QMessageBox::warning(this, "Échec", "Vous n'avez pas assez de ressources pour construire cette merveille.");
                }
                dialog->accept(); // Fermer le dialogue après tentative de construction
            });
            layoutMerveilles->addWidget(button);
            row++;
        }
    }

    dialog->exec();
    refreshCartes();
    updatePlateauMilitaire();
    victoire();
}

void VuePlateau::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event); // Appel à la fonction de base

    QPainter painter(this);
    // Ajoutez ici le code pour dessiner des éléments supplémentaires sur le plateau
}
void VuePlateau::ouvrirDefausse() {
    Partie& partie = Partie::getInstance();
    if (!vuedefausse) {
        vuedefausse = new QDialog(this);
        vuedefausse->setWindowTitle("Défausse");
        defausseLayout = new QVBoxLayout(vuedefausse);
        vuedefausse->setLayout(defausseLayout);
    }

    updateDefausse();
    vuedefausse->exec();
}

void VuePlateau::updateDefausse() {
    if (!defausseLayout) {
        qWarning() << "defausseLayout is null";
        return;
    }

    // Clear previous cards
    QLayoutItem* item;
    while ((item = defausseLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Add current cards
    const std::vector<Carte*>& defausse = plateau->getDefausse();
    afficherDefausse(defausse);
}

void VuePlateau::afficherDefausse(const std::vector<Carte*>& cartes) {
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
        defausseLayout->addWidget(label);
    }
}

void VuePlateau::refreshJoueurs() {
    vueJoueur1->refresh();
    vueJoueur2->refresh();
}

void VuePlateau::updatePlateauMilitaire() {
    Partie& partie = Partie::getInstance();
    plateauMilitaire->setValue(partie.getPlateau()->getPlateauMilitaire()->getPosition());
}

void VuePlateau::tour_joueur_debut_age() {
    Partie& partie = Partie::getInstance();
    int position_militaire = partie.getPlateau()->getPlateauMilitaire()->getPosition();
    partie.getJ1()->setPeutRejouer(false);
    partie.getJ2()->setPeutRejouer(false);
    Joueur* joueur_choisi_pour_commencer;
    // Si le joueur 1 est mené militairement, alors il doit choisir qui commence le prochain tour
    if (position_militaire < 0) {
        /* Permettre au joueur 1 de choisir qui commence le prochain tour, donc mettre joueur actuel au choix du joueur en question */
        joueur_choisi_pour_commencer = afficherChoixJoueur(partie.getJ1());
    } else if (position_militaire > 0) {
        /* Permettre au joueur 2 de choisir le prochain joueur (comme au-dessus) */
        joueur_choisi_pour_commencer = afficherChoixJoueur(partie.getJ2());
    } else {
        // Le dernier joueur commence le prochain tour donc on ne change pas le joueur actuel
        joueur_choisi_pour_commencer = afficherChoixJoueur(partie.getActuel());
    }
    partie.setActuel(joueur_choisi_pour_commencer);
}

void VuePlateau::restartGame() {
    this->hide();
    Partie& partie = Partie::getInstance();
    partie.resetInstance();
    VuePartie* nouvelleVuePartie = new VuePartie(partie);
    nouvelleVuePartie->showMaximized();
}

void VuePlateau::victoire() {
    Partie& partie = Partie::getInstance();
    Joueur* joueur1 = partie.getJ1();
    Joueur* joueur2 = partie.getJ2();

    // Vérifier la victoire militaire
    if (partie.getPlateau()->getPlateauMilitaire()->getPosition() >= 9) {
        VueVictoireMilitaire* victoireMilitaire = new VueVictoireMilitaire(joueur1);
        connect(victoireMilitaire, &VueVictoireMilitaire::quitterPartie, qApp, &QApplication::quit);
        connect(victoireMilitaire, &VueVictoireMilitaire::relancerPartie, this, &VuePlateau::restartGame);
        victoireMilitaire->exec();
    } else if (partie.getPlateau()->getPlateauMilitaire()->getPosition() <= -9) {
        VueVictoireMilitaire* victoireMilitaire = new VueVictoireMilitaire(joueur2);
        connect(victoireMilitaire, &VueVictoireMilitaire::quitterPartie, qApp, &QApplication::quit);
        connect(victoireMilitaire, &VueVictoireMilitaire::relancerPartie, this, &VuePlateau::restartGame);
        victoireMilitaire->exec();
    }

    // Vérifier la victoire scientifique
    const int requiredJetonsScientifiques = 6;
    if (joueur1->getSymbolScientifique().size() >= requiredJetonsScientifiques) {
        VueVictoireScientifique* victoireScientifique = new VueVictoireScientifique(joueur1);
        connect(victoireScientifique, &VueVictoireScientifique::quitterPartie, qApp, &QApplication::quit);
        connect(victoireScientifique, &VueVictoireScientifique::relancerPartie, this, &VuePlateau::restartGame);
        victoireScientifique->exec();
    } else if (joueur2->getSymbolScientifique().size() >= requiredJetonsScientifiques) {
        VueVictoireScientifique* victoireScientifique = new VueVictoireScientifique(joueur2);
        connect(victoireScientifique, &VueVictoireScientifique::quitterPartie, qApp, &QApplication::quit);
        connect(victoireScientifique, &VueVictoireScientifique::relancerPartie, this, &VuePlateau::restartGame);
        victoireScientifique->exec();
    }

    // Vérifier la victoire normale (par points de victoire)
    int pointsJoueur1 = partie.calculer_point(partie.getJ1());
    int pointsJoueur2 = partie.calculer_point(partie.getJ2());

    if (pointsJoueur1 > pointsJoueur2 && plateau->getAge() == AGE::FIN) {
        VueVictoireNormale* victoireNormale = new VueVictoireNormale(joueur1);
        connect(victoireNormale, &VueVictoireNormale::quitterPartie, qApp, &QApplication::quit);
        connect(victoireNormale, &VueVictoireNormale::relancerPartie, this, &VuePlateau::restartGame);
        victoireNormale->exec();
    } else if (pointsJoueur2 > pointsJoueur1 && plateau->getAge() == AGE::FIN) {
        VueVictoireNormale* victoireNormale = new VueVictoireNormale(joueur2);
        connect(victoireNormale, &VueVictoireNormale::quitterPartie, qApp, &QApplication::quit);
        connect(victoireNormale, &VueVictoireNormale::relancerPartie, this, &VuePlateau::restartGame);
        victoireNormale->exec();
    } else if (plateau->getAge() == AGE::FIN) {
        // En cas d'égalité, il faut gérer ici selon les règles du jeu
        int compteur_j1 = 0;
        int compteur_j2 = 0;
        std::vector<Carte*> carte_j1 = partie.getJ1()->getCartes();
        std::vector<Carte*> carte_j2 = partie.getJ2()->getCartes();

        // on ajoute
        for (Carte* carte : carte_j1) {
            if (carte->getTypeCarte() == Type_Carte::CIVIL) {
                Carte_civil* carteCivil = dynamic_cast<Carte_civil*>(carte);
                if (carteCivil) {
                    compteur_j1 = compteur_j1 + carteCivil->getPointVictoire();
                }
            }
        }

        for (Carte* carte : carte_j2) {
            if (carte->getTypeCarte() == Type_Carte::CIVIL) {
                Carte_civil* carteCivil = dynamic_cast<Carte_civil*>(carte);
                if (carteCivil) {
                    compteur_j2 = compteur_j2 + carteCivil->getPointVictoire();
                }
            }

        }
        VueVictoireNormale* victoireNormale = nullptr;
        if (compteur_j1 >= compteur_j2){
            victoireNormale = new VueVictoireNormale(joueur1);
        }
        else {
            victoireNormale = new VueVictoireNormale(joueur2);
        }
        connect(victoireNormale, &VueVictoireNormale::quitterPartie, qApp, &QApplication::quit);
        connect(victoireNormale, &VueVictoireNormale::relancerPartie, this, &VuePlateau::restartGame);
        victoireNormale->exec();



    }
}
