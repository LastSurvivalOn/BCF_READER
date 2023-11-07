#include "filewindow.h"
#include "ui_filewindow.h"
#include "dialog.h"


FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow),
    file(nullptr),
    row(0),
    col(0),
    toolbar(nullptr),
    fontComboBox(nullptr),
    cdb(nullptr),
    cdbf(nullptr),
    fontslider(nullptr),
    boldAction(nullptr),
    italicAction(nullptr),
    underlineAction(nullptr)
{
    ui->setupUi(this);
}

FileWindow::FileWindow(uni::binfile *binfile):
    QMainWindow(nullptr),
    ui(new Ui::FileWindow),
    file(binfile),
    toolbar(new QToolBar),
    fontComboBox(new QFontComboBox),
    cdb(new QColorDialog),
    cdbf(new QColorDialog),
    fontslider(new QSpinBox),
    boldAction(new QAction("Жирний", this)),
    italicAction(new QAction("Курсив", this)),
    underlineAction(new QAction("Підкреслений", this))
{
    connect(this->fontComboBox, &QFontComboBox::currentFontChanged, this, &FileWindow::fontChanged);

    QAction *colorAction = new QAction("Змінити колір фону", this);
    connect(cdb, &QColorDialog::colorSelected, this, &FileWindow::changeCellBackgroundColor);
    connect(colorAction, &QAction::triggered, cdb, &QColorDialog::show);

    QAction *colorFAction = new QAction("Змінити колір шрифту", this);
    connect(cdbf, &QColorDialog::colorSelected, this, &FileWindow::changeCellFontColor);
    connect(colorFAction, &QAction::triggered, cdbf, &QColorDialog::show);

    connect(fontslider, QOverload<int>::of(&QSpinBox::valueChanged), this, &FileWindow::changeFontSize);


    boldAction->setCheckable(true);
    italicAction->setCheckable(true);
    underlineAction->setCheckable(true);

    connect(boldAction, &QAction::toggled, this, &FileWindow::updateFontStyle);
    connect(italicAction, &QAction::toggled, this, &FileWindow::updateFontStyle);
    connect(underlineAction, &QAction::toggled, this, &FileWindow::updateFontStyle);


    this->file->rewrite();
    ui->setupUi(this);
    this->addToolBar(toolbar);
    this->toolbar->addWidget(this->fontComboBox);
    this->toolbar->addWidget(this->fontslider);
    this->toolbar->addAction(colorAction);
    this->toolbar->addAction(colorFAction);
    this->toolbar->addAction(this->boldAction);
    this->toolbar->addAction(this->italicAction);
    this->toolbar->addAction(this->underlineAction);

    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    this->toolbar->hide();

    if(this->file->get_cols_size()!=0)
    ui->tableWidget->setRowCount(this->file->get_rows_size()+1);
    ui->tableWidget->setColumnCount(this->file->get_cols_size());
    this->file->rewrite();

    for(int i=0; i<this->file->get_cols_size(); i++){
            QTableWidgetItem *it = new QTableWidgetItem(QString::fromStdString(this->file->get_cols()[i]));
            ui->tableWidget->setItem(0, i, it);
    }
    if(this->file->get_cols_size()!=0)
    for(int i=0; i<this->file->get_rows_size(); i++){
            for(int j=0; j<this->file->get_cols_size(); j++){
                QTableWidgetItem *it = new QTableWidgetItem(QString::fromStdString(this->file->get_rows()[i][j]));
                ui->tableWidget->setItem(i+1, j, it);
            }
    }

    this->file->rewrite();
    for(auto c:this->file->get_config()){
        QTableWidgetItem *item = ui->tableWidget->item(c.row, c.col);
        QFont font(QString::fromStdString(c.font));
        font.setPointSize(c.size);
        font.setBold(c.bold);
        font.setItalic(c.italic);
        font.setUnderline(c.cursive);
        item->setFont(font);
        QColor color(QString::fromStdString(c.color));
        QBrush brush(color);
        item->setBackground(brush);
        QColor colorf(QString::fromStdString(c.fcol));
        QBrush brushf(colorf);
        item->setForeground(brushf);
    }
    this->file->close();
}

FileWindow::~FileWindow()
{
    delete ui;
}



void FileWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(item->row()==0) this->file->rename_col(item->text().toStdString(), item->column());
    else this->file->edit_row(item->row()-1, item->column(), item->text().toStdString());
}


void FileWindow::on_tableWidget_cellClicked(int row, int column)
{
    this->row = row;
    this->col = column;
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    this->toolbar->show();
    if (row > 0 && column >= 0) {
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (item) {
            QFont font = item->font();
            //this->fontComboBox->blockSignals(true);
            this->fontComboBox->setCurrentFont(font);
            this->fontslider->setValue(item->font().pointSize());
            this->boldAction->setChecked(font.bold());
            this->italicAction->setChecked(font.italic());
            this->underlineAction->setChecked(font.underline());
    }
    }
}


