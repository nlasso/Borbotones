#include "competencia.h"
#include "atleta.h"
#include "jjoo.h"
#include<string>

JJOO::JJOO()
{

}

JJOO::JJOO(const int anio, const Lista<Atleta>& atletas, const Lista<Lista<Competencia> >& competenciasPorDia)
{
this->_anio = anio;
this->_atletas = atletas;
this->_competenciasPorDia = competenciasPorDia;
this->_jornadaActual = 1;
}

int JJOO::anio() const
{
    return this->_anio;
}

Lista<Atleta> JJOO::atletas() const
{
    return this->_atletas;
}

int JJOO::cantDias() const
{
    int cantidad = 0;
    cantidad = this->_competenciasPorDia.longitud();
    return cantidad;
}

int JJOO::jornadaActual() const
{
    return this->_jornadaActual;
}

Lista<Competencia> JJOO::cronograma(const int dia) const
{
    return this->_competenciasPorDia.iesimo(dia);
}

Lista<Competencia> JJOO::competencias() const
{
    Lista <Competencia> todasLasCompetencias = Lista <Competencia>();
    int i = 0;
    while(i< this->_competenciasPorDia.longitud())
    {
        todasLasCompetencias.concatenar(this->_competenciasPorDia.iesimo(i));
        i++;
    }
    return todasLasCompetencias;
}

Lista<Competencia> JJOO::competenciasFinalizadasConOroEnPodio() const
{
    int h = 0;
    int j=0;
    Lista <Competencia> compXdia= Lista <Competencia>();
    Lista <Competencia> todasLasCompetenciasFinalizadasConOro = Lista <Competencia>();
    while( j< this->_competenciasPorDia.longitud())
    {
        compXdia = this->_competenciasPorDia.iesimo(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            if (compXdia.iesimo(h).finalizada() == true && compXdia.iesimo(h).ranking().longitud()>0)
            {
                todasLasCompetenciasFinalizadasConOro.agregar(compXdia.iesimo(h));
                h++;
            }
            else
            {
                h++;
            }
        }
        j++;
    }
    return todasLasCompetenciasFinalizadasConOro;
}

Lista<Atleta> JJOO::dePaseo() const
{
    Lista<Competencia> comp = this->competencias();
    Lista <Atleta> listaDeAtletas = this->atletas();
    int i = 0;
    Lista<Atleta> atletasDePaseo = Lista<Atleta>();

    while(i < listaDeAtletas.longitud()){
        bool atletaNoPertenece = true;
        int j = 0;
        while(j < comp.longitud() && atletaNoPertenece){
            Competencia comp1 = comp.iesimo(j);
            if(comp1.participantes().pertenece(listaDeAtletas.iesimo(i))){
                atletaNoPertenece = false;
            }
            j++;
        }
        if(atletaNoPertenece){
            atletasDePaseo.agregar(listaDeAtletas.iesimo(i));
        }
        i++;
    }
    return atletasDePaseo;
}

Lista<pair<Pais,Lista<int> > > JJOO::medallero() const
{
    //defino variables
    int j,h,i;
    Competencia comp;
    Atleta a;
    Pais p;
    Lista <Competencia> compXdia = Lista <Competencia>();
    Lista<Pais> todosLosPaises = Lista<Pais>();
    Lista<Pais> paisOro = Lista<Pais>();
    Lista<Pais> paisPlata = Lista<Pais>();
    Lista<Pais> paisBronce = Lista<Pais>();
    Lista<pair<Pais,int> >paisOroYRep = Lista<pair<Pais,int> >();
    Lista<pair<Pais,int> >paisPlataYRep = Lista<pair<Pais,int> >();
    Lista<pair<Pais,int> >paisBronceYRep = Lista<pair<Pais,int> >();
    pair <Pais,Lista<int> > paisCantidadDeMedallas = pair<Pais,Lista<int> >();
    Lista <pair <Pais,Lista<int> > > elMedallero = Lista <pair <Pais,Lista <int> > >();
    Lista <pair <Pais,Lista<int> > > elMedalleroOrdenado = Lista <pair <Pais,Lista <int> > >();

    //obtengo a los paises oro plata y bronce
    j =0;
    while( j< this->cantDias())
    {
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            comp = compXdia.iesimo(h);
            if(comp.finalizada())
            {
                if(comp.ranking().longitud()>0)
                {
                    a = comp.ranking().iesimo(0);
                    paisOro.agregar(a.nacionalidad());
                }
                if(comp.ranking().longitud()>1)
                {
                    a = comp.ranking().iesimo(1);
                    paisPlata.agregar(a.nacionalidad());
                }
                if(comp.ranking().longitud()>2)
                {
                    a = comp.ranking().iesimo(2);
                    paisBronce.agregar(a.nacionalidad());
                }
                h++;
            }
            else
            {
                h++;
            }

        }
        j++;
    }
    // me guardo en duplas los paises oro plata y bronce con su cantidad de rep en oro plata y bronce
    paisOroYRep = paisRep(paisOro);
    paisPlataYRep = paisRep(paisPlata);
    paisBronceYRep = paisRep(paisBronce);
    todosLosPaises = this->paises();
    i=0;
    // recorro todos los paises y me fijo si el pais gano algo en caso de ganar medallas las voy concatenando con elMedallero
    while(i<todosLosPaises.longitud())
    {
        paisCantidadDeMedallas = pair<Pais,Lista<int> >();
        p = todosLosPaises.iesimo(i);
        paisCantidadDeMedallas.first = p;
        paisCantidadDeMedallas.second.agregar(paisMedallero(p,paisBronce,paisBronceYRep).second);
        paisCantidadDeMedallas.second.agregar(paisMedallero(p,paisPlata,paisPlataYRep).second);
        paisCantidadDeMedallas.second.agregar(paisMedallero(p,paisOro,paisOroYRep).second);
        if(paisCantidadDeMedallas.second.iesimo(0)>0 || paisCantidadDeMedallas.second.iesimo(1)>0 || paisCantidadDeMedallas.second.iesimo(2)>0)
        {
            elMedallero.agregar(paisCantidadDeMedallas);
        }
        i++;
    }
    elMedalleroOrdenado = ordenarMedallero(elMedallero);

    return elMedalleroOrdenado;
}


