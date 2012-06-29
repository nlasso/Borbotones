#include <iostream>
#include <fstream>
#include "interfaz.h"


using namespace std;


Atleta atletaProdigio(const JJOO & j)
{
    int i = 0;
    int n = j.competenciasFinalizadasConOroEnPodio().longitud();
	Atleta a = j.competenciasFinalizadasConOroEnPodio().iesimo(0).ranking().iesimo(0);

    while(i< n)
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

