#include <iostream>
#include <iomanip>
#include "../CapaDomini/CtrlRegistreUsuari.hxx"
#include "../CapaDomini/CtrlIniciSessio.hxx"
#include "../CapaDomini/CtrlModificaUsuari.hxx"
#include "../CapaDomini/CtrlEsborraUsuari.hxx"
#include "../CapaDades/DAOUsuari.hxx"

using namespace std;

void separador() {
    cout << "\n" << string(70, '=') << "\n\n";
}

void titol(const string& text) {
    cout << "\n?" << string(68, '?') << "?\n";
    cout << "? " << left << setw(67) << text << "?\n";
    cout << "?" << string(68, '?') << "?\n\n";
}

int main() {
    cout << "\n";
    titol("JOC DE PROVA 02: GESTIÓ D'USUARIS (CRUD COMPLET)");

    int testsPasats = 0;
    int testsFallats = 0;

    try {
        // ====================================================================
        // TEST 1: REGISTRE D'USUARI NOU
        // ====================================================================
        titol("TEST 1: Registrar nou usuari");
        
        string novaMatricula = "testuser01";
        
        // Esborrar si ja existeix
        if (DAOUsuari::existeix(novaMatricula)) {
            cout << "??  L'usuari ja existeix, esborrant...\n";
            DAOUsuari::esborra(novaMatricula);
        }

        try {
            DTOUsuari nouUsuari = CtrlRegistreUsuari::registraUsuari(
                novaMatricula,
                "Test User 01",
                "test1234",
                "testuser01@test.com",
                26
            );

            cout << "? Usuari registrat correctament\n";
            cout << "  Sobrenom: " << nouUsuari.sobrenom << "\n";
            cout << "  Nom: " << nouUsuari.nom << "\n";
            cout << "  Email: " << nouUsuari.correuElectronic << "\n";
            cout << "  Edat: " << nouUsuari.edat << "\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 2: INICI DE SESSIÓ AMB CREDENCIALS CORRECTES
        // ====================================================================
        separador();
        titol("TEST 2: Inici de sessió amb credencials correctes");

        try {
            DTOUsuari usuari = CtrlIniciSessio::iniciSessio(novaMatricula, "test1234");
            cout << "? Inici de sessió correcte\n";
            cout << "  Benvingut/da: " << usuari.nom << "\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 3: INICI DE SESSIÓ AMB CONTRASENYA INCORRECTA
        // ====================================================================
        separador();
        titol("TEST 3: Inici de sessió amb contrasenya incorrecta");

        try {
            DTOUsuari usuari = CtrlIniciSessio::iniciSessio(novaMatricula, "wrongpass");
            cout << "? ERROR: No hauria de permetre login amb contrasenya incorrecta\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 4: MODIFICAR DADES D'USUARI
        // ====================================================================
        separador();
        titol("TEST 4: Modificar dades de l'usuari");

        try {
            DTOUsuari usuariModificat = CtrlModificaUsuari::modificaUsuari(
                novaMatricula,
                "Test User 01 MODIFICAT",
                "newemail@test.com",
                27
            );

            cout << "? Dades modificades correctament\n";
            cout << "  Nou nom: " << usuariModificat.nom << "\n";
            cout << "  Nou email: " << usuariModificat.correuElectronic << "\n";
            cout << "  Nova edat: " << usuariModificat.edat << "\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 5: INTENTAR MODIFICAR AMB EMAIL DUPLICAT
        // ====================================================================
        separador();
        titol("TEST 5: Intentar modificar amb email ja existent");

        try {
            // Utilitzar un email que ja existeix (de l'script d'inicialització)
            DTOUsuari usuari = CtrlModificaUsuari::modificaUsuari(
                novaMatricula,
                "Test User 01",
                "joan@gmail.com",  // Email de Joan
                27
            );
            cout << "? ERROR: Hauria de rebutjar email duplicat\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 6: REGISTRE AMB EDAT INFERIOR A 18
        // ====================================================================
        separador();
        titol("TEST 6: Intentar registrar usuari menor de 18 anys");

        try {
            DTOUsuari menor = CtrlRegistreUsuari::registraUsuari(
                "menor01",
                "Usuari Menor",
                "pass123",
                "menor@test.com",
                17  // Edat < 18
            );
            cout << "? ERROR: No hauria de permetre registre de menors de 18\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 7: REGISTRE AMB SOBRENOM DUPLICAT
        // ====================================================================
        separador();
        titol("TEST 7: Intentar registrar amb sobrenom duplicat");

        try {
            DTOUsuari duplicat = CtrlRegistreUsuari::registraUsuari(
                novaMatricula,  // Mateix sobrenom
                "Altre Usuari",
                "pass999",
                "altre@test.com",
                25
            );
            cout << "? ERROR: No hauria de permetre sobrenom duplicat\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 8: CONSULTAR TOTS ELS USUARIS
        // ====================================================================
        separador();
        titol("TEST 8: Obtenir llista de tots els usuaris");

        try {
            vector<shared_ptr<Usuari>> usuaris = DAOUsuari::tots();
            cout << "? Llista d'usuaris obtinguda\n";
            cout << "  Total usuaris: " << usuaris.size() << "\n\n";
            
            cout << "  Usuaris registrats:\n";
            cout << "  " << string(66, '-') << "\n";
            for (const auto& u : usuaris) {
                cout << "  " << left << setw(15) << u->getSobrenom() 
                     << " | " << setw(30) << u->getNom()
                     << " | " << u->getEdat() << " anys\n";
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 9: ESBORRAR USUARI AMB CONTRASENYA INCORRECTA
        // ====================================================================
        separador();
        titol("TEST 9: Intentar esborrar usuari amb contrasenya incorrecta");

        try {
            CtrlEsborraUsuari::esborraUsuari(novaMatricula, "wrongpassword");
            cout << "? ERROR: No hauria de permetre esborrar amb contrasenya incorrecta\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 10: ESBORRAR USUARI AMB CONTRASENYA CORRECTA
        // ====================================================================
        separador();
        titol("TEST 10: Esborrar usuari amb contrasenya correcta");

        try {
            CtrlEsborraUsuari::esborraUsuari(novaMatricula, "test1234");
            cout << "? Usuari esborrat correctament\n";
            
            // Verificar que ja no existeix
            if (!DAOUsuari::existeix(novaMatricula)) {
                cout << "? Verificat: L'usuari ja no existeix a la BD\n";
            } else {
                cout << "? ERROR: L'usuari encara existeix!\n";
                testsFallats++;
                testsPasats--; // Compensar el ++ anterior
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // RESUM FINAL
        // ====================================================================
        separador();
        titol("RESUM DEL JOC DE PROVA 02");

        cout << "Tests executats: " << (testsPasats + testsFallats) << "\n";
        cout << "Tests pasats:    " << testsPasats << " ?\n";
        cout << "Tests fallats:   " << testsFallats << " ?\n\n";

        if (testsFallats == 0) {
            cout << "??? TOTS ELS TESTS HAN PASSAT CORRECTAMENT! ???\n\n";
            return 0;
        } else {
            cout << "??  Hi ha tests que han fallat\n\n";
            return 1;
        }

    } catch (const exception& e) {
        cout << "\n? ERROR CRÍTIC: " << e.what() << "\n\n";
        return 1;
    }
}
