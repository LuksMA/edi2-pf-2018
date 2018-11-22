#include "customdialog.h"

CustomDialog::CustomDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle("Asistencia");

    resize(530,920);
    createListWidget();
    createOtherWidgets();
    createLayout();
    createConnections();
}

void CustomDialog::createListWidget(){
    widget = new QListWidget;
    QStringList strList;
    strList << "Barrionuevo, Julian" << "Estefan, Julian" << "Llorensi, Julian";
    widget->addItems(strList);

    QFile file("assistance.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);

    QListWidgetItem* item = nullptr;
    for(int i = 0; i < widget->count(); ++i){
        item = widget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);

        while(in.atEnd()){
            if (item->text() == in.readLine()) item->setCheckState(Qt::Checked);
        }
        in.reset();
    }

    file.close();
}

void CustomDialog::createOtherWidgets(){
    viewBox = new QGroupBox(tr("Alumnos"));
    buttonBox = new QDialogButtonBox;
    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
}

void CustomDialog::createLayout(){
    QVBoxLayout* viewLayout = new QVBoxLayout;
    viewLayout->addWidget(widget);
    viewBox->setLayout(viewLayout);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(buttonBox);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

void CustomDialog::createConnections(){
    QObject::connect(widget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(highlightChecked(QListWidgetItem*)));
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CustomDialog::highlightChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked)
        item->setBackgroundColor(QColor("#ffffb2"));
    else
        item->setBackgroundColor(QColor("#ffffff"));
}

void CustomDialog::save(){

    QFile file("assistance.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out << "Asistencia:" << "\n";

    QListWidgetItem* item = nullptr;
    for(int i = 0; i < widget->count(); ++i){
        item = widget->item(i);
        if(item->checkState() == Qt::Checked)
            out << item->text() << "\n";
    }

    QMessageBox::information(this, tr("Asistencia"),
                                   tr("Se ha guardado la asistencia."),
                                   QMessageBox::Ok);
}
