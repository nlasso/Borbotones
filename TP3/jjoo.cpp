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
    return this->_competenciasPorDia.iesimo(dia);
}

Lista<Competencia> JJOO::competencias() const
{
    Lista <Competencia> todasLasCompetencias = Lista <Competencia>();
    int i = 0;
    while(i< this->_competenciasPorDia.longitud())
    {
        todasLasCompetencias.concatenar(this->_competenciasPorDia.iesimo(i));
        i++;
    }
    return todasLasCompetencias;
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
    os << "J " << this->anio() << " " << this->jornadaActual() << endl;
    os << "[(";
    int i = 0;
    int j = 0;
    int h = 0;
    Competencia comp;
    Atleta a;
    Lista <Competencia> compXdia = Lista<Competencia>();
    while(i < this->atletas().longitud())
    {
        a = this->atletas().iesimo(i);
        if (i < this->atletas().longitud()-1)
        {
            a.mostrar(os);
            os << "),(";
            i++;
        }
        else
        {
            a.mostrar(os);
            os << ")";
            i++;
        }
    }
    os << "]" << endl;
    os << "[";
    while( j< this->cantDias())
    {
        os << "[";
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            os << "(";
            if(h< compXdia.longitud()-1)
            {
                comp = compXdia.iesimo(h);
                comp.mostrar(os);
                os << "),";
                h++;
            }
            else
            {
                comp = compXdia.iesimo(h);
                comp.mostrar(os);
                os << ")";
                h++;
            }
        }
        if(j< this->cantDias()-1)
        {
            os << "],[";
            j++;
        }
        else
        {
            os << "]]";
            j++;
        }
    }

}

void JJOO::guardar(std::ostream& os) const
{
    os << "J " << this->anio() << " " << this->jornadaActual() << endl;
    os << "[(";
    int i = 0;
    int j = 0;
    int h = 0;
    Competencia comp;
    Atleta a;
    Lista <Competencia> compXdia = Lista<Competencia>();
    while(i < this->atletas().longitud())
    {
        a = this->atletas().iesimo(i);
        if (i < this->atletas().longitud()-1)
        {
            a.guardar(os);
            os << "),(";
            i++;
        }
        else
        {
            a.guardar(os);
            os << ")";
            i++;
        }
    }
    os << "]" << endl;
    os << "[";
    while( j< this->cantDias())
    {
        os << "[";
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            os << "(";
            if(h< compXdia.longitud()-1)
            {
                comp = compXdia.iesimo(h);
                comp.guardar(os);
                os << "),";
                h++;
            }
            else
            {
                comp = compXdia.iesimo(h);
                comp.guardar(os);
                os << ")";
                h++;
            }
        }
        if(j< this->cantDias()-1)
        {
            os << "],[";
            j++;
        }
        else
        {
            os << "]]";
            j++;
        }
    }

}



void JJOO::cargar (std::istream& is)
{
    char c;
    Atleta a;
    is >> c; // Saco la J
    is >> this->_anio;
    is >> this->_jornadaActual;
    is >> c; //Saco el [ de la lista de atletas
    is >> c;
    while(c == '(')
          {
             a.cargar(is) ;
             this->_atletas.agregar(a);
             is >> c; // saco parentesis q cierra
             is >> c; // saco coma
           }

}

