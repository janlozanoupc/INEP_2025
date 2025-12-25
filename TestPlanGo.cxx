#include "TestPlanGo.hxx"
#include "CapaDomini/Model/PlanGo.hxx"
#include "CapaDomini/Model/Usuari.hxx"
#include "CapaDomini/Model/Escapada.hxx"
#include "CapaDomini/Model/Activitat.hxx"
#include "CapaDomini/Model/Reserva.hxx"
#include "CapaDades/DAOUsuari.hxx"
#include "CapaDades/DAOExperiencia.hxx"
#include "CapaDades/DAOEscapada.hxx"
#include "CapaDades/DAOActivitat.hxx"
#include "CapaDades/DAOReserva.hxx"
#include "CapaDomini/CtrlRegistreUsuari.hxx"
#include "CapaDomini/CtrlIniciSessio.hxx"
#include "CapaDomini/CtrlReservaEscapada.hxx"
#include "CapaDomini/CtrlReservaActivitat.hxx"
#include "CapaDomini/CtrlConsultaReserves.hxx"
#include "CapaDomini/CtrlModificaUsuari.hxx"
#include "CapaDomini/CtrlEsborraUsuari.hxx"
#include "CapaDomini/CtrlConsultaExperiencies.hxx"
#include "CapaDomini/CtrlConsultaNovetats.hxx"
#include "CapaDomini/CtrlConsultaMesReservades.hxx"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;
using namespace boost::gregorian;

int testsPasats = 0;
int testsFallats = 0;

void TestPlanGo::executarTotsElsTests() {
    cout << "\n?????????????????????????????????????????????????????????????\n";
    cout << "?         TESTS DEL SISTEMA PLANGO                          ?\n";
    cout << "?????????????????????????????????????????????????????????????\n\n";

    testsPasats = 0;
    testsFallats = 0;

    // Inicialitzar dades de test
    cout << "Inicialitzant base de dades per als tests...\n";
    inicialitzarDadesTest();
    cout << "\n";

    // Tests del model
    cout << "??? TESTS DEL MODEL ???\n";
    mostrarResultat("Test 01: Crear PlanGo Singleton", test01_CrearPlanGoSingleton());
    mostrarResultat("Test 02: Configurar descompte", test02_ConfigurarDescompte());
    mostrarResultat("Test 03: Crear usuari", test03_CrearUsuari());
    mostrarResultat("Test 04: Crear escapada", test04_CrearEscapada());
    mostrarResultat("Test 05: Crear activitat", test05_CrearActivitat());

    // Tests de DAOs
    cout << "\n??? TESTS DE DAOs ???\n";
    mostrarResultat("Test 06: DAO Usuari - Insertar i obtenir", test06_DAOUsuariInsertarIObte());
    mostrarResultat("Test 07: DAO Experiència - Insertar i obtenir", test07_DAOExperienciaInsertarIObte());
    mostrarResultat("Test 08: DAO Reserva - Insertar i obtenir", test08_DAOReservaInsertarIObte());

    // Tests de controladors bàsics
    cout << "\n??? TESTS DE CONTROLADORS BÀSICS ???\n";
    mostrarResultat("Test 09: Registre d'usuari", test09_RegistreUsuari());
    mostrarResultat("Test 10: Inici de sessió correcte", test10_IniciSessioCorrecte());
    mostrarResultat("Test 11: Inici de sessió incorrecte", test11_IniciSessioIncorrecte());

    // Tests de reserves
    cout << "\n??? TESTS DE RESERVES ???\n";
    mostrarResultat("Test 12: Reserva escapada amb descompte", test12_ReservaEscapadaAmbDescompte());
    mostrarResultat("Test 13: Reserva escapada sense descompte", test13_ReservaEscapadaSenseDescompte());
    mostrarResultat("Test 14: Reserva activitat", test14_ReservaActivitat());
    mostrarResultat("Test 15: Consulta reserves", test15_ConsultaReserves());

    // Tests de gestió d'usuaris
    cout << "\n??? TESTS DE GESTIÓ D'USUARIS ???\n";
    mostrarResultat("Test 16: Modificar usuari", test16_ModificarUsuari());
    mostrarResultat("Test 17: Esborrar usuari", test17_EsborrarUsuari());

    // Tests de consultes avançades
    cout << "\n??? TESTS DE CONSULTES AVANÇADES ???\n";
    mostrarResultat("Test 18: Consulta experiències per ciutat", test18_ConsultaExperienciesPerCiutat());
    mostrarResultat("Test 19: Consulta novetats", test19_ConsultaNovetats());
    mostrarResultat("Test 20: Consulta més reservades", test20_ConsultaMesReservades());

    // Resum
    cout << "\n?????????????????????????????????????????????????????????????\n";
    cout << "?                    RESUM DELS TESTS                       ?\n";
    cout << "?????????????????????????????????????????????????????????????\n";
    cout << "Tests pasats:  " << testsPasats << " / 20\n";
    cout << "Tests fallats: " << testsFallats << " / 20\n";
    
    if (testsFallats == 0) {
        cout << "\n??? TOTS ELS TESTS HAN PASSAT CORRECTAMENT! ???\n";
    } else {
        cout << "\n? Hi ha " << testsFallats << " test(s) que han fallat.\n";
    }
    cout << "\n";
}

