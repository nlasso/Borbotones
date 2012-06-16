#ifndef JJOO_H
#define JJOO_H

#include "competencia.h"

typedef pair<int, pair<int, int> > infoM;

class JJOO{
    public:

        JJOO();
        // |cronograma|==cantDias. Si un día no hay competencias,q esté la lista vacía.
        JJOO(const int anio, const Lista<Atleta>& atletas, const Lista<Lista<Competencia> >& competenciasPorDia);

        int anio() const;
        Lista<Atleta> atletas() const;
        int cantDias() const;
        int jornadaActual() const;
        Lista<Competencia> cronograma(const int dia) const;

        Lista<Competencia> competencias() const;
        Lista<Competencia> competenciasFinalizadasConOroEnPodio() const;

        Lista<Atleta> dePaseo() const;
        Lista<pair<Pais,Lista<int> > > medallero() const;
        int boicotPorDisciplina(const Categoria cat, const Pais p);
        Lista<Atleta> losMasFracasados(const Pais p) const;
        void liuSong(const Atleta& a, const Pais p);
        Atleta stevenBradbury() const;
        bool uyOrdenadoAsiHayUnPatron() const;
        Lista<Pais> sequiaOlimpica() const;
        void transcurrirDia();

		bool operator==(const JJOO& j) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

    private:
        int _anio;
        Lista<Atleta> _atletas;
        int _jornadaActual;
        Lista<Lista<Competencia> > _competenciasPorDia;         // En la i-ésima posición de la lista, las competencias del día i+1.


        Lista<pair <Atleta,pair <Deporte,Sexo> > > ganadoresPorCategoria() const;
        Lista<pair<Pais,int> > paisRep(Lista<Pais>& p) const;
        enum {ENCABEZADO_ARCHIVO = 'J'};
        Lista<Atleta>AtletaMasRepetidoEnTupla(Lista<pair<Atleta,int> >& a) const;
        bool ganoMedallaEseDia(const Lista<Competencia>& comp,const Pais p) const;
        int masDiasSinMedallas(const Pais p) const;
        int maxDiasSinMedallas(const Lista<Pais>& pais) const;
        Lista<Pais> paises() const;
        Lista<int> crearRanking (const Lista<Atleta>& particip,const Deporte& d) const;
        Lista<pair<int,bool> > crearControl(const Atleta& a, bool b)const;
        pair<Pais,int> paisMedallero(Pais p, Lista<Pais> paisConMed, Lista<pair<Pais,int> > paisConInt) const;
        int quitarAtletas(Lista<Atleta >& atletas, const Pais& p);
        Lista<int > filtrarPosiciones(Lista<Atleta >& atletas, const Pais& p);
        Lista<pair<int,bool> > filtrarControl(const Competencia& comp, const Pais& p);
         Pais mejorPais(Lista<pair<Pais,int> >& p) const;
       Lista<pair<Pais,Lista<int> > > ordenarMedallero(Lista<pair<Pais,Lista<int> > >& medallero) const;
       Lista<int> atCia(const Lista<Atleta>& a);


};
std::ostream & operator<<(std::ostream & os,const JJOO & j);

#endif // JJOO_H

