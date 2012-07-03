#include <sstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <algorithm>

#include "atleta.h"
#include "competencia.h"
#include "jjoo.h"
#include "generics.h"
#include "testData.h"

#define A_TEST_FILE "atleta.txt"
#define C_TEST_FILE "competencia.txt"
#define J_TEST_FILE "jjoo.txt"

using namespace std;

Lista<int> ciaNumbers(Lista<Atleta> &ats){
    Lista<int> ret;
    int i=0;
    while(i<ats.longitud()){
        ret.agregarAtras(ats.iesimo(i).ciaNumber());
        i++;
    }
    return ret;
}

Lista<pair<int, bool> > controlados(Lista<pair<Atleta,bool> > &ctrls){
    Lista<pair<int, bool> > ret;
    int i=0;
    while(i<ctrls.longitud()){
        ret.agregarAtras(pair<int, bool>(ctrls.iesimo(i).first.ciaNumber(),ctrls.iesimo(i).second));
        i++;
    }
    return ret;
}


bool isSpace(char c) {
    return c == ' ' or c == '\t' or c == '\n';
}

template<typename T>
void asegurar(const T& t, string s, bool ignorarBlancos = true) {
    ostringstream out;
    out << t;
    string st = out.str();
    if(ignorarBlancos) remove_if(st.begin(), st.end(), isSpace);
    if(ignorarBlancos) remove_if(s.begin(), s.end(), isSpace);
    if (st != s) {
        cerr << "Ooops..." << s << " != " << out.str() << endl;
        //cerr << "false" << endl;
        //assert(false);
    }
    else
        cerr << "OK." << endl;
}

template<typename T, typename R>
void asegurar(string s, const T& t, const R& r, bool ignorarBlancos = true) {
    ostringstream out;
    out << r;
    //cerr << t << " == " << r << ": " ;
    cerr << s << ": ";
    asegurar(t, out.str(), ignorarBlancos);
}

int atletasDePais(const JJOO& j, int dia, int nroComp, string pais) {
  int count = 0;
  bool m = true;
  Lista<Atleta> ca;
  const Lista<Competencia>& tlc = (j.cronograma(dia));
  const Lista<Atleta>& tla = (tlc.iesimo(nroComp).participantes());
  for (int i = 0; i < tla.longitud(); i++)
    if (tla.iesimo(i).nacionalidad() == pais) {
      count++;
      ca.agregarAtras(tla.iesimo(i));
    }

  const Competencia& c = tlc.iesimo(nroComp);
  if (c.finalizada()) {
    for (int i = 0; i < c.ranking().longitud(); i++) {
      if (c.ranking().iesimo(i).nacionalidad() == pais) {
        m = m && ca.pertenece(c.ranking().iesimo(i));
      }
    }
    for (int i = 0; i < c.lesTocoControlAntidoping().longitud(); i++) {
      if (c.lesTocoControlAntidoping().iesimo(i).nacionalidad() == pais) {
        m = m && ca.pertenece(c.lesTocoControlAntidoping().iesimo(i));
      }
    }
  }
  return (m) ? count : -1;
}