void FileWindow::on_pushButton_2_clicked()
{
    int newColumnIndex = this->file->get_cols_size();
    ui->tableWidget->setColumnCount(newColumnIndex + 1);
    this->file->new_col("-");
    if(ui->tableWidget->rowCount()==0) ui->tableWidget->setRowCount(1);
    for (int i = 0; i <= this->file->get_rows_size(); i++) {
    QTableWidgetItem *it = new QTableWidgetItem("-");
    ui->tableWidget->setItem(0, newColumnIndex, it);
    }
}


void FileWindow::on_pushButton_4_clicked()
{
    if(this->row!=0){
        this->file->delete_row(this->row-1);
        ui->tableWidget->removeRow(row);
        }
    this->row=0;
}


void FileWindow::on_pushButton_5_clicked()
{
    this->file->delete_col(this->col);
    ui->tableWidget->removeColumn(col);
    this->col=0;
}


void FileWindow::on_pushButton_3_clicked()
{
    if(this->file->get_cols_size()!=0){
        this->file->add_row("-", 0);
        ui->tableWidget->setRowCount(this->file->get_rows_size()+1);
        for (int i = 0; i < this->file->get_cols_size(); i++) {
            QTableWidgetItem *it = new QTableWidgetItem("-");
            ui->tableWidget->setItem(this->file->get_rows_size(), i, it);
        }
    }
}


void FileWindow::on_action_2_triggered()
{
    Dialog *d = new Dialog;
    d->setWindowTitle("Введіть ім'я файлу");
    d->show();
}


void FileWindow::on_action_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Відкрити файл"), ".", tr("bcf files (*.bcf)"));
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        QString fileDirectory = fileInfo.path();
        uni::binfile *f = new uni::binfile(filePath.toStdString().erase(filePath.size() - 4, 4));
        this->hide();
        FileWindow *window = new FileWindow(f);
        f->rewrite();
        f->write_last(filePath.toStdString());
        window->setWindowTitle(QString::fromStdString(f->get_name())+".bcf");
        window->show();
    }
}


void FileWindow::on_pushButton_6_clicked()
{
    if(this->ui->tableWidget->rowCount()!=0){
        this->file->clear();
        this->ui->tableWidget->clear();
        this->ui->tableWidget->setRowCount(0);
        this->ui->tableWidget->setColumnCount(0);
    }
}

void FileWindow::fontChanged(const QFont &font) {
    QTableWidgetItem *item = ui->tableWidget->item(this->row, this->col);
    if (item) {
        QFont newFont(font.family(), item->font().pointSize());
        item->setFont(newFont);
        this->set_font(font.family());
        this->file->rewrite();
    }
}

void FileWindow::changeCellBackgroundColor(const QColor &color) {
    QTableWidgetItem *item = ui->tableWidget->item(this->row, this->col);
        if (item) {
        QBrush brush(color);
        item->setBackground(brush);
        this->set_back_col(color.name());
        this->file->rewrite();
        }
}

void FileWindow::changeFontSize(int newSize) {
        QTableWidgetItem *currentItem = ui->tableWidget->currentItem();
        if (currentItem) {
        QFont font = currentItem->font();
        font.setPointSize(newSize);
        currentItem->setFont(font);
        this->set_font_size(newSize);
        this->file->rewrite();
        }
}

void FileWindow::changeCellFontColor(const QColor &color) {
        QTableWidgetItem *item = ui->tableWidget->item(this->row, this->col);
        if (item) {
        QBrush brush(color);
        item->setForeground(brush);
        this->set_font_col(color.name());
        this->file->rewrite();
        }
}

void FileWindow::set_font(QString n){
        uni::cell_config c;
        c.font = n.toStdString();
        c.col=this->col;
        c.row=this->row;
        this->file->push_conf(c);
}
void FileWindow::set_back_col(QString n){
        uni::cell_config c;
        c.color = n.toStdString();
        c.col=this->col;
        c.row=this->row;
        this->file->push_conf(c);
}
void FileWindow::set_font_col(QString n){
        uni::cell_config c;
        c.fcol = n.toStdString();
        c.col=this->col;
        c.row=this->row;
        this->file->push_conf(c);
}
void FileWindow::set_font_size(int n){
        uni::cell_config c;
        c.size = n;
        c.col=this->col;
        c.row=this->row;
        this->file->push_conf(c);
}

void FileWindow::updateFontStyle() {
        bool bold = this->boldAction->isChecked();
        bool italic = this->italicAction->isChecked();
        bool underline = this->underlineAction->isChecked();

        QTableWidgetItem *item = ui->tableWidget->item(row, col);
        if (item) {
            QFont font = item->font();
            font.setBold(bold);
            font.setItalic(italic);
            font.setUnderline(underline);
            item->setFont(font);
            setCellFontStyle(bold, italic, underline);
        }

}

void FileWindow::setCellFontStyle(bool bold, bool italic, bool underline) {
        uni::cell_config c;
        c.col = col;
        c.row = row;
        c.bold = bold;
        c.italic = italic;
        c.cursive = underline;
        file->push_conf(c, bold, italic, underline);
}