int JJOO::boicotPorDisciplina(const Categoria cat, const Pais p)
{
    int echados = 0;
    int d = -1;
    int c = -1;
    int i = 0;
    int j = 0;

    // Busco las posiciones del dia y la competencia que tengo que boicotear
    // Recorro los dias
    while(i < _competenciasPorDia.longitud()){

        // Recorro las competencias del dia
        j = 0;
        while(j < _competenciasPorDia.iesimo(i).longitud()){

            if(_competenciasPorDia.iesimo(i).iesimo(j).categoria() == cat){
                d = i;
                c = j;
            }

            j++;
        }

        i++;
    }

    // Genero los dias y sus cronogramas boicoteando lo que corresponda
    Lista<Lista<Competencia> > competenciasBoicoteadas = Lista<Lista<Competencia> >();
    i = 0;
    j = 0;

    while(i < _competenciasPorDia.longitud()){

        Lista<Competencia> competenciasDelDia = Lista<Competencia>();

        // Recorro las competencias del dia
        j = 0;
        while(j < _competenciasPorDia.iesimo(i).longitud()){

            // Si llego a la competencia para modificar, realizo el boicot
            if(d==i && c==j){

                // Si esta finalizada, boicot de participantes, ranking y doping
                if(_competenciasPorDia.iesimo(i).iesimo(j).finalizada()){

                    Lista<Atleta > preParticipantes = _competenciasPorDia.iesimo(i).iesimo(j).participantes();
                    Lista<Atleta > preRanking = _competenciasPorDia.iesimo(i).iesimo(j).ranking();
                    Lista<Atleta > preDoping = _competenciasPorDia.iesimo(i).iesimo(j).lesTocoControlAntidoping();
                    Deporte dep = _competenciasPorDia.iesimo(i).iesimo(j).categoria().first;
                    Sexo sex = _competenciasPorDia.iesimo(i).iesimo(j).categoria().second;

                    Lista<int > posiciones = filtrarPosiciones(preRanking, p);
                    Lista<pair<int,bool> > control = filtrarControl(_competenciasPorDia.iesimo(i).iesimo(j), p);

                    // Boicot
                    echados = quitarAtletas(preParticipantes, p);

                    Competencia comp(dep, sex, preParticipantes);
                    comp.finalizar(posiciones, control);
                    competenciasDelDia.agregarAtras(comp);


                // Si no solo de participantes
                }else{

                    // Competencia a reemplazar
                    Lista<Atleta > preParticipantes = _competenciasPorDia.iesimo(i).iesimo(j).participantes();
                    Deporte dep = _competenciasPorDia.iesimo(i).iesimo(j).categoria().first;
                    Sexo sex = _competenciasPorDia.iesimo(i).iesimo(j).categoria().second;

                    // Boicot
                    echados = quitarAtletas(preParticipantes ,p);

                    Competencia comp(dep, sex, preParticipantes);
                    competenciasDelDia.agregarAtras(comp);

                }

            }else{
                competenciasDelDia.agregarAtras(_competenciasPorDia.iesimo(i).iesimo(j));
            }

            j++;
        }

        // Agrego las competencias del dia
        competenciasBoicoteadas.agregarAtras(competenciasDelDia);

        i++;
    }

    _competenciasPorDia = competenciasBoicoteadas;

    return echados;
}

