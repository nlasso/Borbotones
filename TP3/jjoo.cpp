#include "competencia.h"
#include "atleta.h"
#include "jjoo.h"

JJOO::JJOO()
{

}

JJOO::JJOO(const int anio, const Lista<Atleta>& atletas, const Lista<Lista<Competencia> >& competenciasPorDia)
{
this->_anio = anio;
this->_atletas = atletas;
this->_competenciasPorDia = competenciasPorDia;
this->_jornadaActual = 1;
}

int JJOO::anio() const
{
    return this->_anio;
}

Lista<Atleta> JJOO::atletas() const
{
    return this->_atletas;
}

int JJOO::cantDias() const
{
    int cantidad = 0;
    cantidad = this->_competenciasPorDia.longitud();
    return cantidad;
}

int JJOO::jornadaActual() const
{
    return this->_jornadaActual;
}

Lista<Competencia> JJOO::cronograma(const int dia) const
{
    Lista <Competencia> todasLasCompetencias = Lista <Competencia>();
    return todasLasCompetencias; //no esta hecho solo devuelvo lista vacia para que ande el return
}

Lista<Competencia> JJOO::competencias() const
{
    Lista <Competencia> todasLasCompetencias = Lista <Competencia>();
    return todasLasCompetencias; //no esta hecho solo devuelvo lista vacia para que ande el return
}

Lista<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const
{
    Lista <Competencia> todasLasCompetenciasFinalizadasConOro = Lista <Competencia>();
    return todasLasCompetenciasFinalizadasConOro;
}

Lista<Atleta> JJOO::dePaseo() const
{
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    return listaDeAtletas;
}

Lista<pair<Pais,Lista<int> > > JJOO::medallero() const
{
    Lista <pair <Pais,Lista<int> > > paisInt = Lista <pair <Pais,Lista <int> > >();
    return paisInt;
}

int JJOO::boicotPorDisciplina(const Categoria cat, const Pais p)
{
    return 0;
}

Lista<Atleta> JJOO::losMasFracasados(const Pais p) const
{
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    return listaDeAtletas;
}

void JJOO::liuSong(const Atleta& a, const Pais p)
{

}

Atleta JJOO::stevenBradbury() const
{
    return Atleta();
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const
{
    return true;
}

Lista<Pais> JJOO::sequiaOlimpica() const
{
    Lista <Pais> paisSeco = Lista <Pais>();
    return paisSeco;
}

void JJOO::transcurrirDia()
{

}

bool JJOO::operator==(const JJOO& j) const
{
    return true;
}

void JJOO::mostrar(std::ostream& os) const
{

}

void JJOO::guardar(std::ostream& os) const
{

}

void JJOO::cargar (std::istream& is)
{

}

