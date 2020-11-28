#include "mainwindow.h"
#include "ui_mainwindow.h"
#define ALE(I,F) rand()%(F-I+1)+I

vector<Publicacion*> arrpublic;
vector<Publicacion*> arrpublicnumLikes;
vector<Publicacion*> arrpublicFecha;

vector<User*> arramigos;
vector<Comentario*> arrComem;


//para interacciones:
vector<Interaccion*> arrinteracciones;
 vector<QString> arrIDPUBLIC_Interac;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(nullptr));
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);//iniciar en la ventana 0   
    connect(ui->BRegistrar,SIGNAL(released()),this,SLOT(registrar()));
    connect(ui->Bcontinuar,SIGNAL(released()),this,SLOT(continuar()));
    connect(ui->BRegistrarse,SIGNAL(released()),this,SLOT(registrarse()));
    connect(ui->BLogin,SIGNAL(released()),this,SLOT(login()));

    connect(ui->BCancelar,SIGNAL(released()),this,SLOT(cancelarregistro()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registrar(){
    function<void()>escribirtxtusuario=[&] (){
        USUARIOS.open("Usuarios.txt",ios::app);
        if(USUARIOS.is_open()){
                string linea;
                linea=nombre_.toStdString()+" "+password_.toStdString()+" "+correo_.toStdString()+" "+numero_.toStdString();
            USUARIOS<<linea<<endl;
            USUARIOS.close();
        }
    };
    if(ui->LENombre->text()==""||ui->LECorreo->text()==""||ui->LEPassword->text()==""||ui->LENumero->text()=="")
        QMessageBox::warning(this,"Error ","FALTAN LLENAR LOS DATOS ");
    else{
    nombre_   =ui->LENombre->text();
    correo_   =ui->LECorreo->text();
    password_ =ui->LEPassword->text();
    numero_   =ui->LENumero->text();


   listausuarios.push(new User(nombre_,password_,correo_,numero_,"","12"));
   escribirtxtusuario();

    ui->stackedWidget->setCurrentIndex(0);
    }

}

void MainWindow::continuar(){
    ui->LBnombre->setText(nombre_);
    ui->LBcorreo->setText(usuario->getemail());
    ui->LBnumero->setText(numero_);
    function<void( )>cargarfollowers=[&](){
            FOLLOWERS.open("followers.tsv",ios::in);
             if(FOLLOWERS.is_open()){
                 string idU,idF;
                 while(getline(FOLLOWERS,idU,'\t')){
                    getline(FOLLOWERS,idF);
                     QString aaa = QString::fromStdString(idU);
                     QString bbb = QString::fromStdString(idF);
                    User* aux =btsUIDA->find(aaa);
                    IDUsuarioactual=aux->ID;
                    btsUIDA->find(aaa)->SetFollowers(btsUIDA->find(bbb));

                  }FOLLOWERS.close();
             }else
                 QMessageBox::warning(this,"Error","El archivo no s epudo abrir");
    };
   function<void( )>Setpublicaciones=[&](){
       PUBLICACIONES.open("publications.tsv",ios::in);
            if(PUBLICACIONES.is_open()){

                string idPub, idUSU, Title, desc,fechaP;
                string auxlikes;
                int likes;

                while(getline(PUBLICACIONES,idPub,'\t')){
                   getline(PUBLICACIONES,idUSU,'\t');
                   getline(PUBLICACIONES,Title,'\t');
                   getline(PUBLICACIONES,desc,'\t');
                   getline(PUBLICACIONES,fechaP,'\t');
                   getline(PUBLICACIONES,auxlikes);
                   likes=stoi(auxlikes);
           QString aaa = QString::fromStdString(idUSU);
                  btsUIDA->find(aaa)->SetPublicaciones(new Publicacion(QString::fromStdString(idUSU),QString::fromStdString(idPub),
                                                                                                 QString::fromStdString(Title),QString::fromStdString(desc),
                                                                                                 likes,QString::fromStdString(fechaP)));

                }PUBLICACIONES.close();


            }else
                QMessageBox::warning(this,"Error","El archivo no s epudo abrir");

    };
    crearBSTs();
    cargarfollowers();
    Setpublicaciones();
    cargarpublicacionesiniciales();
    ui->stackedWidget->setCurrentIndex(3);

}



void MainWindow::eliminarpost(){
    listanuncios.pop();
    //publicar();
}


void MainWindow::registrarse(){
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::login(){
    //_______________________________________________________________________________
    function<void( )>cargaramigosguardados=[&](){
    AMIGOSUSER.open("users.tsv",ios::in);
         if(AMIGOSUSER.is_open()){

             string code,nombre,passwor,correo,fechaCrea;
             while(getline(AMIGOSUSER,code,'\t')){
                getline(AMIGOSUSER,correo,'\t');
                getline(AMIGOSUSER,nombre,'\t');
                getline(AMIGOSUSER,fechaCrea);



                AmigosG.push_back(new User(QString::fromStdString(nombre),"123",QString::fromStdString(correo)
                                       ,QString::fromStdString(fechaCrea),QString::fromStdString(code),"2135468"));

             }AMIGOSUSER.close();
         }else
             QMessageBox::warning(this,"Error","El archivo no s epudo abrir");

         for(int i=0 ;i<50;i++){
             QListWidgetItem *item= new QListWidgetItem;
            item->setIcon(*amigo);
            item->setText(AmigosG.at(i)->getNombre());
                 ui->LWamigos->addItem(item);
             }
    };




    function<void( )>cargarpublicaciones=[&](){
        PUBLICACIONES.open("publications.tsv",ios::in);
             if(PUBLICACIONES.is_open()){

                 string idPub, idUSU, Title, desc,fechaP;
                 string auxlikes;
                 int likes;

                 while(getline(PUBLICACIONES,idPub,'\t')){
                    getline(PUBLICACIONES,idUSU,'\t');
                    getline(PUBLICACIONES,Title,'\t');
                    getline(PUBLICACIONES,desc,'\t');
                    getline(PUBLICACIONES,fechaP,'\t');
                    getline(PUBLICACIONES,auxlikes);
                    likes=stoi(auxlikes);
                   /*User* aux =btsUIDA->find(QString::fromStdString(idUSU));
                   Publicacion* publi=new Publicacion(QString::fromStdString(idUSU),QString::fromStdString(idPub),
                                                      QString::fromStdString(Title),QString::fromStdString(desc),
                                                      likes,QString::fromStdString(fechaP)) ;
                   btsUIDA->find(QString::fromStdString(idUSU))->SetPublicaciones(publi);

*/

                    listpublicacion.push(
                    new Publicacion(QString::fromStdString(idUSU),QString::fromStdString(idPub)
                                    ,QString::fromStdString(Title),QString::fromStdString(desc),
                                    likes,QString::fromStdString(fechaP)));
                 }PUBLICACIONES.close();
                 on_numfechaBTN_clicked();

             }else
                 QMessageBox::warning(this,"Error","El archivo no s epudo abrir");

    };
    //_________________________________________________________________________________________________________
     cargarpublicaciones();
     cargaramigosguardados();

     cargarcomentarios();
     cargarinteracciones();

    function<void(fstream& )>leerarchivo=[&](fstream &user){
          user.open("Usuarios.txt",ios::in);
          if(user.is_open()){
              string nom,con,cor,num;
              while(!user.eof()){
                 user>>nom>>con>>cor>>num;
                 listausuarios.push(new User(QString::fromStdString(nom),
                                   QString::fromStdString(con),
                                   QString::fromStdString(cor),"5-12-9",
                                   "",QString::fromStdString(num)));
              }user.close();
          }else
              QMessageBox::warning(this,"Error","El archivo usuarios.txt no se puedo abrir");
      };

    function<bool(string ,string )>coincide=[&](string name,string password){
         for (int i=0;i<listausuarios.size() ;++i ) {
             if(listausuarios.get(i)->getNombre()==QString::fromStdString(name)
                     &&listausuarios.get(i)->getPassword()==QString::fromStdString(password)){
                 USUARIOS.close();
                 nombre_=listausuarios.get(i)->getNombre();
                 correo_=listausuarios.get(i)->getPassword();
                 numero_=listausuarios.get(i)->getNumero();
                 return true;
            }
         }
          return false;
     };
      leerarchivo(AMIGOSUSER);
      if(coincide(ui->LEUsuario->text().toStdString(),ui->LEContrase->text().toStdString())){
          ui->stackedWidget->setCurrentIndex(2);
        }
      else {
          QMessageBox::warning(this,"Error","NO REGISTRADO ");
          ui->LEUsuario->setText("");
          ui->LEContrase->setText("");
      }
       usuario=new User( ui->LEUsuario->text(),"123",ui->LEUsuario->text()+"@gamil.com", "2020-11-26","0","995655225");
}



void MainWindow::agregaramigo(){

}

void MainWindow::eliminaramigo(){

}


void MainWindow::cancelarregistro(){
    ui->LENombre->setText("");
    ui->LEPassword->setText("");
    ui->LECorreo->setText("");
    ui->LENumero->setText("");
    ui->stackedWidget->setCurrentIndex(0);

}
//////////////////////RELLENAR ARBOLES/////////////////////////////////////////
void MainWindow::crearBSTs(){
    //Agregar publicaciones

    for(int i=0;i<listpublicacion.size();++i){
        btsfecha->addelem(listpublicacion.get(i));
        btsnumlikes->addelem(listpublicacion.get(i));
        btstitulo->addelem(listpublicacion.get(i));
        btsIDP->addelem(listpublicacion.get(i));
        btsPublicIDUSER->addelem(listpublicacion.get(i));
    }


    //Agregar amigos usuario
    for(int i=0;i<int(AmigosG.size());++i){
        btsUnombre->addelem(AmigosG.at(i));
        btsUcorreo->addelem(AmigosG.at(i));
        btsUregisterdate->addelem(AmigosG.at(i));
        btsUIDA->addelem(AmigosG.at(i));
    }


    for(int i=0;i<listcomentarios.size();++i){
        btsComentidPUB->addelem(listcomentarios.get(i));
    }
    for(int i=0;i<listinteraction.size();++i){
        bstinteraccionesIDUSER->addelem(listinteraction.get(i));
    }

    for(int i=0;i<int(listinteraction.size());++i){
        //Publicacion* aux=btsIDP->find(listinteraction.get(i)->getidpub());
        listpublicacion.get(i)->agregarinteraccion(listinteraction.get(i));
    }



}

///////////////////////////////////////////////////////////////////////////////////////

void MainWindow::cargarpublicacionesiniciales(){

    ui->LWanuncios->clear();
    arrpublic.clear();
    btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublic.push_back(x);  },30,'u');

    vector<int> arrconts(arrpublic.size());
    for(int i=0;i<int(arrpublic.size());++i){
        for(int j=0;j<int(arrpublic[i]->gervectorinteracc().size());++j){
            if(arrpublic[i]->gervectorinteracc()[j]->getiduser()=="0"){
                arrconts[i]++;
            }
        }

    }

    for(int i=0;i<int(arrpublic.size());++i){
        for(int j=i+1;j<int(arrpublic.size());++j){
            if(arrpublic[i]->getnumlikes()<arrpublic[j]->getnumlikes()){
                swap(arrpublic[i],arrpublic[j]);

            }
        }
    }


    for(int i=0;i<int(arrconts.size());++i){
        for(int j=i+1;j<int(arrconts.size());++j){
            if(arrconts[i]<arrconts[j]){
                swap(arrconts[i],arrconts[j]);
                swap(arrpublic[i],arrpublic[j]);

            }
        }
    }




    for(int i=0;i<int(arrpublic.size());++i){

        ui->LWanuncios->addItem(arrpublic[i]->gettitle());
    }

}


void MainWindow::on_numlikesBTN_clicked(){
    ui->LWanuncios->clear();
    arrpublic.clear();
    btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublic.push_back(x);  },30,'u');
    for(int i=0;i<int(arrpublic.size());++i){
        ui->LWanuncios->addItem(arrpublic[i]->gettitle());
    }
}

