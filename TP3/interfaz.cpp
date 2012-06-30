#include "interfaz.h"
//#include "lista.h"


using namespace std;

bool atletaCreado = false;
bool competenciaCreada = false;
bool jjooCreado = false;


void MenuPrincipal()
{
    cout.setf(ios::boolalpha);

    bool exit = false;
    int maximaOpcion = 3;

    while (!exit)
    {
        cout << endl
                << "Londres 2012" << endl
                << "0. Atleta" << endl
                << "1. Competencia" << endl
                << "2. JJOO" << endl
                << "3. Salir" << endl;

        int opt = LeerOpcion(maximaOpcion);
        switch(opt)
        {
            case 0:
            {
                LimpiarPantalla();
                MenuAtleta();
                break;
            }
            case 1:
            {
                LimpiarPantalla();
                MenuCompetencia();
                break;
            }
            case 2:
            {
                LimpiarPantalla();
                MenuJJOO();
                break;
            }
            case 3:
            {
                exit = true;
                LimpiarPantalla();
                break;
            }
        }

    }
}

/////// MENU ATLETA

Atleta atleta;
void MenuAtleta()
{
    int maximaOpcion = 2;

    cout << "Creando atleta" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear atleta" << endl
            << "2. Cargar atleta" << endl;
    if (atletaCreado)
    {
        maximaOpcion = 10;
        cout << "3. Entrenar nuevo deporte" << endl
            << "4. Guardar atleta" << endl
            << "5. Mostrar" << endl
            << "6. Nombre" << endl
            << "7. Sexo" << endl
            << "8. Anio de nacimiento" << endl
            << "9. Nacionalidad" << endl
            << "10. CIA Number" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
                LimpiarPantalla();
                break;
        }
        case 1:
        {
                LimpiarPantalla();
                atleta = MenuCrearAtleta();
                atletaCreado = true;
                LimpiarPantalla();
                MenuAtleta();
                break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            atleta.cargar(archivoEntrada);
            archivoEntrada.close();
            atletaCreado = true;
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 3:
        {
            int cantidad;
            //TODO: Chequear si la capacidad era un parametro más
            string nuevoDeporte;
            cout << "Indicar el deporte que desea entrenar y cuanto :";
            cin >> nuevoDeporte;
            cin >> cantidad;
            atleta.entrenarNuevoDeporte(nuevoDeporte, cantidad);
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            atleta.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 5:
        {
            LimpiarPantalla();
            atleta.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 6:
        {
            cout << "Nombre: " << atleta.nombre() << endl;
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 7:
        {
            cout << "Sexo: " << ((atleta.sexo()==Femenino)?  "Femenino" : "Masculino") << endl;
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 8:
        {
            cout << "Anio de nacimiento: " << atleta.anioNacimiento() << endl;
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 9:
        {
            cout << "Nacionalidad: " << atleta.nacionalidad() << endl;
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
        case 10:
        {
            cout << "CIA Number: " << atleta.ciaNumber() << endl;
            Pausar();
            LimpiarPantalla();
            MenuAtleta();
            break;
        }
    }
}

Atleta MenuCrearAtleta()
{
    string nombre;
    string sexo;
    int anio;
    Pais pais;
    int ciaNumber;
    Sexo sexoFinal;


    cout << "Ingrese el nombre, sexo, anio, pais y ciaNumber entre espacios del atleta: " << endl;
    cin >> nombre;
    cin >> sexo;
    cin >> anio;
    cin >> pais;
    cin >> ciaNumber;

    if (sexo == "f" || sexo == "F" || sexo == "femenino" || sexo == "Femenino")
    {
        sexoFinal = Femenino;
    }
    if (sexo == "m" || sexo == "M" || sexo == "masculino" || sexo == "Masculino")
    {
        sexoFinal = Masculino;
    }

    return Atleta(nombre, sexoFinal, anio, pais, ciaNumber);
}


/////// MENU COMPETENCIA

Competencia competencia;

void MenuCompetencia()
{
    int maximaOpcion = 2;

    cout << "Creando competencia" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear competencia" << endl
            << "2. Cargar competencia" << endl;
    if (competenciaCreada)
    {
        maximaOpcion = 14;
        cout << "3. Finalizar competencia" << endl
            << "4. LinfordChristie" << endl
            << "5. ¿Ganan los mas capaces?" << endl
            << "6. Sancionar Tramposos" << endl
            << "7. ¿Le Dio positivo?" << endl
            << "8. Ranking" << endl
            << "9. Atletas que les toco control" << endl
            << "10. ¿Finalizada?" << endl
            << "11. Guardar" << endl
            << "12. Mostrar" << endl
            << "13. Participantes" << endl
            << "14. Categoria" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
                LimpiarPantalla();
                break;
        }
        case 1:
        {
                LimpiarPantalla();
                competencia = MenuCrearCompetencia();
                competenciaCreada = true;
                LimpiarPantalla();
                MenuCompetencia();
                break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            competencia.cargar(archivoEntrada);
            archivoEntrada.close();
            competenciaCreada = true;
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 3:
        {
            int id;
            string doping;

            Lista<int> posiciones = Lista<int>();
            Lista< pair<int, bool> > resultados = Lista< pair<int, bool> >();

            MostrarAtletas(competencia.participantes(), "Lista de participantes :");

            cout << competencia.participantes() << endl;

            cout << "Ingrese la lista de atletas segun id de la lista, seguido del resultado de doping del mismo."<< endl;

            for (int i = 0; i < competencia.participantes().longitud(); i++)
            {
                cout << "Puesto numero " << i+1 << " : ";
                cin >> id;
                cin >> doping;
                posiciones.agregarAtras(competencia.participantes().iesimo(id).ciaNumber());
                resultados.agregar(pair<int, bool>(competencia.participantes().iesimo(id).ciaNumber(), doping == "s"));
            }

            competencia.finalizar(posiciones, resultados);
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 4:
        {
            int id;
            string nombre;
            LimpiarPantalla();
            MostrarAtletas(competencia.participantes(), "Lista de participantes :");
            cout << "Indique que atleta desea descalificar : " << endl;
            cin >> id;
            nombre = competencia.participantes().iesimo(id).nombre();
            competencia.linfordChristie(competencia.participantes().iesimo(id).ciaNumber());
            cout << "El atleta " << nombre <<" fue descalificado";
            Pausar();
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 5:
        {
            LimpiarPantalla();
            cout << "¿Ganan los más capaces? " << competencia.gananLosMasCapaces() << endl;
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 6:
        {
            cout << "Sancionando tramposos" << endl;
            competencia.sancionarTramposos();
            cout << "Tramposos sancionados" << endl;
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 7:
        {
            int id;
            MostrarAtletas(competencia.participantes(), "Lista de participantes :");
            cout << "Indique el id de atleta del que desea saber su resultado de doping :";
            cin >> id;
            cout << "Su resultado fue: " << competencia.leDioPositivo(competencia.participantes().iesimo(id)) << endl;
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 8:
        {
            MostrarAtletas(competencia.ranking(), "Ranking de la competencia :");
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 9:
        {
            MostrarAtletas(competencia.lesTocoControlAntidoping(), "Atletas a los que le toco control antidoping :");
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 10:
        {
            cout << "¿Está finalizada la competencia? " << competencia.finalizada() << endl;
            Pausar();
            LimpiarPantalla();
            break;
        }
        case 11:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            competencia.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 12:
        {
            LimpiarPantalla();
            competencia.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 13:
        {
            MostrarAtletas(competencia.participantes(), "Participantes de la competencia: ");
            Pausar();
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
        case 14:
        {
            cout << "Categoria: " << "[ Deporte: " << competencia.categoria().first << "| Sexo: " << competencia.categoria().second << "]" << endl;
            Pausar();
            LimpiarPantalla();
            MenuCompetencia();
            break;
        }
    }
}

Competencia MenuCrearCompetencia()
{
    string nombre;
    string sexo;

    Lista<Atleta> atletas = Lista<Atleta>();

    Sexo sexoFinal;

    cout << "Ingrese el deporte y sexo de la competenciaentre espacios: " << endl;
    cin >> nombre;
    cin >> sexo;

    if (sexo == "f" || sexo == "F" || sexo == "femenino" || sexo == "Femenino")
    {
        sexoFinal = Femenino;
    }
    if (sexo == "m" || sexo == "M" || sexo == "masculino" || sexo == "Masculino")
    {
        sexoFinal = Masculino;
    }

    bool otroAtleta;
    string eleccion;

    cout << "Desea ingresar un atleta? [s/n] " << endl;
    cin >> eleccion;
    otroAtleta = eleccion == "s";

    while(otroAtleta)
    {
        atletas.agregarAtras(MenuCrearAtleta());
        cout << "Desea ingresar un atleta? [s/n] ";
        cin >> eleccion;
        cout << endl;
        otroAtleta = eleccion == "s";

    }

    return Competencia(nombre, sexoFinal, atletas);
}


/////// MENU JJOO

JJOO jjoo;

void MenuJJOO()
{
    int maximaOpcion = 2;

    cout << "Creando competencia" << endl
            << "0. Volver al Menu Principal" << endl
            << "1. Crear JJOO" << endl
            << "2. Cargar JJOO" << endl;
    if (jjooCreado)
    {
        maximaOpcion = 18;
        cout << "3. Transcurrir dia" << endl
            << "4. StevenBradbury" << endl
            << "5. LiuSong" << endl
            << "6. Los mas fracasados" << endl
            << "7. Medallero" << endl
            << "8. De paseo" << endl
            << "9. Sequia olimpica" << endl
            << "10. ¿Ordenados asi hay un patron?" << endl
            << "11. Boicot por disciplina" << endl
            << "12. Guardar" << endl
            << "13. Mostrar" << endl
            << "14. Ver anio" << endl
            << "15. Ver Jornada actual" << endl
            << "16. Ver atletas" << endl
            << "17. Cantidad de dias" << endl
            << "18. Atleta Prodigio" << endl;
    }

    int opt = LeerOpcion(maximaOpcion);

    LimpiarPantalla();
    switch(opt)
    {
        case 0:
        {
            LimpiarPantalla();
            break;
        }
        case 1:
        {
            LimpiarPantalla();
            jjoo = MenuCrearJJOO();
            jjooCreado = true;
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 2:
        {
            LimpiarPantalla();
            ifstream archivoEntrada;
            AbrirArchivoParaLeer(archivoEntrada);
            jjoo.cargar(archivoEntrada);
            archivoEntrada.close();
            jjooCreado = true;
            LimpiarPantalla();

            JJOO jjoo2;
            ifstream archivoEntrada2;
            AbrirArchivoParaLeer(archivoEntrada2);
            jjoo2.cargar(archivoEntrada2);
            archivoEntrada2.close();
            jjooCreado = true;
            LimpiarPantalla();
            if(jjoo==jjoo2)
            {
            MenuJJOO();
            }
            break;
        }
        case 3:
        {
            LimpiarPantalla();
            cout << "Comenzando a transcurrir dia" << endl;
            jjoo.transcurrirDia();
            cout << "Dia transcurrido" << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 4:
        {
            LimpiarPantalla();
            cout << "Nombre: " << jjoo.stevenBradbury().nombre() <<  "CIA Number: " << jjoo.stevenBradbury().ciaNumber() << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 5:
        {
            int id;
            string pais;
            LimpiarPantalla();
            MostrarAtletas(jjoo.atletas(), "Atletas del Juego Olimpico: ");
            cout << "Indique el atleta y el pais al cual sera nacionalizado :" << endl;
            cin >> id;
            cin >> pais;
            jjoo.liuSong(jjoo.atletas().iesimo(id), pais);
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 6:
        {
            string pais;
            cout << "Indique el pais del cual desea conocer sus atletas mas fracasados: ";
            cin >> pais;
            MostrarAtletas(jjoo.losMasFracasados(pais), "Los mas fracasados: ");
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 7:
        {
            cout << "Medallero olimpico" << endl;
            cout << "Pais" << "     " << "Medallas" << endl;
            for (int i = 0; i < jjoo.medallero().longitud(); i++)
            {
                cout << jjoo.medallero().iesimo(i).first << "       " << jjoo.medallero().iesimo(i).second << endl;
            }
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 8:
        {
            MostrarAtletas(jjoo.dePaseo(), "Atletas de paseo :");
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 9:
        {
            cout << "Sequia olimpica: " << endl;
            for (int i = 0; i < jjoo.sequiaOlimpica().longitud(); i++)
            {
                cout << jjoo.sequiaOlimpica().iesimo(i) << " ";
            }
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 10:
        {
            cout << "¿Hay un patron? " << jjoo.uyOrdenadoAsiHayUnPatron() << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 11:
        {
            string deporte, sexo, pais;
            Sexo sexoFinal;
            cout << "Indique el deporte y sexo de la categoria y el pais que desea boicotear : ";
            cin >> deporte;
            cin >> sexo;
            cin >> pais;

            if (sexo == "f" || sexo == "F" || sexo == "femenino" || sexo == "Femenino")
            {
                sexoFinal = Femenino;
            }
            if (sexo == "m" || sexo == "M" || sexo == "masculino" || sexo == "Masculino")
            {
                sexoFinal = Masculino;
            }
            jjoo.boicotPorDisciplina(pair<Deporte, Sexo>(deporte, sexoFinal), pais);
            cout << "Boicot aplicado" << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 12:
        {
            LimpiarPantalla();
            ofstream archivoSalida;

            AbrirArchivoParaEscribir(archivoSalida);
            jjoo.guardar(archivoSalida);
            archivoSalida.close();

            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 13:
        {
            LimpiarPantalla();
            jjoo.mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 14:
        {
            cout << "Anio: " << jjoo.anio() << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 15:
        {
            cout << "Jornada actual: " << jjoo.jornadaActual() << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 16:
        {
            MostrarAtletas(jjoo.atletas(), "Atletas del Juego olimpico: ");
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 17:
        {
            cout << "Cantidad de dias: " << jjoo.cantDias() << endl;
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
        case 18:
        {
            cout << "El Atleta prodigio es: " << endl;
            atletaProdigio(jjoo).mostrar(cout);
            Pausar();
            LimpiarPantalla();
            MenuJJOO();
            break;
        }
    }
}

JJOO MenuCrearJJOO()
{
    int anio;

    Lista<Atleta> atletas = Lista<Atleta>();
    Lista< Lista<Competencia> > cronograma = Lista< Lista<Competencia> >();

    cout << "Ingrese el año del Juego olimpico: " << endl;
    cin >> anio;


    bool otraFecha;
    string eleccion;

    cout << "¿Desea ingresar una fecha al JJOO? [s/n] ";
    cin >> eleccion;
    otraFecha = eleccion == "s";

    while(otraFecha)
    {
        cout << endl;
        cout<< "Ingresando nueva Fecha" << endl;

        Lista<Competencia> nuevaLista = Lista<Competencia>();
        bool otraCompetencia;

        cout << "Desea ingresar una competencia? [s/n] ";
        cin >> eleccion;
        otraCompetencia = eleccion == "s";

        while(otraCompetencia)
        {
            nuevaLista.agregarAtras(MenuCrearCompetencia());
            cout << "Desea ingresar otra competencia? [s/n] ";
            cin >> eleccion;
            cout << endl;
            otraCompetencia = eleccion == "s";
        }
        cronograma.agregarAtras(nuevaLista);

        cout << "¿Desea ingresar otra fecha al JJOO? [s/n] ";
        cin >> eleccion;
        otraFecha = eleccion == "s";
    }
    cout << "¿Desea ingresar todos los participantes de las competencias ingresadas? :" << endl;
    cin >> eleccion;

    if (eleccion == "s")
    {
        for (int i = 0; i < cronograma.longitud(); i++)
        {
            for (int j = 0; j < cronograma.iesimo(i).longitud(); j++)
            {
                for(int k = 0; k < cronograma.iesimo(i).iesimo(j).participantes().longitud(); k++)
                {
                    if (!atletas.pertenece(cronograma.iesimo(i).iesimo(j).participantes().iesimo(k)))
                    {
                        atletas.agregarAtras(cronograma.iesimo(i).iesimo(j).participantes().iesimo(k));
                    }
                }
            }
        }
    }

    bool otroAtleta;
    cout << "Desea ingresar otro atleta? [s/n] " << endl;
    cin >> eleccion;
    otroAtleta = eleccion == "s";

    while(otroAtleta)
    {
        atletas.agregarAtras(MenuCrearAtleta());
        cout << "Desea ingresar otro atleta? [s/n] ";
        cin >> eleccion;
        cout << endl;
        otroAtleta = eleccion == "s";
    }




    return JJOO(anio, atletas, cronograma);
}


//AUX
int LeerOpcion(int maxOpcion)
{
    cout << "  Ingrese una opcion [" << 0 << "-" << maxOpcion << "]: ";
    int opt;
    bool ok = false;
    while (!ok)
    {
        cin >> opt;
        ok = (opt <= maxOpcion);

        if (!ok)
            cout << "  Opcion incorrecta. Ingrese un numero entre [" << 1 << "-" << maxOpcion << "]: ";
    }
    return opt;
}

void Salir()
{
    cout << "Gracias, Vuelvan prontos!" << endl;
}

void Pausar()
{
    cout << endl;
    string opt = "n";
#ifdef WIN32
    system("Pause");
#else
    cout << "Press any key to continue . . . ";
    cin >> opt;
#endif

}

void LimpiarPantalla()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}

void AbrirArchivoParaLeer(ifstream &archivo)
{
    cout << "  Ingrese nombre de archivo existente: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo existente: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}


void AbrirArchivoParaEscribir(ofstream &archivo)
{
    cout << "  Ingrese nombre de archivo: ";
    string opt;
    bool ok = false;
    getline(cin, opt);
    getline(cin, opt);
    archivo.open(opt.c_str());
    ok = archivo.good();

    while (!ok)
    {
        cout << "  Valor incorrecto. Ingrese nombre de archivo: ";
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
    }
}


void MostrarAtletas(Lista<Atleta> atletas, string titulo)
{
    int tam = atletas.longitud();
    cout << titulo << endl;
    for (int i = 0; i < tam; i++)
    {
        cout << i << " : " << atletas.iesimo(i).nombre() << endl;
    }
}