Lista<Atleta> JJOO::losMasFracasados(const Pais p) const
{
    int i=0;
    int h=0;
    int j=0;
    Lista <Competencia> compXdia= Lista <Competencia>();
    Competencia comp;
    Atleta a;
    pair <Atleta,int> atletaYrepeticiones= pair<Atleta,int>();
    Lista<pair<Atleta,int> > listAtletaYrepeticiones = Lista<pair<Atleta,int> >();
    Lista <Atleta> atletasDelPais = Lista <Atleta>();
    Lista <Atleta> atletasParticipantes = Lista <Atleta>();
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    Lista <Atleta> listaDeAtletasFracasados = Lista <Atleta>();
    Lista <Atleta> participaronMuchoYNoGanaronNada = Lista <Atleta>();
    while(i<this->_atletas.longitud()) // saco todos los atletas del pais p del jjoo
    {
        if(this->_atletas.iesimo(i).nacionalidad() == p)
        {
            atletasDelPais.agregar(this->_atletas.iesimo(i));
            i++;
        }
        else
        {
            i++;
        }
    }
    while( j< this->cantDias()) // saco todos los participantes del jjoo
    {
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            comp = compXdia.iesimo(h);
            atletasParticipantes.concatenar(comp.participantes());
            h++;
        }
        j++;
    }
    i=0;
    while(i<atletasDelPais.longitud()) //obtengo la cantidad de veces que participaron los atletas del pais p
    {
        atletaYrepeticiones.first = atletasDelPais.iesimo(i);
        atletaYrepeticiones.second= atletasParticipantes.cantidadDeApariciones(atletaYrepeticiones.first);
        if(listAtletaYrepeticiones.pertenece(atletaYrepeticiones)==false)
        {
        listAtletaYrepeticiones.agregar(atletaYrepeticiones);
        }
        i++;

    }
    listaDeAtletas= AtletaMasRepetidoEnTupla(listAtletaYrepeticiones); //obtengo los mas repetidos de la tupla
    i=0;
    while(i<listaDeAtletas.longitud()) // obtengo a los fracasados que participaron mas y no ganaron nada
    {
        a = listaDeAtletas.iesimo(i);
        j=0;
        while( j< this->cantDias())
        {
            compXdia = this->cronograma(j);
            h = 0;
            while(h< compXdia.longitud())
            {
                comp = compXdia.iesimo(h);
                if(comp.participantes().pertenece(a)== true)
                {
                   if(!(a== comp.ranking().iesimo(0) && a== comp.ranking().iesimo(1) && a== comp.ranking().iesimo(2)))
                    {
                        participaronMuchoYNoGanaronNada.agregar(a);
                    }
                    h++;
                }
                else
                {
                    h++;
                }

            }
        j++;
        }
        i++;
    }
    listAtletaYrepeticiones= Lista<pair<Atleta,int> >();
    i=0;
    while(i<participaronMuchoYNoGanaronNada.longitud()) //obtengo las repeticiones
    {
        atletaYrepeticiones.first = participaronMuchoYNoGanaronNada.iesimo(i);
        atletaYrepeticiones.second = participaronMuchoYNoGanaronNada.cantidadDeApariciones(atletaYrepeticiones.first);
        if(listAtletaYrepeticiones.pertenece(atletaYrepeticiones)==false)
        {
        listAtletaYrepeticiones.agregar(atletaYrepeticiones);
        }
        i++;
    }
    listaDeAtletasFracasados= AtletaMasRepetidoEnTupla(listAtletaYrepeticiones); //obtengo los mas repetidos de la tupla de los fracasados
    return listaDeAtletasFracasados;
}

void JJOO::liuSong(const Atleta& a, const Pais p)
{
    Atleta atNuevo( a.nombre(), a.sexo(), a.anioNacimiento(), p, a.ciaNumber());
    int j,h,i;
    Lista <Competencia> compXdia= Lista <Competencia>();
    Lista <Competencia> compXdiaNuevo= Lista <Competencia>();
    Lista<Lista<Competencia> > todasLasCompetencias = Lista<Lista<Competencia> >();
    Competencia comp;
    j=0;
    Lista <Atleta> atletaSacandoALiu = Lista<Atleta>();
    Lista<Atleta> todosLosAtletas = Lista<Atleta>();
    Lista<int> losDelRanking = Lista<int>();
    Lista<Atleta> atletasDelRanking = Lista<Atleta>();
    pair<int,bool> atletaDop = pair<int,bool>();
    Lista<pair<int,bool> >listaAtletaDop = Lista<pair<int,bool> >();
    while(j<a.deportes().longitud())
    {
        atNuevo.entrenarNuevoDeporte(a.deportes().iesimo(j),a.capacidad(a.deportes().iesimo(j)));
       j++;
    }
    j=0;
    while(j<this->_atletas.longitud())
    {
        if(a == this->_atletas.iesimo(j))
        {
            atletaSacandoALiu.agregar(atNuevo);
            j++;
        }
        else
        {
            atletaSacandoALiu.agregar(this->_atletas.iesimo(j));
            j++;
        }
    }
    atletaSacandoALiu.darVuelta();
    this->_atletas = Lista <Atleta>();
    this->_atletas = atletaSacandoALiu;
    j = 0;
    while( j< this->_competenciasPorDia.longitud())
        {
            compXdia = Lista<Competencia>();
            compXdia = this->_competenciasPorDia.iesimo(j);
            h = 0;
            while(h< compXdia.longitud())
            {
                comp = compXdia.iesimo(h);
                if(comp.participantes().pertenece(a))
                {
                    atletaSacandoALiu = Lista<Atleta>();
                    atletaSacandoALiu.concatenar(comp.participantes());
                    atletaSacandoALiu.sacar(a); // saco a liu
                    atletaSacandoALiu.agregar(atNuevo); // agrego al nuevo con el pais cambiado
                    Competencia compConLiuCambiada(comp.categoria().first, comp.categoria().second, atletaSacandoALiu);
                    if(comp.finalizada()== true) // SI ESTA FINALIZADA ARMO LAS LISTAS PARA FINALIZARLA
                    {
                        atletasDelRanking = comp.participantes();
                        losDelRanking = atCia(atletasDelRanking);
                        atletasDelRanking = Lista<Atleta>();
                        i =0;
                        listaAtletaDop = Lista<pair<int,bool> >();
                        while(i<comp.lesTocoControlAntidoping().longitud())
                        {
                            atletaDop.first = comp.lesTocoControlAntidoping().iesimo(i).ciaNumber();
                            atletaDop.second = comp.leDioPositivo(comp.lesTocoControlAntidoping().iesimo(i));
                            listaAtletaDop.agregarAtras(atletaDop);
                            i++;
                        }
                        compConLiuCambiada.finalizar(losDelRanking,listaAtletaDop); // LA FINALIZO
                    }
                    compXdiaNuevo.agregar(compConLiuCambiada); // AGREGO MI COMPETENCIA CON LIU CAMBIADA PARA IR INSERTANDO ORDENADAMENTE
                }
                else
                {
                    compXdiaNuevo.agregar(comp); // COMO NO ESTA LIU INSERTO LA COMPETENCIA COMO ESTABA SIN CAMBIAR
                }
                h++;
            }
            compXdiaNuevo.darVuelta(); // DOY VUELTA PARA MANTENER ORDEN ORIGINAL
        todasLasCompetencias.agregar(compXdiaNuevo); // AGREGO AL LISTAS DE LISTAS
        compXdiaNuevo = Lista<Competencia>();
        j++;
        }
this->_competenciasPorDia = Lista<Lista<Competencia> >();
todasLasCompetencias.darVuelta();
this->_competenciasPorDia = todasLasCompetencias;
}

