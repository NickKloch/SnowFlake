#include "qsnowflake.h"
#include "ui_qsnowflake.h"
#include <QDateTime>
#include <QMessageBox>
#include <QString>
#include <sys/mman.h>

void CreateTable(QTableWidget* tableWidget,int columnCount,int rowCount,
                 int coloumn,int columnSize,bool visible)
{
    tableWidget->setColumnCount(columnCount);
    // Включаем сетку
    tableWidget->verticalHeader()->setVisible(false);
    // Разрешаем выделение только одного элемента
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setRowCount(rowCount);
    // Растягиваем последнюю колонку на всё доступное пространство
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setColumnWidth(0,120);
    for (int count = 2;count < coloumn; count++)
    {
        tableWidget->setColumnWidth(coloumn,columnSize);
    }
    if (!visible)
    {
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setVisible(false);
    }
}

void QSnowflake::createListData()
{
    listData = {
        prog.get_pm(),prog.get_r_pdlina(),
        prog.get_pi(),prog.get_pa(),
        prog.get_aTs(),prog.get_paKolvots(),
        prog.get_padlina(),prog.get_b()
    };
}

std::vector <void*> QSnowflake::getListData()
{
    return listData;
}

void setDataItem(QTableWidget* tableWidget,int columnCount,int rowCount,char* pBuf,
                  std::vector <void*> dataList,std::vector <QString> nameList, int listStep)
{
    int j = 0;
    for (int i = 0; i <= columnCount; i++)
    {
        sprintf(pBuf,"%p",dataList[j + listStep]);
        tableWidget->setItem(i,0,new QTableWidgetItem(pBuf));
        j++;
    }
    j = 0;
    for (int i = 0; i <= rowCount;i++)
    {
        tableWidget->setItem(i,1,new QTableWidgetItem(nameList[j + listStep]));
        j++;
    }
}

QSnowflake::QSnowflake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSnowflake)
{
    ui->setupUi(this);

    pBuf = (char*)malloc(sizeof(int*));
    if(!pBuf)
    {
        QMessageBox::critical(this,"Ошибка","Ошибка выделения памяти");
        return;
    }

    createListData();

    std::vector <QString> nameList = {
      "m","r_dlina","i","a",
      "a.ts","a.kolvots",
      "a.dlina","b"
    };

    // Создаём таблиицу для m
    CreateTable(ui->tableWidget_m,3,3,0,120,true);
    // Устанавливаем заголовки колонок
    ui->tableWidget_m->setHorizontalHeaderLabels(QStringList() << "Адрес" << "Имя" << "Значение");

    // устанавилваем начальные данные в таблицу m
    setDataItem(ui->tableWidget_m,2,2,pBuf,getListData(),nameList,0);

    // Создаем таблицу для а
    CreateTable(ui->tableWidget_a,15,13,15,10,false);
    // устанавилваем начальные данные в таблицу a
    setDataItem(ui->tableWidget_a,0,0,pBuf,getListData(),nameList,3);


    // Создаем таблицу для а.ts
    CreateTable(ui->tableWidget_aTs,16,1,18,10,false);
    sprintf(pBuf,"%p",prog.get_aTs());
    // Устанавливаем начальные данные в таблицу a.ts
    setDataItem(ui->tableWidget_aTs,0,0,pBuf,getListData(),nameList,4);

    // Создаём таблицу для a.dlina
    CreateTable(ui->tableWidget_dlina,3,2,0,120,false);
    // Устанавливаем начальные данные в таблицу a.dlina
    setDataItem(ui->tableWidget_dlina,1,1,pBuf,getListData(),nameList,5);

    // Создаем таблицу для b
    CreateTable(ui->tableWidget_b,16,625,18,10,false);
    // устанавилваем начальные данные в таблицу b
    sprintf(pBuf,"%p",prog.get_b());
    setDataItem(ui->tableWidget_b,0,0,pBuf,getListData(),nameList,7);

    // Создаем таблицу для сегмента кода
    CreateTable(ui->tableWidgetCode,6,59,0,15,false);
    ui->tableWidgetCode->setColumnWidth(0,20);

    // обнуляем значения переменных
    memset(prog.get_aTs(),0,16);
    memset(prog.get_b(),0,10000);
}

