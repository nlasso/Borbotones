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
    int h = 0;
    int j=0;
    Lista <Competencia> compXdia= Lista <Competencia>();
    Lista <Competencia> todasLasCompetenciasFinalizadasConOro = Lista <Competencia>();
    while( j< this->cantDias())
    {
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            if (compXdia.iesimo(h).finalizada() == true && compXdia.iesimo(h).ranking().longitud()>0)
            {
                todasLasCompetenciasFinalizadasConOro.agregar(compXdia.iesimo(h));
                h++;
            }
            else
            {
                h++;
            }
        }
        j++;
    }
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
    int i=0;
    int h=0;
    int j=0;
    Lista <Competencia> compXdia= Lista <Competencia>();
    Competencia comp;
    Atleta a;
    pair <Atleta,int> atletaYrepeticiones= pair<Atleta,int>();
    Lista<pair<Atleta,int> > listAtletaYrepeticiones = Lista<pair<Atleta,int> >();
    Lista <Atleta> atletasDelPais = Lista <Atleta>();
    Lista <Atleta> atletasParticipantes = Lista <Atleta>();
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    Lista <Atleta> listaDeAtletasFracasados = Lista <Atleta>();
    Lista <Atleta> participaronMuchoYNoGanaronNada = Lista <Atleta>();
    while(i<this->_atletas.longitud()) // saco todos los atletas del pais p del jjoo
    {
        if(this->_atletas.iesimo(i).nacionalidad() == p)
        {
            atletasDelPais.agregar(this->_atletas.iesimo(i));
            i++;
        }
        else
        {
            i++;
        }
    }
    while( j< this->cantDias()) // saco todos los participantes del jjoo
    {
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            comp = compXdia.iesimo(h);
            atletasParticipantes.concatenar(comp.participantes());
            h++;
        }
        j++;
    }
    i=0;
    while(i<atletasDelPais.longitud()) //obtengo la cantidad de veces que participaron los atletas del pais p
    {
        atletaYrepeticiones.first = atletasDelPais.iesimo(i);
        atletaYrepeticiones.second= atletasParticipantes.cantidadDeApariciones(atletaYrepeticiones.first);
        listAtletaYrepeticiones.agregar(atletaYrepeticiones);
        i++;

    }
    listaDeAtletas= AtletaMasRepetidoEnTupla(listAtletaYrepeticiones); //obtengo los mas repetidos de la tupla
    i=0;
    while(i<listaDeAtletas.longitud()) // obtengo a los fracasados que participaron mas y no ganaron nada
    {
        a = listaDeAtletas.iesimo(i);
        j=0;
        while( j< this->cantDias())
        {
            compXdia = this->cronograma(j);
            h = 0;
            while(h< compXdia.longitud())
            {
                comp = compXdia.iesimo(h);
                if(comp.participantes().pertenece(a)== true)
                {
                   if(!(a== comp.ranking().iesimo(0) && a== comp.ranking().iesimo(1) && a== comp.ranking().iesimo(2)))
                    {
                        participaronMuchoYNoGanaronNada.agregar(a);
                    }
                    h++;
                }
                else
                {
                    h++;
                }

            }
        j++;
        }
        i++;
    }
    listAtletaYrepeticiones= Lista<pair<Atleta,int> >();
    i=0;
    while(i<participaronMuchoYNoGanaronNada.longitud()) //obtengo las repeticiones
    {
        atletaYrepeticiones.first = participaronMuchoYNoGanaronNada.iesimo(i);
        atletaYrepeticiones.second = participaronMuchoYNoGanaronNada.cantidadDeApariciones(atletaYrepeticiones.first);
        listAtletaYrepeticiones.agregar(atletaYrepeticiones);
        i++;
    }
    listaDeAtletasFracasados= AtletaMasRepetidoEnTupla(listAtletaYrepeticiones); //obtengo los mas repetidos de la tupla de los fracasados
    return listaDeAtletasFracasados;
}

// -------------------- Auxiliar para obtener el maximo repetido
Lista<Atleta>JJOO::AtletaMasRepetidoEnTupla(Lista<pair<Atleta,int> >& a) const
{
    pair <Atleta,int> atletaYrepeticiones= pair<Atleta,int>();
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    int i=0;
    int j =0;
    while(i<a.longitud()) // obtengo atletas mas repetidos de la lista
    {
        atletaYrepeticiones.second =a.iesimo(i).second;
        atletaYrepeticiones.first =a.iesimo(i).first;
        j=0;

            while(j< a.longitud() && atletaYrepeticiones.second <= a.iesimo(j).second )
            {
                j++;
            }
        if(j== a.longitud())
        {
            listaDeAtletas.agregar(atletaYrepeticiones.first);
            i++;
        }
        else
        {
            i++;
        }
    }
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
        this->mostrar(os);
}

void JJOO::cargar (std::istream& is)
{
char c;
Atleta a;
Competencia comp;
Lista<Competencia> listComp= Lista<Competencia>();
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
is >> c; // saco coma o corchete q cierra
if (c == ',')
{
is >> c; // saco (
}

}
_atletas.darVuelta();
is >> c; // saco corchete
is >> c; // saco corchete
while(c=='[')
{
is >> c;
while(c== '(')
{
comp.cargar(is);
listComp.agregar(comp);
is >> c; //saco el parentesis
is >> c; //saco la coma
is >> c;
is >> c;
is >> c;
}

_competenciasPorDia.agregar(listComp);

}
_competenciasPorDia.darVuelta();
}