void MainWindow::on_numfechaBTN_clicked(){
    ui->LWanuncios->clear();
    arrpublic.clear();
    btsfecha->mostrarenordenconParametro([](Publicacion* x){arrpublic.push_back(x);  },30,'u');
    for(int i=0;i<int(arrpublic.size());++i){

        ui->LWanuncios->addItem(arrpublic[i]->gettitle());
    }

}

void MainWindow::on_SGTBTN_clicked(){
      ui->stackedWidget->setCurrentIndex(5);
}



/////////////////FUNCIONES CARGAR DATOS/////////////////////////////////////////////////////////////////////////////

void MainWindow::cargarcomentarios(){

    COMENTS.open("comentarios.tsv",ios::in);
         if(COMENTS.is_open()){

             string id, idUSU,fechaPublic,text;

             while(getline(COMENTS,id,'\t')){

                getline(COMENTS,idUSU,'\t');
                getline(COMENTS,fechaPublic,'\t');
                getline(COMENTS,text);


                listcomentarios.push(new Comentario(QString::fromStdString(fechaPublic),
                                                    QString::fromStdString(text),
                                                    QString::fromStdString(id),
                                                    QString::fromStdString(idUSU)));
             }COMENTS.close();

         }else
             QMessageBox::warning(this,"Error","El archivo no s epudo abrir");

};