Atleta JJOO::stevenBradbury() const
{
    int i = 0;
    Lista<pair <Atleta,pair <Deporte,Sexo> > > ganadoresPorCat = this->ganadoresPorCategoria();
    Lista<pair <Atleta,int > > atletasPorCapacidad = Lista<pair <Atleta,int > >();
    pair <Atleta,int > pairAtCap = pair <Atleta,int >();
    Deporte dep;
    Atleta steven;

    // Armo la lista de atletas con su capacidad al ganar la medalla de oro correspondiente
    while(i < ganadoresPorCat.longitud()){
        dep = ganadoresPorCat.iesimo(i).second.first;
        pairAtCap.first = ganadoresPorCat.iesimo(i).first;
        pairAtCap.second = ganadoresPorCat.iesimo(i).first.capacidad(dep);
        atletasPorCapacidad.agregar(pairAtCap);
        i++;
    }

    // Busco el atleta con menor capacidad de la lista anterior
    i = 0;
    int j = 0;
    bool menosCapaz = true;
    int capacidad = 0;
    int capacidad2 = 0;

    while(i < atletasPorCapacidad.longitud()){

        capacidad = atletasPorCapacidad.iesimo(i).second; // Tomo la capacidad del atleta para compararla

        while(j < atletasPorCapacidad.longitud()){
            capacidad2 = atletasPorCapacidad.iesimo(j).second; // Tomo la capacidad del atleta para compararla

            if(capacidad > capacidad2){
                menosCapaz = false;
            }

            j++;
        }

        // Si cuando termino de comparar encontre al atleta menos capaz, dejo de buscar
        if(menosCapaz){
            steven = atletasPorCapacidad.iesimo(i).first;
        }else{
            menosCapaz = true; // Si no lo encontre, preasumo que el siguiente va a ser para seguir con las comparaciones
        }

        i++;

    }

    return steven;
}

