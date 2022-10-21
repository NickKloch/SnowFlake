#include "qsnowflake.h"
#include "ui_qsnowflake.h"
#include "QSourceProg.h"
#include <QMessageBox>
#include <QFileDialog>

void CreateTable(QTableWidget* tableWidget,int ColumnCount)
{
    tableWidget->setColumnCount(ColumnCount);
    // Включаем сетку
    tableWidget->verticalHeader()->setVisible(false);
    // Разрешаем выделение только одного элемента
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

QSnowflake::QSnowflake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSnowflake)
{
    ui->setupUi(this);
    QSourceProg prog;
    // Создаём таблиицу для m
    CreateTable(ui->tableWidget_m,3);
    ui->tableWidget_m->setRowCount(3);

    // Устанавливаем заголовки колонок
    ui->tableWidget_m->setHorizontalHeaderLabels(QStringList() << "Адрес" << "Имя" << "Значение");
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget_m->horizontalHeader()->setStretchLastSection(true);

    char buf[4] = {0,0,0,0};
    sprintf(buf,"%p",prog.get_pm());

    ui->tableWidget_m->setItem(0,0,new QTableWidgetItem(buf));
    ui->tableWidget_m->setItem(1,0,new QTableWidgetItem(buf));
    ui->tableWidget_m->setItem(2,0,new QTableWidgetItem(buf));

    ui->tableWidget_m->setItem(0,1,new QTableWidgetItem("m"));
    ui->tableWidget_m->setItem(1,1,new QTableWidgetItem("r_dlina"));
    ui->tableWidget_m->setItem(2,1,new QTableWidgetItem("i"));

    // Создаем таблицу для а
    CreateTable(ui->tableWidget_a,15);
    ui->tableWidget_a->setRowCount(13);
    ui->tableWidget_a->verticalHeader()->setVisible(false);
    ui->tableWidget_a->horizontalHeader()->setVisible(false);
    // устанавлииваем ширину каждой колонны
    for (int stepColumn = 2; stepColumn < 15 ; stepColumn ++)
    {
        ui->tableWidget_a->setColumnWidth(stepColumn,10);
    }

    // Создаем таблицу для а.ts
    CreateTable(ui->tableWidget_aTs,16);
    ui->tableWidget_aTs->setRowCount(1);
    ui->tableWidget_aTs->verticalHeader()->setVisible(false);
    ui->tableWidget_aTs->horizontalHeader()->setVisible(false);
    // устанавлииваем ширину каждой колонны
    for (int stepColumn = 2; stepColumn < 18 ; stepColumn ++)
    {
        ui->tableWidget_aTs->setColumnWidth(stepColumn,10);
    }

    // Создаём таблицу для a.dlina
    CreateTable(ui->tableWidget_dlina,3);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget_dlina->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_dlina->setRowCount(2);
    ui->tableWidget_dlina->verticalHeader()->setVisible(false);
    ui->tableWidget_dlina->horizontalHeader()->setVisible(false);

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
