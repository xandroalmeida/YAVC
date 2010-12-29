#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_cbQuality_currentIndexChanged(QString );
    void on_btnRemove_clicked();
    void on_tblMovies_itemClicked(QListWidgetItem* item);
    void on_actionAdd_Movie_triggered();
    void on_actionAbout_triggered();
    void on_actionOptions_triggered();
};

#endif // MAINWINDOW_H
