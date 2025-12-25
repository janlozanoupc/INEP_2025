#include "CapaDePresentacio.hxx"
#include "../CapaDomini/CtrlIniciSessio.hxx"
#include "../CapaDomini/CtrlRegistreUsuari.hxx"
#include "../CapaDomini/CtrlModificaUsuari.hxx"
#include "../CapaDomini/CtrlEsborraUsuari.hxx"
#include "../CapaDomini/CtrlReservaEscapada.hxx"
#include "../CapaDomini/CtrlReservaActivitat.hxx"
#include "../CapaDomini/CtrlConsultaReserves.hxx"
#include "../CapaDomini/CtrlConsultaExperiencies.hxx"
#include "../CapaDomini/CtrlConsultaNovetats.hxx"
#include "../CapaDomini/CtrlConsultaMesReservades.hxx"
#include "../CapaDomini/Model/PlanGo.hxx"
#include "../CapaDades/DAOExperiencia.hxx"
#include <iostream>
#include <locale>
#include <stdexcept>
#include <iomanip>

using namespace std;

// Inicialització de la instància estàtica
CapaDePresentacio* CapaDePresentacio::_instancia = nullptr;

// Constructor privat
CapaDePresentacio::CapaDePresentacio() : _usuariActual("") {
    // Configurar locale per suportar caràcters UTF-8
    locale::global(locale(""));
    wcout.imbue(locale());
    cout.imbue(locale());
}

// PRE: cert
// POST: retorna la instància única de CapaDePresentacio
CapaDePresentacio& CapaDePresentacio::getInstance() {
    if (_instancia == nullptr) {
        _instancia = new CapaDePresentacio();
    }
    return *_instancia;
}

// PRE: cert
// POST: mostra el menú i gestiona les opcions de l'usuari
void CapaDePresentacio::executar() {
    int opcio;
    bool sortir = false;

    while (!sortir) {
        if (_usuariActual.empty()) {
            mostrarMenuPrincipal();
            cout << "Selecciona una opció: ";
            cin >> opcio;
            cin.ignore(); // Netejar el buffer

            switch (opcio) {
                case 1:
                    iniciarSessio();
                    break;
                case 2:
                    registrarUsuari();
                    break;
                case 3:
                    mostrarTotesExperiencies();
                    break;
                case 0:
                    sortir = true;
                    cout << "\nAdéu! Gràcies per utilitzar PlanGo.\n";
                    break;
                default:
                    cout << "\nOpció no vàlida. Torna-ho a intentar.\n";
                    pausar();
            }
        } else {
            mostrarMenuUsuari(_usuariActual);
            cout << "Selecciona una opció: ";
            cin >> opcio;
            cin.ignore(); // Netejar el buffer

            switch (opcio) {
                case 1:
                    reservarEscapada();
                    break;
                case 2:
                    reservarActivitat();
                    break;
                case 3:
                    consultarReserves();
                    break;
                case 4:
                    mostrarMenuConsultes();
                    break;
                case 5:
                    mostrarMenuGestioUsuari();
                    break;
                case 6:
                    if (_usuariActual == "admin") {
                        configurarDescompte();
                    } else {
                        cout << "\nNo tens permisos per aquesta acció.\n";
                        pausar();
                    }
                    break;
                case 0:
                    _usuariActual = "";
                    cout << "\nSessió tancada correctament.\n";
                    pausar();
                    break;
                default:
                    cout << "\nOpció no vàlida. Torna-ho a intentar.\n";
                    pausar();
            }
        }
    }
}

void CapaDePresentacio::mostrarMenuPrincipal() {
    netejaPantalla();
    cout << "??????????????????????????????????????????\n";
    cout << "?          SISTEMA PLANGO                ?\n";
    cout << "?    Gestió de Reserves d'Experiències  ?\n";
    cout << "??????????????????????????????????????????\n\n";
    cout << "  1. Iniciar sessió\n";
    cout << "  2. Registrar-se\n";
    cout << "  3. Veure experiències disponibles\n";
    cout << "  0. Sortir\n\n";
}

