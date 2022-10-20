#include "qsnowflake.h"
#include "ui_qsnowflake.h"
#include <QMessageBox>
#include <QFileDialog>

QSnowflake::QSnowflake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSnowflake)
{
    ui->setupUi(this);

    modle = new QStandardItemModel(2,3,this);
    modle->setHorizontalHeaderLabels(QStringList() << "Адрес" << "Имя" << "Значение");

    ui->tableView_m->setModel(modle);
}

QSnowflake::~QSnowflake()
{
    delete ui;
}

void QSnowflake::on_GetFileBtn_clicked()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this,"Выбрать файл текста","/home","All Files(*.*);; *.txt (*.txt)");
    if ("" == filePath)
    {
        return;
    }
    else if(!filePath.endsWith(".txt"))
    {
        QMessageBox::critical(this,"Ошибка","Выбран не текстовый файл");
        return;
    }
}


void QSnowflake::on_GetKeyBtn_clicked()
{
    QString keyPath;
    keyPath = QFileDialog::getOpenFileName(this,"Выбрать файл текста","/home","All Files(*.*);; *.txt (*.txt)");
    if ("" == keyPath)
    {
        return;
    }
    else if(!keyPath.endsWith(".txt"))
    {
        QMessageBox::critical(this,"Ошибка","Выбран не текстовый файл");
        return;
    }
}

void QSnowflake::on_startBtn_clicked()
{

}

void QSnowflake::on_cancelBtn_clicked()
{

}
