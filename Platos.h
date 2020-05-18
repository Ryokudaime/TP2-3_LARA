#ifndef PLATOS_H_INCLUDED
#define PLATOS_H_INCLUDED


struct Platos
{
    int    ID;
    char   Nombre[50];
    float  Costo;
    float  Valor;
    int    TemPrep;
    int    IDResto;
    int    comResto;
    int    IDCat;
    bool   Estado;
};
struct Fecha
{
    int Dia;
    int Mes;
    int Anio;
};

struct Clientes
{
    int ID,CP;
    char Apellidos[50],Nombres[50],Mail[50],Domicilio[100];
    struct Fecha Fechanac;
    bool Estado;
};

struct Pedidos
{

    int ID, IDCliente, IDPlato, Cantidad;
    float pUnitario,Valoracion;
    Fecha FechPed;
    int Estado;

};

//declaracion de dir
const char *Dir_Platos= "Platos.dat";
const char *Dir_Clientes= "Clientes.dat";
const char *Dir_Pedidos= "Pedidos.dat";
const char *Dir_Platos_bkp= "Platos.bkp";
const char *Dir_Clientes_bkp= "Clientes.bkp";
const char *Dir_Pedidos_bkp= "Pedidos.bkp";

//Declaraciones
//                      Platos
void Menu_Platos(Platos);
bool cargarPlatos(struct Platos);
int buscarID(int);
bool SavePlatos(struct Platos);
void ShowPlatos();
void Mostrar_Platos(Platos);
void listarxID();
int CantPlatos();
Platos leerID(int);
void Mod_Plato();
bool Mod_file_Platos(Platos, int);
void Supr_Plato();
Platos leerIDResto(int);
int buscarIDResto(int);
void Listar_Platos_Resto();

//                      Clientes
void Menu_clientes(Clientes);
bool Validar_Mail(char *mail);
void CargarCliente(struct Clientes);
bool Verf_Fecha(int, int, int);
bool SaveClientes(struct Clientes);
void ShowClientes();
int CantClientes();
Clientes leerID_Clientes(int);
void Mostrar_Clientes(Clientes);
void Mod_Cliente();
int buscarID_Cliente(int);
bool Mod_file_Clientes(Clientes, int);
void listarxID_Clientes();
void Supr_Cliente();

//                      Pedidos

void Menu_Pedidos(Pedidos);
void CargarPedidos(Pedidos);
void ShowPedidos();
int CantPedidos();
Pedidos leerID_Pedidos(int);
bool SavePedidos(Pedidos);
void Mostrar_Pedidos(Pedidos);
int buscarID_Pedido(int);
bool Mod_file_Pedidos(Pedidos, int);
void Mod_Pedido();
void ListarxID_Pedidos();

//                      Configuracion
void Menu_Configuraciones(Pedidos,Platos,Clientes);

void Realizar_bkp();
bool SaveClientes_bkp();
bool SavePlatos_bkp();
bool SavePedidos_bkp();

void Restarurar_bkp();
bool RecoverClientes_bkp();
bool RecoverPlatos_bkp();
bool RecoverPedidos_bkp();
int CantClientesBKP();
int CantPedidosBKP();
int CantPlatosBKP();




//FUNCIONES

void Mod_Plato()
{
    //MODIFICACION DE PLATO
    /*La opción Modificar Plato deberá solicitar el ID de un plato y
      permitir modificar el costo de venta y el tiempo de preparación.*/

    cls();
    int id, pos,opc;
    bool salir=true;
    cout << "ID a Modificar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0)
    {
        while (salir)
        {
            Platos vPlatos= leerID(pos);
            Mostrar_Platos(vPlatos);
            cout<<endl<<"-----------------------------";
            cout<<endl<<"DESEA MODIFICAR PLATO? ";
            cout<<endl<<"1 - SI";
            cout<<endl<<"0 - VOLVER AL MENU ANTERIOR";
            cout<<endl<<"-----------------------------"<<endl;
            cout<<endl<<"INGRESE OPCION: ";
            cin >> opc;
            switch(opc)
            {
            case 1:
                cout<<"COSTO DE PREPARACION: $"<<vPlatos.Costo;
                cout<<endl<<"Ingrese NUEVO costo de Venta (debe ser mayor a Valor de costo): $";
                cin>>vPlatos.Valor;
                cout<<endl<<"Ingrese NUEVO tiempo de elaboracino: " ;
                cin>>vPlatos.TemPrep;

                if((vPlatos.Valor>vPlatos.Costo)&&(vPlatos.TemPrep>0))
                {

                    if( Mod_file_Platos(vPlatos,pos))
                    {
                        cout<<endl<<"----------------------------------------";
                        cout<<endl<<"EXITO EN MODIFICAR EL ARCHIVO PLATOS.DAT";
                        cout<<endl<<"----------------------------------------";

                    }

                    else
                    {
                        cout<<endl<<"------------------------------------";
                        cout<<endl<<"NO SE MODIFICO EL ARCHIVO PLATOS.DAT";
                        cout<<endl<<"------------------------------------";
                    }

                }
                else
                {
                    cout<<endl<<"NO SE CARGO CORRECTAMENTE LA MODIFICACION DEL PLATO"<<endl;
                    getch();
                    cls();
                    salir=false;
                }
                break;

            case 0:
                cls();
                salir=false;
                break;

            default:
                cout<<"OPCION INCORRECTA"<<endl;
                getch();
                break;
            }
        }

    }
    else
    {
        cout << "ID INCORRECTO INGRESE NUEVAMENTE.";
        getch();
        cls();
    }


}

Platos leerID(int pos)
{

    Platos vPlatos;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        vPlatos.ID = -1;
        return vPlatos;
    }
    fseek(p, pos * sizeof(Platos),SEEK_SET);
    fread(&vPlatos, sizeof(Platos), 1, p);
    fclose(p);
    return vPlatos;
}

