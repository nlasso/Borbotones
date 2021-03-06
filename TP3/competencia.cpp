#include "competencia.h"
#include "atleta.h"

Competencia::Competencia()
{
    this->_categoria = pair<Deporte,Sexo>();
    this->_participantes = Lista<Atleta>();
    this->_finalizada = false;
    this->_ranking = Lista<int>();
    this->_controlAntidoping = Lista<pair<int,bool> >();
}

Competencia::Competencia(const Deporte d, const Sexo s, const Lista<Atleta>& participantes)
{
    _categoria= pair <Deporte,Sexo>(d,s);
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
        atletasDelRanking.agregarAtras(participantes().iesimo(j));
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
        if(a.ciaNumber() == _controlAntidoping.iesimo(i).first){
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
    while(i < _participantes.longitud()){
        if(ciaNum == _participantes.iesimo(i).ciaNumber()){
            _participantes.eliminarPosicion(i);
        }
        i++;
    }

}

bool Competencia::gananLosMasCapaces() const
{
    bool res = true;
    Lista<Atleta> rank = this->ranking();
    Deporte dep = this->categoria().first;

    while(rank.longitud() > 1 ){
        int capacidad1 = rank.iesimo(0).capacidad(dep);
        rank.eliminarPosicion(0);
        int capacidad2 = rank.iesimo(0).capacidad(dep);
        if(capacidad1 < capacidad2){
            res = false;
        }
    }
    return res;
}

Atleta Competencia::buscarAtleta (Lista<Atleta> a, int b){
    int i = 0;
    Atleta miAtleta;

    while(i < a.longitud() ){
        if(b == a.iesimo(i).ciaNumber()){
            miAtleta = a.iesimo(i);
        }
        i++;
    }
    return miAtleta;
}

void Competencia::sancionarTramposos()
{
    Lista<Atleta> dopados = this->lesTocoControlAntidoping();
    int i = 0;

    while(i < _ranking.longitud()){
        Atleta a = this->buscarAtleta(_participantes, _ranking.iesimo(i));

        if(dopados.pertenece(a) && this->leDioPositivo(a)){
            _ranking.sacar(_ranking.iesimo(i));
        }
        else
        {
         i++;
        }
    }
}

void Competencia::clasificoTarde(const Atleta& a){
    _participantes.agregarAtras(a);
}


bool Competencia::operator==(const Competencia& c) const
{
    bool res = true;
    int i= 0;
    // Miro observadores simples para ver la igualdad
    if(categoria() != c.categoria() || finalizada() != c.finalizada()  || !(_ranking == c._ranking) )
    {
       res = false;
    }
    if(_participantes.longitud() != c._participantes.longitud())
    {
        res = false;
    }
    else
    {        //Veo que los participantes son los mismos
     i = 0;
        while(i < _participantes.longitud()){
            if(!c._participantes.pertenece(_participantes.iesimo(i))){
                res = false;
            }
            i++;
        }
    }


    // Si la lista de lesTocoControlAntidoping es distinta, ya es falsa la igualdad
    if(this->lesTocoControlAntidoping().longitud() != c.lesTocoControlAntidoping().longitud()){
        res = false;
    }else{

     i = 0;
        while(i < _controlAntidoping.longitud()){
            if(!c._controlAntidoping.pertenece(_controlAntidoping.iesimo(i))){
                res = false;
            }
            i++;
        }

    }

   return res;
}

void Competencia::mostrar(std::ostream& os) const
{
    string cat = categoria().first;
    string sex = "";
    string final = "";

    if (categoria().second == Femenino){
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

        while( i < participantes().longitud() ){
            os << "(";
            participantes().iesimo(i).mostrar(os);
            os << ")";
            //Pongo la coma final si corresponde
            if( i+1 != participantes().longitud() ){ os << ", "; }
            i++;
        }

    os << "] ";

    os << "[";

    if (finalizada()){

        i = 0;

        while( i < _ranking.longitud() ){
            os << _ranking.iesimo(i);
            //Pongo la coma final si corresponde
            if( i+1 != _ranking.longitud() ){ os << ", "; }
            i++;
        }
    }

    os << "] ";
    os << "[";

    if (finalizada()){

        i = 0;
        string positivo = "";

        while( i < lesTocoControlAntidoping().longitud() ){
            Atleta at = lesTocoControlAntidoping().iesimo(i);
            if (leDioPositivo(at)){
                positivo = "True";
            }else{
                positivo = "False";
            }
            os << "(" << at.ciaNumber() << ", |" << positivo << "|)";
            //Pongo la coma final si corresponde
            if( i+1 != lesTocoControlAntidoping().longitud() ){ os << ", "; }
            i++;
        }

    }

    os << "]";

}

void Competencia::guardar(std::ostream& os) const
{
    this->mostrar(os);
}

void Competencia::cargar (std::istream& is)
{
    string cat = "";
    string sex = "";
    string finalizada = "";
    char b;

    is >> b; // Saco la cabecera
    is >> b;
    is >> b;

    getline(is,_categoria.first, '|');

    is >> b;
    is >> b;

    getline(is,sex, '|');

    if (sex == "Femenino"){
        _categoria.second = Femenino;
    }else{
        _categoria.second = Masculino;
    }

    is >> b;
    is >> b;

    getline(is,finalizada, '|');

    if (finalizada == "True"){
        _finalizada = true;
    }else{
        _finalizada = false;
    }

    is >> b;
    is >> b; // Agarro el '(' inicial del atleta

    Atleta atl;
    _participantes = Lista<Atleta>();
    while(b == '('){
        atl = Atleta();
        atl.cargar(is);
        _participantes.agregarAtras(atl);
        is >> b; // Saco el ')'
        is >> b; // Saco el ','
        if(b == ','){
            is >> b;
        }
    }

    //_participantes.darVuelta();

    is >> b; // Saco el '['

    int ciaNum = 0;
    _ranking = Lista<int>();
    while(b != ']'){

        if(is.peek() != ']'){

            is >> ciaNum;
            _ranking.agregarAtras(ciaNum);

        }

        is >> b;

    }

    is >> b; // Saco el '['

    pair<int, bool> dop = pair<int, bool>();
    ciaNum = 0;
    string resultDop = "";

    is >> b; // Saco el '('
    _controlAntidoping = Lista<pair<int,bool> >();
    while( b == '(')
       {
            is >> dop.first;
            is >> b; // saco ','
            is >> b; // saco '|'
            getline(is,resultDop, '|');

            if(resultDop == "True"){
                dop.second = true;
            }else{
                dop.second = false;
            }
            _controlAntidoping.agregarAtras(dop);

            is >> b; // saco ')'
            is >> b; // saco ',' o ']'
            if ( b == ',' )
            {
                    is >> b; // saco '('
            }



       }




}


