#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <QApplication>
#include <mainwindow.h>
#include <QMainWindow>
#include <ui_mainwindow.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <Comentario.h>
#include <Interaccion.h>
#include <stdlib.h>
class Publicacion {
private:
    QString IDuser;
    QString ID;
    QString  title = "";
    QString desc;
    int numlikes;
    QString fechapublicacion = "";
    QString NomUsuario;




    vector<Comentario*> arrcomentariosP;



    vector<Interaccion*> arrinteractionsP;


public:

    Publicacion(QString _IDuser,QString _ID,QString _title, QString _desc, int _numlikes,
                QString _fechapublicacion) :IDuser(_IDuser),ID(_ID),title(_title), desc(_desc)
                ,numlikes(_numlikes), fechapublicacion(_fechapublicacion) {


    }
    QString gettitle() { return title; }
    int getnumlikes() { return numlikes; }
    QString getfechapublicacion() { return fechapublicacion; }
    QString getdesc() { return desc; }

    QString getIDuser() { return IDuser; }
    QString getID() { return ID; }





 //   QString getnomUser() { return NomUsuario; } NO ES NECESARIO PARA TITLE Y FECHA DE PUBLICACION ESO PASA COMO PARAMETRO EN EL CONSTRUCTOR

    void settitle(QString a) { title = a; }
    void setnumlikes(int a) { numlikes = a; }
    void setfechapublicacion(QString a) { fechapublicacion = a; }
    void setdesc(QString a) { desc = a; }

    void agregarinteraccion(Interaccion* aux){
        arrinteractionsP.push_back(aux);
    }
    vector<Interaccion*> gervectorinteracc(){
        return arrinteractionsP;
    }

};








#endif // PUBLICACION_H