int buscarID(int ID)
{
    //BUSCA ID EN FILE PLATOS.DAT,COMPARA SI ESTA O NO Y
    //DEVUELVE POSICION DEL MISMO SI LO ENCUENTRA
    Platos vPlatos;
    int i=0;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        return -2;
    }
    while (fread(&vPlatos, sizeof(Platos), 1, p))
    {
        if (vPlatos.ID == ID)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

void listarxID()
{

//LISTAR POR ID LOS PLATOS
    cls();
    int id, pos;
    cout << "ID a buscar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0)
    {
        Platos vPlatos= leerID(pos);

        Mostrar_Platos(vPlatos);
    }
    else
    {
        cout << "No existe el id buscado.";
        getch();
        cls();
    }
}

void Listar_Platos_Resto()
{
// MUESTRA PLATOS POR RESTAURANT
    cls();
    int cant = CantPlatos(), i,IDresto;
    cout<<"ingrese ID del Restaurante: ";
    cin>>IDresto;

    if (cant == 0)
    {
        cout << "No hay Platos";
        return;
    }
    Platos *vPlatos;
    vPlatos = (Platos *) malloc(cant * sizeof(Platos));
    if (vPlatos == NULL)
    {
        cout << "No hay memoria para continuar...";
        return;
    }
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        free(vPlatos);
        cout << "No existe el archivo...";
        return;
    }
    fread(&vPlatos[0], sizeof(Platos), cant, p);
    fclose(p);

//  ordenar_productos(vPlatos, cant);

    for(i=0; i<cant; i++)
    {
        if(vPlatos[i].IDResto==IDresto && vPlatos[i].Estado==true)
        {

            Mostrar_Platos(vPlatos[i]);
            cout << endl;

            getch();
        }
    }

    free (vPlatos);
}

bool SavePlatos(Platos vPlatos)
{
// GUARDA LOS NUEVOS PLATOS EN  "PLATOS.DAT"
    bool b;
    FILE *p;
    p=fopen(Dir_Platos, "ab");

    b = fwrite(&vPlatos,sizeof(Platos),1,p);

    fclose(p);
    return b;

}

void ShowPlatos()
{
//BUSCA Y MUESTRA TODOS LOS PLATOS

    cls();
    Platos vPlatos;
    int cant = CantPlatos(), i;
    for(i=0; i<cant; i++)
    {
        vPlatos = leerID(i);
        Mostrar_Platos(vPlatos);

        cout << endl;
    }
    getch();
}

int CantPlatos()
{
//
    int bytes, regs;
    FILE *p;
    p = fopen(Dir_Platos, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Platos);
    fclose(p);
    return regs;
}

bool Mod_file_Platos(Platos vPlatos, int pos)
{
//ACTUALIZA EL ARCHIVO AL MODIFICARLO EN FUNCION MOD_PLATOS

    bool modifico;
    FILE *p;
    p = fopen(Dir_Platos, "rb+");
    if (p == NULL)
    {
        return false;
    }
    fseek(p, pos * sizeof(Platos), SEEK_SET);
    modifico = fwrite(&vPlatos, sizeof(Platos), 1, p);
    fclose(p);
    return modifico;

}

void Mostrar_Platos(Platos vPlatos)
{
//MUESTRA LOS PLATOS CON ESTADO TRUE

    if  (vPlatos.Estado==true)
    {
        cout<<"ID: "<<vPlatos.ID<<endl;
        cout<<"Nombre: "<<vPlatos.Nombre<<endl;
        cout<<"Costo Preparacion: "<<vPlatos.Costo<<endl;
        cout<<"Valor de venta: "<<vPlatos.Valor<<endl;
        cout<<"Tiempo de Elaboracion en Minutos: "<<vPlatos.TemPrep<<endl;
        cout<<"ID Restaurante: "<<vPlatos.IDResto<<endl;
        cout<<"Comision: "<<vPlatos.IDCat<<endl;
        //est=vPlatos.Estado;
        // cout<<"Estado: "<<est<<endl;
        cout<<"--------------------------------"<<endl;
    }
//    else{return false;}
    //  getch();
    //cls();
}

void Supr_Plato()
{

    int id, pos;

    cout << "Plato a eliminar: ";
    cin >> id;
    pos = buscarID(id);
    if (pos >= 0)
    {
        Platos vPlatos = leerID(pos);
        cout << endl;
        Mostrar_Platos(vPlatos);
        cout << endl << "INGRESE '0' SI ESTA SEGURO: ";
        cin >> vPlatos.Estado;
        if (Mod_file_Platos(vPlatos, pos))
        {
            cout << "PLATO ELIMINADO.";
        }
        else
        {
            cout << "NO SE ELIMINO EL PLATO.";
        }
    }
    else
    {
        cout << "EL ID DEL PLATO NO FUE ENCONTRADO.";
    }
}

bool cargarPlatos(Platos *vPlatos)
{
    //CARGA Y COMPROBACION DE PLATOS
    int id;
    cout<<"Cargar ID de Plato: ";
    cin>>vPlatos->ID;
    if(vPlatos->ID<0)
    {
        cout<<"ID incorrecto";
        getch();
        return false;
    }
    else
    {
        id=buscarID(vPlatos->ID);
        if(id>=0)
        {
            cls();
            cout<<"ID ya cargado"<<endl;
            getch();
            return false;
        }
    }

    cout<<"Cargar Nombre de Plato: ";
    cin.ignore();
    cin.getline(vPlatos->Nombre,50);
    if(strlen(vPlatos->Nombre)<=0)
    {
        cout<<"No se ingreso un nombre valido";
        return false;
    }

    cout<<"Cargar Costo de preparacion: ";
    cin>>vPlatos->Costo;
    if(vPlatos->Costo<=0)
    {
        cout<<"Valor de venta menor a valor de costo o igual a 0.";
        return false;
    }

    cout<<"Cargar Valor de venta: ";
    cin>>vPlatos->Valor;
    if((vPlatos->Valor<=0)||(vPlatos->Valor<vPlatos->Costo))
    {
        cout<<"Valor de venta menor a valor de costo o igual a 0.";
        return false;
    }

    cout<<"Cargar Tiempo de preparación: ";
    cin>>vPlatos->TemPrep;
    if(vPlatos->TemPrep<=0)
    {
        cout<<"Tiempo de Preparacion menor a 0.";
        return false;
    }

    cout<<"Cargar ID Restaurant del Plato: ";
    cin>>vPlatos->IDResto;
    if(vPlatos->IDResto<=0)
    {
        cout<<"ID Restaurante menor a 0.";
        return false;
    }
    cout<<"Cargar Comisión restaurante: ";
    cin>>vPlatos->comResto;
    if(vPlatos->comResto<=0||vPlatos->comResto>=100)
    {
        cout<<"Comision incorrecta";
        return false;
    }

    cout<<"Cargar ID Categoría de Plato: ";
    cin>>vPlatos->IDCat;
    if(vPlatos->IDCat<=0)
        return false;

    vPlatos->Estado=true;

    cout<<endl<<"--------------------------"<<endl;



    return true;
}




