#ifndef TEST_DATA_H
#define TEST_DATA_H

typedef Lista<Lista<Competencia> > Calendario;

class TestData {

  public:
    TestData() {
      generarAtletas();
      generarCompetencias();
      generarCalendarios();
      generarPaises();
    }

    void generarAtletas() {
      la = Lista<Atleta>();
      at1 = Atleta("Juan", Masculino, 20, "Argentina",1);
      at2 = Atleta("Jorge", Masculino, 30, "Argentina",2);
      at3 = Atleta("Juliana", Femenino, 32, "Bosnia",3);
      at4 = Atleta("Jenny", Femenino, 22, "USA",4);
      at5 = Atleta("Jordan", Masculino, 30, "USA",5);
      at6 = Atleta("Jackson", Masculino, 35, "Escocia",6);
      at1.entrenarNuevoDeporte("Football", 35);
      at1.entrenarNuevoDeporte("Rugby", 10);
      at2.entrenarNuevoDeporte("Football", 32);
      at2.entrenarNuevoDeporte("Rugby", 20);
      at3.entrenarNuevoDeporte("Handball", 50);
      at4.entrenarNuevoDeporte("Softball", 20);
      at5.entrenarNuevoDeporte("Football", 40);
      at5.entrenarNuevoDeporte("Rugby", 5);
      at5.entrenarNuevoDeporte("Basket", 25);
      at6.entrenarNuevoDeporte("Football", 40);
      at6.entrenarNuevoDeporte("Rugby", 5);
      at6.entrenarNuevoDeporte("Basket", 25);
      la.agregarAtras(at1);
      la.agregarAtras(at2);
      la.agregarAtras(at3);
      la.agregarAtras(at4);
      la.agregarAtras(at5);
      la.agregarAtras(at6);
    }

    void generarCompetencias() {
      lc = Lista<Competencia>();
      c1 = Competencia("Rugby", Masculino, sublist(la, "0 1 5"));
      c2 = Competencia("Football", Masculino, sublist(la, "0 1"));
      c3 = Competencia("Handball", Femenino, sublist(la, "2"));
      c4 = Competencia("Softball", Femenino, Lista<Atleta>());
      lc.agregarAtras(c1);
      lc.agregarAtras(c2);
      lc.agregarAtras(c3);
      lc.agregarAtras(c4);

      c1f = Competencia("Rugby", Masculino, sublist(la, "0 1 5"));
      c2f = Competencia("Football", Masculino, sublist(la, "0 1"));
      c3f = Competencia("Handball", Femenino, sublist(la, "2"));
      c4f = Competencia("Softball", Femenino, Lista<Atleta>());
      Lista<pair<Atleta, bool> > ctrl;
      // c1f.finalizar(sublist(la, "0"), ctrl);
      // c2f.finalizar(sublist(la, "0"), ctrl);
      // c3f.finalizar(sublist(la, "2"), ctrl);
      // c4f.finalizar(Lista<Atleta>(), ctrl);
      lcf = Lista<Competencia>();
      lcf.agregarAtras(c1f);
      lcf.agregarAtras(c2f);
      lcf.agregarAtras(c3f);
      lcf.agregarAtras(c4f);
    }

    void generarCalendarios() {
      cc1.agregarAtras(sublist(lc, "0 1"));
      cc1.agregarAtras(Lista<Competencia>());
      cc1.agregarAtras(sublist(lc, "2 3"));
      cc1.agregarAtras(Lista<Competencia>());

      cc2.agregarAtras(sublist(lcf, "0")); //patron == False
      cc2.agregarAtras(sublist(lcf, "1"));
      cc2.agregarAtras(sublist(lcf, "2"));
      cc2.agregarAtras(sublist(lcf, "3"));
      cc2.agregarAtras(Lista<Competencia>());

      cc3.agregarAtras(sublist(lcf, "0")); //patron == True
      cc3.agregarAtras(sublist(lcf, "3"));
      cc3.agregarAtras(sublist(lcf, "0"));
      cc3.agregarAtras(sublist(lcf, "0"));
      cc3.agregarAtras(Lista<Competencia>());

      cc4.agregarAtras(sublist(lcf, "2")); //patron == True
      cc4.agregarAtras(sublist(lcf, "1"));
      cc4.agregarAtras(sublist(lcf, "3"));
      cc4.agregarAtras(sublist(lcf, "1"));
      cc4.agregarAtras(Lista<Competencia>());

      cc5.agregarAtras(sublist(lcf, "1")); //patron == False
      cc5.agregarAtras(sublist(lcf, "1"));
      cc5.agregarAtras(sublist(lcf, "3"));
      cc5.agregarAtras(sublist(lcf, "2"));
      cc5.agregarAtras(Lista<Competencia>());

      cc6.agregarAtras(sublist(lc, "1"));
      cc6.agregarAtras(sublist(lc, "0"));
      cc6.agregarAtras(sublist(lc, "2"));
      cc6.agregarAtras(sublist(lc, "3"));
      cc6.agregarAtras(Lista<Competencia>());
    }

    void generarPaises() {
      lps = Lista<Pais>();
      lps.agregarAtras("Argentina");
      lps.agregarAtras("Bosnia");
      lps.agregarAtras("USA");
      lps.agregarAtras("Escocia");
    }

    Lista<Atleta> la;
    Lista<Competencia> lc;
    Lista<Competencia> lcf;

    //Atletas
    Atleta at1;
    Atleta at2;
    Atleta at3;
    Atleta at4;
    Atleta at5;
    Atleta at6;

    //Competencias
    Competencia c1;
    Competencia c2;
    Competencia c3;
    Competencia c4;

    Competencia c1f;
    Competencia c2f;
    Competencia c3f;
    Competencia c4f;


    //Calendarios
    Calendario cc1;
    Calendario cc2;
    Calendario cc3;
    Calendario cc4;
    Calendario cc5;
    Calendario cc6;

    Lista<Pais> lps;



};

// #define at1 td.la.iesimo(0)
// #define at2 td.la.iesimo(1)
// #define at3 td.la.iesimo(2)
// #define at4 td.la.iesimo(3)
// #define at5 td.la.iesimo(4)
// #define at6 td.la.iesimo(5)

#endif
