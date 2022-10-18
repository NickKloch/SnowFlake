#include "mainwindow.h"
#include "ui_qsnowflake.h"

QSnowflake::QSnowflake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QSnowflake)
{
    ui->setupUi(this);
}

QSnowflake::~QSnowflake()
{
    delete ui;
}

