#include "atleta.h"

Atleta::Atleta()
{
    this->_nombre = "Atleta1";
    this->_sexo = Masculino;
    this->_anioNacimiento = 1990;
    this->_nacionalidad = "Argentina";
    this->_ciaNumber = 2012;
    Lista<pair<Deporte,int> > depcapvacio;
    this->_deportes = depcapvacio;
}

Atleta::Atleta(const string nombre,const Sexo sexo, const int anio, const Pais pais, const int ciaNumber){
this->_nombre = nombre;
this->_sexo = sexo;
this->_anioNacimiento = anio;
this->_nacionalidad = pais;
this->_ciaNumber = ciaNumber;
Lista<pair<Deporte,int> > depcapvacio;
this->_deportes = depcapvacio;
}

 string Atleta::nombre() const{
 return this->_nombre;
 }

 Sexo Atleta::sexo() const{
  return this->_sexo;
 }

 int Atleta::anioNacimiento() const{
 return this->_anioNacimiento;
 }

Pais Atleta::nacionalidad() const{
return this->_nacionalidad;
}

int Atleta::ciaNumber() const{
return this->_ciaNumber;
}

Lista<Deporte> Atleta::deportes() const{
int i = 0;
Lista<Deporte> deportesDelAtleta = Lista <Deporte>();
pair <Deporte,int> dep = pair <Deporte,int>();
while(i< this->_deportes.longitud())
{
        dep = this->_deportes.iesimo(i);
        deportesDelAtleta.agregar(dep.first);
        i++;
}
return deportesDelAtleta;
}

int Atleta::capacidad(const Deporte d)const{
int i = 0;
int cap = 0;
while (i< this->_deportes.longitud() && d!= this->_deportes.iesimo(i).first){
        i++;
}
cap = this->_deportes.iesimo(i).second;
return cap;
}

void Atleta::entrenarNuevoDeporte(const Deporte deporte, const int cap){
pair <Deporte,int> depcap = pair<Deporte,int>();
depcap.first = deporte;
depcap.second = cap;
if (!deportes().pertenece(deporte))
    {this->_deportes.agregar(depcap);
    }
}

bool Atleta::operator==(const Atleta& a) const
{
    return true;
}

void Atleta::mostrar(std::ostream& os) const
{

}

void Atleta::guardar(std::ostream& os) const
{

}

void Atleta::cargar(std::istream& is)
{

}