void MainWindow::cargarinteracciones(){

    INTERACTIONS.open("interaction.tsv",ios::in);
         if(INTERACTIONS.is_open()){

             string idPu, idUSU,fechaInteraccion,tipointerac;

             while(getline(INTERACTIONS,idUSU,'\t')){
                getline(INTERACTIONS,idPu,'\t');
                getline(INTERACTIONS,fechaInteraccion,'\t');
                getline(INTERACTIONS,tipointerac);


                listinteraction.push(new Interaccion(QString::fromStdString(fechaInteraccion),
                                                    QString::fromStdString(tipointerac),
                                                    QString::fromStdString(idUSU),
                                                    QString::fromStdString(idPu)));
             }INTERACTIONS.close();

         }else
             QMessageBox::warning(this,"Error","El archivo no s epudo abrir");



};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////para mostrarpublicaciones::::::******
///
///



void MainWindow::on_LWanuncios_itemDoubleClicked(){
    //int num =ui->LWanuncios->currentIndex().row();

    arrComem.clear();
    ui->LWcomentarios1->clear();
    QString aaa = ui->LWanuncios->currentItem()->text();
    Publicacion* aux =btstitulo->find(aaa);


    IDPublicacionactual=aux->getID();

    ui->TEXTpublicstacked1->setText(aux->gettitle()+"\n"+aux->getdesc());
    ui->Labellikespublic->setText(QString::number(aux->getnumlikes()));
    ui->labelfechapublic->setText(aux->getfechapublicacion());
    btsComentidPUB->mostrartodascoincidencias([](Comentario* x){arrComem.push_back(x);},aux->getID());

    for(int i=0;i<int(arrComem.size());++i){
       ui->LWcomentarios1->addItem("\n"+arrComem[i]->gettext()+"\n"+"______________________________________________" + "\n");

    }

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);




}
void MainWindow::on_BTNcomentarios1_clicked(){
    ui->LWcomentarios1->clear();
    Comentario* aux;

    if(ui->textEditcomentario1->toPlainText()!=""){
    QString text= "\n"+ ui->textEditcomentario1->toPlainText()+"\n";
    aux=new Comentario("18-11-35",text,QString::fromStdString(to_string(listcomentarios.size()+1))
                      ,IDPublicacionactual);

    arrComem.push_back(aux);
    btsComentidPUB->addelem(aux);
    }


    for(int i=0;i<int(arrComem.size());++i){
        ui->LWcomentarios1->addItem("\n"+arrComem[i]->gettext()+"______________________________________________" + "\n");

    }
    ui->textEditcomentario1->setText("");


    ////////////interaccion///////// crear
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);



}
void MainWindow::on_Bafabetamigo_clicked()
{
    ui->LWamigos->clear();
    arramigos.clear();
    btsUnombre->mostrarenordenconParametro([](User* x){arramigos.push_back(x);  },50,'p');
    for(int i=0;i<int(arramigos.size());++i){
        QListWidgetItem *item= new QListWidgetItem;
       item->setIcon(*amigo);
       item->setText(arramigos.at(i)->getNombre()+"\n"+arramigos.at(i)->getemail());
       ui->LWamigos->addItem(item);

    }
}

