#include <iostream>
#include <fstream>
#include "interfaz.h"


using namespace std;


Atleta atletaProdigio(const JJOO & j)
{
    Lista<Competencia> competenciasConOro = j.competenciasFinalizadasConOroEnPodio();
    Lista<Atleta> misAtletasOro = Lista<Atleta>();

    return Atleta();
}

int main()
{
    MenuPrincipal();
    return 0;
}

