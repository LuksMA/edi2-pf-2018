#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this) ;

    QString databaseName ;
    databaseName.append( "listado.db" ) ;

    db = QSqlDatabase::addDatabase( "QSQLITE" ) ; // set the drive that the database use
    db.setDatabaseName( databaseName ) ;

    db.open() ; // create the database

    createTable() ;
    loadList() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable( void )
{
    QString query ;
    query.append("CREATE TABLE IF NOT EXISTS listado ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "estudiante VARCHAR(50),"
                 "materia VARCHAR(50),"
                 "presente VARCHAR(50),"
                 "fecha VARCHAR(50)"
                 ");") ;

    QSqlQuery create ;
    create.prepare( query ) ;

    if ( create.exec() )
    {
        qDebug() << "CREATED" ;
    }
    else
    {
        qDebug() << "ERROR WHEN CREATE!" ;
    }

}

void MainWindow::insertRow( void )
{
    QString query ;
    query.append("INSERT INTO listado("
                 "estudiante,"
                 "materia,"
                 "presente,"
                 "fecha)"
                 "VALUES("
                 "'"+ui->lineEditEstudiante->text()+"',"
                 "'"+ui->lineEditMateria->text()+"',"
                 "'"+ui->lineEditAsistencia->text()+"',"
                 "'"+ui->lineEditFecha->text()+"'"
                 ");") ;

    QSqlQuery insert ;
    insert.prepare( query ) ;

    if ( insert.exec() )
    {
        qDebug() << "INSERTED" ;
    }
    else
    {
        qDebug() << "ERROR WHEN INSERT!" << insert.lastError() ;
    }
}

void MainWindow::loadList( void )
{
    QString query ;
    query.append("SELECT * FROM listado") ;

    QSqlQuery select ;
    select.prepare( query ) ;

    if ( select.exec() )
    {
        qDebug() << "CONSULTED" ;
    }
    else
    {
        qDebug() << "ERROR WHEN CONSULTE!" << select.lastError() ;
    }

    int rowNumber = 0 ;

    ui->tableWidgetListado->setRowCount( 0 ) ; // clean the table

    enum { ID_COLUMN = 0, STUDENT_COLUMN, SUBJECT_COLUMN, ASSISTANCE_COLUMN, DATE_COLUMN } ;

    while ( select.next() )
    {
        ui->tableWidgetListado->insertRow( rowNumber ) ;

        ui->tableWidgetListado->setItem( rowNumber, ID_COLUMN, new QTableWidgetItem( select.value( ID_COLUMN ).toByteArray().constData() ) ) ;
        ui->tableWidgetListado->setItem( rowNumber, STUDENT_COLUMN, new QTableWidgetItem( select.value( STUDENT_COLUMN ).toByteArray().constData() ) ) ;
        ui->tableWidgetListado->setItem( rowNumber, SUBJECT_COLUMN, new QTableWidgetItem( select.value( SUBJECT_COLUMN ).toByteArray().constData() ) ) ;
        ui->tableWidgetListado->setItem( rowNumber, ASSISTANCE_COLUMN, new QTableWidgetItem( select.value( ASSISTANCE_COLUMN ).toByteArray().constData() ) ) ;
        ui->tableWidgetListado->setItem( rowNumber, DATE_COLUMN, new QTableWidgetItem( select.value( DATE_COLUMN ).toByteArray().constData() ) ) ;

        rowNumber++ ;
    }
}

void MainWindow::deleteAll()
{
    QString query ;
    query.append("DELETE FROM listado") ;

    QSqlQuery deleteInstruction ;
    deleteInstruction.prepare( query ) ;

    if ( deleteInstruction.exec() )
    {
        qDebug() << "DELETED" ;
    }
    else
    {
        qDebug() << "ERROR WHEN DELETE!" << deleteInstruction.lastError() ;
    }
}

void MainWindow::on_pushButtonAgregar_clicked( void )
{
    insertRow() ;
    loadList() ;
}

void MainWindow::on_pushButtonBorrar_clicked()
{
    deleteAll() ;
    loadList() ;
}
