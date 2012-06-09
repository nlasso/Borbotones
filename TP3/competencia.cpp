#include "competencia.h"
#include "atleta.h"

Competencia::Competencia()
{

}

Competencia::Competencia(const Deporte d, const Sexo s, const Lista<Atleta>& participantes)
{
//PROBANDO MAIN CON METODOS VACIOS
}


Categoria Competencia::categoria() const
{
    return this->_categoria;
}

Lista<Atleta> Competencia::participantes() const
{
    return this->_participantes;
}

bool Competencia::finalizada() const
{
    return this->_finalizada;
}

Lista<Atleta> Competencia::ranking() const
{
    Lista<Atleta> atletasDelRanking = Lista <Atleta>();
    int i = 0;
    int j = 0;
    while(i< this->_ranking.longitud())
    {
        while(j < participantes().longitud() && participantes().iesimo(j).ciaNumber() != this->_ranking.iesimo(i) )
        {
            j++;
        }
        atletasDelRanking.agregar(participantes().iesimo(j));
        i++;
        j = 0;
    }
    return atletasDelRanking;
}

Lista<Atleta> Competencia::lesTocoControlAntidoping() const{
Lista<Atleta> atletasDop = Lista <Atleta>();
//int i = 0;
//int j = 0;
//while(i< _controlAntidoping.longitud())
//{
 //   while(j < participantes().longitud() && participantes().iesimo(j).ciaNumber() != _ranking.iesimo(i) )
  //  {
   //     j++;
    //}
   // atletasDelRanking.agregar(participantes().iesimo(j));
    //i++;
   // j = 0;
    //}
return atletasDop;
}

bool Competencia::leDioPositivo(const Atleta& a) const
{
    return true;
}

void Competencia::finalizar(const Lista<int>& posiciones, const Lista<pair<int, bool> >& control)
{

}

void Competencia::linfordChristie(const int ciaNum)
{

}

bool Competencia::gananLosMasCapaces() const
{
    return true;
}

void Competencia::sancionarTramposos()
{

}


bool Competencia::operator==(const Competencia& c) const
{
    return true;
}

void Competencia::mostrar(std::ostream& os) const
{

}

void Competencia::guardar(std::ostream& os) const
{

}

void Competencia::cargar (std::istream& is)
{

}
