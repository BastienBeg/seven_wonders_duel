#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QAction>
#include "vuejoueur.h"
#include "vueplateau.h"
#include "partie.h"  // Assurez-vous que Partie est inclus

class VuePartie : public QWidget
{
    Q_OBJECT

public:
    explicit VuePartie(Partie& partie, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void nouvellePartie2J();
    //void nouvellePartie1J();

    void afficherEcranDemarrage();
    void lancerPartie();

private:
    Partie& partie;
    void demanderNomsJoueurs();
    void demanderNomJoueur();
    VuePlateau* plateau;

    QMenu* menuPartie;
    QAction* actionNouvellePartie2J;
    QAction* actionNouvellePartie1J;

    std::string nomJoueur1;
    std::string nomJoueur2;

    QPixmap backgroundPixmap;
};

#endif // VUEPARTIE_H
