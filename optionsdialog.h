/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef OPTIONSDIALOG_H_
#define OPTIONSDIALOG_H_

#include <QDialog>

namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog {
    Q_OBJECT

 public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

 private:
    Ui::OptionsDialog *ui;

 private slots:
    void on_pushButton_clicked();
};

#endif  // OPTIONSDIALOG_H_