void MainWindow::on_LWamigos_itemDoubleClicked(){
    ui->LWamigosdeamigos->clear();

    QString aaa = ui->LWamigos->currentItem()->text();
    User* aux =btsUnombre->find(aaa);
    ui->Lnombreamigo->setText(aux->nombre);
    ui->Lcorreoamigo->setText(aux->getemail());

    vector<User*>follower =aux->getfollower();

    for (int i=0;i<int(follower.size()) ;++i ) {
        ui->LWamigosdeamigos->addItem(follower[i]->getNombre());

    }
    ui->LWanunciosamigos->clear();

    User *users= btsUnombre->find(ui->LWamigos->currentItem()->text());
    vector<Publicacion*> aux1=users->GetPublicaciones();
    //btsPublicIDUSER->mostrartodascoincidencias([](Publicacion* x){arrpublicPerfil.push_back(x);  },IDACTUALparaperfil);
    for(int i=0;i<int(aux1.size());++i){
       ui->LWanunciosamigos->addItem(aux1[i]->gettitle()) ;
    }

     ui->SWmostrar->setCurrentIndex(3);
}
















// //////Botones barra
void MainWindow::on_BTNINICIO_clicked()        {    ui->stackedWidget->setCurrentIndex(3);
                                                    ui->SWmostrar->setCurrentIndex(0);
                                                    cargarpublicacionesiniciales();
                                               }
void MainWindow::on_BTNPERFIL1_clicked()       {    ui->SWmostrar->setCurrentIndex(1);
                                                    ui->Lnombreuser->setText(usuario->getNombre());
                                                    ui->Lcorreouser->setText(usuario->getemail());






                                               }
void MainWindow::on_BTNPublicaciones1_clicked(){    ui->SWmostrar->setCurrentIndex(2);


                                                    //primer pestaña dos parametros con numlikes y mas reciente y es de un amigo..
                                                    ui->LWanunciosPag->clear();
                                                    arrpublic.clear();
                                                    btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublic.push_back(x);  },30,'u');
                                                             for(int i=0;i<int(arrpublic.size());++i){
                                                                 for(int j=i+1;j<int(arrpublic.size());++j){
                                                                     if(arrpublic[i]->getnumlikes()<arrpublic[j]->getnumlikes()){
                                                                         swap(arrpublic[i],arrpublic[j]);

                                                                     }
                                                                 }
                                                             }

                                                    for(int i=0;i<int(arrpublic.size());++i){
                                                        ui->LWanunciosPag->addItem(arrpublic[i]->gettitle());
                                                    }




                                                    //segunda pestaña mas numlikes

                                                    ui->LWanuncios_popular->clear();
                                                    arrpublicnumLikes.clear();
                                                    btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublicnumLikes.push_back(x);  },30,'u');

                                                           for(int i=0;i<int(arrpublicnumLikes.size());++i){
                                                               for(int j=i+1;j<int(arrpublicnumLikes.size());++j){
                                                                   if(arrpublicnumLikes[i]->getnumlikes()<arrpublicnumLikes[j]->getnumlikes()){
                                                                       swap(arrpublicnumLikes[i],arrpublicnumLikes[j]);

                                                                   }
                                                               }
                                                           }

                                                    for(int i=0;i<int(arrpublicnumLikes.size());++i){
                                                        ui->LWanuncios_popular->addItem(arrpublicnumLikes[i]->gettitle());
                                                    }

                                                    //tercera pestaña  mas reciente
                                                    ui->LWanuncios_Recientes->clear();
                                                    arrpublicFecha.clear();
                                                    btsfecha->mostrarenordenconParametro([](Publicacion* x){arrpublicFecha.push_back(x);  },30,'u');

                                                           for(int i=0;i<int(arrpublicFecha.size());++i){
                                                               for(int j=i+1;j<int(arrpublicFecha.size());++j){
                                                                   if(arrpublicFecha[i]->getfechapublicacion()<arrpublicFecha[j]->getfechapublicacion()){
                                                                       swap(arrpublicFecha[i],arrpublicFecha[j]);

                                                                   }
                                                               }
                                                           }
                                                    for(int i=0;i<int(arrpublicFecha.size());++i){
                                                        ui->LWanuncios_Recientes->addItem(arrpublicFecha[i]->gettitle());
                                                    }

                                                      ui->auxprobar->setText(QString::fromStdString(to_string(btsnumlikes->getlen())));

                                               }
