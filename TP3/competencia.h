#ifndef COMPETENCIA_H
#define COMPETENCIA_H

#include "atleta.h"
#include "lista.h"

class Competencia{
    public:

        Competencia();
        Competencia(const Deporte d, const Sexo s, const Lista<Atleta>& participantes);

        Categoria categoria() const;
        Lista<Atleta> participantes() const;
        bool finalizada() const;
        Lista<Atleta> ranking() const;
        Lista<Atleta> lesTocoControlAntidoping() const;
        bool leDioPositivo(const Atleta& a) const;

        void finalizar(const Lista<int>& posiciones, const Lista<pair<int, bool> >& control);
        void linfordChristie(const int ciaNum);
        bool gananLosMasCapaces() const;
        void sancionarTramposos();

        bool operator==(const Competencia& c) const;

        void mostrar(std::ostream& os) const;
	void guardar(std::ostream& os) const;
	void cargar (std::istream& is);

    private:

        Categoria _categoria;
        Lista<Atleta> _participantes;
        bool _finalizada;
        Lista<int> _ranking;
        Lista<pair<int, bool> > _controlAntidoping;

        enum {ENCABEZADO_ARCHIVO = 'C'};
};
std::ostream & operator<<(std::ostream & os,const Competencia & c);

#endif // COMPETENCIA_H
