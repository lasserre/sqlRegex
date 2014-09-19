#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void UpdateSearchResults(QString Text);
    void InitDatabase();

private:
    Ui::MainWindow *ui;
    QSqlDatabase *db;
};

#endif // MAINWINDOW_H
