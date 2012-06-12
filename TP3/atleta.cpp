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
    if (!deportes().pertenece(deporte)){
        this->_deportes.agregar(depcap);
    }
}

bool Atleta::operator==(const Atleta& a) const
{
    bool res = true;
    int i = 0;

    // Si la lista de deportes es distinta, ya es falsa la igualdad
    if(this->deportes().longitud() != a.deportes().longitud()){
        res = false;
    }else{

        while(i < this->_deportes.longitud() ){
            if(this->_deportes.iesimo(i).first != a._deportes.iesimo(i).first || this->_deportes.iesimo(i).second != a._deportes.iesimo(i).second){
                res = false;
            }
        }
    }

    if(this->nombre() != a.nombre() || this->sexo() != a.sexo() || this->anioNacimiento() != a.anioNacimiento() ||
       this->nacionalidad() != a.nacionalidad() || this->ciaNumber() != a.ciaNumber()){
        res = false;
    }

    return res;

}


void Atleta::mostrar(std::ostream& os) const
{
    string sex = "";
    string deportes = "";
    int capacidad;
    int i = 0;
        if (this->sexo() == Femenino)
        {
            sex = "Femenino";
        }
        else{
            sex = "Masculino";
        }
    os << "A |" << this->nombre() << "| " << "|" << sex << "| " << this->anioNacimiento() << " " << "|" << this->nacionalidad() << "| " << this->ciaNumber() << " " << "[";
    while (i< _deportes.longitud())
    {
             deportes = _deportes.iesimo(i).first;
             capacidad = _deportes.iesimo(i).second;
             if (i== (_deportes.longitud()-1))
             {
                 os << "(|" << deportes << "|,";
                 os <<  capacidad << ")";
                 i++;
             }
             else
             {
                 os << "(|" << deportes << "|,";
                 os <<  capacidad << "),";
                 i++;
             }
    }
    os << "]";
}

void Atleta::guardar(std::ostream& os) const
{
string deportes = "";
int capacidad;
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
os << "A |" << this->nombre() << "| " << "|" << sex << "| " << this->anioNacimiento() << " " << "|" << this->nacionalidad() << "| " << this->ciaNumber() << "" << "[";
while (i< _deportes.longitud())
{
         deportes = _deportes.iesimo(i).first;
         capacidad = _deportes.iesimo(i).second;
         if (i== (_deportes.longitud()-1))
         {
             os << "(|" << deportes << "|,";
             os <<  capacidad << ")";
             i++;
         }
         else
         {
             os << "(|" << deportes << "|,";
             os <<  capacidad << "),";
             i++;
         }
}
os << "]";
}

void Atleta::cargar(std::istream& is)
{
   Lista<pair <Deporte,int> > depcap2 = Lista<pair<Deporte,int> >();
   this->_deportes =depcap2;
   char c;
   string sex;
   pair <Deporte,int> depcap = pair <Deporte,int>();
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
   is >> c;
   is >> c;
   if(c == '(')
   {
       while( c == '(')
       {
            is >> c;
            getline(is,depcap.first, '|');
            is >> c;
            is >> depcap.second;
            this->_deportes.agregar(depcap);
            is >> c; // tomo parentesis
            is >> c; // tomo , o ]
            if(c == ',') // si no es el ultimo deporte sacas otro char para llegar al ( siguiente
            {
                is >> c;
            }

       }
   }

   _deportes.darVuelta(); // Invierto el orden para mantener el original
}

std::ostream & operator<<(std::ostream & os,const Atleta & a)
{
    Lista <int> cap = Lista <int>();
    int i = 0;
    while(i< a.deportes().longitud())
    {
        cap.agregar(a.capacidad(a.deportes().iesimo(i)));
        i++;
    }
    os << "Nombre: " << a.nombre() << "Sexo" << a.sexo() << "fecha de nacimiento" << a.anioNacimiento() << "nacionalidad" << a.nacionalidad() << "cianumber" << a.ciaNumber() << "deportes" << a.deportes() <<  "Capacidades" << cap << endl;
    return os;
}