void Menu_Platos()
{
    setlocale(LC_ALL, "spanish");
    cls();
    int opc;
    struct Platos vPlatos;
    bool salir=true;


    while (salir)
    {
        cls();
        cout<< "----------MENU PLATOS----------"<<endl;
        cout<< "1 - NUEVO PLATO."<<endl;
        cout<< "2 - MODIFICAR PLATO."<<endl;
        cout<< "3 - LISTAR PLATO POR ID. "<<endl;
        cout<< "4 - PLATOS POR RESTAURANT."<<endl;
        cout<< "5 - LISTAR TODOS LOS PLATOS."<<endl;
        cout<< "6 - ELIMINAR PLATO."<<endl<<endl;
        cout<< "0 - SALIR"<<endl<<endl;
        cout<<"--------------------------------"<<endl;
        cout<< "INGRESE OPCION: ";
        cin>>opc;

        switch (opc)
        {
        case 1:
            cls();
            if(cargarPlatos(&vPlatos)) //carga de platos en vector PLatos (vPlatos) .
            {
                if(SavePlatos(vPlatos)) //graba en el archivo "Platos.dat" los registros generados en cargar
                {
                    cout<<"Carga de Plato, OK. "<<endl;
                    getch();
                    cls();
                }
                else
                {
                    cout << "No se pudo guardar el Plato en el archivo.";
                }
            }
            else
            {
                cls();
                cout << "No se cargo el Plato.";
                getch();
            }
            break;
        case 2:
            cls();
            Mod_Plato();//SE SUPONE QUE MODIFICA LOS PLATOS
            getch();
            break;
        case 3:
            cls();
            listarxID();
            getch();
            //busca por id de plato
            break;
        case 4:
            cls();
            Listar_Platos_Resto();
            break;
        case 5:
            cls();
            ShowPlatos(); //lista todos los platos juntos
            break;
        case 6:
            cls();
            Supr_Plato();
            break;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        case 0:
            salir=false;
            break;

        }
    }

};









//              Funciones Clientes

bool Validar_Mail(char *mail)
{
    //verifica el mail para que sea valido
    int i,cChars= strlen(mail),c=0;


    for(cChars = 0 ; ; cChars++)
    {
        if(mail[cChars] == '\0')
            break;
    }
    if((mail[0]!='@')&&(mail[0]!='.'))
    {
        for(i=0; i<cChars; i++)
        {


            if((mail[cChars-1]=='@')||(mail[cChars-1]=='.'))
            {
                cout<<"No puede terminar con '@' o '.' "<<endl;
                return false;
            }
            if((mail[i]=='.')&&(mail[i+1]=='.'))
            {
                cout<<"No se puede repetir el doble '..'"<<endl;
                return false;
            }

            if((mail[i+1]=='@')&&(mail[i]=='@'))
            {

                cout<<"No se puede repetir el doble '@'"<<endl;
                return false;

            }

            if (mail[i]=='@')
            {
                c++;
            }


        }

        if(c>1)
        {
            cout<<"No puede haber mas de 2 '@'"<<endl;
            return false;

        }
        return true;


    }
    else
    {
        cout<<"Mail invalido no puede iniciar con '@' o '.' "<<endl;
        getch();
        return 0;
    }

}



bool Verf_Fecha(int Dia,int Mes,int Anio)
{

    time_t t;
    t=time(NULL);
    struct tm*f;
    f=localtime(&t);

    /* if (((f->tm_year+1900) <= Anio)&&((f->tm_mon + 1) <= Mes)&&(f->tm_mday <= Dia))

         return 1;
     else
         return 0;*/
    if((f->tm_year+1900)>Anio)
    {
        return true;
    }
    else if((f->tm_year+1900)==Anio)
    {
        if((f->tm_mon + 1)>Mes)
        {
            return true;
        }
        else if((f->tm_mon + 1)==Mes)
        {
            if(f->tm_mday>=Dia)
            {
                return true;
            }
        }
    }
    return false;

}

void Mostrar_Clientes(Clientes vClientes)
{
//MUESTRA LOS CLIENTES CON ESTADO TRUE
    if  (vClientes.Estado==true)
    {
        cout<< endl <<"CLIENTE: "<<endl<<endl;
        cout<<"ID: "              <<vClientes.ID<<endl;
        cout<<"Apellido: "        <<vClientes.Apellidos<<endl;
        cout<<"Nombre: "          <<vClientes.Nombres<<endl;
        cout<<"Mail: "            <<vClientes.Mail<<endl;
        cout<<"Domicilio: "       <<vClientes.Domicilio<<endl;
        cout<<"Codigo Postal: "   <<vClientes.CP<<endl;
        cout<<"Fecha Nacimiento: "<<vClientes.Fechanac.Dia<<"/"<<vClientes.Fechanac.Mes<<"/"<<vClientes.Fechanac.Anio<<endl;
        getch();
        //est=vClientes.Estado;
        //cout<<"Estado: "<<est<<endl;
        cout<<"--------------------------------"<<endl<<endl;
    }
    //else{return false;}

    //cls();
}

int CantClientes()
{
//
    int bytes, regs;
    FILE *p;
    p = fopen(Dir_Clientes, "rb");
    if (p == NULL)
    {

        return 0;
    }

    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Clientes);
    fclose(p);
    return regs;
}