void testAtleta() {
  Atleta at1 = Atleta("Juan", Masculino, 20, "Argentina", 1);
  Atleta at2 = Atleta("Juan", Masculino, 20, "Argentina", 1);
  Atleta at3 = Atleta("Ivonne", Femenino, 25, "Rusia", 3);

  asegurar("at1 != at2", at1 == at2, true);
  asegurar("at1 != at3", at1 == at3, false);

  at1.entrenarNuevoDeporte("Rugby", 5);
  asegurar("at1 != at2", at1 == at2, false);
  at2.entrenarNuevoDeporte("Rugby", 5);
  asegurar("at1 == at2", at1 == at2, true);
  at1.entrenarNuevoDeporte("Football", 3);
  at2.entrenarNuevoDeporte("Football", 2);

  asegurar("at1 != at2", at1 == at2, false);
  asegurar("at1.deportes() == [Football, Rugby]", at1.deportes(), "[Football,Rugby]");
  asegurar("at2.deportes() == [Football, Rugby]", at2.deportes(), "[Football,Rugby]");
  asegurar("at3.deportes() == [Football, Rugby]", at3.deportes(), "[]");

  string listDeporte[] = {"B", "D", "C", "E", "A"};
  for (int i = 0; i < 5; i++) {
    at3.entrenarNuevoDeporte(listDeporte[i], i+1);
  }
  asegurar("at1.deportes() == [A,B,C,D,E]", at3.deportes(), "[A,B,C,D,E]");

  for (int i = 0; i < 5; i++) {
    ostringstream out;
    out << "at3.capacidad(listDeporte[" << i << "]) == " << i + 1;
    asegurar(out.str(), at3.capacidad(listDeporte[i]) == i+1, true);
  }


  //Testeando IO
  ofstream of;
  ifstream inf;

  Atleta at4 = Atleta("Juliana", Femenino, 32, "China", 4);
  of.open(A_TEST_FILE);
  at4.guardar(of);
  of.close();

  inf.open(A_TEST_FILE);
  Atleta at5;
  at5.cargar(inf);
  inf.close();

  asegurar("at4 == at5", at4 == at5, true);

  at4.entrenarNuevoDeporte("C", 3);
  of.open(A_TEST_FILE);
  at4.guardar(of);
  of.close();

  inf.open(A_TEST_FILE);
  at5.cargar(inf);
  inf.close();

  asegurar("at4 == at5", at4 == at5, true);
  at4.entrenarNuevoDeporte("C", 2);
  asegurar("at4 != at5", at4 == at5, false);
  at4.entrenarNuevoDeporte("C", 3);
  asegurar("at4 == at5", at4 == at5, true);

  at4.entrenarNuevoDeporte("A", 100);
  of.open(A_TEST_FILE);
  at4.guardar(of);
  of.close();

  inf.open(A_TEST_FILE);
  at5.cargar(inf);
  inf.close();

  asegurar("at4 == at5", at4 == at5, true);
}


