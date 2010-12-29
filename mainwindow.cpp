#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "aboutdialog.h"
#include "movieinfo.h"

#include <QFileDialog>
#include <QDebug>

static QListWidgetItem* selectedItem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog optDlg;
    optDlg.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog abtDlg;
    abtDlg.exec();
}

void MainWindow::on_actionAdd_Movie_triggered()
{
    QFileDialog fileDlg;
    fileDlg.setFileMode(QFileDialog::ExistingFiles);
    fileDlg.setNameFilter(tr("Movies (*.mov *.*)"));
    if (fileDlg.exec()) {
        for (int i = 0; i < fileDlg.selectedFiles().length(); i++) {
            ui->tblMovies->addItem(fileDlg.selectedFiles()[i]);
        }
    }
}

void MainWindow::on_tblMovies_itemClicked(QListWidgetItem* item)
{
    selectedItem = item;
    ui->txtMovieInfo->setPlainText(MovieInfo::get(item->text()).info());
    ui->btnRemove->setEnabled(true);
    qDebug() << item->text();
}

void MainWindow::on_btnRemove_clicked()
{
    if (selectedItem) {
        ui->tblMovies->removeItemWidget(selectedItem);
        delete selectedItem;
        selectedItem = 0;
        ui->btnRemove->setEnabled(false);
    }
}
