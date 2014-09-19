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
    *db = QSqlDatabase::addDatabase("QMYSQL");
    db->setHostName("localhost");
    db->setDatabaseName("test");
    db->setUserName("root");
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
    //QSqlQuery query2(*db);
    if (query.exec("select * from mytable;"))
    {
        ui->listWidget->clear();
        while (query.next())
            ui->listWidget->addItem(query.value(0).toString());

//        QString queryStr1 = "SELECT load_extension('/usr/lib/sqlite3/pcre.so');";
//        QString queryStr2 = "SELECT sqlite_compileoption_used('ENABLE_LOAD_EXTENSION');";

//        if (query2.exec(queryStr2))
//        {
//            query2.next();
//            ui->label->setText(query2.value(0).toString());
//        }
//        if (query2.exec(queryStr1))
//            ui->label->setText("Loaded");
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
