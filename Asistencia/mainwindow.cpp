#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE") ;

    QString databaseName ;
    databaseName.append("listado.sqlite") ;

    db.setDatabaseName( databaseName ) ;

    if ( db.open() ) {
        qDebug() << "BASE DE DATOS CREADA" ;
    } else {
        qDebug() << "LA BASE DE DATOS NO SE HA CREADO WEY!!!" << db.lastError() ;
    }

    crearTabla() ;
    verEnTabla() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearTabla( void )
{
    QString query ;

    query.append("CREATE TABLE IF NOT EXISTS listado("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                  "alumno VARCHAR(50),"
                  "materia VARCHAR(50),"
                  "fecha VARCHAR(50),"
                  "presente VARCHAR(50)"
                  ");") ;

    QSqlQuery createTable ;
    createTable.prepare( query ) ;

    if ( createTable.exec() ) {
        qDebug() << "TABLA CREADA" ;
    } else {
        qDebug() << "NO SE CREO LA TABLA" << createTable.lastError() ;
    }
}

void MainWindow::insertar()
{
    QString query ;

    query.append("INSERT INTO listado("
                  "alumno,"
                  "materia,"
                  "fecha,"
                  "presente)"
                  "VALUES ("
                  "'"+ui->lineEditALUMNO->text()+"',"
                  "'"+ui->lineEditMATERIA->text()+"',"
                  "'"+ui->lineEditFECHA->text()+"',"
                  "'"+ui->lineEditPRESENTE->text()+"'"
                  ");"
                  );

    QSqlQuery insert ;
    insert.prepare( query ) ;

    if ( insert.exec() ) {
        qDebug() << "FILA INSERTADA" ;
    } else {
        qDebug() << "NO SE INSERTO LA FILA" << insert.lastError() ;
    }
}

void MainWindow::verEnTabla()
{
    QString query ;

    query.append("SELECT * FROM listado") ;

    QSqlQuery select ;

    select.prepare( query ) ;

    if ( select.exec() ) {
        qDebug() << "SELECCIONADO" ;
    } else {
        qDebug() << "ERROR" << select.lastError() ;
    }

    int rowNumber = 0 ;

    ui->tableWidget->setRowCount( 0 ) ;

    while ( select.next() )
    {
        ui->tableWidget->insertRow( rowNumber ) ;
        ui->tableWidget->setItem( rowNumber, 0, new QTableWidgetItem( select.value( 0 ).toByteArray().constData() ) );
        ui->tableWidget->setItem( rowNumber, 1, new QTableWidgetItem( select.value( 1 ).toByteArray().constData() ) );
        ui->tableWidget->setItem( rowNumber, 2, new QTableWidgetItem( select.value( 2 ).toByteArray().constData() ) );
        ui->tableWidget->setItem( rowNumber, 3, new QTableWidgetItem( select.value( 3 ).toByteArray().constData() ) );
        ui->tableWidget->setItem( rowNumber, 4, new QTableWidgetItem( select.value( 4 ).toByteArray().constData() ) );

        rowNumber++ ;
    }
}

void MainWindow::borrarListado()
{
    QString query ;

    query.append("DELETE FROM listado") ;

    QSqlQuery deleteList ;

    deleteList.prepare( query ) ;

    if ( deleteList.exec() ) {
        qDebug() << "LISTADO BORRADO" ;
    } else {
        qDebug() << "ERROR" << deleteList.lastError() ;
    }
}


void MainWindow::on_pushButtonAGREGAR_clicked()
{
    insertar() ;
    verEnTabla() ;
}

void MainWindow::on_pushButtonBORRAR_clicked()
{
    borrarListado() ;
    verEnTabla() ;
}
