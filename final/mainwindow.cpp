#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include "filewindow.h"
#include "dialog.h"
namespace fs = std::experimental::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BCF Reader");
    //setFixedSize(size());
    list = this->getUI()->list;
    output_files(this->list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUI(){
    return this->ui;
}

void MainWindow::on_list_itemDoubleClicked(QListWidgetItem *item)
{
    int i = ui->list->currentRow();
    open_file(files[i]);
    files[i].write_last(files[i].get_name()+".bcf");
}

void MainWindow::output_files(QListWidget *list) {
    list->clear();
    scan_files();
    for (int i = 0; i < this->files.size(); i++) {
        list->addItem(QString::fromStdString(files[i].get_name()));
    }

}

void MainWindow::scan_files(){
    std::string extension = ".bcf";
    std::string path = ".";
    for (const auto& entry : fs::directory_iterator(path)) {
        fs::file_status status = entry.status();
        if (fs::is_regular_file(status) && entry.path().extension() == extension)
        {
            std::string file_name = entry.path().filename().string();
            file_name.erase(file_name.size() - 4, 4);
            uni::binfile file(file_name);
            auto it = std::find(this->files.begin(), this->files.end(), file);
            if (it == this->files.end()) {
                this->files.push_back(file);
            }
            file.close();
        }
    }
}

void MainWindow::open_file(uni::binfile&f){
    FileWindow *window = new FileWindow(&f);
    f.rewrite();
    window->setWindowTitle(QString::fromStdString(f.get_name())+".bcf");
    window->show();
    this->hide();
}


void MainWindow::on_action_2_triggered()
{
    Dialog *d = new Dialog;
    d->setWindowTitle("Введіть ім'я файлу");
    d->show();
    this->hide();
}


void MainWindow::on_action_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Відкрити файл"), ".", tr("bcf files (*.bcf)"));
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        QString fileDirectory = fileInfo.path();
        uni::binfile *f = new uni::binfile(filePath.toStdString().erase(filePath.size() - 4, 4));
        f->write_last(filePath.toStdString());
        this->hide();
        open_file(*f);
    }
}


void MainWindow::on_pushButton_clicked()
{
    std::ifstream f("last_file.txt");
    if(f.peek() != std::ifstream::traits_type::eof()){
        std::string l;
        f >> std::quoted(l);
        f.close();
        l.erase(l.size()-4, 4);
        uni::binfile* g= new uni::binfile(l);
        open_file(*g);
    }
}

