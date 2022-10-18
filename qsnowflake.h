#ifndef QSNOWFLAKE_H
#define QSNOWFLAKE_H

#include <QMainWindow>

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

private:
    Ui::QSnowflake *ui;
};
#endif // QSNOWFLAKE_H
