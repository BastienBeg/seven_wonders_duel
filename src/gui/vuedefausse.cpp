#include "vuedefausse.h"

VueDefausse::VueDefausse(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Ceci est la fenêtre VueDefausse", this);
    QPushButton *closeButton = new QPushButton("Fermer", this);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    layout->addWidget(label);
    layout->addWidget(closeButton);

    setLayout(layout);
}
