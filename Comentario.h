#ifndef COMENTARIO_H
#define COMENTARIO_H



#include <QApplication>
#include <fstream>
#include <sstream>
#include <stdlib.h>

class Comentario {
private:
    QString  date = "";
    QString text="";
    QString id;
    QString idPUB;

    ///arreglo de comentarios
    ///arreglo de interacciones
public:
    Comentario(QString _date, QString _text,QString _id,QString _idPUB) :date(_date), text(_text),id(_id)
    ,idPUB(_idPUB){}
    QString getdate() { return date; }
    QString gettext() { return text; }
    QString getid() { return id; }
    QString getidPUB() { return idPUB; }

    void setdate(QString a) { date = a; }
    void settext(QString a) { text = a; }

};


#endif // COMENTARIO_H
