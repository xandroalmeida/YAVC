#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "aboutdialog.h"
#include "videoprofile.h"
#include "settings.h"
#include "movieconvertthread.h"

#include <QFileDialog>
#include <QList>
#include <QDebug>
#include <QVariant>
#include <QProcess>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_selectedItem = NULL;

    QList<VideoProfile> profiles = VideoProfile::getList();
    for (int i = 0; i < profiles.size(); i++) {
        QVariant data;
        data.setValue(profiles.at(i));
        ui->cbQuality->addItem(profiles.at(i).name(), data);
    }
    ui->txtOutpuFolder->setText(AppSettings::outputFolder());
    ui->pbMovie->hide();
    ui->pbTotal->hide();
    this->movieConvertThread = NULL;

    this->ui->tblMovies->model();
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
    fileDlg.setDirectory(AppSettings::defaultInputFolder());
    if (fileDlg.exec()) {
        AppSettings::setDefaultInputFolder(QFileInfo(fileDlg.selectedFiles()[0]).absoluteDir().absolutePath());
        for (int i = 0; i < fileDlg.selectedFiles().length(); i++) {
            QListWidgetItem item;
            item.setText(fileDlg.selectedFiles()[i]);
            addMovie(fileDlg.selectedFiles()[i]);
        }
    }

    if (hasMovieToConvert())
        ui->actionConvert_Movies->setEnabled(true);

}

void MainWindow::on_btnRemove_clicked()
{
    if (m_selectedItem) {
        removeselectedMovieMovie();
        ui->btnRemove->setEnabled(false);
        ui->txtMovieInfo->setPlainText("");

        if (hasMovieToConvert())
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
    if (enable) {
        ui->pbMovie->show();
        ui->pbTotal->show();
    } else {
        ui->pbMovie->hide();
        ui->pbTotal->hide();
    }
}

void MainWindow::on_actionConvert_Movies_triggered()
{
    setUiToConvertingVideo(true);
    QStringList sources;

    for (int i = 0; i < ui->tblMovies->count(); i++) {
        QListWidgetItem* item = ui->tblMovies->itemAt(i,0);
        sources << item->text();
    }

    int idx = ui->cbQuality->currentIndex();
    VideoProfile data = ui->cbQuality->itemData(idx).value<VideoProfile>();
    this->movieConvertThread = new MovieConvertThread(sources, data);
    connect(this->movieConvertThread
            ,SIGNAL(finished())
            ,this
            ,SLOT(on_movieConverterThread_finished()));
    connect(this->movieConvertThread
            ,SIGNAL(progress(int))
            ,ui->pbMovie
            ,SLOT(setValue(int)));
    ui->pbMovie->setValue(0);
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (this->movieConvertThread != NULL) {
        this->movieConvertThread->stopWhenYouCan();
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::addMovie(QString const &fileName)
{
    qDebug() << "addMovie" << fileName;
    MovieInfo movieInfo = MovieInfo::get(fileName);
    QVariant data;
    data.setValue(movieInfo);

    QListWidgetItem* item = new QListWidgetItem(fileName);
    item->setData(Qt::UserRole, data);
    ui->tblMovies->addItem(item);
}

bool MainWindow::hasMovieToConvert()
{
    return ui->tblMovies->count() > 0;
}

void MainWindow::removeselectedMovieMovie()
{
    if (m_selectedItem) {
        ui->tblMovies->removeItemWidget(m_selectedItem);
        delete m_selectedItem;
        m_selectedItem = NULL;
    }
}

void MainWindow::on_tblMovies_itemClicked(QListWidgetItem* item)
{
    ui->txtMovieInfo->setPlainText(item->data(Qt::UserRole).value<MovieInfo>().info());
    ui->btnRemove->setEnabled(true);
    m_selectedItem = item;
}
