#include <clocale>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <ctime>
#include "rlutil.h"

using namespace rlutil;

using namespace std;
#include "Platos.h"







int main()
{
    setlocale(LC_ALL, "spanish");
    int opc;
    while (true)
    {

        cout<<"MENU PRINCIPAL"<<endl<<endl<<"------------------------------"<<endl<<endl;
        cout<< "1 - Platos"<<endl;
        cout<< "2 - Clientes"<<endl;
        cout<< "3 - Pedidos"<<endl;
        cout<< "4 - Reportes"<<endl;
        cout<< "5 - Configuracion"<<endl;
        cout<< "0 - Salir"<<endl<<endl;
        cout<<endl<<"------------------------------"<<endl<<endl;
        cout<< "INGRESE OPCION: "<<endl;
        cin>>opc;
        cls();

        switch (opc)
        {
        case 1:
            Menu_Platos();
            break;
        case 2:
            Menu_clientes();
        break;
        case 3:
            Menu_Pedidos();
        break;

        case 5:
            Menu_Configuraciones();
        break;





        default:
            cout<<"OPCION INCORRECTA"<<endl;;
            break;
        case 0:
            return 0;
            break;


        }
        cls();
    }
    return 0;
}
