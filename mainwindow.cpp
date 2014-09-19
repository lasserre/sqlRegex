#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Make connections
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(UpdateSearchResults(QString)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(InitDatabase()));

    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setHostName("localhost");
    db->setDatabaseName("/Users/calebstewart/test.db");
    db->setUserName("calebstewart");
    //db.setPassword("");

    // Check for successful open...
    if (db->open())
    {
        ui->label->setText("Open!");
        ui->listWidget->addItems(db->tables());
    }
    else
        ui->label->setText(db->lastError().text());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDatabase()
{
    QSqlQuery query(*db);
    if (query.exec("select * from mytable;"))
    {
        ui->listWidget->clear();
        while (query.next())
            ui->listWidget->addItem(query.value(0).toString());
    }
    else
        ui->label->setText("Unsuccessful");
}

void MainWindow::UpdateSearchResults(QString Text)
{
    QString queryStr = "select myname from mytable where myname REGEXP ";
    QString regexStr = "'.*";

    for (int i = 0; i < Text.count(); i++)
        regexStr += Text[i] + ".*";

    regexStr += "';";

    QSqlQuery query(*db);

    if (query.exec(queryStr + regexStr))
    {
        ui->listWidget->clear();
        while (query.next())
            ui->listWidget->addItem(query.value(0).toString());
    }
}