// //////////////////////////////
void MainWindow::on_BTNpubliclike1_clicked(){

    Publicacion* aux = btsIDP->find(IDPublicacionactual);
    btsnumlikes->Removercon2P(aux->getnumlikes(),aux->getID());
    aux->setnumlikes(aux->getnumlikes()+1);
    btsnumlikes->addelem(aux);
    ui->Labellikespublic->clear();
    ui->Labellikespublic->setText(QString::fromStdString(to_string(aux->getnumlikes())));



    ////////////interaccion///////// crear
    ///

    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);


}
void MainWindow::mostrarTendecias(){}
void MainWindow::mostrarRecientes(){}
void MainWindow::on_Bbuscaramigo_clicked()
{
    ui->LWamigos->clear();
    arramigos.clear();

    btsUnombre->mostrartodascoincidencias([](User* x){arramigos.push_back(x);  }, ui->LEbuscarA->text());
    for(int i=0;i<arramigos.size();++i){

         ui->LWamigos->addItem(arramigos.at(i)->getNombre() + "\n" + arramigos.at(i)->getemail());

    }
}


//Parte de publicaciones

void MainWindow::on_tabWidget_tabBarClicked(int index){
}

/////Parte de relevantes:
///
///
///
void MainWindow::on_LWanunciosPag_itemDoubleClicked()
{
    //int num =ui->LWanunciosPag->currentIndex().row();

    arrComem.clear();
    ui->LWcomentarios1_2->clear();

    QString aaa = ui->LWanunciosPag->currentItem()->text();
    Publicacion* aux =btstitulo->find(aaa);




    IDPublicacionactual=aux->getID();

    ui->TEXTpublicstacked1_2->setText(aux->gettitle()+"\n"+aux->getdesc());
    ui->Labellikespublic_2->setText(QString::number(aux->getnumlikes()));
    ui->labelfechapublic_2->setText(aux->getfechapublicacion());
    btsComentidPUB->mostrartodascoincidencias([](Comentario* x){arrComem.push_back(x);},aux->getID());

    for(int i=0;i<int(arrComem.size());++i){
       ui->LWcomentarios1_2->addItem("\n" + arrComem[i]->gettext()+"\n"+"______________________________________________" + "\n");

    }

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);



}

void MainWindow::on_BTNpubliclike1_2_clicked()
{

    Publicacion* aux = btsIDP->find(IDPublicacionactual);
    btsnumlikes->Removercon2P(aux->getnumlikes(),aux->getID());
    aux->setnumlikes(aux->getnumlikes()+1);
    btsnumlikes->addelem(aux);
    ui->Labellikespublic_2->clear();
    ui->Labellikespublic_2->setText(QString::fromStdString(to_string(aux->getnumlikes())));

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);




}

void MainWindow::on_BTNComent_Relevantes_clicked()
{
    ui->LWcomentarios1_2->clear();
    Comentario* aux;

    if(ui->textEditComentario2->toPlainText()!=""){
    QString text= "\n"+ ui->textEditComentario2->toPlainText()+"\n";
    aux=new Comentario("18-11-35",text,QString::fromStdString(to_string(listcomentarios.size()+1))
                      ,IDPublicacionactual);

    arrComem.push_back(aux);
    btsComentidPUB->addelem(aux);
    }


    for(int i=0;i<int(arrComem.size());++i){
        ui->LWcomentarios1_2->addItem("\n"+arrComem[i]->gettext()+"______________________________________________" + "\n");

    }
    ui->textEditComentario2->setText("");
    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);



}

