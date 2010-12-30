#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "aboutdialog.h"
#include "movieinfo.h"
#include "videoprofile.h"
#include "settings.h"
#include "movieconvertthread.h"

#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <QVariant>
#include <QProcess>

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
    ui->txtOutpuFolder->setText(AppSettings::outputFolder());
    ui->progressBar->hide();
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
    fileDlg.setDirectory(AppSettings::defaultInputFolder());
    if (fileDlg.exec()) {
        AppSettings::setDefaultInputFolder(QFileInfo(fileDlg.selectedFiles()[0]).absoluteDir().absolutePath());
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
    ui->txtOutpuFolder->setEnabled(!enable);
    ui->btnSelectOutputFolder->setEnabled(!enable);
    ui->tblMovies->setEnabled(!enable);
    ui->btnRemove->setEnabled(!enable);
    if (enable)
        ui->progressBar->show();
    else
        ui->progressBar->hide();
}

void MainWindow::on_actionConvert_Movies_triggered()
{
    setUiToConvertingVideo(true);
    QStringList sources;
    for (int i = 0; i < ui->tblMovies->count(); i++) {
        QListWidgetItem* item = ui->tblMovies->itemAt(i,0);
        sources << item->text();
    }
    this->movieConvertThread = new MovieConvertThread(sources);
    connect(this->movieConvertThread
            ,SIGNAL(finished())
            ,this
            ,SLOT(on_movieConverterThread_finished()));
    connect(this->movieConvertThread
            ,SIGNAL(progress(int))
            ,ui->progressBar
            ,SLOT(setValue(int)));

    movieConvertThread->start();
}

void MainWindow::on_actionStop_Convert_triggered()
{
    this->movieConvertThread->stopWhenYouCan();
}

void MainWindow::on_btnSelectOutputFolder_clicked()
{
    QFileDialog fileDlg;
    fileDlg.setOption(QFileDialog::ShowDirsOnly, true);
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
    fileDlg.setDirectory(ui->txtOutpuFolder->text());
    if (fileDlg.exec())
    {
        ui->txtOutpuFolder->setText(fileDlg.selectedFiles().at(0));
        AppSettings::setOutputFolder(ui->txtOutpuFolder->text());
    }
}

void MainWindow::on_txtOutpuFolder_editingFinished()
{
    AppSettings::setOutputFolder(ui->txtOutpuFolder->text());
}



void MainWindow::on_movieConverterThread_finished()
{
    qDebug() << "on_movieConverterThread_finished";
    this->movieConvertThread->disconnect(this);
    delete this->movieConvertThread;
    this->movieConvertThread = NULL;
    setUiToConvertingVideo(false);
}