bool JJOO::uyOrdenadoAsiHayUnPatron() const
{
    int i,j,h;
    Pais p;
    Atleta a;
    Lista <Pais> mejoresPaisesDeCadaDia = Lista <Pais>();
    Lista <Pais> paisOro = Lista <Pais>();
    Pais mejorPaisDelDia;
    Lista<Competencia> compXdia = Lista<Competencia>();
    Lista<pair<Pais,int> > paisEnTupla =Lista<pair<Pais,int> >();
    Competencia comp;
    Lista <Pais> listaPatron = Lista<Pais>();
    bool terminarCiclo;
    bool hayPatron;
    i=0;
    while(i< this->cantDias())
    {
        compXdia = Lista<Competencia>();
        compXdia = this->cronograma(i);
        Lista <Pais> paisOro = Lista <Pais>();
        j = 0;
        while(j<compXdia.longitud())
        {
            comp = compXdia.iesimo(j);
            if(comp.finalizada()==true && comp.ranking().longitud()>0)
            {
                a = comp.ranking().iesimo(0);
                paisOro.agregar(a.nacionalidad());
            }
            j++;
        }
        if( paisOro.longitud()>0)
        {
        paisEnTupla = paisRep(paisOro);
        mejorPaisDelDia = mejorPais(paisEnTupla);
        mejoresPaisesDeCadaDia.agregar(mejorPaisDelDia);
        Lista <Pais> paisOro = Lista <Pais>();
        }
        i++;
    }
    mejoresPaisesDeCadaDia.darVuelta();
    p = mejoresPaisesDeCadaDia.iesimo(0);
    i=1;
    h=1;

    // obtengo cuando se repite el primer pais
    while(i<=mejoresPaisesDeCadaDia.longitud())
    {
        if(!(p == mejoresPaisesDeCadaDia.iesimo(i)))
        {
            h++;
            i++;
        }
        else
        {
            i= mejoresPaisesDeCadaDia.longitud()+1;
        }
    }
    i=0;
    j=0;

    // obtengo bajando h mi lista patron
    while(i<mejoresPaisesDeCadaDia.longitud())
    {
        if(h>0)
        {
        listaPatron.agregar(mejoresPaisesDeCadaDia.iesimo(i));
        i++;
        h--; // h es mi contador de lugares de patron
        }
        else
        {
            i=mejoresPaisesDeCadaDia.longitud();
        }
    }
    i=0;
    j=0;
    while(i<mejoresPaisesDeCadaDia.longitud() && !terminarCiclo)
    {
        if(listaPatron.longitud() == mejoresPaisesDeCadaDia.longitud()) // si son iguales las long significa q no encontro igualdad x ende true
        {
            hayPatron = true;
            terminarCiclo = true;
        }
        else
        {
        if(listaPatron.longitud()< mejoresPaisesDeCadaDia.longitud()) // si es menor, recorro la listas y cuando j = longitud la mando a cero y vuelve a empezar
        {
            if(mejoresPaisesDeCadaDia.iesimo(i)== listaPatron.iesimo(j))
            {
                i++;
                if(j== listaPatron.longitud())
                {
                    j=0;
                }
                else
                {
                    j++;
                }
            }
            else
            {
                hayPatron = false;
                terminarCiclo = true;
            }
        }
        }
    }
    if(i==mejoresPaisesDeCadaDia.longitud())
    {
        hayPatron = true;
    }
    return hayPatron;
}

Lista<Pais> JJOO::sequiaOlimpica() const
{
    Lista<Pais> todosLosPaises = this->paises();
    Lista<Pais> paisesSecos = Lista<Pais>();
    int j = 0;
    while(todosLosPaises.longitud() > j){
        if(this->masDiasSinMedallas(todosLosPaises.iesimo(j)) == this->maxDiasSinMedallas(todosLosPaises)){
            paisesSecos.agregar(todosLosPaises.iesimo(j));
        }
        j++;
    }

    return paisesSecos;
}

bool JJOO::operator==(const JJOO& j) const
{
    bool res = true;
    int dias = 0;
    if(this->_anio == j._anio && this->_jornadaActual == j._jornadaActual && this->cantDias()==j.cantDias() && mismos(this->_atletas,j._atletas)){
        dias = this->cantDias();
        bool sonMismos = true;
        while(dias > 0 && sonMismos){
            if(!mismos(this->_competenciasPorDia.iesimo(dias),j._competenciasPorDia.iesimo(dias))){
                sonMismos = false;
                res = false;
            }
            dias--;
        }
    }
    else{
        res = false;
    }
    return res;
}


void JJOO::mostrar(std::ostream& os) const
{
    os << "J " << this->anio() << " " << this->jornadaActual() << endl;
    os << "[(";
    int i = 0;
    int j = 0;
    int h = 0;
    Competencia comp;
    Atleta a;
    Lista <Competencia> compXdia = Lista<Competencia>();
    while(i < this->atletas().longitud())
    {
        a = this->atletas().iesimo(i);
        if (i < this->atletas().longitud()-1)
        {
            a.mostrar(os);
            os << "),(";
            i++;
        }
        else
        {
            a.mostrar(os);
            os << ")";
            i++;
        }
    }
    os << "]" << endl;
    os << "[";
    while( j< this->cantDias())
    {
        os << "[";
        compXdia = this->cronograma(j);
        h = 0;
        while(h< compXdia.longitud())
        {
            os << "(";
            if(h< compXdia.longitud()-1)
            {
                comp = compXdia.iesimo(h);
                comp.mostrar(os);
                os << "),";
                h++;
            }
            else
            {
                comp = compXdia.iesimo(h);
                comp.mostrar(os);
                os << ")";
                h++;
            }
        }
        if(j< this->cantDias()-1)
        {
            os << "],";
            j++;
        }
        else
        {
            os << "]]";
            j++;
        }
    }

}

void JJOO::guardar(std::ostream& os) const
{
        this->mostrar(os);
}

