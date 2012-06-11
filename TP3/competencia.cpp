#include "competencia.h"
#include "atleta.h"

Competencia::Competencia()
{

}

Competencia::Competencia(const Deporte d, const Sexo s, const Lista<Atleta>& participantes)
{
    pair<Deporte,Sexo> cat = pair <Deporte,Sexo>();
    cat.first = d;
    cat.second = s;
    this->_categoria = cat;
    this->_participantes = participantes;
    this->_finalizada = false;
    this->_ranking = Lista<int>();
    this->_controlAntidoping = Lista<pair<int, bool> >();
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
    int i = 0;
    int j = 0;
    while(i< _controlAntidoping.longitud())
    {
        while(j < participantes().longitud() && participantes().iesimo(j).ciaNumber() != _controlAntidoping.iesimo(i).first )
        {
            j++;
        }
        atletasDop.agregar(participantes().iesimo(j));
        i++;
        j = 0;
        }
    return atletasDop;
}

bool Competencia::leDioPositivo(const Atleta& a) const
{
    bool res;
    int i = 0;

    while(i < _controlAntidoping.longitud()){
        if(a.ciaNumber() == _controlAntidoping.iesimo(i).first){ //consultar si tenemos que poner el this aca o no!!!!
            res = _controlAntidoping.iesimo(i).second;
            i = _controlAntidoping.longitud() + 1;
        }
        i++;
    }
    return res;
}

void Competencia::finalizar(const Lista<int>& posiciones, const Lista<pair<int, bool> >& control)
{
    _finalizada = true;
    _ranking = posiciones;
    _controlAntidoping = control;
}

void Competencia::linfordChristie(const int ciaNum)
{
    int i = 0;
    bool loEncontre = false;

    while(i < _participantes.longitud() && !loEncontre){
        if(ciaNum == _participantes.iesimo(i).ciaNumber()){
            _participantes.sacar(_participantes.iesimo(i));
            loEncontre = true;
        }
        i++;
    }

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
    bool res = true;

    // Miro observadores simples para ver la igualdad
    if(this->categoria() != c.categoria() || this->finalizada() != c.finalizada() || !(this->participantes() == c.participantes())
       || !(this->ranking() == c.ranking()) || !(this->lesTocoControlAntidoping() == c.lesTocoControlAntidoping()) )
    {
       res = false;
    }

    // Si la lista de lesTocoControlAntidoping es distinta, ya es falsa la igualdad
    if(this->lesTocoControlAntidoping().longitud() != c.lesTocoControlAntidoping().longitud()){
        res = false;
    }else{

        int i = 0;

        // Recorro los que les toco control antidoping para ver si dio el mismo resultado en las 2 competencias
        while(i < this->lesTocoControlAntidoping().longitud())
        {

            Atleta a1 = this->lesTocoControlAntidoping().iesimo(i);
            Atleta a2 = c.lesTocoControlAntidoping().iesimo(i);

            if( this->leDioPositivo(a1) != c.leDioPositivo(a2) ){
                res = false;
            }

            i++;
        }

    }


    return res;
}

void Competencia::mostrar(std::ostream& os) const
{

}

void Competencia::guardar(std::ostream& os) const
{
    string cat = this->categoria().first;
    string sex = "";
    string final = "";

    if (this->categoria().second == Femenino){
        sex = "Femenino";
    }else{
        sex = "Masculino";
    }

    if (finalizada()){
        final = "True";
    }else{
        final = "False";
    }

    os << "C ";
    os << "(|" << cat << "|, |" << sex << "|) ";
    os << "|" << final << "| " ;

    os << "[";

        int i = 0;

        while( i < this->participantes().longitud() ){
            os << "(";
            this->participantes().iesimo(i).mostrar(os);
            os << ")";
            //Pongo la coma final si corresponde
            if( i+1 != this->participantes().longitud() ){ os << ", "; }
            i++;
        }

    os << "] ";

    os << "[";

        i = 0;

        while( i < this->ranking().longitud() ){
            os << this->ranking().iesimo(i).ciaNumber();
            //Pongo la coma final si corresponde
            if( i+1 != this->ranking().longitud() ){ os << ", "; }
            i++;
        }

    os << "] ";
    os << "[";

        i = 0;
        string positivo = "";

        while( i < this->lesTocoControlAntidoping().longitud() ){
            Atleta at = this->lesTocoControlAntidoping().iesimo(i);
            if (this->leDioPositivo(at)){
                positivo = "True";
            }else{
                positivo = "False";
            }
            os << "(" << at.ciaNumber() << ", |" << positivo << "|)";
            //Pongo la coma final si corresponde
            if( i+1 != this->lesTocoControlAntidoping().longitud() ){ os << ", "; }
            i++;
        }

    os << "]";

}

void Competencia::cargar (std::istream& is)
{

}