Clientes leerID_Clientes(int pos)
{

    Clientes vClientes;
    FILE *p;
    p = fopen(Dir_Clientes, "rb");
    if (p == NULL)
    {
        vClientes.ID = -1;
        return vClientes;
    }
    fseek(p, pos * sizeof(Clientes),SEEK_SET);
    fread(&vClientes, sizeof(Clientes), 1, p);
    fclose(p);
    return vClientes;
}


void ShowClientes()
{

//BUSCA Y MUESTRA TODOS LOS CLIENTES
    cls();

    //  Clientes vClientes;

    int i,cant = CantClientes();
    Clientes *vClientes;
    Clientes temp;
    cout<<"LISTAR TODOS LOS CLIENTES"<<endl;

    vClientes = (Clientes *) malloc(cant * sizeof(Clientes));
    if (vClientes == NULL)
    {
        cout << "No hay memoria para continuar...";
        return;
    }
    FILE *p;
    p = fopen(Dir_Clientes, "rb");
    if (p == NULL)
    {
        free(vClientes);
        cout << "No existe el archivo...";
        return;
    }
    fread(vClientes, sizeof(Clientes), cant, p);
    fclose(p);


    for( i=0; i<cant; i++)
    {
        for (int j=i+1; j<cant; j++)
        {
            if ((strcoll(vClientes[i].Apellidos,vClientes[j].Apellidos))>0)
            {
                strcpy ( temp.Apellidos, vClientes[i].Apellidos );
                strcpy ( vClientes[i].Apellidos, vClientes[j].Apellidos );
                strcpy ( vClientes[j].Apellidos, temp.Apellidos );

                strcpy ( temp.Nombres, vClientes[i].Nombres );
                strcpy ( vClientes[i].Nombres, vClientes[j].Nombres );
                strcpy ( vClientes[j].Nombres, temp.Nombres );

                strcpy ( temp.Mail, vClientes[i].Mail );
                strcpy ( vClientes[i].Mail, vClientes[j].Mail );
                strcpy ( vClientes[j].Mail, temp.Mail );

                strcpy ( temp.Domicilio, vClientes[i].Domicilio );
                strcpy ( vClientes[i].Domicilio, vClientes[j].Domicilio );
                strcpy ( vClientes[j].Domicilio, temp.Domicilio );


                temp.CP=vClientes[i].CP;
                vClientes[i].CP=vClientes[j].CP;
                vClientes[j].CP = temp.CP;

                temp.ID=vClientes[i].ID;
                vClientes[i].ID=vClientes[j].ID;
                vClientes[j].ID=temp.ID;

                temp.Fechanac.Dia=vClientes[i].Fechanac.Dia;
                vClientes[i].Fechanac.Dia =vClientes[j].Fechanac.Dia;
                vClientes[j].Fechanac.Dia= temp.Fechanac.Dia;

                temp.Fechanac.Mes=vClientes[i].Fechanac.Mes;
                vClientes[i].Fechanac.Mes =vClientes[j].Fechanac.Mes;
                vClientes[j].Fechanac.Mes=temp.Fechanac.Mes;

                temp.Fechanac.Anio=vClientes[i].Fechanac.Anio;
                vClientes[i].Fechanac.Anio =vClientes[j].Fechanac.Anio;
                vClientes[j].Fechanac.Anio=temp.Fechanac.Anio;


            }
        }
    }

    for (int x=0; x<cant; x++)
    {
        Mostrar_Clientes(vClientes[x]);
        cout << endl;
    }

    free (vClientes);

    getch();
    /*for(i=0; i<cant; i++)
     {
         //vClientes = leerID_Clientes(i);
         Mostrar_Clientes(vClientes[i]);

         cout << endl;
     }*/

}


bool SaveClientes(Clientes vClientes)
{
// GUARDA LOS NUEVOS CLIENTES EN  "CLIENTES.DAT"
    bool b;
    FILE *p;
    p=fopen(Dir_Clientes, "ab");
    if(p==NULL)
    {
        return false;

    }
    b = fwrite(&vClientes,sizeof(Clientes),1,p);

    fclose(p);
    return b;

}

void CargarCliente()
{
    //CARGA Y COMPROBACION DE DATOS DE CLIENTES
    int CP,ID;
    int Dia=0,Mes=0,Anio=0;
    char nombre[50],apellido[50], domicilio[100];
    Clientes vClientes;
    cout<<"CARGA DE CLIENTE: "<<endl;
    cout<<"COMPLETAR LOS CAMPOS PARA LA CARGA:"<<endl<<endl;
    cout<<"APELLIDO: ";
    cin.ignore();
    cin.getline(apellido,50);
    if(strlen(apellido)== 0)
    {
        cout<<"Campo Apellido Vacio";
        return ;
    }
    else
    {
        strcpy(vClientes.Apellidos,apellido);
    }
    cout<<"NOMBRE: ";
    cin.getline(nombre,50);
    if(strlen(nombre)== 0)
    {
        cout<<"Campo Nombre Vacio";
        return ;
    }
    else
    {
        strcpy(vClientes.Nombres,nombre);
    }
    cout<<"MAIL: "; //FALTA VERIFICAR MAIL QUE NO ANDA
    cin>>vClientes.Mail;

    if(!Validar_Mail(vClientes.Mail))
        cout<<endl<<"MAIL INVALIDO";

    cout<<"DOMICILIO: ";
    cin.getline(domicilio,100);

    if(strlen(domicilio)== 0)
    {
        cout<<"Campo Domicilio Vacio";
        return ;
    }
    else
    {
        strcpy(vClientes.Domicilio,domicilio);
    }

    cout<<"CODIGO POSTAL: ";
    cin>>CP;
    if(CP>=1000&&CP<=9999)
    {
        vClientes.CP=CP;
    }
    else
    {
        cout<<"Codigo Postal Invalido debe ser un numero entre 1000 y 9999";
        getch();
        return ;
    }
    cout<<"FECHA DE NACIMIENTO: "<<endl;
    cout<<"DIA: ";
    cin>>Dia;
    cout<<"MES: ";
    cin>>Mes;
    cout<<"AÑO: ";
    cin>>Anio;


    if(Verf_Fecha(Dia,Mes,Anio)==0)
    {

        cout<< "Fecha invalida";
        getch();
        return ;
    }

    vClientes.Fechanac.Dia=Dia;
    vClientes.Fechanac.Mes=Mes;
    vClientes.Fechanac.Anio=Anio;


    ID=CantClientes();
    vClientes.ID=ID+1;

    vClientes.Estado=true;

    if(SaveClientes(vClientes))
    {
        cout<<"SE REALIZO CARGA CORRECTA EN FILE 'Clientes.dat'";
        getch();
    }
    else
    {
        cout<<"HUBO UN ERROR EN LA FUNCION 'SAVECLIENTES'";
        getch();
        return ;
    }
}