void TestPlanGo::mostrarResultat(const string& nomTest, bool resultat) {
    cout << left << setw(50) << nomTest << " : ";
    if (resultat) {
        cout << "? PASSAT\n";
        testsPasats++;
    } else {
        cout << "? FALLAT\n";
        testsFallats++;
    }
}

void TestPlanGo::inicialitzarDadesTest() {
    try {
        // Configurar descompte inicial
        PlanGo::getInstance().setDescompte(0.1f); // 10% de descompte

        // Crear experiències de test
        shared_ptr<Escapada> esc1 = make_shared<Escapada>("Escapada Barcelona", 
            "Weekend a Barcelona", "Barcelona", 4, 500.0f, "Hotel Arts", 2);
        shared_ptr<Escapada> esc2 = make_shared<Escapada>("Escapada Madrid", 
            "Visita a Madrid", "Madrid", 6, 600.0f, "Hotel Ritz", 3);
        shared_ptr<Activitat> act1 = make_shared<Activitat>("Parapent Costa Brava", 
            "Vol en parapent", "Girona", 8, 80.0f, 120);
        shared_ptr<Activitat> act2 = make_shared<Activitat>("Kayak Pirineus", 
            "Descens en kayak", "Lleida", 10, 50.0f, 180);

        // Insertar experiències si no existeixen
        if (!DAOExperiencia::existeix("Escapada Barcelona")) {
            DAOExperiencia::inserta(esc1);
        }
        if (!DAOExperiencia::existeix("Escapada Madrid")) {
            DAOExperiencia::inserta(esc2);
        }
        if (!DAOExperiencia::existeix("Parapent Costa Brava")) {
            DAOExperiencia::inserta(act1);
        }
        if (!DAOExperiencia::existeix("Kayak Pirineus")) {
            DAOExperiencia::inserta(act2);
        }

        cout << "? Dades de test inicialitzades correctament\n";
    } catch (const exception& e) {
        cout << "? Error inicialitzant dades: " << e.what() << "\n";
    }
}

// ==================== TESTS DEL MODEL ====================