/////Parte de populares:
///
///
///
void MainWindow::on_LWanuncios_popular_itemDoubleClicked(){
    //int num =ui->LWanuncios_popular->currentIndex().row();

    arrComem.clear();
    ui->LWcomentariosPopular->clear();
    QString aaa = ui->LWanuncios_popular->currentItem()->text();
    Publicacion* aux =btstitulo->find(aaa);




    IDPublicacionactual=aux->getID();

    ui->TEXTpublicstacked1_popular->setText(aux->gettitle()+"\n"+aux->getdesc());
    ui->Labellikespublic_popular->setText(QString::number(aux->getnumlikes()));
    ui->labelfechapublic_popular->setText(aux->getfechapublicacion());
    btsComentidPUB->mostrartodascoincidencias([](Comentario* x){arrComem.push_back(x);},aux->getID());

    for(int i=0;i<int(arrComem.size());++i){
       ui->LWcomentariosPopular->addItem("\n" + arrComem[i]->gettext()+"\n"+"______________________________________________" + "\n");

    }

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);


}
void MainWindow::on_BTNcomentarPopular_clicked()
{
    ui->LWcomentariosPopular->clear();
    Comentario* aux;

    if(ui->textEditPopulares->toPlainText()!=""){
    QString text= "\n"+ ui->textEditPopulares->toPlainText()+"\n";
    aux=new Comentario("18-11-35",text,QString::fromStdString(to_string(listcomentarios.size()+1))
                      ,IDPublicacionactual);

    arrComem.push_back(aux);
    btsComentidPUB->addelem(aux);
    }


    for(int i=0;i<int(arrComem.size());++i){
        ui->LWcomentariosPopular->addItem("\n"+arrComem[i]->gettext()+"______________________________________________" + "\n");

    }
    ui->textEditPopulares->setText("");


    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);

}
void MainWindow::on_BTNpubliclike1_popular_clicked()
{
    Publicacion* aux = btsIDP->find(IDPublicacionactual);
    btsnumlikes->Removercon2P(aux->getnumlikes(),aux->getID());
    aux->setnumlikes(aux->getnumlikes()+1);
    btsnumlikes->addelem(aux);
    ui->Labellikespublic_popular->clear();
    ui->Labellikespublic_popular->setText(QString::fromStdString(to_string(aux->getnumlikes())));

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);


}
/////Parte de recientes:
///
///
///
void MainWindow::on_LWanuncios_Recientes_itemDoubleClicked()
{
    //int num =ui->LWanuncios_Recientes->currentIndex().row();

    arrComem.clear();
    ui->LWcomentarios1_recientes->clear();

    QString aaa = ui->LWanuncios_Recientes->currentItem()->text();
    Publicacion* aux =btstitulo->find(aaa);



    IDPublicacionactual=aux->getID();

    ui->TEXTpublicstacked1_recientes->setText(aux->gettitle()+"\n"+aux->getdesc());
    ui->Labellikespublic_recientes->setText(QString::number(aux->getnumlikes()));
    ui->labelfechapublic_recientes->setText(aux->getfechapublicacion());
    btsComentidPUB->mostrartodascoincidencias([](Comentario* x){arrComem.push_back(x);},aux->getID());

    for(int i=0;i<int(arrComem.size());++i){
       ui->LWcomentarios1_recientes->addItem("\n" + arrComem[i]->gettext()+"\n"+"______________________________________________" + "\n");

    }
    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);


}
void MainWindow::on_BTNcomentar_recientes_clicked()
{
    ui->LWcomentarios1_recientes->clear();
    Comentario* aux;

    if(ui->textEditcomentar_recientes->toPlainText()!=""){
    QString text= "\n"+ ui->textEditcomentar_recientes->toPlainText()+"\n";
    aux=new Comentario("18-11-35",text,QString::fromStdString(to_string(listcomentarios.size()+1))
                      ,IDPublicacionactual);

    arrComem.push_back(aux);
    btsComentidPUB->addelem(aux);
    }


    for(int i=0;i<int(arrComem.size());++i){
        ui->LWcomentarios1_recientes->addItem("\n"+arrComem[i]->gettext()+"________________________________" + "\n");

    }
    ui->textEditcomentar_recientes->setText("");

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);




}
void MainWindow::on_BTNpubliclike1_recientes_clicked()
{
    Publicacion* aux = btsIDP->find(IDPublicacionactual);
    btsnumlikes->Removercon2P(aux->getnumlikes(),aux->getID());
    aux->setnumlikes(aux->getnumlikes()+1);
    btsnumlikes->addelem(aux);
    ui->Labellikespublic_recientes->clear();
    ui->Labellikespublic_recientes->setText(QString::fromStdString(to_string(aux->getnumlikes())));

    ////////////interaccion///////// crear
    ///
    ///
    Interaccion* aui=new Interaccion("12_01_12","FALSE","0",IDPublicacionactual);
    listinteraction.push(aui);
    btsIDP->find(IDPublicacionactual)->agregarinteraccion(aui);



}



//BUSQUEDA POR TITULO::

void MainWindow::buscarporTitulo(QString titulo){
       ui->LWanuncios->clear();
       arrpublic.clear();

       btstitulo->mostrartodascoincidenciascontains(titulo,[](Publicacion* x){arrpublic.push_back(x);},
       [](Publicacion* x,QString a){
           if(x->gettitle().contains(a,Qt::CaseInsensitive)){return true;}
           else{return false;}
       }
       );

       for(int i=0;i<int(arrpublic.size());++i){
           ui->LWanuncios->addItem(arrpublic[i]->gettitle());
       }




}
void MainWindow::buscarporTitulorecientes(QString titulo){
       ui->LWanuncios_Recientes->clear();
       arrpublicFecha.clear();

       btstitulo->mostrartodascoincidenciascontains(titulo,[](Publicacion* x){arrpublicFecha.push_back(x);},
       [](Publicacion* x,QString a){
           if(x->gettitle().contains(a,Qt::CaseInsensitive)){return true;}
           else{return false;}
       }
       );

       for(int i=0;i<int(arrpublicFecha.size());++i){
           ui->LWanuncios_Recientes->addItem(arrpublicFecha[i]->gettitle());
       }




}


