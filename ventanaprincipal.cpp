#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QTextStream>

using namespace std;

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    connect(ui->bExit,SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->tbLoad,SIGNAL(clicked()),this, SLOT(leerFichero()));
    connect(ui->tbRun,SIGNAL(clicked()),this,SLOT(ordenarFichero()));
    connect(ui->tbSave,SIGNAL(clicked()),this,SLOT(guardarFichero()));
    connect(ui->tbLoadI,SIGNAL(clicked()),this,SLOT(leerImagen()));
    connect(ui->tbRunI,SIGNAL(clicked()),this,SLOT(transformarImagen()));
    connect(ui->tbSave_2,SIGNAL(clicked()),this,SLOT(guardarImagen()));
    connect(ui->tbClear,SIGNAL(clicked()),this,SLOT(clear()));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::leerFichero(){

    QString fileNumbers = QFileDialog::getOpenFileName(this,"Abrir archivo",NULL,"Text Files (*.txt);;All Files (*.*)");

    if(!fileNumbers.isEmpty()){
        QFile file(fileNumbers);
        if(file.open(QFile::ReadOnly)){
            ui->tebLoaded->insertPlainText(file.readAll());
            ui->tbRun->setEnabled(true);
        } else {
            QMessageBox::warning(this,"TextEditor",tr("No se puede leer %1. \nError: %2").arg(fileNumbers).arg(file.errorString()));
        }
    }
}

void VentanaPrincipal::ordenarFichero(){
    float time[6];
    clock_t strt[5],stp[5];
    std::vector<int> vectorInt, oldVector;
    string tempLine;
    int number;
    int cnt=0;
    tempLine = ui->tebLoaded->toPlainText().toStdString();
    std::stringstream iss(tempLine);
    std::stringstream oss;
    QString qstr;

    while( iss >> number){
        vectorInt.push_back(number);
    }
    oldVector=vectorInt;

    for(int i=0; i<5;i++){
    vectorInt=oldVector;
    strt[i]=clock();
    std::sort (vectorInt.begin(), vectorInt.end());
    stp[i]=clock();
    time[i]=(stp[i]-strt[i])/(CLOCKS_PER_SEC/1000);
    }
    ui->lcdT1->display(QString::number(time[0]));
    ui->lcdT2->display(QString::number(time[1]));
    ui->lcdT3->display(QString::number(time[2]));
    ui->lcdT4->display(QString::number(time[3]));
    ui->lcdT5->display(QString::number(time[4]));
    time[5]= (time[0]+time[1]+time[2]+time[3]+time[4])/5;
    ui->lcdTM->display(QString::number(time[5]));

    for(size_t i=0;i<vectorInt.size();i++){
        if(i != 0) {
            oss << " ";
        }
        oss << vectorInt[i];
    }
    std::string os = oss.str();
    std::stringstream isss(os);
    ui->tebModified->setPlainText("");
    while (isss){
        string subs;
        isss >> subs;
        qstr = QString::fromStdString(subs);
        if (cnt==0){
            ui->tebModified->insertPlainText(qstr);
            cnt++;
        }else{
            ui->tebModified->insertPlainText(" "+ qstr);
            cnt++;
        }
        if(cnt==8){
            ui->tebModified->insertPlainText("\n");
            cnt=0;
        }
    }
    ui->tbSave->setEnabled(true);
}

void VentanaPrincipal::clear(){
    ui->tebModified->setPlainText("");
}

void VentanaPrincipal::guardarFichero(){
    QString filename= QFileDialog::getSaveFileName();
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->tebModified->document()->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this,"TextBrowser", tr("Cannot write File %1.\nError: %2").arg(filename).arg(file.errorString()));
    }

}

void VentanaPrincipal::leerImagen(){

    image.load(QFileDialog::getOpenFileName(this));
    if(!image.isNull()){
       // item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        QGraphicsScene* scene = new QGraphicsScene;
        scene->setBackgroundBrush(image.scaled(311,201,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        ui->gvNormal->setScene(scene);

        ui->tbRunI->setEnabled(true);
    }else{
        QMessageBox::warning(this,"ImageBrowser",tr("You have to specify a file"));
    }
}

void VentanaPrincipal::transformarImagen(){

    float time[6];
    clock_t strt[5],stp[5];
    for(int i=0;i<5;i++){
        strt[i]=clock();
        imagebn=image;
        for (int i = 0; i < imagebn.height(); i++) {
            uchar* scan = imagebn.scanLine(i);
            int depth =4;
            for (int j = 0; j < imagebn.width(); j++) {
                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + j*depth);
                int gray = qGray(*rgbpixel);
                *rgbpixel = QColor(gray, gray, gray).rgba();
            }
        }
        stp[i]=clock();
        time[i]=1000L*(stp[i]-strt[i])/CLOCKS_PER_SEC;
    }
    ui->lcdT1I->display(QString::number(time[0]));
    ui->lcdT2I->display(QString::number(time[1]));
    ui->lcdT3I->display(QString::number(time[2]));
    ui->lcdT4I->display(QString::number(time[3]));
    ui->lcdT5I->display(QString::number(time[4]));
    time[5]= (time[0]+time[1]+time[2]+time[3]+time[4])/5;
    ui->lcdTMI->display(QString::number(time[5]));
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setBackgroundBrush(imagebn.scaled(311,201,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->gvTransformada->setScene(scene);
    ui->tbSave_2->setEnabled(true);
}

void VentanaPrincipal::guardarImagen(){

    QString sImage= QFileDialog::getSaveFileName();
    imagebn.save(sImage);
}