void Mod_Cliente()
{
    //MODIFICACION DE CLIENTE
    /*La opción Modificar Pedido deberá solicitar el ID de un pedido
    y permitir modificar el Estado del mismo.*/

    cls();
    int id, pos,opc;
    char dom[100];
    bool salir=true;
    cout << "ID DE PEDIDO A MODIFICAR: ";
    cin >> id;
    pos = buscarID_Pedido(id);
    if (pos >= 0)
    {
        while (salir)
        {
            Clientes vClientes= leerID_Clientes(pos);
            Mostrar_Clientes(vClientes);
            cout<<endl<<"-----------------------------";
            cout<<endl<<"DESEA MODIFICAR PEDIDO? ";
            cout<<endl<<"1 - SI";
            cout<<endl<<"0 - VOLVER AL MENU ANTERIOR";
            cout<<endl<<"-----------------------------"<<endl;
            cout<<endl<<"INGRESE OPCION: ";
            cin >> opc;
            switch(opc)
            {
            case 1:
                cout<<"DOMICILIO ACTUAL: "<<vClientes.Domicilio;
                cout<<endl<<"INGRESE NUEVO DOMICILIO: ";
                cin.ignore();
                cin.getline(dom,100);
                strcpy(vClientes.Domicilio,dom);

                if( Mod_file_Clientes(vClientes,pos)==1)
                {
                    cout<<endl<<"----------------------------------------";
                    cout<<endl<<"EXITO EN MODIFICAR EL ARCHIVO CLIENTES.DAT";
                    cout<<endl<<"----------------------------------------";
                }

                else
                {
                    cout<<endl<<"------------------------------------";
                    cout<<endl<<"NO SE MODIFICO EL ARCHIVO CLIENTES.DAT";
                    cout<<endl<<"------------------------------------";
                }


                break;


            case 0:
                return;
                break;

            default:
                cout<<"OPCION INCORRECTA"<<endl;
                getch();
                break;
            }
        }

    }
    else
    {
        cout << "ID INCORRECTO INGRESE NUEVAMENTE."<< endl << endl;
        getch();
        cls();
    }


}