void testCompetencia() {
  TestData td;

  Lista<Atleta>& la = td.la;
  Lista<Atleta> sla;
  Lista<pair<Atleta, bool> > dop;
  Competencia c1 = Competencia();
  asegurar("not c1.finalizada()", c1.finalizada(), false);
  // asegurar(c1.participantes(), "[]");
  c1 = Competencia("Rugby", Masculino, sublist(la, "0 5 1"));

  Competencia c2 = Competencia("Rugby", Masculino, sublist(la, "0 1 5"));

  asegurar("not c2.finalizada()", c2.finalizada(), false);
  // asegurar(c2.participantes(), sublist(la, "1 2 6"));
  asegurar("c1 == c2", c1 == c2, true);

  //Testeo IO para no finalizada
  ofstream of;
  of.open(C_TEST_FILE);
  c1.guardar(of);
  of.close();

  ifstream inf;
  inf.open(C_TEST_FILE);
  Competencia c6;
  c6.cargar(inf);
  inf.close();
  asegurar("c6 == c1", c6 == c1, true);


  sla = sublist(la, "0 5");
  c1.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c1 != c2", c1 == c2, false);

  sla = sublist(la, "0 1");
  c2.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c1 != c2", c1 == c2, false);

  Competencia c3 = Competencia("Rugby", Masculino, sublist(la,"0 1 5"));
  sla = sublist(la, "0 5");
  c3.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c1 == c3", c1 == c3, true);


  //Testeo IO para ranking no vacío
  of.open(C_TEST_FILE);
  c3.guardar(of);
  of.close();

  inf.open(C_TEST_FILE);
  c6.cargar(inf);
  inf.close();
  asegurar("c6 == c3", c6 == c3, true);

  Lista<pair<Atleta, bool> > ld4;
  ld4.agregarAtras(pair<Atleta, bool>(td.at1, true));
  ld4.agregarAtras(pair<Atleta, bool>(td.at6, false));
  Competencia c4 = Competencia("Rugby", Masculino, sublist(la,"0 1 5"));
  sla = sublist(la, "0 5");
  c4.finalizar(ciaNumbers(sla), controlados(ld4));

  Lista<pair<Atleta, bool> > ld5;
  ld5.agregarAtras(pair<Atleta, bool>(td.at1, true));
  ld5.agregarAtras(pair<Atleta, bool>(td.at6, true));
  Competencia c5 = Competencia("Rugby", Masculino, sublist(la,"0 1 5"));
  sla = sublist(la, "0 5");
  c5.finalizar(ciaNumbers(sla), controlados(ld5));

  asegurar("c4 == c5", c4 == c5, false);

  //Testeo IO para control no vacío
  of.open(C_TEST_FILE);
  c5.guardar(of);
  of.close();

  inf.open(C_TEST_FILE);
  c6.cargar(inf);
  inf.close();
  asegurar("c6 == c5", c6 == c5, true);

  // Linford Christie
  Competencia c7("Handball", Femenino, sublist(td.la, "2"));
  asegurar("mismos(c7.participantes(), sublist(td.la, '2'))", mismos(c7.participantes(), sublist(td.la, "2")), true);
  c7.linfordChristie(td.at3.ciaNumber());
  asegurar("c7.participantes() == []", c7.participantes(), "[]");

  Competencia c8("Football", Masculino, sublist(td.la, "0 1"));
  asegurar("mismos(c8.participantes(), sublist(td.la, '0 1'))", mismos(c8.participantes(), sublist(td.la, "0 1")), true);
  c8.linfordChristie(td.at1.ciaNumber());
  asegurar("mismos(c8.participantes(), sublist(td.la, '1'))", mismos(c8.participantes(), sublist(td.la, "1")), true);

  // Sancionar Tramposos
  Competencia c9 = c3;
  c3.sancionarTramposos();
  asegurar("c3 == c9", c3 == c9, true);
  c4.sancionarTramposos();
  asegurar("c4.ranking() == sublist(td.la, '5')", c4.ranking() == sublist(td.la, "5"), true);
  c5.sancionarTramposos();
  asegurar("c5.ranking() == Lista<Atleta>()", c5.ranking(), Lista<Atleta>());
  Competencia c10("Softball", Femenino, sublist(td.la, "3"));
  sla = Lista<Atleta>();
  dop = Lista<pair<Atleta, bool> >();
  c10.finalizar(ciaNumbers(sla), controlados(dop));
  c10.sancionarTramposos();
  asegurar("c10.ranking() == Lista<Atleta>()", c10.ranking(), Lista<Atleta>());

  // Mas Mejores
  c10 = Competencia("Football", Masculino, sublist(td.la, "0 1 5"));
  sla = sublist(td.la, "5 0 1");
  c10.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c10.gananLosMasCapaces()", c10.gananLosMasCapaces(), true);

  Competencia c11("Football", Masculino, sublist(td.la, "0 1 5"));
  sla = sublist(td.la, "5 1 0");
  c11.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("not c11.gananLosMasCapaces()", c11.gananLosMasCapaces(), false);

  Competencia c12("Football", Masculino, sublist(td.la, "0 1 5"));
  sla = Lista<Atleta>();
  c12.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c12.gananLosMasCapaces()", c12.gananLosMasCapaces(), true);

  Competencia c13("Football", Masculino, sublist(td.la, "0 1 5"));
  sla = sublist(td.la, "0");
  c13.finalizar(ciaNumbers(sla), controlados(dop));
  asegurar("c13.gananLosMasCapaces()", c13.gananLosMasCapaces(), true);
}

