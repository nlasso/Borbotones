#include "competencia.h"
#include "atleta.h"
#include "jjoo.h"

JJOO::JJOO()
{

}

JJOO::JJOO(const int anio, const Lista<Atleta>& atletas, const Lista<Lista<Competencia> >& competenciasPorDia)
{

}

int JJOO::anio() const
{
    return 0;
}

Lista<Atleta> JJOO::atletas() const
{
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    return listaDeAtletas; //devuelvo una lista vacia
}

int JJOO::cantDias() const
{
    return 0;
}

int JJOO::jornadaActual() const
{
    return 0;
}

Lista<Competencia> JJOO::cronograma(const int dia) const
{
    Lista <Competencia> todasLasCompetencias = Lista <Competencia>();
    return todasLasCompetencias;
}

Lista<Competencia> JJOO::competencias() const
{
    Lista <Competencia> todasLasCompetenciasDelDia = Lista <Competencia>();
    return todasLasCompetenciasDelDia;
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

