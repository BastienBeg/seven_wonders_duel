#ifndef VUEDEFAUSSE_H
#define VUEDEFAUSSE_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class VueDefausse: public QDialog
{
    Q_OBJECT

public:
    explicit VueDefausse(QWidget *parent = nullptr);
};

#endif // VUEDEFAUSSE_H
