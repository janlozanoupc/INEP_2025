#include <iostream>
#include <iomanip>
#include "../CapaDomini/CtrlReservaEscapada.hxx"
#include "../CapaDomini/CtrlReservaActivitat.hxx"
#include "../CapaDomini/CtrlConsultaReserves.hxx"
#include "../CapaDomini/Model/PlanGo.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "../CapaDades/DAOReserva.hxx"

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
    titol("JOC DE PROVA 04: SISTEMA DE RESERVES");

    int testsPasats = 0;
    int testsFallats = 0;

    try {
        // ====================================================================
        // CONFIGURACIÓ INICIAL
        // ====================================================================
        titol("CONFIGURACIÓ: Establir descompte al 15%");
        
        PlanGo::getInstance().setDescompte(0.15f);
        float descompte = PlanGo::getInstance().getDescompte();
        cout << "? Descompte configurat: " << fixed << setprecision(1) << (descompte * 100) << "%\n";

        // Esborrar reserves anteriors de l'usuari de test
        string sobrenomTest = "pere";  // Usuari de l'script d'inicialització
        
        shared_ptr<Usuari> usuariPere = DAOUsuari::obte(sobrenomTest);
        if (usuariPere) {
            vector<shared_ptr<Reserva>> reservesAnteriors = DAOReserva::obteReservesUsuari(usuariPere);
            for (const auto& res : reservesAnteriors) {
                DAOReserva::esborra(res->getId());
            }
            cout << "? Reserves anteriors esborrades per començar net\n";
        }

        // ====================================================================
        // TEST 1: PRIMERA RESERVA AMB DESCOMPTE (ESCAPADA)
        // ====================================================================
        separador();
        titol("TEST 1: Primera reserva d'escapada (amb descompte 15%)");

        try {
            // Reservar "Weekend Barcelona" (450€)
            // Amb 15% descompte: 450 - (450 * 0.15) = 382.50€
            DTOReserva reserva1 = CtrlReservaEscapada::creaReserva(sobrenomTest, "Weekend Barcelona", 4);
            
            float preuEsperat = 450.00f * (1 - 0.15f);  // 382.50
            
            if (abs(reserva1.preuPagat - preuEsperat) < 0.01f) {
                cout << "? Reserva amb descompte correcta\n";
                cout << "  ID Reserva: " << reserva1.id << "\n";
                cout << "  Experiència: " << reserva1.experiencia.nom << "\n";
                cout << "  Places: " << reserva1.numPlaces << "\n";
                cout << "  Preu original: 450.00 €\n";
                cout << "  Descompte 15%: 67.50 €\n";
                cout << "  Preu pagat: " << fixed << setprecision(2) << reserva1.preuPagat << " €\n";
                testsPasats++;
            } else {
                cout << "? ERROR: El preu no és correcte\n";
                cout << "  Esperat: " << preuEsperat << " €\n";
                cout << "  Obtingut: " << reserva1.preuPagat << " €\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 2: SEGONA RESERVA SENSE DESCOMPTE (ESCAPADA)
        // ====================================================================
        separador();
        titol("TEST 2: Segona reserva d'escapada (sense descompte)");

        try {
            // Reservar "Madrid Cultural" (520€)
            // No ha d'aplicar descompte
            DTOReserva reserva2 = CtrlReservaEscapada::creaReserva(sobrenomTest, "Madrid Cultural", 4);
            
            float preuEsperat = 520.00f;  // Sense descompte
            
            if (abs(reserva2.preuPagat - preuEsperat) < 0.01f) {
                cout << "? Reserva sense descompte correcta\n";
                cout << "  ID Reserva: " << reserva2.id << "\n";
                cout << "  Experiència: " << reserva2.experiencia.nom << "\n";
                cout << "  Preu pagat: " << fixed << setprecision(2) << reserva2.preuPagat << " €\n";
                testsPasats++;
            } else {
                cout << "? ERROR: El preu no és correcte\n";
                cout << "  Esperat: " << preuEsperat << " €\n";
                cout << "  Obtingut: " << reserva2.preuPagat << " €\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 3: RESERVA D'ACTIVITAT (preu per persona)
        // ====================================================================
        separador();
        titol("TEST 3: Reserva d'activitat per 3 persones (sense descompte)");

        try {
            // Reservar "BTT Collserola" (40€ per persona) per 3 persones
            // 40 * 3 = 120€ (ja no aplica descompte)
            DTOReserva reserva3 = CtrlReservaActivitat::creaReserva(sobrenomTest, "BTT Collserola", 3);
            
            float preuEsperat = 40.00f * 3;  // 120€
            
            if (abs(reserva3.preuPagat - preuEsperat) < 0.01f) {
                cout << "? Reserva d'activitat correcta\n";
                cout << "  ID Reserva: " << reserva3.id << "\n";
                cout << "  Activitat: " << reserva3.experiencia.nom << "\n";
                cout << "  Persones: " << reserva3.numPlaces << "\n";
                cout << "  Preu per persona: 40.00 €\n";
                cout << "  Preu total: " << fixed << setprecision(2) << reserva3.preuPagat << " €\n";
                testsPasats++;
            } else {
                cout << "? ERROR: El preu no és correcte\n";
                cout << "  Esperat: " << preuEsperat << " €\n";
                cout << "  Obtingut: " << reserva3.preuPagat << " €\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 4: CONSULTAR RESERVES D'USUARI
        // ====================================================================
        separador();
        titol("TEST 4: Consultar totes les reserves de l'usuari");

        try {
            DTOLlistaReserves llista = CtrlConsultaReserves::consultaReserves(sobrenomTest);
            
            if (llista.reserves.size() == 3) {
                cout << "? Llista de reserves correcta\n";
                cout << "  Total reserves: " << llista.reserves.size() << "\n\n";
                
                cout << "  Detall de reserves:\n";
                cout << "  " << string(66, '-') << "\n";
                
                for (size_t i = 0; i < llista.reserves.size(); i++) {
                    const auto& res = llista.reserves[i];
                    cout << "  " << (i + 1) << ". " << res.experiencia.nom << "\n";
                    cout << "     Preu pagat: " << fixed << setprecision(2) << res.preuPagat << " €\n";
                    cout << "     Data: " << res.dataReserva << "\n\n";
                }
                
                cout << "  TOTAL PAGAT: " << fixed << setprecision(2) << llista.totalPagat << " €\n";
                
                // Verificar total
                float totalEsperat = 382.50f + 520.00f + 120.00f;  // 1022.50
                if (abs(llista.totalPagat - totalEsperat) < 0.01f) {
                    cout << "  ? Total verificat correctament\n";
                    testsPasats++;
                } else {
                    cout << "  ? ERROR en el total\n";
                    testsFallats++;
                }
            } else {
                cout << "? ERROR: Nombre de reserves incorrecte\n";
                cout << "  Esperat: 3\n";
                cout << "  Obtingut: " << llista.reserves.size() << "\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 5: PRIMERA RESERVA NOU USUARI (AMB DESCOMPTE)
        // ====================================================================
        separador();
        titol("TEST 5: Primera reserva d'un altre usuari (amb descompte)");

        try {
            // Usuari Joan (sense reserves prèvies)
            string sobrenomJoan = "joan";
            
            // Esborrar reserves anteriors si existeixen
            shared_ptr<Usuari> usuariJoan = DAOUsuari::obte(sobrenomJoan);
            if (usuariJoan) {
                vector<shared_ptr<Reserva>> reservesJoan = DAOReserva::obteReservesUsuari(usuariJoan);
                for (const auto& res : reservesJoan) {
                    DAOReserva::esborra(res->getId());
                }
            }
            
            // Activitat "Parapent Costa Brava" (85€) per 2 persones
            // 85 * 2 = 170€, amb 15% desc = 144.50€
            DTOReserva reservaJoan = CtrlReservaActivitat::creaReserva(sobrenomJoan, "Parapent Costa Brava", 2);
            
            float preuEsperat = (85.00f * 2) * (1 - 0.15f);  // 144.50
            
            if (abs(reservaJoan.preuPagat - preuEsperat) < 0.01f) {
                cout << "? Primera reserva amb descompte per Joan\n";
                cout << "  Preu base: 170.00 € (85€ x 2)\n";
                cout << "  Descompte 15%: 25.50 €\n";
                cout << "  Preu pagat: " << fixed << setprecision(2) << reservaJoan.preuPagat << " €\n";
                testsPasats++;
            } else {
                cout << "? ERROR: El preu no és correcte\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 6: VALIDACIÓ PLACES MÀXIMES
        // ====================================================================
        separador();
        titol("TEST 6: Intentar reservar més places del màxim");

        try {
            // "Costa Brava Luxury" té màxim 2 places
            // Intentar reservar per 3 persones
            DTOReserva reserva = CtrlReservaEscapada::creaReserva(sobrenomTest, "Costa Brava Luxury", 3);
            cout << "? ERROR: Hauria de rebutjar reserva que supera places màximes\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 7: RESERVA AMB EXPERIÈNCIA INEXISTENT
        // ====================================================================
        separador();
        titol("TEST 7: Intentar reservar experiència inexistent");

        try {
            DTOReserva reserva = CtrlReservaEscapada::creaReserva(sobrenomTest, "Experiència Falsa", 2);
            cout << "? ERROR: Hauria de rebutjar experiència inexistent\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 8: RESERVA AMB USUARI INEXISTENT
        // ====================================================================
        separador();
        titol("TEST 8: Intentar reservar amb usuari inexistent");

        try {
            DTOReserva reserva = CtrlReservaEscapada::creaReserva("usuari_fals", "Weekend Barcelona", 2);
            cout << "? ERROR: Hauria de rebutjar usuari inexistent\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 9: INCREMENT DEL COMPTADOR DE RESERVES
        // ====================================================================
        separador();
        titol("TEST 9: Verificar increment del comptador de reserves");

        try {
            // Obtenir experiència i verificar que numReserves ha augmentat
            shared_ptr<Experiencia> exp = DAOExperiencia::obte("Weekend Barcelona");
            if (exp && exp->getNumReserves() > 0) {
                cout << "? Comptador de reserves incrementat\n";
                cout << "  Experiència: " << exp->getNom() << "\n";
                cout << "  Nombre de reserves: " << exp->getNumReserves() << "\n";
                testsPasats++;
            } else {
                cout << "? ERROR: El comptador no s'ha incrementat\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 10: ESBORRAR RESERVES
        // ====================================================================
        separador();
        titol("TEST 10: Esborrar reserves de test");

        try {
            shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenomTest);
            if (usuari) {
                vector<shared_ptr<Reserva>> reserves = DAOReserva::obteReservesUsuari(usuari);
                int numEsborrades = reserves.size();
                
                for (const auto& res : reserves) {
                    DAOReserva::esborra(res->getId());
                }
                
                cout << "? Reserves esborrades: " << numEsborrades << "\n";
                testsPasats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // RESUM FINAL
        // ====================================================================
        separador();
        titol("RESUM DEL JOC DE PROVA 04");

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
