#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "aboutdialog.h"
#include "movieinfo.h"
#include "videoprofile.h"


#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <QVariant>

static QListWidgetItem* selectedItem;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<VideoProfile> profiles = VideoProfile::getList();
    for (int i = 0; i < profiles.size(); i++) {
        ui->cbQuality->addItem(profiles.at(i).name());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (selectedItem)
        delete selectedItem;
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
            QListWidgetItem item;
            item.setText(fileDlg.selectedFiles()[i]);
            ui->tblMovies->addItem(fileDlg.selectedFiles()[i]);
        }
    }
    if (ui->tblMovies->count() > 0)
        ui->actionConvert_Movies->setEnabled(true);

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
        ui->txtMovieInfo->setPlainText("");
        if (ui->tblMovies->count() < 1)
            ui->actionConvert_Movies->setEnabled(false);
    }
}

void MainWindow::on_cbQuality_currentIndexChanged(QString str)
{
    qDebug() << str;
}

void MainWindow::setUiToConvertingVideo(bool enable)
{
    ui->actionStop_Convert->setEnabled(enable);

    ui->actionConvert_Movies->setEnabled(!enable);
    ui->actionAdd_Movie->setEnabled(!enable);
    ui->actionOptions->setEnabled(!enable);
    ui->cbQuality->setEnabled(!enable);

}

void MainWindow::on_actionConvert_Movies_triggered()
{
    setUiToConvertingVideo(true);
    for (int i = 0; i < ui->tblMovies->count(); i++) {
        QListWidgetItem* item = ui->tblMovies->itemAt(i,0);
        qDebug() << "Converting" << item->text();

    }
}

void MainWindow::on_actionStop_Convert_triggered()
{
    setUiToConvertingVideo(false);

}