QSnowflake::~QSnowflake()
{
    free(pBuf);
    delete ui;
}
QString QSnowflake::getLog(QString log)
{
    QString dateTime = QDateTime::currentDateTime().toString("[hh:mm dd.MM.yyyy]");
    return dateTime + " "+ log;
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
    if(!prog.setFileData(filePath.toUtf8().constData()))
    {
        ui->textBrowser->insertPlainText(getLog("Ошибка файла открытого текста"));
    }
    ui->textBrowser->insertPlainText(getLog("Получен файл с открытым текстом\n"));
    UpdateData();
}


void QSnowflake::UpdateData()
{
    for (int i = 0; i < 3; i++)
    {
        ui->tableWidget_m->setItem(i,2,new QTableWidgetItem(QString("%1").arg(*(int*)listData[i])));
    }

    int data = 0;
    for (int i = 0; i < 16; i++)
    {
        data = ((char*)listData.at(4))[i];
        ui->tableWidget_aTs->setItem(0,2 + i,new QTableWidgetItem(QString("%1").arg(data)));
    }

    //for (int i=0; i < 2; i++)
    //{
        //ui->tableWidget_dlina->setItem(i,2,new QTableWidgetItem(QString("%1").arg(*(int*)listData[i+5])));
    //}
    ui->tableWidget_dlina->setItem(0,2,new QTableWidgetItem(QString("%1").arg(prog.get_aKolvots())));
    ui->tableWidget_dlina->setItem(1,2,new QTableWidgetItem(QString("%1").arg(prog.get_adlina())));
    int dataText;
    for (int i = 0; i < 625; i++ )
    {
        for (int j = 0; j < 14; j++)
        {
            dataText = ((char*)listData.at(7))[j+i];
            ui->tableWidget_b->setItem(i,2+j,new QTableWidgetItem(QString("%1").arg(dataText)));
        }
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
    if(!prog.setKeyData(keyPath.toUtf8().constData()))
    {
        ui->textBrowser->insertPlainText(getLog("Ошибка получения ключа"));
    }
    ui->textBrowser->insertPlainText(getLog("Получен ключ\n"));
    UpdateData();
}



void QSnowflake::on_startBtn_clicked()
{
    ui->textBrowser->insertPlainText(getLog("Запуск моделирования\n"));
    // ввод измененных значений
    ui->textBrowser->insertPlainText(getLog("Измените значения в сегменте кода и сегмент данных в соответствии с вариантом\n"));

    // Берем изменные данные на m и помещаем их по адрессу
    //*(int*)listData.at(0) = atoi(ui->tableWidget_m->item(0,2)->text().toUtf8().constData());
    // Берем изменные данные на dlina и помещаем их по адрессу
    //*(int*)listData.at(1) = atoi(ui->tableWidget_m->item(1,2)->text().toUtf8().constData());
    // Берем изменные данные на i и помещаем их по адрессу
    //*(int*)listData.at(2) = atoi(ui->tableWidget_m->item(2,2)->text().toUtf8().constData());

    // тут будет передаваться указатель на а

    // Берем изменные данные на a.Ts и помещаем их по адрессу
    //for (int i = 0; i < 14; i++)
    //{
        //((char*)listData.at(4))[i] = atoi(ui->tableWidget_aTs->item(0,2+i)->text().toUtf8().constData());
    //}
    // Берем изменные данные на a.Kolvots и помещаем их по адрессу
    //*(int*)listData.at(5) = atoi(ui->tableWidget_dlina->item(0,2)->text().toUtf8().constData());
    // Берем изменные данные на a.dlina и помещаем их по адрессу
    //*(int*)listData.at(6) = atoi(ui->tableWidget_dlina->item(1,2)->text().toUtf8().constData());
    // Берем изменные данные на b и помещаем их по адрессу

    prog.crypt(listData);
    UpdateData();
    prog.writeDataFile();   

    ui->textBrowser->insertPlainText(getLog("Моделирование завершено\n"));
}

void QSnowflake::on_cancelBtn_clicked()
{

}
