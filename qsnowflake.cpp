#include "qsnowflake.h"
#include "ui_qsnowflake.h"
#include <QMessageBox>
#include <QFileDialog>

void CreateTable(QTableWidget* tableWidget,int ColumnCount,int RowCount)
{
    tableWidget->setColumnCount(ColumnCount);
    tableWidget->setRowCount(RowCount);
    tableWidget->setColumnWidth(0,3);
    tableWidget->setColumnWidth(1,3);
    tableWidget->setRowHeight(0,3);
    tableWidget->setRowHeight(1,3);
    tableWidget->setRowHeight(2,3);
    // Включаем сетку
    tableWidget->setShowGrid(true);
    // Разрешаем выделение только одного элемента
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Растягиваем последнюю колонку на всё доступное пространство
    tableWidget->horizontalHeader()->setStretchLastSection(true);
}

QSnowflake::QSnowflake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSnowflake)
{
    ui->setupUi(this);

    CreateTable(ui->tableWidget_m,3,3);
    // Устанавливаем заголовки колонок
    ui->tableWidget_m->setHorizontalHeaderLabels(QStringList() << "Адрес" << "Имя" << "Значение");
    CreateTable(ui->tableWidget_a,13,13);
    for (int i =0; i <13; i++)
    {
        ui->tableWidget_a->setRowHeight(i,3);
    }

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
