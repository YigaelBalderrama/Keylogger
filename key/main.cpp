#include <windows.h>
#include <iostream>
#include <conio.h>
//#include <vector>
#include <fstream>
#include <string>
//#include <mysql.h>
using namespace std;
string ubi="D:\\barcode.csv";
//vector < string > codigos;
void EscribirArchivo(string texto)
{
    ofstream archivo;
    archivo.open(ubi.c_str(), fstream::app);
    archivo << texto;
    archivo.close();
}
/*void llenarcsvBD()
{
    string aux;
    ofstream archivo;
    archivo.open(ubi.c_str(), fstream::app);
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost","root","","curtiembre", 0, NULL, 0);
    int qstate;
    for(unsigned int i=0;i<codigos.size();i++)
    {
        aux="SELECT * FROM Cuero where codigo="+codigos[i];
        if(conn)
        {
            qstate = mysql_query(conn,aux.c_str());

            if(!qstate)
            {
                res = mysql_store_result(conn);

                while(row = mysql_fetch_row(res))
                {
                    archivo << row[0] <<";" << row[1] <<";" << row[2] <<";\n";
                }
            }
        }
        else
        {
            Beep(523,500);
            Beep(523,500);
            Beep(523,500);
            break;
        }

    }
    archivo.close();
    codigos.clear();

}*/
void Empezando(bool &salir)
{
    while (salir)
    {
        for (unsigned int key = 8; key <= 255; key++)
        {
            if (GetAsyncKeyState(key) == -32767)
            {
                if(key==VK_F3)
                {
                   Beep(523,500);
                   salir=false;
                   EscribirArchivo("");
                   system("del \f D:\\barcode.csv");
                   break;
                }
            }
        }
    }
}
void Escuchando(bool &salir)
{
    bool active=false;
    string texto="";
    unsigned short int aux=0;
    while (!salir)
    {
        for (unsigned int key = 8; key <= 255; key++)
        {
            if (GetAsyncKeyState(key) == -32767)
            {
                if(key==VK_F4)
                {
                   Beep(523,500);
                   Beep(523,500);
                   salir=true;
                   break;

                }
                if(key==VK_RETURN && aux>=3)
                {
                   texto+=";\n";
                   EscribirArchivo(texto);
                   texto="";
                   aux=0;

                }
                //48 a 57 nros
                if(key>=48 && key<=57)
                {
                    aux++;
                    texto+=key;

                }
                else
                {
                    aux=0;
                    texto="";
                }
            }
        }
    }
    //cout<<texto<<endl;
}
int main()
{
    bool salir=true;
    FreeConsole();
    EscribirArchivo("");
    ///EscribirArchivo("ID;Codigo;Concepto;\n");
    Empezando(salir);
    Escuchando(salir);
    string aux="start "+ubi;
    system(aux.c_str());
    return 0;
}