void JJOO::cargar (std::istream& is)
{
    char c;
    Atleta a;
    Competencia comp;
    Lista<Competencia> listComp= Lista<Competencia>();
    is >> c; // Saco la J
    is >> this->_anio;
    is >> this->_jornadaActual;
    is >> c; //Saco el [ de la lista de atletas
    is >> c;
    while(c == '(')
    {
    a.cargar(is) ;
    this->_atletas.agregar(a);
    is >> c; // saco parentesis q cierra
    is >> c; // saco coma o corchete q cierra
    if (c == ',')
    {
    is >> c; // saco (
    }

    }
    _atletas.darVuelta();
    is >> c; // saco corchete
    is >> c; // saco corchete
    while(c=='[')
    {
        is >> c;

        while(c== '(')
        {
            comp = Competencia();
            comp.cargar(is);
            listComp.agregarAtras(comp);
            is >> c; //saco el parentesis
            if(is.peek() == ','){
                is >> c; //saco la coma
                is >> c;
            }else{
                is >> c; //saco ( o ]
            }

        }

        is >> c; //saco la coma
        is >> c;

        _competenciasPorDia.agregar(listComp);

        listComp= Lista<Competencia>();

    }

    _competenciasPorDia.darVuelta();

}

/* ==================================== AUXILIARES ========================================= */

Lista<int> JJOO::atCia(const Lista<Atleta>& a)
{
    int i=0;
    Lista<int> listaDeCia = Lista<int>();
    while(i<a.longitud())
    {
        listaDeCia.agregarAtras(a.iesimo(i).ciaNumber());
        i++;
    }
    return listaDeCia;
}

//------------------------------

Lista<pair <Atleta,pair <Deporte,Sexo> > > JJOO::ganadoresPorCategoria() const
{
    int dia = 0;
    int c = 0;
    pair <Atleta,pair <Deporte,Sexo> > ganadorPorCat = pair <Atleta,pair <Deporte,Sexo> > ();
    Lista<Competencia> competenciasList = Lista<Competencia>();
    Lista<pair <Atleta,pair <Deporte,Sexo> > > ganadoresPorCat = Lista<pair <Atleta,pair <Deporte,Sexo> > >();

    // Recorro las jornadas
    while(dia < this->_competenciasPorDia.longitud()){

        // Recorro las competencias del dia
        c = 0;
        competenciasList = this->_competenciasPorDia.iesimo(dia);
        while(c < competenciasList.longitud()){

            if(competenciasList.iesimo(c).finalizada() && competenciasList.iesimo(c).ranking().longitud() > 0){
                ganadorPorCat.first = competenciasList.iesimo(c).ranking().iesimo(0); // Guardo al ganador de ORO
                ganadorPorCat.second = competenciasList.iesimo(c).categoria(); // Guardo la categoria
                ganadoresPorCat.agregar(ganadorPorCat);
            }

            c++;
        }
        // Fin competencias del dia

        dia++;
    }
    // Fin de jornadas

    return ganadoresPorCat;

}

// -------------------- Auxiliar para obtener el maximo repetido
Lista<Atleta>JJOO::AtletaMasRepetidoEnTupla(Lista<pair<Atleta,int> >& a) const
{
    pair <Atleta,int> atletaYrepeticiones= pair<Atleta,int>();
    Lista <Atleta> listaDeAtletas = Lista <Atleta>();
    int i=0;
    int j =0;
    while(i<a.longitud()) // obtengo atletas mas repetidos de la lista
    {
        atletaYrepeticiones.second =a.iesimo(i).second;
        atletaYrepeticiones.first =a.iesimo(i).first;
        j=0;

            while(j< a.longitud() && atletaYrepeticiones.second <= a.iesimo(j).second )
            {
                j++;
            }
        if(j== a.longitud())
        {
            listaDeAtletas.agregar(atletaYrepeticiones.first);
            i++;
        }
        else
        {
            i++;
        }
    }
    return listaDeAtletas;
}

//---------------------Auxiliar medallero

pair<Pais,int> JJOO::paisMedallero(Pais p, Lista<Pais> paisConMed, Lista<pair<Pais,int> > paisConInt) const
{
    int j;
    pair <Pais,int> paisCantidadDeMedallas = pair<Pais,int> ();
    if(paisConMed.pertenece(p))
        {
            j=0;
            while(j<paisConInt.longitud())
            {
                if(p == paisConInt.iesimo(j).first)
                {
                    paisCantidadDeMedallas.first =p;
                    paisCantidadDeMedallas.second= paisConInt.iesimo(j).second;
                    j = paisConInt.longitud();
                }
                else
                {
                    j++;
                }

            }
        }
    else
    {
        paisCantidadDeMedallas.first = p;
        paisCantidadDeMedallas.second = 0;
    }
    return paisCantidadDeMedallas;
}

Lista<pair<Pais,int> > JJOO::paisRep(Lista<Pais>& p) const
{
    int i=0;
    Lista<pair<Pais,int> > paisesYRepeticiones = Lista<pair<Pais,int> >();
    pair<Pais,int> paisYRep= pair<Pais,int>();
    while(i<p.longitud())
    {
        paisYRep.first = p.iesimo(i);
        paisYRep.second = p.cantidadDeApariciones(paisYRep.first);
        if(paisesYRepeticiones.pertenece(paisYRep)==false)
        {
            paisesYRepeticiones.agregar(paisYRep);
        }
        i++;
    }
    return paisesYRepeticiones;
}

