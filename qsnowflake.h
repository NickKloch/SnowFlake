#ifndef QSNOWFLAKE_H
#define QSNOWFLAKE_H

#include <QMainWindow>
#include <QStandardItemModel>

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
    QStandardItemModel* modle;
};
#endif // QSNOWFLAKE_H
