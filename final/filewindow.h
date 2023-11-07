#ifndef FILEWINDOW_H
#define FILEWINDOW_H
#include "custfile.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolBar>
#include <QAction>
#include <QFontComboBox>
#include <QColorDialog>
#include <QColor>
#include <QSpinBox>

namespace Ui {
class FileWindow;
}

class FileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget *parent = nullptr);
    FileWindow(uni::binfile *binfile);
    ~FileWindow();

    void set_font(QString);
    void set_back_col(QString);
    void set_font_col(QString);
    void set_font_size(int);
    void set_bold(bool);
    void set_italic(bool);
    void set_underline(bool);


private slots:

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_pushButton_6_clicked();

    void fontChanged(const QFont &font);

    void changeCellBackgroundColor(const QColor &color);

    void changeFontSize(int newSize);

    void changeCellFontColor(const QColor &color);

    //void setCellFontBold(bool);

    //void setCellFontItalic(bool);

    //void setCellFontUnderline(bool);

    void setCellFontStyle(bool bold, bool italic, bool underline);

    void updateFontStyle();

private:
    Ui::FileWindow *ui;
    uni::binfile *file;
    int row, col;
    QToolBar *toolbar;
    QFontComboBox *fontComboBox;
    QColorDialog *cdb, *cdbf;
    QSpinBox *fontslider;
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
};

#endif // FILEWINDOW_H
