/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef ABOUTDIALOG_H_
#define ABOUTDIALOG_H_

#include <QDialog>

namespace Ui {
    class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT

 public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

 private:
    Ui::AboutDialog *ui;
};

#endif  // ABOUTDIALOG_H_
