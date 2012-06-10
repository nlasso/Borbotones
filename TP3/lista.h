#ifndef LISTA_H
#define LISTA_H

#include <list>
#include <iostream>

template<class T> class Lista {
public:
	Lista(){};
	int longitud() const;
	const T & iesimo(int i) const;

	const T & cabeza() const;
	void cola();

	void agregar(T);
	void agregarAtras(T);

	void sacar(const T &);

	bool pertenece(const T &) const;

	int cantidadDeApariciones(const T &) const;

	void concatenar(const Lista<T> &);
	void darVuelta();

	bool operator==(const Lista<T> &) const;

	int posicion(const T &) const;
	void eliminarPosicion(int);

	void mostrar(std::ostream &) const;
private:
	std::list<T> lista;
};

template<class T>
bool mismos(const Lista<T> & l1, const Lista<T> & l2);

template<class T>
bool iguales(const Lista<T> & l1,const Lista<T> & l2);

template<class T>
std::ostream & operator<<(std::ostream & salida,const Lista<T> & l);

template<class T>
std::ostream & operator<<(std::ostream & salida,const Lista< std::pair < T, T > > & l);

/* Implementaciones - template */

template<class T>
std::ostream & operator<<(std::ostream & salida,const Lista<T> & l)
{
    salida << "[";
    for( int i = 0; i < l.longitud(); i++ ){
        salida << l.iesimo(i);

        if ( i+1 < l.longitud() ){
            salida << ",";
        }
    }
    salida << "]";
    return salida;
}

template<class T>
std::ostream & operator<<(std::ostream & salida,const Lista< std::pair < T, T > > & l)
{
    salida << "[";
    for( int i = 0; i < l.longitud(); i++ ){
        salida << "(" << l.iesimo(i).first << "," << l.iesimo(i).second << ")";

        if ( i+1 < l.longitud() ){
            salida << ",";
        }
    }
    salida << "]";
    return salida;
}

template <class T>
void Lista<T>::eliminarPosicion(int pos)
{
	// Copio los elementos que estan antes de pos a otra lista
	Lista<T> nuevaLista;
	int i = 0;
	while (i < pos) {
		nuevaLista.agregar(iesimo(i));
		i++;
	}
	// Saco todos los elementos hasta pos en inclusive (pos + 1 elementos)
	i = pos;
	while (i >= 0) {
		cola();
		i--;
	}

	// Vuelvo a poner los que habia guardado
	i = 0;
	while (i < pos) {
		agregar(nuevaLista.iesimo(i));
		i++;
	}
}

template <class T>
int Lista<T>::posicion(const T & elemento) const
{
	int indice = 0;
	while (!(iesimo(indice) == elemento))
		indice++;

	return indice;
}

template<class T> void Lista<T>::darVuelta()
{
	// Primero copiamos los elementos al final de la lista
	int i = longitud() - 2;
	while (i >= 0) {
		agregarAtras(iesimo(i));
		i--;
	}
	// Para terminar, sacamos los originales del principio
	for (i = longitud() / 2;i >= 1;i--)
		cola();
}

template<class T> void Lista<T>::mostrar(std::ostream & salida) const
{
	salida << "[";
	if (longitud() > 0) {
		salida << iesimo(0);
	}
	for (int i = 1;i< longitud();i++)
		salida << "," << iesimo(i);
	salida << "]";
}

template<class T> bool Lista<T>::operator==(const Lista<T> & otraLista) const
{
	bool result = longitud() == otraLista.longitud();
	int i = 0;
	while (result && i < longitud()) {
		result = iesimo(i) == otraLista.iesimo(i);
		i++;
	}
	return result;
}

template<class T> void Lista<T>::concatenar(const Lista<T> & otraLista)
{
	for (int i = 0;i < otraLista.longitud();i++)
		agregarAtras(otraLista.iesimo(i));
}

template<class T> bool Lista<T>::pertenece(const T & e) const
{
	bool result = false;
	int i = 0;
	while (!result && i < longitud()) {
		result = (iesimo(i) == e);
		i++;
	}
	return result;
}

template<class T> int Lista<T>::cantidadDeApariciones(const T & e) const
{
	int cant = 0;
	int i = 0;
	while (i < longitud()) {
		if (iesimo(i) == e)
			cant++;
		i++;
	}
	return cant;
}

template<class T> const T & Lista<T>::cabeza() const
{
	return iesimo(0);
}

template<class T> void Lista<T>::sacar(const T & e)
{
	typename std::list<T>::iterator iter;
	iter = lista.begin();
	while (iter != lista.end()) {
		if(*iter == e) {
			iter = lista.erase(iter);
		} else {
			iter++;
		}
	}
}

template<class T> void Lista<T>::cola()
{
	lista.pop_front();
}

template<class T> int Lista<T>::longitud() const
{
	return lista.size();
}

template<class T> void Lista<T>::agregar(T e)
{
	lista.push_front(e);
}

template<class T> void Lista<T>::agregarAtras(T e)
{
	lista.push_back(e);
}

template<class T> const T & Lista<T>::iesimo(int i) const
{
	typename std::list<T>::const_iterator iter;
	iter = lista.begin();
	while (i > 0) {
		iter++;
		i--;
	}
	return *iter;
}

template<class T>
bool iguales(const Lista<T> & l1,const Lista<T> & l2)
{
	bool resultado = true;
	for (int i = 0;i < l2.longitud();i++)
		resultado = resultado && l1.pertenece(l2.iesimo(i));
	for (int i = 0;i < l1.longitud();i++)
		resultado = resultado && l2.pertenece(l1.iesimo(i));
	return resultado;
}

template<class T>
bool mismos(const Lista<T> & l1, const Lista<T> & l2) {
	Lista<T> b(l2);
	for(Lista<T> a(l1); a.longitud(); a.cola()) {
		if (!b.pertenece(a.cabeza())) return false;
		b.sacar(a.cabeza());
	}
	return b.longitud() == 0;
}


#endif