Lista<pair<Pais,Lista<int> > > JJOO::ordenarMedallero(Lista<pair<Pais,Lista<int> > >& medallero) const
{
    Lista<pair<Pais,Lista<int> > > paisesYMedallas = Lista<pair<Pais,Lista<int> > >();
    int p;
    int i;
    int j;
    pair <Pais,Lista<int> > pais= pair <Pais,Lista<int> >();
    i = 0;
    p = 0;
    while (i < medallero.longitud())
    {
        pais = medallero.iesimo(i);
        j = i+1;
        p = i;
        while (j < medallero.longitud())
        {

            if(pais.second.iesimo(0) == medallero.iesimo(j).second.iesimo(0)) //si son mismo oro matchea plata
            {
                if(pais.second.iesimo(1) == medallero.iesimo(j).second.iesimo(1)) //si son mismo plata matcheo bronze
                {
                    if(pais.second.iesimo(2) >= medallero.iesimo(j).second.iesimo(2)) //matchea bronce, si son iguales deja el primero
                    {
                        j++;
                    }
                    else
                    {
                        pais = medallero.iesimo(j);
                        p = j;
                        j++;
                    }
                }
                else
                {
                    if( pais.second.iesimo(1) > medallero.iesimo(j).second.iesimo(1)) // matchea plata
                    {
                        j++;
                    }
                    else
                    {
                        pais = medallero.iesimo(j);
                        p = j;
                        j++;
                    }
                }
            }
            else
            {
                if( pais.second.iesimo(0) > medallero.iesimo(j).second.iesimo(0)) // matchea oro
                {
                    j++;
                }
                else
                {
                    pais = medallero.iesimo(j);
                    p = j;
                    j++;
                }
            }
        }


    paisesYMedallas.agregarAtras(medallero.iesimo(p));
    medallero.eliminarPosicion(p);
    i = 0 ;
    }
    return paisesYMedallas;
}

//---------------------------UyOrdenadoAsiHayPatron

Pais JJOO::mejorPais(Lista<pair<Pais,int> >& p) const
{
    pair <Pais,int> paisYrepeticiones= pair<Pais,int>();
    Lista <Pais> listaDePaises = Lista <Pais>();
    int i=0;
    int j =0;
    bool terminoCiclo;
    while(i<p.longitud() && !terminoCiclo) // obtengo pais mas repetidos de la lista
    {
        paisYrepeticiones.second =p.iesimo(i).second;
        paisYrepeticiones.first =p.iesimo(i).first;
        j=i+1;
        while(j<=p.longitud())
        {
            if(paisYrepeticiones.second> p.iesimo(j).second)
            {
                j++;
            }
            if(paisYrepeticiones.second == p.iesimo(j).second)
            {
                if(paisYrepeticiones.first > p.iesimo(j).first)
                {
                    j++;
                }
                else
                {
                    j=p.longitud()*2; // lo hago salir del while
                }
            }
            else
            {
                j=p.longitud()*2;
            }
        }
        if(j==p.longitud())
        {
            terminoCiclo =true;
        }
        else
        {
            i++;
        }
    }

    return paisYrepeticiones.first;
}

//-----------------

int JJOO::masDiasSinMedallas(const Pais p) const
{
    int dia = this->jornadaActual();
    Lista<int> diasSinMedallas = Lista<int>();
    diasSinMedallas.agregar(this->jornadaActual());
    dia = dia - 1;
    while(dia > 0){
        if(this->ganoMedallaEseDia(this->cronograma(dia),p)){
            diasSinMedallas.agregar(dia);
        }
        dia--;
    }

    diasSinMedallas.darVuelta();

    Lista<int> diferencias = Lista<int>();
    while(diasSinMedallas.longitud()>1){
        diferencias.agregar(diasSinMedallas.iesimo(1) - diasSinMedallas.iesimo(0));
        diasSinMedallas.cola();
    }

    while(diferencias.longitud() > 1){
        if(diferencias.iesimo(0) > diferencias.iesimo(1)){
            diferencias.sacar(diferencias.iesimo(1));
        }
        else{
            if(diferencias.iesimo(0) < diferencias.iesimo(1)){
            diferencias.sacar(diferencias.iesimo(0));
            }
            else{
                diferencias.cola();
            }
        }
    }

    return diferencias.iesimo(0);
}

bool JJOO::ganoMedallaEseDia(const Lista<Competencia>& comp,const Pais p) const
{
    bool res = false;
    int i = 0;
    while(i < comp.longitud() && !res){
        Competencia comp1 = comp.iesimo(i);
        Atleta atletaOro;
        Atleta atletaPlata;
        Atleta atletaBronce;
        if(comp1.ranking().longitud() >=1){
            atletaOro = comp1.ranking().iesimo(0);
            if(p == atletaOro.nacionalidad()){
                res = true;
            }
        }
        if(comp1.ranking().longitud() >=2){
            atletaPlata = comp1.ranking().iesimo(1);
            if(p == atletaOro.nacionalidad() || p == atletaPlata.nacionalidad()){
                res = true;
            }
        }
        if(comp1.ranking().longitud() >=3){
            atletaBronce = comp1.ranking().iesimo(2);
            if(p == atletaOro.nacionalidad() || p == atletaPlata.nacionalidad() || p == atletaBronce.nacionalidad()){
                res = true;
            }
        }

        i++;
    }
    return res;
}

