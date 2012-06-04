#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <fstream>

#include "tipos.h"
#include "atleta.h"
#include "competencia.h"
#include "jjoo.h"

void MenuPrincipal();
void MenuAtleta();
Atleta MenuCrearAtleta();
void MenuCompetencia();
Competencia MenuCrearCompetencia();
void MenuJJOO();
JJOO MenuCrearJJOO();
Atleta atletaProdigio(const JJOO &jjoo);

//AUX
int LeerOpcion(int maxOpcion);
void Pausar();
void Salir();
void LimpiarPantalla();
void AbrirArchivoParaLeer(ifstream &archivo);
void AbrirArchivoParaEscribir(ofstream &archivo);
void MostrarAtletas(Lista<Atleta> atletas, string titulo);

#endif // INTERFAZ_H
