#include "dialog.h"
#include "ui_dialog.h"
#include <fstream>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    file(nullptr)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    uni::binfile* f= new uni::binfile(ui->lineEdit->text().toStdString());
    this->file=f;
    FileWindow *window = new FileWindow(this->file);
    this->file->rewrite();
    window->setWindowTitle(QString::fromStdString(this->file->get_name())+".bcf");
    std::ofstream d("last_file.txt", std::ios::trunc);
    d<<this->file->get_name()+".bcf";
    d.close();
    window->show();
    this->close();
}




void Dialog::on_buttonBox_rejected()
{
    QWidget *parentWidget = qobject_cast<QWidget*>(parent());
    if (parentWidget) {
        parentWidget->show();
    }
    this->close();
}