int JJOO::maxDiasSinMedallas(const Lista<Pais>& pais) const
{
    Lista<Pais> p = pais;

     while(p.longitud() > 1){
        if(this->masDiasSinMedallas(p.iesimo(0)) > this->masDiasSinMedallas(p.iesimo(1))){
            p.sacar(p.iesimo(1));
        }
        else{
            if(this->masDiasSinMedallas(p.iesimo(0)) < this->masDiasSinMedallas(p.iesimo(1))){
            p.sacar(p.iesimo(0));
            }
        }
    }
    return this->masDiasSinMedallas(p.iesimo(0));
}

Lista<Pais> JJOO::paises() const
{
Lista<Atleta> todosLosAtletas = this->atletas();
Lista<Pais> todosLosPaises = Lista<Pais>();
int i=0;
    while(todosLosAtletas.longitud() > i)
    {
        if(!todosLosPaises.pertenece(todosLosAtletas.iesimo(i).nacionalidad()))
        {
            todosLosPaises.agregar(todosLosAtletas.iesimo(i).nacionalidad());
        }
        i++;
    }
return todosLosPaises;
}

void JJOO::transcurrirDia()
{
    Lista<Lista<Competencia> > competenciasDelDia = Lista<Lista<Competencia> >();
    Lista<Competencia> competenciasActuales = _competenciasPorDia.iesimo(_jornadaActual-1);
    Lista<Competencia> competenciasModificadas = Lista<Competencia>();
    int i = 0;
    while(competenciasActuales.longitud() > i){
        Competencia comp = competenciasActuales.iesimo(i);
        if(!comp.finalizada()){
            comp.finalizar(this->crearRanking(comp.participantes(),comp.categoria().first),this->crearControl(comp.participantes().iesimo(0),true));
            competenciasModificadas.agregar(comp);
        }
        else{
            competenciasModificadas.agregar(competenciasActuales.iesimo(i));
        }
        i++;
    }
    int j = 0;
    while(_competenciasPorDia.longitud() > j){
        if(j == (_jornadaActual-1)){
            competenciasDelDia.agregarAtras(competenciasModificadas);
        }
        else{
            competenciasDelDia.agregarAtras(_competenciasPorDia.iesimo(j));
        }
        j++;
    }
    _competenciasPorDia = Lista<Lista<Competencia> >();
    _competenciasPorDia = competenciasDelDia;

    if((_jornadaActual) < this->cantDias()){
    _jornadaActual = _jornadaActual + 1;
    }
}

//----------------AUXILIARES TRANSCURRIR DIA--------------
Lista<int> JJOO::crearRanking(const Lista<Atleta>& participant,const Deporte& d) const
{
    Lista<int> posiciones = Lista<int>();
    Lista<Atleta> particip = participant;
    while(particip.longitud() > 0){
        int i = 0;
        int j = 1;

        while(j < particip.longitud()){
            Atleta participante1 = particip.iesimo(i);
            Atleta participante2 = particip.iesimo(j);
            if(participante1.capacidad(d) >= participante2.capacidad(d)){
                j++;
            }
            else{
                i = j;
                j++;
            }
        }
        Atleta participanteFinal = particip.iesimo(i);
        int number = participanteFinal.ciaNumber();
        posiciones.agregar(number);
        particip.sacar(participanteFinal);
        j = 1;
        i = 0;
    }
    return posiciones;
}

Lista<pair<int,bool> > JJOO::crearControl(const Atleta& a, bool b)const
{
    Lista<pair<int,bool> > result = Lista<pair<int,bool> >();
    pair<int,bool> item = pair<int,bool>();
    item.first = a.ciaNumber();
    item.second = b;
    result.agregar(item);
    return result;
}

int JJOO::quitarAtletas(Lista<Atleta >& atletas, const Pais& p)
{
    int i = 0;
    int echados = 0;

    while(i < atletas.longitud()){

        if(atletas.iesimo(i).nacionalidad() == p){
            atletas.sacar(atletas.iesimo(i));
            echados++;
        }

        i++;
    }

    return echados;
}

Lista<int > JJOO::filtrarPosiciones(Lista<Atleta >& atletas, const Pais& p)
{
    int i = 0;
    Lista<int > posiciones = Lista<int >();

    while(i < atletas.longitud()){

        if(atletas.iesimo(i).nacionalidad() != p){
            posiciones.agregarAtras(atletas.iesimo(i).ciaNumber());
        }

        i++;
    }

    return posiciones;
}

Lista<pair<int,bool> > JJOO::filtrarControl(const Competencia& comp, const Pais& p)
{
    int i = 0;
    Lista<pair<int,bool> > doping = Lista<pair<int,bool> >();

    while(i < comp.lesTocoControlAntidoping().longitud()){

        if(comp.lesTocoControlAntidoping().iesimo(i).nacionalidad() != p){
            doping.agregarAtras(pair<int,bool>(comp.lesTocoControlAntidoping().iesimo(i).ciaNumber(), comp.leDioPositivo(comp.lesTocoControlAntidoping().iesimo(i))));
        }

        i++;
    }

    return doping;

}
