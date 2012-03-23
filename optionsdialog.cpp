/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include <QFileDialog>

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::OptionsDialog) {
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog() {
    delete ui;
}

void OptionsDialog::on_pushButton_clicked() {
    QFileDialog fileDlg;
    fileDlg.setOption(QFileDialog::ShowDirsOnly, true);
    if (fileDlg.exec()) {
        ui->edtOutputFolder->setText(fileDlg.selectedFiles().at(0));
    }
}
