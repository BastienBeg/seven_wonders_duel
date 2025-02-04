#ifndef VUEMERVEILLE_H
#define VUEMERVEILLE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include "joueur.h"

class VueMerveille : public QDialog {
    Q_OBJECT

public:
    explicit VueMerveille(Joueur* joueur, QWidget *parent = nullptr);
    void refresh();

private:
    Joueur* joueur;
    QVBoxLayout* layoutMerveilles;
    void afficherMerveilles();
};

#endif // VUEMERVEILLE_H
