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

void OptionsDialog::on_pushButton_clicked()
{
    QFileDialog fileDlg;
    fileDlg.setOption(QFileDialog::ShowDirsOnly, true);
    if (fileDlg.exec())
    {
        ui->edtOutputFolder->setText(fileDlg.selectedFiles().at(0));
    }
}