void MainWindow::buscarporTitulopopulares(QString titulo){
       ui->LWanuncios_popular->clear();
       arrpublicnumLikes.clear();

       btstitulo->mostrartodascoincidenciascontains(titulo,[](Publicacion* x){arrpublicnumLikes.push_back(x);},
       [](Publicacion* x,QString a){
           if(x->gettitle().contains(a,Qt::CaseInsensitive)){return true;}
           else{return false;}
       }
       );

       for(int i=0;i<int(arrpublicnumLikes.size());++i){
           ui->LWanuncios_popular->addItem(arrpublicnumLikes[i]->gettitle());
       }




}

void MainWindow::buscarporTituloRelevantes(QString titulo){
       ui->LWanunciosPag->clear();
       arrpublic.clear();

       btstitulo->mostrartodascoincidenciascontains(titulo,[](Publicacion* x){arrpublic.push_back(x);},
       [](Publicacion* x,QString a){
           if(x->gettitle().contains(a,Qt::CaseInsensitive)){return true;}
           else{return false;}
       }
       );

       for(int i=0;i<int(arrpublic.size());++i){
           ui->LWanunciosPag->addItem(arrpublic[i]->gettitle());
       }




}

void MainWindow::on_LEbusqueda_Titulo_textEdited(const QString &arg1)
{
    if(arg1!=""){buscarporTitulo(arg1);
      }
    else{
        cargarpublicacionesiniciales();
    }
}

void MainWindow::on_LEbuscarTitulo_Recientes_textEdited(const QString &arg1)
{
    if(arg1!=""){buscarporTitulorecientes(arg1);
      }
    else{
        //tercera pestaña  mas reciente
        ui->LWanuncios_Recientes->clear();
        arrpublicFecha.clear();
        btsfecha->mostrarenordenconParametro([](Publicacion* x){arrpublicFecha.push_back(x);  },30,'u');

        for(int i=0;i<int(arrpublicFecha.size());++i){
            for(int j=i+1;j<int(arrpublicFecha.size());++j){
                if(arrpublicFecha[i]->getfechapublicacion()<arrpublicFecha[j]->getfechapublicacion()){
                    swap(arrpublicFecha[i],arrpublicFecha[j]);

                }
            }
        }
        for(int i=0;i<int(arrpublicFecha.size());++i){
            ui->LWanuncios_Recientes->addItem(arrpublicFecha[i]->gettitle());
        }

          ui->auxprobar->setText(QString::fromStdString(to_string(btsnumlikes->getlen())));
    }
}


void MainWindow::on_LEbuscar_Popular_textEdited(const QString &arg1)
{
    if(arg1!=""){buscarporTitulopopulares(arg1);
      }
    else{
        //segunda pestaña mas numlikes

        ui->LWanuncios_popular->clear();
        arrpublicnumLikes.clear();
        btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublicnumLikes.push_back(x);  },30,'u');

        for(int i=0;i<int(arrpublicnumLikes.size());++i){
            for(int j=i+1;j<int(arrpublicnumLikes.size());++j){
                if(arrpublicnumLikes[i]->getnumlikes()<arrpublicnumLikes[j]->getnumlikes()){
                    swap(arrpublicnumLikes[i],arrpublicnumLikes[j]);

                }
            }
        }
        for(int i=0;i<int(arrpublicnumLikes.size());++i){
            ui->LWanuncios_popular->addItem(arrpublicnumLikes[i]->gettitle());
        }
    }
}

void MainWindow::on_LEbuscar_Relevantes_textEdited(const QString &arg1)
{
    if(arg1!=""){buscarporTituloRelevantes(arg1);
      }
    else{
        //primer pestaña dos parametros con numlikes y mas reciente y es de un amigo..
        ui->LWanunciosPag->clear();
        arrpublic.clear();
        btsnumlikes->mostrarenordenconParametro([](Publicacion* x){arrpublic.push_back(x);  },30,'u');

        for(int i=0;i<int(arrpublic.size());++i){
            for(int j=i+1;j<int(arrpublic.size());++j){
                if(arrpublic[i]->getnumlikes()<arrpublic[j]->getnumlikes()){
                    swap(arrpublic[i],arrpublic[j]);

                }
            }
        }

        for(int i=0;i<int(arrpublic.size());++i){
            ui->LWanunciosPag->addItem(arrpublic[i]->gettitle());
        }

    }
}
void MainWindow::SetPublicacionUser(QString idp,QString idu,QString titulo,QString descrip,QString Fpub,int likes){
    Publicacion* aux=new Publicacion(idu,idp,titulo,descrip,likes,Fpub);
    usuario->SetPublicaciones(aux);

}
//void MainWindow::publicar(){

   /* function<void()> mostraranuncios=[&](){

        Stack<QString> aux;
        for(int i=listanuncios.size()-1;i>=0;i--){
            aux.push(listanuncios.get(i));
        }

        while(!aux.empty()){
            ui->LWanuncios->addItem(aux.top());
            aux.pop();
        }
    };

     if(ui->TXEanuncios->toPlainText()!=""){
    QString text= "@"+nombre_+"\n"+ ui->TXEanuncios->toPlainText()+"\n"+"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
    listanuncios.push(text);}
    mostraranuncios();
    ui->TXEanuncios->setText("");*/



//}

