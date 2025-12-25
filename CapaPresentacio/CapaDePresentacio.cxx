#include "CapaDePresentacio.hxx"
#include "../CapaDomini/CtrlIniciSessio.hxx"
#include "../CapaDomini/CtrlRegistreUsuari.hxx"
#include "../CapaDomini/CtrlReservaEscapada.hxx"
#include "../CapaDomini/CtrlConsultaReserves.hxx"
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
                    consultarReserves();
                    break;
                case 3:
                    mostrarTotesExperiencies();
                    break;
                case 4:
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
    cout << "  1. Reservar experiència\n";
    cout << "  2. Consultar les meves reserves\n";
    cout << "  3. Veure experiències disponibles\n";
    if (sobrenom == "admin") {
        cout << "  4. Configurar descompte (ADMIN)\n";
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
