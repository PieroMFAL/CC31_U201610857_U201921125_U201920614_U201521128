#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Publicacion.h"
#include "User.h"
#include "Amigos.h"
#include "Lista.h"
#include "Stack.h"
#include <sstream>
#include "AVL2P.h"
#include "AVL.h"
#include <stdlib.h>
#include <QMessageBox>
#include <functional>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QIcon *amigo= new QIcon(":/imagenes/imagenes/amistad.png");
    QString  nombre_;
    QString  numero_;
    QString  password_;
    QString  correo_;
    fstream  USUARIOS;
    int      IDUser=0;

    fstream  PUBLICACIONES;
    fstream  AMIGOSUSER;
    ifstream COMENTS;
    ifstream INTERACTIONS;
    ifstream FOLLOWERS;

    //antiguo
    Lista<User*> listamigos;
    Stack<User*>   listausuarios;
    Stack<QString> listanuncios;
   ///



    User* usuario;

    Stack<Comentario*>  listcomentarios;
    Stack<Publicacion*> listpublicacion;
    vector<User*>      AmigosG;
    Stack<Interaccion*> listinteraction;

     //ARBOLES PARA PUBLICACIONES:
    typedef AVL<Publicacion*,   QString> Bst_S;
    typedef AVL<Publicacion*,   int> Bst_I;
    typedef AVL2P<Publicacion*, int,QString> BstLike_ID;


    Bst_S* btsfecha = new Bst_S([](Publicacion* a) { return a->getfechapublicacion(); });

    BstLike_ID* btsnumlikes = new BstLike_ID([](Publicacion* a) { return a->getnumlikes();},[](Publicacion* a) { return a->getID(); });

    Bst_S* btstitulo= new Bst_S([](Publicacion* a) { return a->gettitle(); });



    Bst_S* btsIDP = new Bst_S([](Publicacion* a) { return a->getID(); });
    Bst_S* btsPublicIDUSER= new Bst_S([](Publicacion* a) { return a->getIDuser(); });
    QString IDACTUALparaperfil;

    //ARBOLES PARA USUARIOS AMIGOS
    typedef AVL<User*, QString> UBst_S;
    typedef AVL<User*, int>     UBst_I;

    UBst_S* btsUnombre =      new UBst_S([](User* a) { return a->getNombre(); });
    UBst_S* btsUcorreo=       new UBst_S([](User* a) { return a->fecharegistro; });
    UBst_S* btsUregisterdate= new UBst_S([](User* a) { return a->getFecha(); });
    UBst_S* btsUIDA= new UBst_S([](User* a) { return a->ID; });
    QString IDUsuarioactual;
    //COMENTARIOS
    typedef AVL<Comentario*, QString>  CBst_S;
    CBst_S* btsComentidPUB= new CBst_S([](Comentario* a) { return a->getidPUB(); });
    QString IDPublicacionactual;


    //INTERACTIONS
    typedef AVL<Interaccion*, QString>  IBst_S;
    IBst_S* bstinteraccionesIDUSER= new IBst_S([](Interaccion* a) { return a->getiduser(); });




    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void registrar();
    void continuar();
    void registrarse();
    void login();
    void agregaramigo();
    void eliminaramigo();
    void eliminarpost();
    void cancelarregistro();
     //void cargarpublicaciones();
    void cargarcomentarios();
    void cargarinteracciones();
    void cargarpublicacionesiniciales();
    void crearBSTs();

    //void mostrarlosprimerasNpublicaciones();


    //void cargaramigosguardados();
   //


    void mostrarTendecias();
    void mostrarRecientes();




   // void leerarchivo(Stack<User*>archivotxtusuario);//lambdas
    //bool coincide(string name,string password);//se convirtio en lambdas

    void on_numlikesBTN_clicked();
    void on_numfechaBTN_clicked();

    void on_SGTBTN_clicked();

    void on_LWanuncios_itemDoubleClicked();
    void on_BTNINICIO_clicked();
    void on_BTNPERFIL1_clicked();
    void on_BTNPublicaciones1_clicked();
    void on_BTNpubliclike1_clicked();
    void on_Bafabetamigo_clicked();
    void on_Bbuscaramigo_clicked();

    void on_BTNcomentarios1_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_LWanunciosPag_itemDoubleClicked();

    void on_BTNpubliclike1_2_clicked();

    void on_BTNComent_Relevantes_clicked();

    void on_LWanuncios_popular_itemDoubleClicked();

    void on_LWanuncios_Recientes_itemDoubleClicked();

    void on_BTNcomentarPopular_clicked();

    void on_BTNpubliclike1_popular_clicked();

    void on_BTNcomentar_recientes_clicked();

    void on_BTNpubliclike1_recientes_clicked();
    void buscarporTitulo(QString titulo);
    void buscarporTitulorecientes(QString titulo);
    void buscarporTitulopopulares(QString titulo);

    void buscarporTituloRelevantes(QString titulo);

    void on_LEbusqueda_Titulo_textEdited(const QString &arg1);



    void on_LEbuscarTitulo_Recientes_textEdited(const QString &arg1);

    void on_LEbuscar_Popular_textEdited(const QString &arg1);

    void on_LEbuscar_Relevantes_textEdited(const QString &arg1);
    void on_LWamigos_itemDoubleClicked();

    void on_BTAmigosdeamigos_clicked();
    void SetPublicacionUser(QString,QString,QString,QString,QString,int);

    void on_BPublicar_clicked();

    void on_BTNcompartir_clicked();

    void on_BTPublicacionesamigos_clicked();

    void on_BTSeguiramigo_clicked();

    void on_BTtoppublicacione_clicked();

    void on_BTAmigosuser_clicked();

    void on_BTPublicacionesuser_clicked();
void BuscarPor_nombreAmigos(QString nombre);
    void on_LEbuscarA_textEdited(const QString &arg1);




private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