void MainWindow::on_BPublicar_clicked()
{

   int id=1;
    SetPublicacionUser(QString::number(id),"0",ui->TXEanuncios->toPlainText(),usuario->getNombre(),"2020-12-15",0);
    id++;
    ui->LWanunciosusuario->clear();
    vector<Publicacion*> aux1=usuario->GetPublicaciones();
    for (int i=0;i<int(aux1.size()) ;++i ) {
        ui->LWanunciosusuario->addItem(aux1[i]->gettitle());
    }
    Publicacion* aux = new Publicacion("0",QString::fromStdString(to_string(btsPublicIDUSER->getlen()+1)),ui->TXEanuncios->toPlainText(),nombre_,0,"2020-11-26");
       btsfecha->addelem(aux);
       btsnumlikes->addelem(aux);
       btstitulo->addelem(aux);
       btsIDP->addelem(aux);
       btsPublicIDUSER->addelem(aux);
}

void MainWindow::on_BTNcompartir_clicked()
{
    ui->LWanunciosusuario->clear();
    Publicacion* aux = btsIDP->find(IDPublicacionactual);
    SetPublicacionUser(aux->getID(),aux->getIDuser(),aux->gettitle(),aux->getdesc(),aux->getfechapublicacion(),aux->getnumlikes());
    vector<Publicacion*> aux1=usuario->GetPublicaciones();

    for (int i=0;i<int(aux1.size()) ;++i ) {
        ui->LWanunciosusuario->addItem(aux1[i]->gettitle());
    }
}

void MainWindow::on_BTPublicacionesamigos_clicked()
{
    ui->SWPerfilamigo->setCurrentIndex(0);
}

void MainWindow::on_BTSeguiramigo_clicked()
{
    usuario->SetFollowers(btsUnombre->find(ui->LWamigos->currentItem()->text()));
    btsUnombre->find(ui->LWamigos->currentItem()->text())->SetFollowers(usuario);
}
void MainWindow::on_BTAmigosdeamigos_clicked()
{
    ui->SWPerfilamigo->setCurrentIndex(1);
    ui->LWamigosdeamigos->clear();
    vector<User*> aux=btsUnombre->find(ui->LWamigos->currentItem()->text())->getfollower();

    for (int i=0;i<int(aux.size()) ;++i ) {

        QListWidgetItem *item= new QListWidgetItem;
       item->setIcon(*amigo);
       item->setText(aux[i]->getNombre());
            ui->LWamigosdeamigos->addItem(item);
    }

}

void MainWindow::on_BTtoppublicacione_clicked()
{
     ui->SWPerfilamigo->setCurrentIndex(2);

     ui->LWmejoresanuncios->clear();

     User *users= btsUnombre->find(ui->LWamigos->currentItem()->text());
     vector<Publicacion*> aux1=users->GetPublicaciones();
     vector<Publicacion*> aux2;
     //btsPublicIDUSER->mostrartodascoincidencias([](Publicacion* x){arrpublicPerfil.push_back(x);  },IDACTUALparaperfil);
 vector<int> likes;
 for (int i=0;i<aux1.size() ;++i ) {
     likes.push_back(aux1[i]->getnumlikes());
 }
 sort(likes.begin(),likes.end());
 for (int i=0;i<aux1.size() ;++i ) {
     for (int j=0;i<aux1.size() ;++i ) {
         if(likes[i]==aux1[j]->getnumlikes()){
             aux2.push_back(aux1[j]);
         }

     }
 }

     for(int i=0;i<int(aux2.size());++i){
        ui->LWmejoresanuncios->addItem(aux2[i]->gettitle()) ;
     }


}

void MainWindow::on_BTAmigosuser_clicked()
{
ui->SWPerfil->setCurrentIndex(1);
ui->LWamigosusuario->clear();
vector<User*>auxx=usuario->getfollower();
for(int i=0;i<int(auxx.size());++i){
    QListWidgetItem *item= new QListWidgetItem;
   item->setIcon(*amigo);
   item->setText(auxx[i]->getNombre());
   ui->LWamigosusuario->addItem(item);

   }
}


void MainWindow::on_BTPublicacionesuser_clicked()
{
    ui->SWPerfil->setCurrentIndex(0);
}
void MainWindow::BuscarPor_nombreAmigos(QString nombre){
    ui->LWamigos->clear();
     arramigos.clear();

    btsUnombre->mostrartodascoincidenciascontains(nombre,[](User* x){arramigos.push_back(x);},
    [](User* x,QString a){
        if(x->getNombre().contains(a,Qt::CaseInsensitive)){return true;}
        else{return false;}
    }
    );

    for(int i=0;i<int(arramigos.size());++i){
        QListWidgetItem *item= new QListWidgetItem;
       item->setIcon(*amigo);
       item->setText(arramigos[i]->getNombre());
       ui->LWamigos->addItem(item);

    }

}
void MainWindow::on_LEbuscarA_textEdited(const QString &arg1)
{
    if(arg1!=""){
        BuscarPor_nombreAmigos(arg1);
    }
    else{
        ui->LWamigos->clear();
         arramigos.clear();

        for(int i=0 ;i<50;i++){
            QListWidgetItem *item= new QListWidgetItem;
           item->setIcon(*amigo);
           item->setText(AmigosG.at(i)->getNombre());
                ui->LWamigos->addItem(item);
           }

    }
}
