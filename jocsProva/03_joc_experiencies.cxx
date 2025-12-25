#include <iostream>
#include <iomanip>
#include "../CapaDades/DAOExperiencia.hxx"
#include "../CapaDades/DAOEscapada.hxx"
#include "../CapaDades/DAOActivitat.hxx"
#include "../CapaDomini/Model/Escapada.hxx"
#include "../CapaDomini/Model/Activitat.hxx"

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
    titol("JOC DE PROVA 03: GESTIÓ D'EXPERIÈNCIES");

    int testsPasats = 0;
    int testsFallats = 0;

    try {
        // ====================================================================
        // TEST 1: CREAR NOVA ESCAPADA
        // ====================================================================
        titol("TEST 1: Crear nova escapada");

        string nomEscapada = "Test Escapada Valencia";
        
        // Esborrar si ja existeix
        if (DAOExperiencia::existeix(nomEscapada)) {
            DAOExperiencia::esborra(nomEscapada);
        }

        try {
            shared_ptr<Escapada> novaEscapada = make_shared<Escapada>(
                nomEscapada,
                "Escapada de test a València amb paella i platja",
                "València",
                4,      // 4 places
                350.00, // 350€
                "Hotel Las Arenas",
                2       // 2 nits
            );

            DAOExperiencia::inserta(novaEscapada);
            
            cout << "? Escapada creada correctament\n";
            cout << "  Nom: " << novaEscapada->getNom() << "\n";
            cout << "  Ciutat: " << novaEscapada->getCiutat() << "\n";
            cout << "  Preu: " << fixed << setprecision(2) << novaEscapada->getPreu() << " €\n";
            cout << "  Hotel: " << novaEscapada->getHotel() << "\n";
            cout << "  Nits: " << novaEscapada->getNumNits() << "\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 2: CREAR NOVA ACTIVITAT
        // ====================================================================
        separador();
        titol("TEST 2: Crear nova activitat");

        string nomActivitat = "Test Senderisme Montseny";
        
        if (DAOExperiencia::existeix(nomActivitat)) {
            DAOExperiencia::esborra(nomActivitat);
        }

        try {
            shared_ptr<Activitat> novaActivitat = make_shared<Activitat>(
                nomActivitat,
                "Ruta de senderisme pel Parc Natural del Montseny",
                "Montseny",
                15,     // 15 places
                35.00,  // 35€ per persona
                240     // 240 minuts (4 hores)
            );

            DAOExperiencia::inserta(novaActivitat);
            
            cout << "? Activitat creada correctament\n";
            cout << "  Nom: " << novaActivitat->getNom() << "\n";
            cout << "  Ciutat: " << novaActivitat->getCiutat() << "\n";
            cout << "  Preu per persona: " << fixed << setprecision(2) << novaActivitat->getPreu() << " €\n";
            cout << "  Places: " << novaActivitat->getMaximPlaces() << "\n";
            cout << "  Durada: " << novaActivitat->getDurada() << " minuts\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 3: OBTENIR TOTES LES EXPERIÈNCIES
        // ====================================================================
        separador();
        titol("TEST 3: Obtenir totes les experiències");

        try {
            vector<shared_ptr<Experiencia>> experiencies = DAOExperiencia::tots();
            cout << "? Llista d'experiències obtinguda\n";
            cout << "  Total experiències: " << experiencies.size() << "\n\n";
            
            cout << "  Experiències disponibles:\n";
            cout << "  " << string(66, '-') << "\n";
            for (const auto& exp : experiencies) {
                DTOExperiencia dto = exp->obteInfo();
                cout << "  " << left << setw(30) << dto.nom 
                     << " | " << setw(15) << dto.tipusExperiencia
                     << " | " << setw(12) << dto.ciutat
                     << " | " << fixed << setprecision(0) << dto.preu << " €\n";
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 4: FILTRAR ESCAPADES PER CIUTAT
        // ====================================================================
        separador();
        titol("TEST 4: Filtrar escapades per ciutat i places");

        try {
            vector<shared_ptr<Escapada>> escapades = DAOEscapada::obtePerCiutatIPlaces("Barcelona", 2);
            cout << "? Escapades filtrades per ciutat=Barcelona i places>=2\n";
            cout << "  Total trobades: " << escapades.size() << "\n\n";
            
            for (const auto& esc : escapades) {
                cout << "  - " << esc->getNom() << " (" << esc->getMaximPlaces() << " places)\n";
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 5: FILTRAR ACTIVITATS PER CIUTAT
        // ====================================================================
        separador();
        titol("TEST 5: Filtrar activitats per ciutat i places");

        try {
            vector<shared_ptr<Activitat>> activitats = DAOActivitat::obtePerCiutatIPlaces("Barcelona", 5);
            cout << "? Activitats filtrades per ciutat=Barcelona i places>=5\n";
            cout << "  Total trobades: " << activitats.size() << "\n\n";
            
            for (const auto& act : activitats) {
                cout << "  - " << act->getNom() << " (" << act->getMaximPlaces() << " places)\n";
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 6: OBTENIR ÚLTIMES EXPERIÈNCIES
        // ====================================================================
        separador();
        titol("TEST 6: Obtenir últimes 5 escapades donades d'alta");

        try {
            vector<shared_ptr<Escapada>> ultimes = DAOEscapada::obteUltimes(5);
            cout << "? Últimes escapades obtingudes\n";
            cout << "  Total: " << ultimes.size() << "\n\n";
            
            for (const auto& esc : ultimes) {
                cout << "  - " << esc->getNom() << " (Alta: " << esc->getDataAlta() << ")\n";
            }
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 7: MODIFICAR ESCAPADA
        // ====================================================================
        separador();
        titol("TEST 7: Modificar dades d'una escapada");

        try {
            shared_ptr<Experiencia> exp = DAOExperiencia::obte(nomEscapada);
            if (exp) {
                shared_ptr<Escapada> escapada = dynamic_pointer_cast<Escapada>(exp);
                if (escapada) {
                    escapada->setPreu(399.00); // Nou preu
                    escapada->setHotel("Hotel Nuevo Las Arenas");
                    
                    DAOExperiencia::modifica(escapada);
                    
                    cout << "? Escapada modificada correctament\n";
                    cout << "  Nou preu: " << fixed << setprecision(2) << escapada->getPreu() << " €\n";
                    cout << "  Nou hotel: " << escapada->getHotel() << "\n";
                    testsPasats++;
                } else {
                    cout << "? ERROR: No s'ha pogut fer cast a Escapada\n";
                    testsFallats++;
                }
            } else {
                cout << "? ERROR: No s'ha trobat l'escapada\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 8: MODIFICAR ACTIVITAT
        // ====================================================================
        separador();
        titol("TEST 8: Modificar dades d'una activitat");

        try {
            shared_ptr<Experiencia> exp = DAOExperiencia::obte(nomActivitat);
            if (exp) {
                shared_ptr<Activitat> activitat = dynamic_pointer_cast<Activitat>(exp);
                if (activitat) {
                    activitat->setPreu(40.00); // Nou preu
                    activitat->setDurada(300); // Nova durada
                    
                    DAOExperiencia::modifica(activitat);
                    
                    cout << "? Activitat modificada correctament\n";
                    cout << "  Nou preu: " << fixed << setprecision(2) << activitat->getPreu() << " €\n";
                    cout << "  Nova durada: " << activitat->getDurada() << " minuts\n";
                    testsPasats++;
                } else {
                    cout << "? ERROR: No s'ha pogut fer cast a Activitat\n";
                    testsFallats++;
                }
            } else {
                cout << "? ERROR: No s'ha trobat l'activitat\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 9: CÀLCUL DE PREU PER ESCAPADA (fix)
        // ====================================================================
        separador();
        titol("TEST 9: Verificar càlcul de preu per escapada (preu fix)");

        try {
            shared_ptr<Experiencia> exp = DAOExperiencia::obte(nomEscapada);
            if (exp) {
                // Per escapades, el preu és fix independentment del nombre de persones
                float preu1 = exp->calculaPreu(1);
                float preu4 = exp->calculaPreu(4);
                
                if (preu1 == preu4) {
                    cout << "? Correcte: Preu fix per escapada\n";
                    cout << "  Preu per 1 persona: " << fixed << setprecision(2) << preu1 << " €\n";
                    cout << "  Preu per 4 persones: " << preu4 << " €\n";
                    testsPasats++;
                } else {
                    cout << "? ERROR: El preu hauria de ser fix\n";
                    testsFallats++;
                }
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 10: CÀLCUL DE PREU PER ACTIVITAT (per persona)
        // ====================================================================
        separador();
        titol("TEST 10: Verificar càlcul de preu per activitat (per persona)");

        try {
            shared_ptr<Experiencia> exp = DAOExperiencia::obte(nomActivitat);
            if (exp) {
                float preuBase = exp->getPreu();
                float preu3 = exp->calculaPreu(3);
                float preuEsperat = preuBase * 3;
                
                if (preu3 == preuEsperat) {
                    cout << "? Correcte: Preu per persona multiplicat\n";
                    cout << "  Preu base: " << fixed << setprecision(2) << preuBase << " €\n";
                    cout << "  Preu per 3 persones: " << preu3 << " €\n";
                    testsPasats++;
                } else {
                    cout << "? ERROR: El càlcul no és correcte\n";
                    cout << "  Esperat: " << preuEsperat << " €, Obtingut: " << preu3 << " €\n";
                    testsFallats++;
                }
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 11: ESBORRAR EXPERIÈNCIES
        // ====================================================================
        separador();
        titol("TEST 11: Esborrar experiències de test");

        try {
            DAOExperiencia::esborra(nomEscapada);
            DAOExperiencia::esborra(nomActivitat);
            
            cout << "? Experiències de test esborrades\n";
            testsPasats++;
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // RESUM FINAL
        // ====================================================================
        separador();
        titol("RESUM DEL JOC DE PROVA 03");

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
