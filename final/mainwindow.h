#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QListWidgetItem>
#include "ui_mainwindow.h"
#include "custfile.h"
#include <QFileDialog>
#include <QFileInfo>
//#include <QCoreApplication>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *getUI();
    void output_files(QListWidget *list);
    void open_file(uni::binfile&f);
    void scan_files();

private slots:
    void on_list_itemDoubleClicked(QListWidgetItem *item);
    void on_action_2_triggered();
    void on_action_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<uni::binfile> files;
    QListWidget *list;
};

#endif // MAINWINDOW_H