int buscarID_Cliente(int ID)
{
    //BUSCA ID EN FILE CLIENTES.DAT Y COMPARA SI ESTA O NO
    Clientes vClientes;
    int i=0;
    FILE *p;
    p = fopen(Dir_Clientes, "rb");
    if (p == NULL)
    {
        return -2;
    }
    while (fread(&vClientes, sizeof(Clientes), 1, p))
    {
        if (vClientes.ID == ID)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

bool Mod_file_Clientes(Clientes vClientes, int pos)
{
//ACTUALIZA EL ARCHIVO AL MODIFICARLO EN FUNCION Mod_Cliente

    bool modifico;
    FILE *p;
    p = fopen(Dir_Clientes, "rb+");
    if (p == NULL)
    {
        return false;
    }
    fseek(p, pos * sizeof(Clientes), SEEK_SET);
    modifico = fwrite(&vClientes, sizeof(Clientes), 1, p);
    fclose(p);
    return modifico;

}


void listarxID_Clientes()
{

//LISTAR POR ID LOS CLIENTES
    cls();
    int id, pos;
    cout << endl << "ID a buscar: ";
    cin >> id;
    pos = buscarID_Cliente(id);
    if (pos >= 0)
    {
        Clientes vClientes= leerID_Clientes(pos);
        Mostrar_Clientes(vClientes);
    }
    else
    {
        cout << endl << "No existe el id buscado.";
        getch();
        cls();
    }
}

void Supr_Cliente()
{

    int id, pos;

    cout << "CLIENTE A ELIMINAR: ";
    cin >> id;
    pos = buscarID_Cliente(id);
    if (pos >= 0)
    {
        Clientes vClientes = leerID_Clientes(pos);
        cout << endl;
        Mostrar_Clientes(vClientes);
        cout << endl << "INGRESE '0' SI ESTA SEGURO: ";
        cin >> vClientes.Estado;
        if (Mod_file_Clientes(vClientes, pos))
        {
            cout << "CLIENTE ELIMINADO.";
        }
        else
        {
            cout << "NO SE ELIMINO EL CLIENTE.";
        }
    }
    else
    {
        cout << "EL ID DEL CLIENTE NO FUE ENCONTRADO.";
    }




}


void Menu_clientes()
{
    setlocale(LC_ALL, "spanish");
    cls();
    int opc;
    bool salir=true;
    while (salir)
    {
        cls();
        cout<< "----------MENU CLIENTES----------"<<endl;
        cout<< "1 - NUEVO CLIENTE."<<endl;
        cout<< "2 - MODIFICAR CLIENTE."<<endl;
        cout<< "3 - LISTAR CLIENTE POR ID. "<<endl;
        cout<< "4 - LISTAR TODOS LOS CLIENTES."<<endl;
        cout<< "5 - ELIMINAR CLIENTE."<<endl<<endl;
        cout<< "0 - SALIR"<<endl<<endl;
        cout<<"----------------------------------"<<endl;
        cout<< "INGRESE OPCION: ";
        cin >>opc;

        switch (opc)
        {
        case 1:
            cls();
            CargarCliente(); //Carga de Cliente .
            break;
        case 2:
            Mod_Cliente(); //MODIFICA CLIENTE
            break;
        case 3:
            listarxID_Clientes();
            break;
        case 4:
            cls();
            ShowClientes();// MUESTRA TODOS LOS CLIENTES
            break;
        case 5:
            Supr_Cliente(); //modifica el estado de los clientes a 0 para realizar la baja
            break;


        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        case 0:
            salir=false;
            break;

        }
    }

};





//          Funciones Pedidos
void CargarPedidos()
{
    int IDclientes,IDPlatos,cantidad;
    int Dia,Mes, Anio,id;
    float valoracion;
    Pedidos vPedidos;
    Clientes vCliente;
    Platos vPlatos;
    cls();
    cout<<endl<<"CARGAR PEDIDO"<<endl<<endl;

    cout<<endl<<"ID CLIENTE: ";
    cin>>id;

    IDclientes= buscarID_Cliente(id);
    vCliente= leerID_Clientes(IDclientes);


    if(IDclientes<0||vCliente.Estado==false)
    {
        cout<<"ID de cliente no existente.";
        getch();
        return;
    }
    vPedidos.IDCliente=id;

    cout<<endl<<"ID PLATOS: ";
    cin>>id;
    IDPlatos= buscarID(id);
    vPlatos= leerID(IDPlatos);

    if(IDPlatos<0||vPlatos.Estado==0)
    {
        cout<<"ID de plato no existente.";
        getch();
        return;
    }
    vPedidos.IDPlato=id;

    cout<<endl<<"CANTIDAD: ";
    cin>>cantidad;
    if(cantidad<=0)
    {
        cout<<endl<<"Cantidad incorrecta, ingrese un valor mayor a 0";
        getch();
        return;
    }
    vPedidos.Cantidad=cantidad;
    cout<<endl<<"PRECIO UNITARIO: ";
    vPedidos.pUnitario=vPlatos.Valor;
    cout<<vPedidos.pUnitario;

    cout<<endl<<"FECHA DEL PEDIDO: ";
    cout<<"DIA: ";
    cin>>Dia;
    cout<<"MES: ";
    cin>>Mes;
    cout<<"AÑO: ";
    cin>>Anio;

    if(Verf_Fecha(Dia,Mes,Anio)==0)
    {
        cout<<endl<<"Fecha Invalida.";
        getch();
        return;

    }
    vPedidos.FechPed.Dia=Dia;
    vPedidos.FechPed.Mes=Mes;
    vPedidos.FechPed.Anio=Anio;


    cout<<endl<<"VALORACION: ";
    cin>>valoracion;
    if(valoracion<0&&valoracion>10)
    {
        cout<<endl<<"Valoracion Incorrecta. Debe ser un numero entre 0 y 10";
        getch();
        return;
    }
    vPedidos.Valoracion=valoracion;
    cout<<endl<<"ESTADO: "<<"Pedido en curso";;
    cout<<endl<<endl;

    vPedidos.Estado=1;
    id=CantPedidos();
    vPedidos.ID=id+1;

    if(SavePedidos(vPedidos))
    {
        cout<<"SE REALIZO CARGA CORRECTA EN FILE 'Pedidos.dat'";
        getch();
    }
    else
    {
        cout<<"HUBO UN ERROR EN LA FUNCION 'SavePedidos'";
        getch();
        return ;
    }

}
int CantPedidos()
{
//
    int bytes, regs;
    FILE *p;
    p = fopen(Dir_Pedidos, "rb");
    if (p == NULL)
    {

        return 0;
    }

    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Pedidos);
    fclose(p);
    return regs;
}

bool SavePedidos(Pedidos vPedidos)
{
// GUARDA LOS NUEVOS Pedidos EN  "Pedidos.DAT"
    bool b;
    FILE *p;
    p=fopen(Dir_Pedidos, "ab");
    if(p==NULL)
    {
        return false;

    }
    b = fwrite(&vPedidos,sizeof(Pedidos),1,p);

    fclose(p);
    return b;

}

void ShowPedidos()
{
//BUSCA Y MUESTRA TODOS LOS Pedidos

    cls();
    Pedidos vPedidos;
    int cant = CantPedidos(), i;
    for(i=0; i<cant; i++)
    {
        cout << endl;
        vPedidos = leerID_Pedidos(i);
        Mostrar_Pedidos(vPedidos);
        cout << endl;
    }
    getch();
}

Pedidos leerID_Pedidos(int pos)
{

    Pedidos vPedidos;
    FILE *p;
    p = fopen(Dir_Pedidos, "rb");
    if (p == NULL)
    {
        vPedidos.ID = -1;
        return vPedidos;
    }
    fseek(p, pos * sizeof(Pedidos),SEEK_SET);
    fread(&vPedidos, sizeof(Pedidos), 1, p);
    fclose(p);
    return vPedidos;
}

void Mostrar_Pedidos(Pedidos vPedidos)
{
//Muestra todos los campos de los Pedidos.


    cout<<"PEDIDO: "<<endl<<endl;
    cout<<"ID: "<<vPedidos.ID<<endl;
    cout<<"IDCliente: "<<vPedidos.IDCliente<<endl;
    cout<<"IDPlato: "<<vPedidos.IDPlato<<endl;
    cout<<"Cantidad: "<<vPedidos.Cantidad<<endl;
    cout<<"Precio unitario: "<<vPedidos.pUnitario<<endl;
    cout<<"Fecha Nacimiento: "<<vPedidos.FechPed.Dia<<"/"<<vPedidos.FechPed.Mes<<"/"<<vPedidos.FechPed.Anio<<endl;
    cout<<"Valoración: "<<vPedidos.Valoracion<<endl;
    cout<<"Estado: ";
    switch(vPedidos.Estado)
    {
    case 1:
        cout<<"Pedido en Curso";
        break;
    case 2:
        cout<<"Pedido completado";
        break;
    case 3:
        cout<<"Pedido cancelado";
        break;
    }
    cout<<endl<<"--------------------------------"<<endl;

}

void Mod_Pedido()
{
    //MODIFICACION DE PEDIDO
    /*La opción Modificar Cliente deberá solicitar el ID de un cliente y
    permitir modificar el domicilio del mismo.*/

    cls();
    int id, pos,opc;
    cout << "ID a Modificar: ";
    cin >> id;
    pos = buscarID_Pedido(id);
    if (pos >= 0)
    {

        Pedidos vPedidos= leerID_Pedidos(pos);
        Mostrar_Pedidos(vPedidos);
        cout<<endl<<"-----------------------------";
        cout<<endl<<"DESEA MODIFICAR EL ESTADO DEL PEDIDO? ";
        cout<<endl<<"1 - SI";
        cout<<endl<<"0 - VOLVER AL MENU ANTERIOR";
        cout<<endl<<"-----------------------------"<<endl;
        cout<<endl<<"INGRESE OPCION: ";
        cin >> opc;
        switch(opc)
        {
        case 1:
            cout<<endl<< "INGRESE NUEVO ESTADO DEL PEDIDO";
            cout<<endl<<"1 - Pedido en Curso";
            cout<<endl<<"2 - Pedido completado";
            cout<<endl<<"3 - Pedido cancelado";
            cout<<endl<<"INGRESE OPCION: ";
            cin>>vPedidos.Estado;
            if( Mod_file_Pedidos(vPedidos,pos)==1)
            {
                cout<<endl<<"----------------------------------------";
                cout<<endl<<"EXITO EN MODIFICAR EL ARCHIVO PEDIDOS.DAT";
                cout<<endl<<"----------------------------------------";
            }

            else
            {
                cout<<endl<<"------------------------------------";
                cout<<endl<<"NO SE MODIFICO EL ARCHIVO PEDIDOS.DAT";
                cout<<endl<<"------------------------------------";
            }

            break;
        case 0:
            return;
            break;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
            getch();
            break;
        }


    }
    else
    {
        cout << "ID INCORRECTO INGRESE NUEVAMENTE."<< endl << endl;
        getch();
    }



}

int buscarID_Pedido(int ID)
{
    //BUSCA ID EN FILE PEDIDOS.DAT Y COMPARA SI ESTA O NO
    Pedidos vPedidos;
    int i=0;
    FILE *p;
    p = fopen(Dir_Pedidos, "rb");
    if (p == NULL)
    {
        return -2;
    }
    while (fread(&vPedidos, sizeof(Pedidos), 1, p))
    {
        if (vPedidos.ID == ID)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

bool Mod_file_Pedidos(Pedidos vPedidos, int pos)
{
//ACTUALIZA EL ARCHIVO EN FUNCION Mod_Pedidos

    bool modifico;
    FILE *p;
    p = fopen(Dir_Pedidos, "rb+");
    if (p == NULL)
    {
        return false;
    }
    fseek(p, pos * sizeof(Pedidos), SEEK_SET);
    modifico = fwrite(&vPedidos, sizeof(Pedidos), 1, p);
    fclose(p);
    return modifico;

}


void ListarxID_Pedidos()
{

//LISTAR POR ID LOS PEDIDOS
    cls();
    int id, pos;
    cout << "ID a buscar: ";
    cin >> id;
    pos = buscarID_Pedido(id);
    if (pos >= 0)
    {
        Pedidos vPedidos = leerID_Pedidos(pos);
        Mostrar_Pedidos(vPedidos);
        getch();
    }
    else
    {
        cout << "No existe el id buscado.";
        getch();
        return;
    }
}


void Menu_Pedidos()
{
    setlocale(LC_ALL, "spanish");
    cls();
    int opc;
    bool salir=true;
    while (salir)
    {
        cls();
        cout<< "----------MENU CLIENTES----------"<<endl;
        cout<< "1 - NUEVO PEDIDO."<<endl;
        cout<< "2 - MODIFICAR PEDIDO."<<endl;
        cout<< "3 - LISTAR PEDIDO POR ID. "<<endl;
        cout<< "4 - LISTAR TODOS LOS PEDIDOS."<<endl;
        cout<< "0 - SALIR"<<endl<<endl;
        cout<<"----------------------------------"<<endl;
        cout<< "INGRESE OPCION: ";
        cin >>opc;
        cls();
        switch (opc)
        {
        case 1:
            CargarPedidos();
            break;
        case 2:
            Mod_Pedido();
            break;
        case 3:
            ListarxID_Pedidos();
            break;

        case 4:
            ShowPedidos();
            break;



        default:
            cout<<"OPCION INCORRECTA"<<endl;
            break;
        case 0:
            salir=false;
            break;

        }
    }

};



//  Funciones Configuracion

void Realizar_bkp()
{
//  leer y guardar
    int opc;
    cout<<endl<<"DESEA REALIZAR BACK UP?";
    cout<<endl<<"1) SI";
    cout<<endl<<"0) SALIR";
    cout<<endl<<"INGRESE UNA OPCION PARA CONTINUAR: ";
    cin>>opc;
    switch (opc)
    {
    case 1:
        cout<<endl<<"REALIZANDO BACK UP...";

        if(SavePlatos_bkp())
        {
            cout<<endl<<"BACK UP DE PLATOS REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }

        if(SaveClientes_bkp())
        {
            cout<<endl<<"BACK UP DE CLIENTES REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }

        if(SavePedidos_bkp())
        {
            cout<<endl<<"BACK UP DE PEDIDOS REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }


        break;
    default:
        cout<<endl<<"OPCION INCORRECTA"<<endl;
        break;
    case 0:
        return;
        break;
    }
    getch();
    return;
}

bool SaveClientes_bkp()
{
// GUARDA LOS NUEVOS CLIENTES EN  "Clientes.bkp"

    Clientes vClientes;
    int y, cant = CantClientes();
    FILE *w, *r;
    w = fopen(Dir_Clientes,"rb");
    if(w == NULL)
        return false;
    r = fopen(Dir_Clientes_bkp,"wb");
    if(r == NULL)
        return false;

    for(y=0; y<cant; y++)
    {
        fread(&vClientes,sizeof (Clientes),1,w);
        fwrite(&vClientes,sizeof (Clientes),1,r);
    }
    fclose(w);
    fclose(r);
    return true;
}

bool SavePlatos_bkp()
{
// GUARDA LOS NUEVOS CLIENTES EN  "Platos.bkp"
    Platos vPlatos;
    int y, cant = CantPlatos();
    FILE *w, *r;
    w = fopen(Dir_Platos,"rb");
    if(w == NULL)
        return false;
    r = fopen(Dir_Platos_bkp,"wb");
    if(r == NULL)
        return false;

    for(y=0; y<cant; y++)
    {
        fread(&vPlatos,sizeof (Platos),1,w);
        fwrite(&vPlatos,sizeof (Platos),1,r);
    }
    fclose(w);
    fclose(r);
    return true;
}

bool SavePedidos_bkp()
{
// GUARDA LOS NUEVOS CLIENTES EN  "Pedidos.bkp"
    Pedidos vPedidos;
    int y, cant = CantPedidos();
    FILE *w, *r;
    w = fopen(Dir_Pedidos,"rb");
    if(w == NULL)
        return false;
    r = fopen(Dir_Pedidos_bkp,"wb");
    if(r == NULL)
        return false;

    for(y=0; y<cant; y++)
    {
        fread(&vPedidos,sizeof (Pedidos),1,w);
        fwrite(&vPedidos,sizeof (Pedidos),1,r);
    }
    fclose(w);
    fclose(r);
    return true;

}






void Restarurar_bkp()
{
    int opc;
    cout<<endl<<"DESEA RESTAURAR DESDE UN BACK UP?";
    cout<<endl<<"1) SI";
    cout<<endl<<"0) SALIR";
    cout<<endl<<"INGRESE UNA OPCION PARA CONTINUAR: ";
    cin>>opc;
    switch (opc)
    {
    case 1:
        cout<<endl<<"RESTAURANDO BASE DE DATOS...";

            if(RecoverPlatos_bkp())
        {
            cout<<endl<<"RESTAURACION DE PLATOS REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }

        if(RecoverClientes_bkp())
        {
            cout<<endl<<"RESTAURACION DE CLIENTES REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }

        if(RecoverPedidos_bkp())
        {
            cout<<endl<<"RESTAURACION DE PEDIDOS REALIZADO CON EXITO";
        }
        else
        {
            cout<<endl<<"NO SE REALIZO EL BACK UP";
            return;
        }


        break;
    default:
        cout<<endl<<"OPCION INCORRECTA"<<endl;
        break;
    case 0:
        return;
        break;
    }

    getch();
    return;
}




bool RecoverPedidos_bkp()
{

    //Restaurar Pedidos
    Pedidos vPedidos;
    int x, cant = CantPedidosBKP();
    FILE *p, *q;
    p = fopen(Dir_Pedidos,"wb");
    if(p == NULL)
        return false;
    q = fopen(Dir_Pedidos_bkp,"rb");
    if(q == NULL)
        return false;

    for(x=0; x<cant; x++)
    {
        fread(&vPedidos,sizeof (Pedidos),1,q);
        fwrite(&vPedidos,sizeof (Pedidos),1,p);
    }
    fclose(p);
    fclose(q);
    return true;
}


bool RecoverPlatos_bkp()
{
    //Restauracion Platos
    Platos vPlatos;
    int x, cant = CantPlatosBKP();
    FILE *p, *q;
    p = fopen(Dir_Platos,"wb");
    if(p == NULL)
        return false;
    q = fopen(Dir_Platos_bkp,"rb");
    if(q == NULL)
        return false;

    for(x=0; x<cant; x++)
    {
        fread(&vPlatos,sizeof (Platos),1,q);
        fwrite(&vPlatos,sizeof (Platos),1,p);
    }
    fclose(p);
    fclose(q);
    return true;
}


bool RecoverClientes_bkp()
{
    //Restaurar Clientes
    Clientes vClientes;
    int y, cant = CantClientesBKP();
    FILE *w, *r;
    w = fopen(Dir_Clientes,"wb");
    if(w == NULL)
        return false;
    r = fopen(Dir_Clientes_bkp,"rb");
    if(r == NULL)
        return false;

    for(y=0; y<cant; y++)
    {
        fread(&vClientes,sizeof (Clientes),1,r);
        fwrite(&vClientes,sizeof (Clientes),1,w);
    }
    fclose(w);
    fclose(r);
    return true;
}

int CantClientesBKP()
{
    int bytes,regs;
    FILE *p;
    p = fopen(Dir_Clientes_bkp, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Clientes);
    fclose(p);
    return regs;
}

int CantPedidosBKP()
{
    int bytes,regs;
    FILE *p;
    p = fopen(Dir_Pedidos_bkp, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Pedidos);
    fclose(p);
    return regs;
}

int CantPlatosBKP()
{
    int bytes,regs;
    FILE *p;
    p = fopen(Dir_Platos_bkp, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    regs = bytes / sizeof(Platos);
    fclose(p);
    return regs;
}





void Menu_Configuraciones()
{
    setlocale(LC_ALL, "spanish");
    cls();
    int opc;

    cout<<endl<<"MENÚ CONFIGURACIÓN";
    cout<<endl<<"------------------";
    cout<<endl<<"1) REALIZAR COPIA DE SEGURIDAD";
    cout<<endl<<"2) RESTAURAR COPIA DE SEGURIDAD";
    cout<<endl<<"--------------------------------";
    cout<<endl<<"0) VOLVER AL MENÚ PRINCIPAL";
    cout<<endl<<"INGRESE UNA OPCION PARA CONTINUAR: ";

    cin>>opc;
    switch(opc)
    {

    case 1:
        Realizar_bkp();
        break;
    case 2:
        Restarurar_bkp();

        break;
    default:
        cout<<"OPCION INCORRECTA"<<endl;
        break;
    case 0:
        return;
        break;
    }


}

#endif // PLATOS_H_INCLUDED
