#ifndef QSNOWFLAKE_H
#define QSNOWFLAKE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "QSourceProg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QSnowflake; }
QT_END_NAMESPACE

class QSnowflake : public QMainWindow
{
    Q_OBJECT

public:
    QSnowflake(QWidget *parent = nullptr);
    ~QSnowflake();

private slots:

    void on_GetFileBtn_clicked();

    void on_GetKeyBtn_clicked();

    void on_startBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::QSnowflake *ui;

    char* pBuf;
    QSourceProg prog;
    QString getLog(QString log);

    std::vector <void*> listData;
    void createListData();
    std::vector <void*> getListData();

    void UpdateData();
    void getData();
};
#endif // QSNOWFLAKE_H
