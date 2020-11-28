#ifndef USER_H
#define USER_H

#include <QApplication>
#include <fstream>
#include <vector>
#include <sstream>
#include <Publicacion.h>
#include <Comentario.h>
#include <Interaccion.h>
#include <stdlib.h>
using namespace std;
struct User{
public:
    QString nombre;
    QString password;
    QString email;
    QString fechaCrea;
    QString ID;
    QString number;

    ////*****
    QString fecharegistro;
    vector<Publicacion*> publicaciones;
    vector<User*> follower;
    ////*****
    vector<Comentario*> arrcomentsUser;


    //////------------///////
    vector<Interaccion*> arrinteractionsUser;

    /*constructor para la usuario amigo*/
    User(QString nombre,QString password, QString email, QString _fechaCre,QString _ID,QString _number):

        nombre(nombre),password(password),email(email),fechaCrea(_fechaCre),ID(_ID),number(_number){};

    /*constructor para el usuario*/
   // User(QString nombre, QString password, QString email, QString number):
       // nombre(nombre),password(password),email(email),number(number){}

    QString getNombre(){
        return nombre;
    }
    QString getPassword(){
        return password;
    }
    QString getNumero(){
        return number;
    }
    QString getFecha(){
        return fechaCrea;
    }

    QString getemail(){
        return email;
    }

    void SetFollowers(User *follower){
       this->follower.push_back(follower);
    }
    vector<User*> getfollower(){
        return follower;
    }
    void SetPublicaciones(Publicacion* pub){
        this->publicaciones.push_back(pub);
    }
    vector<Publicacion*> GetPublicaciones(){
        return publicaciones;
    }



};
#endif // USER_H
