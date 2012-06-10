#include "atleta.h"
#include <fstream>

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
string sex = "";
string deportes = "";
string capacidad;
string finalConcatenacion;
string abroParentesis;
string cierroParentesisYComa;
string coma;
Lista <string> deportesycap = Lista<string>();
int i = 0;
    if (this->sexo() == Femenino)
    {
        sex = "Femenino";
    }
    else{
        sex = "Masculino";
    }
while (i< _deportes.longitud())
{
         deportes = _deportes.iesimo(i).first;
         capacidad = _deportes.iesimo(i).second;
         abroParentesis = "(";
         cierroParentesisYComa = "),";
         coma = ",";
         finalConcatenacion = abroParentesis + deportes + coma + capacidad + cierroParentesisYComa;
         deportesycap.agregar(finalConcatenacion);
        i++;
}
 os << "A |" << this->nombre() << "| " << "|" << sex << "| " << this->anioNacimiento() << " " << "|" << this->nacionalidad() << "| " << this->ciaNumber() << "|" << "[" <<deportesycap << "]";
}

void Atleta::guardar(std::ostream& os) const
{
string deportes = "";
string capacidad = "";
string finalConcatenacion = "";
string abroParentesis = "";
string cierroParentesisYComa = "";
string coma = "";
int i = 0;
string sex = "";
Lista <string> deportesycap = Lista<string>();
    if (this->sexo() == Femenino)
    {
        sex = "Femenino";
    }
    else{
        sex = "Masculino";
    }
while (i< _deportes.longitud())
{
         deportes = _deportes.iesimo(i).first;
         capacidad = _deportes.iesimo(i).second;
         abroParentesis = "(";
         cierroParentesisYComa = "),";
         coma = ",";
         finalConcatenacion = abroParentesis + deportes + coma + capacidad + cierroParentesisYComa;
         deportesycap.agregar(finalConcatenacion);
        i++;
}
os << "A |" << this->nombre() << "| " << "|" << sex << "| " << this->anioNacimiento() << " " << "|" << this->nacionalidad() << "| " << this->ciaNumber() << "|" << deportesycap << "|";


}

void Atleta::cargar(std::istream& is)
{
   char c;
   string sex;
   is >> c;
   is >> c;
   getline(is,this->_nombre, '|');
   is >> c;
   getline(is,sex,'|');
   if (sex == "Masculino")
   {
        this->_sexo = Masculino;
   }
   else
   {
        this->_sexo = Femenino;
   }
   is >>this->_anioNacimiento;
   is >> c;
   getline(is,this->_nacionalidad, '|');
   is >> this->_ciaNumber;

}

std::ostream & operator<<(std::ostream & os,const Atleta & a)
{
    os << "Nombre: " << a.nombre() << "Sexo" << a.sexo() << "fecha de nacimiento" << a.anioNacimiento() << "nacionalidad" << a.nacionalidad() << "cianumber" << a.ciaNumber() << endl;
    return os;
}
