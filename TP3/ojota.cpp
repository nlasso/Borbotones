#include <iostream>
#include <fstream>
#include "interfaz.h"


using namespace std;


Atleta atletaProdigio(const JJOO & j)
{

    int i = 0;
    Atleta a;
    if(j.competenciasFinalizadasConOroEnPodio().longitud()>0)
        {
            a = j.competenciasFinalizadasConOroEnPodio().iesimo(0).ranking().iesimo(0);
        }
    while(i< j.competenciasFinalizadasConOroEnPodio().longitud())
    {
            if(a.anioNacimiento()< j.competenciasFinalizadasConOroEnPodio().iesimo(i).ranking().iesimo(0).anioNacimiento())
            {
                a = j.competenciasFinalizadasConOroEnPodio().iesimo(i).ranking().iesimo(0);
            }
            i++;
    }
    return a;

}

int main()
{
    MenuPrincipal();
    return 0;
}

