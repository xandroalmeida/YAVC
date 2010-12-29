#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QTextEdit>


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
    QTextEdit b;
   // b.sizePolicy()
}
