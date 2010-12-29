#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include <QFileDialog>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::on_sldQuality_valueChanged(int value)
{
    this->ui->lblQualityName->setText(QString::number(value));
}

void OptionsDialog::on_pushButton_clicked()
{
    QFileDialog fileDlg;
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
    fileDlg.setAcceptMode(QFileDialog::);
    if (fileDlg.exec())
    {
        fileDlg.selectedFiles().at(0);
    }
}