bool TestPlanGo::test01_CrearPlanGoSingleton() {
    try {
        PlanGo& plango1 = PlanGo::getInstance();
        PlanGo& plango2 = PlanGo::getInstance();
        return &plango1 == &plango2; // Han de ser la mateixa instància
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test02_ConfigurarDescompte() {
    try {
        PlanGo::getInstance().setDescompte(0.15f);
        float descompte = PlanGo::getInstance().getDescompte();
        return (descompte == 0.15f);
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test03_CrearUsuari() {
    try {
        Usuari usuari("testuser", "Test User", "password123", "test@test.com", 25);
        return (usuari.getSobrenom() == "testuser" && usuari.getEdat() == 25);
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test04_CrearEscapada() {
    try {
        Escapada escapada("Test Escapada", "Descripció test", "Barcelona", 4, 400.0f, "Hotel Test", 3);
        return (escapada.getNom() == "Test Escapada" && escapada.getNumNits() == 3);
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test05_CrearActivitat() {
    try {
        Activitat activitat("Test Activitat", "Descripció test", "Madrid", 10, 50.0f, 120);
        return (activitat.getNom() == "Test Activitat" && activitat.getDurada() == 120);
    } catch (...) {
        return false;
    }
}

// ==================== TESTS DE DAOs ====================

bool TestPlanGo::test06_DAOUsuariInsertarIObte() {
    try {
        string sobrenom = "daotest1";
        
        // Esborrar si existeix
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }

        // Crear i insertar
        shared_ptr<Usuari> usuari = make_shared<Usuari>(sobrenom, "DAO Test", "pass", "dao@test.com", 30);
        DAOUsuari::inserta(usuari);

        // Obtenir i verificar
        shared_ptr<Usuari> obtingut = DAOUsuari::obte(sobrenom);
        bool resultat = (obtingut != nullptr && obtingut->getSobrenom() == sobrenom);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test07_DAOExperienciaInsertarIObte() {
    try {
        string nom = "DAO Test Exp";
        
        // Esborrar si existeix
        if (DAOExperiencia::existeix(nom)) {
            DAOExperiencia::esborra(nom);
        }

        // Crear i insertar
        shared_ptr<Escapada> exp = make_shared<Escapada>(nom, "Test", "Barcelona", 4, 300.0f, "Hotel", 2);
        DAOExperiencia::inserta(exp);

        // Obtenir i verificar
        shared_ptr<Experiencia> obtingut = DAOExperiencia::obte(nom);
        bool resultat = (obtingut != nullptr && obtingut->getNom() == nom);

        // Neteja
        DAOExperiencia::esborra(nom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test08_DAOReservaInsertarIObte() {
    try {
        // Crear usuari i experiència de test
        string sobrenom = "reservatest";
        if (!DAOUsuari::existeix(sobrenom)) {
            shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Reserva Test", "pass", "res@test.com", 28);
            DAOUsuari::inserta(u);
        }

        shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
        shared_ptr<Experiencia> exp = DAOExperiencia::obte("Escapada Barcelona");

        if (usuari && exp) {
            // Crear reserva
            shared_ptr<Reserva> reserva = Reserva::create(usuari, exp, 2, false);
            DAOReserva::inserta(reserva);

            // Verificar
            vector<shared_ptr<Reserva>> reserves = DAOReserva::obteReservesUsuari(usuari);
            bool resultat = !reserves.empty();

            // Neteja
            DAOUsuari::esborra(sobrenom);
            return resultat;
        }
        return false;
    } catch (...) {
        return false;
    }
}

// ==================== TESTS DE CONTROLADORS BÀSICS ====================

bool TestPlanGo::test09_RegistreUsuari() {
    try {
        string sobrenom = "ctrltest1";
        
        // Esborrar si existeix
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }

        // Registrar
        DTOUsuari dto = CtrlRegistreUsuari::registraUsuari(sobrenom, "Ctrl Test", "password", "ctrl@test.com", 22);
        bool resultat = (dto.sobrenom == sobrenom && dto.edat == 22);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test10_IniciSessioCorrecte() {
    try {
        string sobrenom = "logintest";
        string password = "testpass";
        
        // Crear usuari
        if (!DAOUsuari::existeix(sobrenom)) {
            shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Login Test", password, "login@test.com", 25);
            DAOUsuari::inserta(u);
        }

        // Intentar login
        DTOUsuari dto = CtrlIniciSessio::iniciSessio(sobrenom, password);
        bool resultat = (dto.sobrenom == sobrenom);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test11_IniciSessioIncorrecte() {
    try {
        string sobrenom = "loginfail";
        
        // Crear usuari
        if (!DAOUsuari::existeix(sobrenom)) {
            shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Login Fail", "correctpass", "fail@test.com", 25);
            DAOUsuari::inserta(u);
        }

        // Intentar login amb contrasenya incorrecta
        try {
            CtrlIniciSessio::iniciSessio(sobrenom, "wrongpass");
            DAOUsuari::esborra(sobrenom);
            return false; // No hauria d'arribar aquí
        } catch (const runtime_error&) {
            DAOUsuari::esborra(sobrenom);
            return true; // Ha de llançar excepció
        }
    } catch (...) {
        return false;
    }
}

// ==================== TESTS DE RESERVES ====================

bool TestPlanGo::test12_ReservaEscapadaAmbDescompte() {
    try {
        string sobrenom = "desctest";
        
        // Crear usuari nou (sense reserves)
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Desc Test", "pass", "desc@test.com", 30);
        DAOUsuari::inserta(u);

        // Configurar descompte del 10%
        PlanGo::getInstance().setDescompte(0.1f);

        // Fer reserva (ha d'aplicar descompte)
        DTOReserva dto = CtrlReservaEscapada::creaReserva(sobrenom, "Escapada Barcelona", 4);
        
        // Preu original: 500€, amb 10% desc: 450€
        bool resultat = (dto.preuPagat == 450.0f);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test13_ReservaEscapadaSenseDescompte() {
    try {
        string sobrenom = "nodesctest";
        
        // Crear usuari i fer una primera reserva
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "No Desc Test", "pass", "nodisc@test.com", 28);
        DAOUsuari::inserta(u);

        // Primera reserva
        CtrlReservaEscapada::creaReserva(sobrenom, "Escapada Barcelona", 4);

        // Segona reserva (no ha d'aplicar descompte)
        DTOReserva dto = CtrlReservaEscapada::creaReserva(sobrenom, "Escapada Madrid", 6);
        
        // Preu original: 600€, sense descompte: 600€
        bool resultat = (dto.preuPagat == 600.0f);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test14_ReservaActivitat() {
    try {
        string sobrenom = "acttest";
        
        // Crear usuari
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Act Test", "pass", "act@test.com", 26);
        DAOUsuari::inserta(u);

        // Configurar descompte
        PlanGo::getInstance().setDescompte(0.1f);

        // Reservar activitat per 3 persones
        // Preu: 80€ x 3 = 240€, amb 10% desc = 216€
        DTOReserva dto = CtrlReservaActivitat::creaReserva(sobrenom, "Parapent Costa Brava", 3);
        bool resultat = (dto.preuPagat == 216.0f);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test15_ConsultaReserves() {
    try {
        string sobrenom = "consultarest";
        
        // Crear usuari
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Consulta Test", "pass", "cons@test.com", 27);
        DAOUsuari::inserta(u);

        // Fer 2 reserves
        CtrlReservaEscapada::creaReserva(sobrenom, "Escapada Barcelona", 4);
        CtrlReservaActivitat::creaReserva(sobrenom, "Kayak Pirineus", 2);

        // Consultar reserves
        DTOLlistaReserves llista = CtrlConsultaReserves::consultaReserves(sobrenom);
        bool resultat = (llista.reserves.size() == 2 && llista.totalPagat > 0);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

// ==================== TESTS DE GESTIÓ D'USUARIS ====================

bool TestPlanGo::test16_ModificarUsuari() {
    try {
        string sobrenom = "modiftest";
        
        // Crear usuari
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Original", "pass", "orig@test.com", 25);
        DAOUsuari::inserta(u);

        // Modificar
        DTOUsuari dto = CtrlModificaUsuari::modificaUsuari(sobrenom, "Modificat", "nou@test.com", 26);
        bool resultat = (dto.nom == "Modificat" && dto.edat == 26);

        // Neteja
        DAOUsuari::esborra(sobrenom);
        return resultat;
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test17_EsborrarUsuari() {
    try {
        string sobrenom = "esborratest";
        string password = "testpass";
        
        // Crear usuari
        if (DAOUsuari::existeix(sobrenom)) {
            DAOUsuari::esborra(sobrenom);
        }
        shared_ptr<Usuari> u = make_shared<Usuari>(sobrenom, "Esborra Test", password, "esb@test.com", 24);
        DAOUsuari::inserta(u);

        // Esborrar
        CtrlEsborraUsuari::esborraUsuari(sobrenom, password);
        
        // Verificar que no existeix
        return !DAOUsuari::existeix(sobrenom);
    } catch (...) {
        return false;
    }
}

// ==================== TESTS DE CONSULTES AVANÇADES ====================

bool TestPlanGo::test18_ConsultaExperienciesPerCiutat() {
    try {
        vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("Barcelona", 2);
        return !exp.empty();
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test19_ConsultaNovetats() {
    try {
        vector<DTOExperiencia> exp = CtrlConsultaNovetats::consultaNovetats(5);
        return !exp.empty();
    } catch (...) {
        return false;
    }
}

bool TestPlanGo::test20_ConsultaMesReservades() {
    try {
        vector<DTOExperiencia> exp = CtrlConsultaMesReservades::consultaMesReservades(3);
        // Pot retornar buit si no hi ha reserves encara
        return true; // El test passa si no hi ha errors
    } catch (...) {
        return false;
    }
}