void testJJOO() {
  TestData td;
  JJOO j3;
  JJOO j1;
  JJOO j2(2012, td.la, td.cc1);
  j1 = JJOO(2012, td.la, td.cc1);

  asegurar("j2 == j2", j2 == j2, true);
  asegurar("j1 == j2", j1 == j2, true);

  j1.transcurrirDia();
  asegurar("j1 != j2", j1 == j2, false);
  j2.transcurrirDia();
  asegurar("j1 == j2", j1 == j2, true);
  asegurar("j1.cantDias() == td.cc1.longitud()", j1.cantDias(), td.cc1.longitud());
  asegurar("j1.jornadaActual() == 2", j1.jornadaActual(), 2);

  j1.transcurrirDia();
  j2.transcurrirDia();
  asegurar("j1 == j2", j1 == j2, true);

  //Testeo IO
  ofstream of;
  of.open(J_TEST_FILE);
  j1.guardar(of);
  of.close();

  ifstream inf;
  inf.open(J_TEST_FILE);
  j3.cargar(inf);
  inf.close();
  asegurar("j3 == j1", j3 == j1, true);

  j3 = j1;

  // cout << j1 << endl;
  // dePaseo
  asegurar("mismos(j1.dePaseo(), sublist(td.la, '3 4'))", mismos(j1.dePaseo(), sublist(td.la, "3 4")), true);

  // medallero
  asegurar("j1.medallero() == [(Argentina, [2,2,0]),(Escocia, [0,0,1])])", j1.medallero(), "[(Argentina, [2,2,0]),(Escocia, [0,0,1])]");
  j1.transcurrirDia();
  asegurar("j1.medallero() == [(Argentina, [2,2,0]),(Bosnia, [1,0,0]),(Escocia, [0,0,1])])",j1.medallero(), "[(Argentina, [2,2,0]),(Bosnia, [1,0,0]),(Escocia, [0,0,1])]");

  // boicotPorDisciplina //!TODO: UnitTest
  int argentinos = atletasDePais(j2, 1, 0, "Argentina");
  asegurar("argentinos == 2", argentinos, 2);
  j2.boicotPorDisciplina(pair<Deporte, Sexo>("Rugby", Masculino), "Argentina");

  argentinos = atletasDePais(j2, 1, 0, "Argentina");
  asegurar("argentinos == 0", argentinos, 0);

  int bosnios = atletasDePais(j2, 3, 0, "Bosnia");
  asegurar("bosnios == 1", bosnios, 1);

  j2.boicotPorDisciplina(pair<Deporte, Sexo>("Handball", Femenino), "Bosnia");
  bosnios = atletasDePais(j2, 3, 0, "Bosnia");
  asegurar("bosnios == 0", bosnios, 0);

  Lista<Competencia> tlc = j2.cronograma(3);
  asegurar("tlc.iesimo(1).participantes().longitud() == 0", tlc.iesimo(1).participantes().longitud(), 0);

  j2.boicotPorDisciplina(pair<Deporte, Sexo>("Softball", Femenino), "Bosnia");
  tlc = j2.cronograma(3);
  asegurar("tlc.iesimo(1).participantes().longitud() == 0", tlc.iesimo(1).participantes().longitud(), 0);

  //// losMasFracasados
  j3 = JJOO(2012, td.la, td.cc1);
  asegurar("mismos(losMasFracasados('Argentina'), sublist(td.la, '0 1'))",mismos(j3.losMasFracasados("Argentina"), sublist(td.la, "0 1")), true);
  asegurar("j3.losMasFracasados('Yugoslavia') == []", j3.losMasFracasados("Yugoslavia"),"[]");
  j3.transcurrirDia();
  asegurar("j3.losMasFracasados('Argentina') == []", j3.losMasFracasados("Argentina"), "[]");

  j3.transcurrirDia();
  j3.transcurrirDia();

  // liuSong
  asegurar("atletasDePais(j3, 1, 0, 'Argentina') == 2", atletasDePais(j3, 1, 0, "Argentina"), 2);

  j3.liuSong(td.at5, "China");
  asegurar("atletasDePais(j3, 1, 0, 'Argentina') == 2", atletasDePais(j3, 1, 0, "Argentina"), 2);

  j3.liuSong(td.at1, "China");
  asegurar("atletasDePais(j3, 1, 0, 'Argentina') == 1", atletasDePais(j3, 1, 0, "Argentina"), 1);
  asegurar("atletasDePais(j3, 3, 0, 'Bosnia') == 1", atletasDePais(j3, 3, 0, "Bosnia"), 1);

  j3.liuSong(td.at3, "China");
  asegurar("atletasDePais(j3, 3, 0, 'Bosnia') == 0", atletasDePais(j3, 3, 0, "Bosnia"), 0);
  asegurar("atletasDePais(j3, 1, 0, 'China') == 1", atletasDePais(j3, 1, 0, "China"), 1);
  asegurar("atletasDePais(j3, 3, 0, 'China') == 1", atletasDePais(j3, 3, 0, "China"), 1);

  // uyOrdenadoAsiHayParton
  JJOO j4(2012, td.la, td.cc2);
  JJOO j5(2012, td.la, td.cc3);
  JJOO j6(2012, td.la, td.cc4);
  JJOO j7(2012, td.la, td.cc5);
  j4.transcurrirDia();
  j4.transcurrirDia();
  j4.transcurrirDia();
  j4.transcurrirDia();
  j5.transcurrirDia();
  j5.transcurrirDia();
  j5.transcurrirDia();
  j5.transcurrirDia();
  j6.transcurrirDia();
  j6.transcurrirDia();
  j6.transcurrirDia();
  j6.transcurrirDia();
  j7.transcurrirDia();
  j7.transcurrirDia();
  j7.transcurrirDia();
  j7.transcurrirDia();

  asegurar("not j4.uyOrdenadoAsiHayUnPatron()", j4.uyOrdenadoAsiHayUnPatron(), false);
  asegurar("j5.uyOrdenadoAsiHayUnPatron()", j5.uyOrdenadoAsiHayUnPatron(), true);
  asegurar("j6.uyOrdenadoAsiHayUnPatron()", j6.uyOrdenadoAsiHayUnPatron(), true);
  asegurar("not j7.uyOrdenadoAsiHayUnPatron()", j7.uyOrdenadoAsiHayUnPatron(), false);

  // stevenBradbury
  JJOO j8(2012, td.la, td.cc6);

  j8.transcurrirDia();
  asegurar("j8.stevenBradbury() == td.at1", j8.stevenBradbury() == td.at1, true);
  j8.transcurrirDia();
  asegurar("j8.stevenBradbury() == td.at2", j8.stevenBradbury() == td.at2, true);

  j8.transcurrirDia();
  asegurar("j8.stevenBradbury() == td.at2",j8.stevenBradbury() == td.at2, true);

  // sequiaOlimpica
  JJOO j9(2012, td.la, td.cc6);

  asegurar("mismos(j9.sequiaOlimpica(), sublist(td.lps,'0 1 2 3'))", mismos(j9.sequiaOlimpica(), sublist(td.lps,"0 1 2 3")), true);

  j9.transcurrirDia();
  asegurar("mismos(j9.sequiaOlimpica(), sublist(td.lps,'1 2 3'))", mismos(j9. sequiaOlimpica(), sublist(td.lps,"1 2 3")), true);

  j9.transcurrirDia();
  asegurar("mismos(j9.sequiaOlimpica(), sublist(td.lps,'1 2'))", mismos(j9.sequiaOlimpica(), sublist(td.lps,"1 2")), true);

  j9.transcurrirDia();
  asegurar("mismos(j9.sequiaOlimpica(), sublist(td.lps,'2'))", mismos(j9.sequiaOlimpica(), sublist(td.lps,"2")), true);


}

#define RUNTEST(t) { cerr << "Corriendo test " << #t << endl; t (); cerr << "Terminado test " << #t << endl; }

int main() {
  RUNTEST(testAtleta);
   RUNTEST(testCompetencia);
   RUNTEST(testJJOO);

return 0;
}

