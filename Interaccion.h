#ifndef INTERACCION_H
#define INTERACCION_H



#include <QApplication>
#include <fstream>
#include <sstream>
#include <stdlib.h>

class Interaccion {

private:
    QString  fecha = "";
   // int shared=0;
    QString idUSER;
    QString idPub;
    QString interac;


    ///arreglo de comentarios
    ///arreglo de interacciones
public:
    Interaccion(QString _fecha, QString _interac,QString _iduser, QString _idpub) :fecha(_fecha),idUSER(_iduser),idPub(_idpub) {
        interac=_interac;

    }
    QString getfecha() { return fecha; }
    QString getiduser() { return idUSER; }
    QString getidpub() { return idPub; }
    QString getinterac() { return interac; }

    void setfecha(QString a) { fecha = a; }
    void setiduser(QString a) { idUSER = a; }
    void setidpub(QString a) { idPub = a; }
    void setinterac(QString  a) { interac = a; }

};



#endif // INTERACCION_H
