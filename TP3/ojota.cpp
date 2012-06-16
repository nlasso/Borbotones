#include <iostream>
#include <fstream>
#include "interfaz.h"


using namespace std;


Atleta atletaProdigio(const JJOO & j)
{
<<<<<<< HEAD
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
=======
    Lista<Competencia> competenciasConOro = j.competenciasFinalizadasConOroEnPodio();
    Lista<Atleta> misAtletasOro = Lista<Atleta>();

    return Atleta();
>>>>>>> 39fb5224a7fd39d4c76776a420d358d1b94639b5
}

int main()
{
    MenuPrincipal();
    return 0;
}

