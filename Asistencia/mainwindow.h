#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void crearTabla( void );
    void insertar( void );
    void verEnTabla( void );
    void borrarListado( void );
private slots:
    void on_pushButtonAGREGAR_clicked();

    void on_pushButtonBORRAR_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db ;

};

#endif // MAINWINDOW_H
