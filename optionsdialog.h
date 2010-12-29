#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

private:
    Ui::OptionsDialog *ui;

private slots:
    void on_sldQuality_valueChanged(int value);
};

#endif // OPTIONSDIALOG_H