void CapaDePresentacio::mostrarMenuUsuari(const string& sobrenom) {
    netejaPantalla();
    cout << "??????????????????????????????????????????\n";
    cout << "?          SISTEMA PLANGO                ?\n";
    cout << "?    Usuari: " << left << setw(28) << sobrenom << "?\n";
    cout << "??????????????????????????????????????????\n\n";
    cout << "  1. Reservar escapada\n";
    cout << "  2. Reservar activitat\n";
    cout << "  3. Consultar les meves reserves\n";
    cout << "  4. Consultes d'experiències\n";
    cout << "  5. Gestió del meu compte\n";
    if (sobrenom == "admin") {
        cout << "  6. Configurar descompte (ADMIN)\n";
    }
    cout << "  0. Tancar sessió\n\n";
}

void CapaDePresentacio::iniciarSessio() {
    netejaPantalla();
    cout << "??? INICIAR SESSIÓ ???\n\n";

    string sobrenom, contrasenya;
    cout << "Sobrenom: ";
    getline(cin, sobrenom);
    cout << "Contrasenya: ";
    getline(cin, contrasenya);

    try {
        DTOUsuari usuari = CtrlIniciSessio::iniciSessio(sobrenom, contrasenya);
        _usuariActual = sobrenom;
        cout << "\n? Benvingut/da, " << usuari.nom << "!\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::registrarUsuari() {
    netejaPantalla();
    cout << "??? REGISTRE D'USUARI ???\n\n";

    string sobrenom, nom, contrasenya, email;
    int edat;

    cout << "Sobrenom: ";
    getline(cin, sobrenom);
    cout << "Nom complet: ";
    getline(cin, nom);
    cout << "Contrasenya: ";
    getline(cin, contrasenya);
    cout << "Correu electrònic: ";
    getline(cin, email);
    cout << "Edat: ";
    cin >> edat;
    cin.ignore(); // Netejar el buffer

    try {
        DTOUsuari usuari = CtrlRegistreUsuari::registraUsuari(sobrenom, nom, contrasenya, email, edat);
        cout << "\n? Usuari registrat correctament!\n";
        cout << "Ja pots iniciar sessió amb el sobrenom: " << usuari.sobrenom << "\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::reservarEscapada() {
    netejaPantalla();
    cout << "??? RESERVAR EXPERIÈNCIA ???\n\n";

    // Mostrar experiències disponibles
    try {
        vector<shared_ptr<Experiencia>> experiencies = DAOExperiencia::tots();
        
        if (experiencies.empty()) {
            cout << "No hi ha experiències disponibles.\n";
            pausar();
            return;
        }

        cout << "Experiències disponibles:\n";
        cout << "?????????????????????????????????????????????????????????????\n";
        for (const auto& exp : experiencies) {
            DTOExperiencia dto = exp->obteInfo();
            cout << "• " << dto.nom << " (" << dto.tipusExperiencia << ")\n";
            cout << "  Ciutat: " << dto.ciutat << "\n";
            cout << "  Preu: " << fixed << setprecision(2) << dto.preu << " €\n";
            cout << "  Places màximes: " << dto.maximPlaces << "\n";
            cout << "  Reserves: " << dto.numReserves << "\n\n";
        }
        cout << "?????????????????????????????????????????????????????????????\n\n";

    } catch (const exception& e) {
        cout << "? Error carregant experiències: " << e.what() << "\n";
        pausar();
        return;
    }

    string nomExperiencia;
    int numPlaces;

    cout << "Nom de l'experiència: ";
    getline(cin, nomExperiencia);
    cout << "Nombre de places: ";
    cin >> numPlaces;
    cin.ignore(); // Netejar el buffer

    try {
        DTOReserva reserva = CtrlReservaEscapada::creaReserva(_usuariActual, nomExperiencia, numPlaces);
        cout << "\n? Reserva creada correctament!\n";
        cout << "?????????????????????????????????????????\n";
        cout << "ID Reserva: " << reserva.id << "\n";
        cout << "Experiència: " << reserva.experiencia.nom << "\n";
        cout << "Places: " << reserva.numPlaces << "\n";
        cout << "Preu pagat: " << fixed << setprecision(2) << reserva.preuPagat << " €\n";
        cout << "Data: " << reserva.dataReserva << "\n";
        cout << "?????????????????????????????????????????\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::consultarReserves() {
    netejaPantalla();
    cout << "??? LES MEVES RESERVES ???\n\n";

    try {
        DTOLlistaReserves llista = CtrlConsultaReserves::consultaReserves(_usuariActual);

        if (llista.reserves.empty()) {
            cout << "No tens cap reserva.\n";
        } else {
            cout << "Total de reserves: " << llista.reserves.size() << "\n";
            cout << "?????????????????????????????????????????????????????????????\n\n";

            for (const auto& reserva : llista.reserves) {
                cout << "Reserva #" << reserva.id << "\n";
                cout << "?????????????????????????????????????????\n";
                cout << "Experiència: " << reserva.experiencia.nom << "\n";
                cout << "Tipus: " << reserva.experiencia.tipusExperiencia << "\n";
                cout << "Ciutat: " << reserva.experiencia.ciutat << "\n";
                cout << "Places: " << reserva.numPlaces << "\n";
                cout << "Preu pagat: " << fixed << setprecision(2) << reserva.preuPagat << " €\n";
                cout << "Data reserva: " << reserva.dataReserva << "\n";
                cout << "\n";
            }

            cout << "?????????????????????????????????????????????????????????????\n";
            cout << "TOTAL PAGAT: " << fixed << setprecision(2) << llista.totalPagat << " €\n";
            cout << "?????????????????????????????????????????????????????????????\n";
        }
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::configurarDescompte() {
    netejaPantalla();
    cout << "??? CONFIGURAR DESCOMPTE ???\n\n";

    float descompteActual = PlanGo::getInstance().getDescompte();
    cout << "Descompte actual per primera reserva: " << fixed << setprecision(1) 
         << (descompteActual * 100) << "%\n\n";

    float nouDescompte;
    cout << "Nou descompte (0.0 - 1.0): ";
    cin >> nouDescompte;
    cin.ignore(); // Netejar el buffer

    try {
        PlanGo::getInstance().setDescompte(nouDescompte);
        cout << "\n? Descompte actualitzat correctament!\n";
        cout << "Nou descompte: " << fixed << setprecision(1) << (nouDescompte * 100) << "%\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::mostrarTotesExperiencies() {
    netejaPantalla();
    cout << "??? EXPERIÈNCIES DISPONIBLES ???\n\n";

    try {
        vector<shared_ptr<Experiencia>> experiencies = DAOExperiencia::tots();

        if (experiencies.empty()) {
            cout << "No hi ha experiències disponibles.\n";
        } else {
            cout << "Total d'experiències: " << experiencies.size() << "\n";
            cout << "?????????????????????????????????????????????????????????????\n\n";

            for (const auto& exp : experiencies) {
                DTOExperiencia dto = exp->obteInfo();
                cout << "• " << dto.nom << " (" << dto.tipusExperiencia << ")\n";
                cout << "  ?????????????????????????????????????????\n";
                cout << "  Descripció: " << dto.descripcio << "\n";
                cout << "  Ciutat: " << dto.ciutat << "\n";
                cout << "  Preu: " << fixed << setprecision(2) << dto.preu << " €";
                
                if (dto.tipusExperiencia == "ACTIVITAT") {
                    cout << " (per persona)";
                } else {
                    cout << " (preu total)";
                }
                cout << "\n";
                
                cout << "  Places màximes: " << dto.maximPlaces << "\n";
                cout << "  Nombre de reserves: " << dto.numReserves << "\n";
                cout << "  Data d'alta: " << dto.dataAlta << "\n";

                if (dto.tipusExperiencia == "ESCAPADA") {
                    cout << "  Hotel: " << dto.hotel << "\n";
                    cout << "  Nombre de nits: " << dto.numNits << "\n";
                } else if (dto.tipusExperiencia == "ACTIVITAT") {
                    cout << "  Durada: " << dto.durada << " minuts\n";
                }
                cout << "\n";
            }

            cout << "?????????????????????????????????????????????????????????????\n";
        }
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::pausar() {
    cout << "\nPrem ENTER per continuar...";
    cin.get();
}

void CapaDePresentacio::netejaPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CapaDePresentacio::modificarUsuari() {
    netejaPantalla();
    cout << "??? MODIFICAR DADES D'USUARI ???\n\n";

    string nouNom, nouEmail;
    int novaEdat;

    cout << "Nou nom complet: ";
    getline(cin, nouNom);
    cout << "Nou correu electrònic: ";
    getline(cin, nouEmail);
    cout << "Nova edat: ";
    cin >> novaEdat;
    cin.ignore();

    try {
        DTOUsuari usuari = CtrlModificaUsuari::modificaUsuari(_usuariActual, nouNom, nouEmail, novaEdat);
        cout << "\n? Dades actualitzades correctament!\n";
        cout << "Nom: " << usuari.nom << "\n";
        cout << "Email: " << usuari.correuElectronic << "\n";
        cout << "Edat: " << usuari.edat << "\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::esborrarUsuari() {
    netejaPantalla();
    cout << "??? ESBORRAR COMPTE D'USUARI ???\n\n";
    cout << "??  ATENCIÓ: Aquesta acció és irreversible!\n";
    cout << "S'esborraran totes les teves reserves.\n\n";

    string contrasenya, confirmacio;
    cout << "Introdueix la teva contrasenya per confirmar: ";
    getline(cin, contrasenya);
    cout << "Escriu 'CONFIRMAR' per continuar: ";
    getline(cin, confirmacio);

    if (confirmacio != "CONFIRMAR") {
        cout << "\nOperació cancel·lada.\n";
        pausar();
        return;
    }

    try {
        CtrlEsborraUsuari::esborraUsuari(_usuariActual, contrasenya);
        cout << "\n? Compte esborrat correctament.\n";
        _usuariActual = "";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::reservarActivitat() {
    netejaPantalla();
    cout << "??? RESERVAR ACTIVITAT ???\n\n";

    string nomActivitat;
    int numPersones;

    cout << "Nom de l'activitat: ";
    getline(cin, nomActivitat);
    cout << "Nombre de persones: ";
    cin >> numPersones;
    cin.ignore();

    try {
        DTOReserva reserva = CtrlReservaActivitat::creaReserva(_usuariActual, nomActivitat, numPersones);
        cout << "\n? Reserva d'activitat creada correctament!\n";
        cout << "?????????????????????????????????????????\n";
        cout << "ID Reserva: " << reserva.id << "\n";
        cout << "Activitat: " << reserva.experiencia.nom << "\n";
        cout << "Persones: " << reserva.numPlaces << "\n";
        cout << "Preu pagat: " << fixed << setprecision(2) << reserva.preuPagat << " €\n";
        cout << "Data: " << reserva.dataReserva << "\n";
        cout << "?????????????????????????????????????????\n";
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::consultarExperienciesPerCiutat() {
    netejaPantalla();
    cout << "??? CONSULTAR EXPERIÈNCIES PER CIUTAT ???\n\n";

    string ciutat;
    int numPersones;

    cout << "Ciutat: ";
    getline(cin, ciutat);
    cout << "Nombre de persones: ";
    cin >> numPersones;
    cin.ignore();

    try {
        vector<DTOExperiencia> experiencies = CtrlConsultaExperiencies::consultaPerCiutatIPersones(ciutat, numPersones);

        if (experiencies.empty()) {
            cout << "\nNo s'han trobat experiències per aquests criteris.\n";
        } else {
            cout << "\n??? RESULTATS ???\n";
            cout << "Experiències a " << ciutat << " per a " << numPersones << " persones:\n";
            cout << "?????????????????????????????????????????????????????????????\n\n";

            for (const auto& exp : experiencies) {
                cout << "• " << exp.nom << " (" << exp.tipusExperiencia << ")\n";
                cout << "  Preu: " << fixed << setprecision(2) << exp.preu << " €";
                if (exp.tipusExperiencia == "ACTIVITAT") {
                    cout << " per persona";
                }
                cout << "\n";
                cout << "  Places màximes: " << exp.maximPlaces << "\n\n";
            }
        }
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::consultarNovetats() {
    netejaPantalla();
    cout << "??? ÚLTIMES EXPERIÈNCIES ???\n\n";

    try {
        vector<DTOExperiencia> experiencies = CtrlConsultaNovetats::consultaNovetats(10);

        if (experiencies.empty()) {
            cout << "No hi ha experiències disponibles.\n";
        } else {
            cout << "Últimes 10 experiències donades d'alta:\n";
            cout << "?????????????????????????????????????????????????????????????\n\n";

            for (const auto& exp : experiencies) {
                cout << "• " << exp.nom << " (" << exp.tipusExperiencia << ")\n";
                cout << "  Ciutat: " << exp.ciutat << "\n";
                cout << "  Data d'alta: " << exp.dataAlta << "\n";
                cout << "  Preu: " << fixed << setprecision(2) << exp.preu << " €\n\n";
            }
        }
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::consultarMesReservades() {
    netejaPantalla();
    cout << "??? TOP 5 EXPERIÈNCIES MÉS RESERVADES ???\n\n";

    try {
        vector<DTOExperiencia> experiencies = CtrlConsultaMesReservades::consultaMesReservades(5);

        if (experiencies.empty()) {
            cout << "No hi ha experiències disponibles.\n";
        } else {
            cout << "Top 5 experiències amb més reserves:\n";
            cout << "?????????????????????????????????????????????????????????????\n\n";

            int posicio = 1;
            for (const auto& exp : experiencies) {
                cout << posicio << ". " << exp.nom << " (" << exp.tipusExperiencia << ")\n";
                cout << "   Ciutat: " << exp.ciutat << "\n";
                cout << "   Reserves: " << exp.numReserves << "\n";
                cout << "   Preu: " << fixed << setprecision(2) << exp.preu << " €\n\n";
                posicio++;
            }
        }
        pausar();
    } catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
        pausar();
    }
}

void CapaDePresentacio::mostrarMenuConsultes() {
    int opcio;
    bool tornar = false;

    while (!tornar) {
        netejaPantalla();
        cout << "??????????????????????????????????????????\n";
        cout << "?       CONSULTES D'EXPERIÈNCIES         ?\n";
        cout << "??????????????????????????????????????????\n\n";
        cout << "  1. Cercar per ciutat i nombre de persones\n";
        cout << "  2. Veure últimes experiències (Novetats)\n";
        cout << "  3. Top 5 més reservades\n";
        cout << "  4. Veure totes les experiències\n";
        cout << "  0. Tornar\n\n";
        cout << "Selecciona una opció: ";
        cin >> opcio;
        cin.ignore();

        switch (opcio) {
            case 1:
                consultarExperienciesPerCiutat();
                break;
            case 2:
                consultarNovetats();
                break;
            case 3:
                consultarMesReservades();
                break;
            case 4:
                mostrarTotesExperiencies();
                break;
            case 0:
                tornar = true;
                break;
            default:
                cout << "\nOpció no vàlida.\n";
                pausar();
        }
    }
}

void CapaDePresentacio::mostrarMenuGestioUsuari() {
    int opcio;
    bool tornar = false;

    while (!tornar) {
        netejaPantalla();
        cout << "??????????????????????????????????????????\n";
        cout << "?       GESTIÓ DEL MEU COMPTE            ?\n";
        cout << "??????????????????????????????????????????\n\n";
        cout << "  1. Modificar les meves dades\n";
        cout << "  2. Esborrar el meu compte\n";
        cout << "  0. Tornar\n\n";
        cout << "Selecciona una opció: ";
        cin >> opcio;
        cin.ignore();

        switch (opcio) {
            case 1:
                modificarUsuari();
                break;
            case 2:
                esborrarUsuari();
                if (_usuariActual.empty()) {
                    tornar = true; // Si s'ha esborrat el compte, tornar al menú principal
                }
                break;
            case 0:
                tornar = true;
                break;
            default:
                cout << "\nOpció no vàlida.\n";
                pausar();
        }
    }
}

