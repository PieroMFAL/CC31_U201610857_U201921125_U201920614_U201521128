#ifndef AMIGOS_H
#define AMIGOS_H
#include <QMainWindow.h>
#include <stdlib.h>
#include<fstream>
#include <time.h>
#include <Comentario.h>
#include <Interaccion.h>
#include <Publicacion.h>
#include <conio.h>
#include <User.h>
using namespace std;
struct Amigos{
public:
    QString name;
    QString email;
    int number;


    ////*****
    QString fecharegistro;
    vector<Publicacion*> arr;
    vector<User*> seguiendo;
    ////*****
    vector<Comentario*> arrcomentsUser;
    vector<Interaccion*> arrinteractionsUser;


    Amigos(QString _name,QString _email, QString _fecharegistro):
        name(_name),email(_email),number(rand()%9999999+990010000),fecharegistro(_fecharegistro){

    }
    QString getNombre(){
        return name;
    }
    QString getFecha(){
        return fecharegistro;
    }


   /* void escribir(){

        int aux=rand()%9+10;
        email=name +QString::number (aux)+"@gmail.com";
        ofstream archivo;
        archivo.open("ListaAmigos.txt",ios::app);
        archivo<< name.toStdString()<<" "<<email.toStdString()<<" "<<number<<endl;
        archivo.close();
    }*/
};
#endif // AMIGOS_H
