#ifndef CHOIXJETONDIALOGUE_H
#define CHOIXJETONDIALOGUE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "jeton.h"


class ChoixJetonDialogue : public QDialog {
    Q_OBJECT

public:
    ChoixJetonDialogue(const std::vector<Jeton_Progres*>& jetons, QWidget* parent = nullptr);
    Jeton_Progres* getJetonChoisi() const;

private slots:
    void handleChoisirJeton(int index);

private:
    std::vector<Jeton_Progres*> jetons;
    Jeton_Progres* jetonChoisi;
    QVBoxLayout* layoutJetons;
    QLabel* labelInstructions;
};

#endif // CHOIXJETONDIALOGUE_H
