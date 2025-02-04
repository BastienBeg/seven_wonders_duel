#ifndef VUEVICTOIRE_H
#define VUEVICTOIRE_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "joueur.h"

class VueVictoireScientifique : public QDialog {
    Q_OBJECT

public:
    explicit VueVictoireScientifique(Joueur* joueur, QWidget *parent = nullptr);

signals:
    void quitterPartie();
    void relancerPartie();

private:
    QString message;
    QLabel* messageVictoire;
    QPushButton* fermer;
    QPushButton* relancer;
};

class VueVictoireMilitaire : public QDialog {
    Q_OBJECT

public:
    explicit VueVictoireMilitaire(Joueur* joueur, QWidget *parent = nullptr);

signals:
    void quitterPartie();
    void relancerPartie();

private:
    QString message;
    QLabel* messageVictoire;
    QPushButton* fermer;
    QPushButton* relancer;
};


class VueVictoireNormale : public QDialog {
    Q_OBJECT

public:
    explicit VueVictoireNormale(Joueur* joueur, QWidget *parent = nullptr);

signals:
    void quitterPartie();
    void relancerPartie();

private:
    QString message;
    QLabel* messageVictoire;
    QPushButton* fermer;
    QPushButton* relancer;
};

#endif // VUEVICTOIRE_H
