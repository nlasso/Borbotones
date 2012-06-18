#ifndef ATLETA_H
#define ATLETA_H

#include "tipos.h"
#include "lista.h"

class Atleta{
    public:

        Atleta();
        Atleta(const string nombre,const Sexo sexo, const int anio, const Pais pais, const int ciaNumber);

        string nombre() const;
        Sexo sexo() const;
        int anioNacimiento() const;
        Pais nacionalidad() const;
        int ciaNumber() const;
        Lista<Deporte> deportes() const;
        int capacidad(const Deporte d) const;

        void entrenarNuevoDeporte(const Deporte deporte, const int capacidad);
        bool operator==(const Atleta& a) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

    private:
        string _nombre;
        Sexo _sexo;
        int _anioNacimiento;
        Pais _nacionalidad;
        int _ciaNumber;
        Lista<pair<Deporte, int> > _deportes;
        enum {ENCABEZADO_ARCHIVO = 'A'};
        Lista<pair<Deporte,int> >ordenadoDeportes(const Lista<pair<Deporte,int> > deportescap);
};

std::ostream & operator<<(std::ostream & os,const Atleta & a);

#endif // ATLETA_H
