#include "atleta.h"
#include <string>
#include <fstream>

Atleta::Atleta()
{
    _nombre = "Atleta1";
    _sexo = Masculino;
    _anioNacimiento = 1990;
    _nacionalidad = "Argentina";
    _ciaNumber = 2012;
    _deportes = Lista<pair<Deporte,int> >();
}

Atleta::Atleta(const string nombre,const Sexo sexo, const int anio, const Pais pais, const int ciaNumber){
    _nombre = nombre;
    _sexo = sexo;
    _anioNacimiento = anio;
    _nacionalidad = pais;
    _ciaNumber = ciaNumber;
    _deportes = Lista<pair<Deporte,int> >();
}

 string Atleta::nombre() const{
    return _nombre;
 }

 Sexo Atleta::sexo() const{
    return _sexo;
 }

 int Atleta::anioNacimiento() const{
    return _anioNacimiento;
 }

Pais Atleta::nacionalidad() const{
    return _nacionalidad;
}

int Atleta::ciaNumber() const{
    return _ciaNumber;
}

Lista<Deporte> Atleta::deportes() const{
    int i = 0;
    Lista<Deporte> deportesDelAtleta = Lista <Deporte>();
    pair <Deporte,int> dep = pair <Deporte,int>();
    while(i< _deportes.longitud())
    {
            dep = _deportes.iesimo(i);
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
    pair <Deporte,int> depcap = pair<Deporte,int>(deporte, cap);
    Lista<pair<Deporte,int> > listdepcap = Lista<pair<Deporte,int> >();
    if (!deportes().pertenece(deporte)){
        _deportes.agregar(depcap);
    }else{
        int i = 0;
        while(i < _deportes.longitud()){
            if(depcap.first == _deportes.iesimo(i).first){
                _deportes.sacar(_deportes.iesimo(i));
            }
            i++;
        }
        _deportes.agregar(depcap);
    }
    listdepcap = ordenadoDeportes(this->_deportes);
    _deportes = Lista<pair<Deporte,int> >();
    _deportes = listdepcap;

}

bool Atleta::operator==(const Atleta& a) const
{
    bool res = true;
    int i = 0;

    // Si la lista de deportes es distinta, ya es falsa la igualdad
    if(this->_deportes.longitud() != a._deportes.longitud()){
        res = false;
    }else{

        while(i < this->_deportes.longitud() ){
            if(this->_deportes.iesimo(i).first != a._deportes.iesimo(i).first || this->_deportes.iesimo(i).second != a._deportes.iesimo(i).second){
                res = false;
            }

            i++;

        }
    }

    if(this->_nombre != a._nombre || this->_sexo != a._sexo || this->_anioNacimiento != a._anioNacimiento ||
       this->_nacionalidad != a._nacionalidad || this->_ciaNumber != a._ciaNumber){
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
                 os << "(|" << deportes << "|, ";
                 os <<  capacidad << ")";
                 i++;
             }
             else
             {
                 os << "(|" << deportes << "|, ";
                 os <<  capacidad << "), ";
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
             os << "(|" << deportes << "|, ";
             os <<  capacidad << ")";
             i++;
         }
         else
         {
             os << "(|" << deportes << "|, ";
             os <<  capacidad << "), ";
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




//----------------------------ORDENAR DEPORTES

    Lista<pair<Deporte,int> > Atleta::ordenadoDeportes(Lista<pair<Deporte,int> > deportescap)
    {
    Lista<pair <Deporte,int> > listadepcap = Lista<pair <Deporte,int> >();
	pair<Deporte,int> depcap = pair<Deporte,int>();
	int p = 0;
	int i = 0;
	int j = 0;
    while(j < deportescap.longitud())
		{
        p = j;
        depcap = deportescap.iesimo(0);
        i =j+1;
		while (i < deportescap.longitud())
			{
				if (depcap.first <= deportescap.iesimo(i).first)
				{
				i++;
			}
				else
				{
					depcap = deportescap.iesimo(i);
					p = i;
					i++;
				}
			}
		listadepcap.agregar(deportescap.iesimo(p));
		deportescap.eliminarPosicion(p);
        j = 0;
		}
    return listadepcap;
	}
