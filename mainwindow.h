/*
 * Copyright (C) 2012 Alexandro D. Almeida <alexandro@sonicit.com.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "movieconvertthread.h"
#include "movieinfo.h"
#include <QMainWindow>
#include <QListWidgetItem>
#include <QTableWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private:
    Ui::MainWindow *ui;
    void setUiToConvertingVideo(bool enable);
    MovieConvertThread* movieConvertThread;

    void addMovie(QString const &fileName);
    bool hasMovieToConvert();
    QListWidgetItem *m_selectedItem;
    void removeselectedMovieMovie();
    QListWidgetItem* getListItem(MovieInfo const &movieInfo);


 protected:
    void closeEvent(QCloseEvent *event);

 private slots:
    void on_tblMovies_itemClicked(QListWidgetItem* item);
    void on_txtOutpuFolder_editingFinished();
    void on_btnSelectOutputFolder_clicked();
    void on_actionStop_Convert_triggered();
    void on_actionConvert_Movies_triggered();
    void on_cbQuality_currentIndexChanged(QString);
    void on_btnRemove_clicked();
    void on_actionAdd_Movie_triggered();
    void on_actionAbout_triggered();
    void on_actionOptions_triggered();

    void on_movieConverterThread_finished();
    void on_movieConverterThread_startConvert(MovieInfo const & movieInfo);
    void on_movieConverterThread_finishedConvert(MovieInfo const & movieInfo, bool ok);
};

#endif  // MAINWINDOW_H_
