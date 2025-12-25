#include <iostream>
#include <iomanip>
#include "../CapaDomini/CtrlConsultaExperiencies.hxx"
#include "../CapaDomini/CtrlConsultaNovetats.hxx"
#include "../CapaDomini/CtrlConsultaMesReservades.hxx"

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
    titol("JOC DE PROVA 05: CONSULTES AVANÇADES");

    int testsPasats = 0;
    int testsFallats = 0;

    try {
        // ====================================================================
        // TEST 1: FILTRAR PER CIUTAT I PLACES (Barcelona, 4 persones)
        // ====================================================================
        titol("TEST 1: Filtrar experiències a Barcelona per 4 persones");

        try {
            vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("Barcelona", 4);
            
            cout << "? Consulta executada correctament\n";
            cout << "  Resultats trobats: " << exp.size() << "\n\n";
            
            if (!exp.empty()) {
                cout << "  Experiències disponibles:\n";
                cout << "  " << string(66, '-') << "\n";
                for (const auto& e : exp) {
                    cout << "  - " << left << setw(30) << e.nom;
                    cout << " | " << setw(12) << e.tipusExperiencia;
                    cout << " | Places: " << e.maximPlaces;
                    cout << " | " << fixed << setprecision(0) << e.preu << " €\n";
                }
                testsPasats++;
            } else {
                cout << "  ??  No s'han trobat experiències per aquests criteris\n";
                testsPasats++;  // No és un error, simplement no hi ha resultats
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 2: FILTRAR PER CIUTAT I PLACES (Girona, 5 persones)
        // ====================================================================
        separador();
        titol("TEST 2: Filtrar experiències a Girona per 5 persones");

        try {
            vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("Girona", 5);
            
            cout << "? Consulta executada correctament\n";
            cout << "  Resultats trobats: " << exp.size() << "\n\n";
            
            if (!exp.empty()) {
                for (const auto& e : exp) {
                    cout << "  - " << e.nom << " (Places: " << e.maximPlaces << ")\n";
                }
                testsPasats++;
            } else {
                cout << "  ??  No s'han trobat experiències per aquests criteris\n";
                testsPasats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 3: FILTRAR AMB CIUTAT QUE NO EXISTEIX
        // ====================================================================
        separador();
        titol("TEST 3: Filtrar amb ciutat inexistent");

        try {
            vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("CiutatFalsa", 2);
            
            if (exp.empty()) {
                cout << "? Correcte: No hi ha resultats per ciutat inexistent\n";
                testsPasats++;
            } else {
                cout << "? ERROR: Hauria de retornar llista buida\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 4: CONSULTAR NOVETATS (últimes 10 experiències)
        // ====================================================================
        separador();
        titol("TEST 4: Consultar últimes 10 experiències (novetats)");

        try {
            vector<DTOExperiencia> novetats = CtrlConsultaNovetats::consultaNovetats(10);
            
            cout << "? Novetats obtingudes\n";
            cout << "  Total experiències: " << novetats.size() << "\n\n";
            
            if (!novetats.empty()) {
                cout << "  Últimes experiències donades d'alta:\n";
                cout << "  " << string(66, '-') << "\n";
                
                for (size_t i = 0; i < novetats.size() && i < 10; i++) {
                    const auto& e = novetats[i];
                    cout << "  " << (i + 1) << ". " << left << setw(30) << e.nom;
                    cout << " | " << e.dataAlta;
                    cout << " | " << e.tipusExperiencia << "\n";
                }
                testsPasats++;
            } else {
                cout << "  ??  No hi ha experiències a la BD\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 5: CONSULTAR NOVETATS AMB LÍMIT REDUÏT
        // ====================================================================
        separador();
        titol("TEST 5: Consultar últimes 3 experiències");

        try {
            vector<DTOExperiencia> novetats = CtrlConsultaNovetats::consultaNovetats(3);
            
            if (novetats.size() <= 3) {
                cout << "? Límit respectat correctament\n";
                cout << "  Experiències retornades: " << novetats.size() << "\n";
                testsPasats++;
            } else {
                cout << "? ERROR: S'ha superat el límit demanat\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 6: TOP 5 EXPERIÈNCIES MÉS RESERVADES
        // ====================================================================
        separador();
        titol("TEST 6: Consultar Top 5 experiències més reservades");

        try {
            vector<DTOExperiencia> topExp = CtrlConsultaMesReservades::consultaMesReservades(5);
            
            cout << "? Top experiències obtingut\n";
            cout << "  Total experiències: " << topExp.size() << "\n\n";
            
            if (!topExp.empty()) {
                cout << "  Top experiències més populars:\n";
                cout << "  " << string(66, '-') << "\n";
                
                for (size_t i = 0; i < topExp.size() && i < 5; i++) {
                    const auto& e = topExp[i];
                    cout << "  " << (i + 1) << ". " << left << setw(30) << e.nom;
                    cout << " | Reserves: " << setw(3) << e.numReserves;
                    cout << " | " << e.tipusExperiencia << "\n";
                }
                testsPasats++;
            } else {
                cout << "  ??  No hi ha reserves encara\n";
                testsPasats++;  // No és un error
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 7: TOP 3 MÉS RESERVADES
        // ====================================================================
        separador();
        titol("TEST 7: Consultar Top 3 més reservades");

        try {
            vector<DTOExperiencia> top3 = CtrlConsultaMesReservades::consultaMesReservades(3);
            
            if (top3.size() <= 3) {
                cout << "? Top 3 obtingut correctament\n";
                cout << "  Experiències retornades: " << top3.size() << "\n\n";
                
                if (!top3.empty()) {
                    // Verificar que estan ordenades descendentment
                    bool ordenades = true;
                    for (size_t i = 1; i < top3.size(); i++) {
                        if (top3[i].numReserves > top3[i-1].numReserves) {
                            ordenades = false;
                            break;
                        }
                    }
                    
                    if (ordenades) {
                        cout << "  ? Correctament ordenades per nombre de reserves\n";
                    } else {
                        cout << "  ? ERROR: No estan ordenades correctament\n";
                        testsFallats++;
                        testsPasats--;  // Compensar el ++ del final
                    }
                }
                testsPasats++;
            } else {
                cout << "? ERROR: S'ha superat el límit\n";
                testsFallats++;
            }
        } catch (const exception& e) {
            cout << "? ERROR: " << e.what() << "\n";
            testsFallats++;
        }

        // ====================================================================
        // TEST 8: FILTRAR AMB 0 PERSONES (validació)
        // ====================================================================
        separador();
        titol("TEST 8: Intentar filtrar amb 0 persones");

        try {
            vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("Barcelona", 0);
            cout << "? ERROR: Hauria de rebutjar 0 persones\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 9: FILTRAR AMB CIUTAT BUIDA
        // ====================================================================
        separador();
        titol("TEST 9: Intentar filtrar amb ciutat buida");

        try {
            vector<DTOExperiencia> exp = CtrlConsultaExperiencies::consultaPerCiutatIPersones("", 2);
            cout << "? ERROR: Hauria de rebutjar ciutat buida\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 10: NOVETATS AMB LÍMIT NEGATIU
        // ====================================================================
        separador();
        titol("TEST 10: Intentar consultar novetats amb límit negatiu");

        try {
            vector<DTOExperiencia> novetats = CtrlConsultaNovetats::consultaNovetats(-1);
            cout << "? ERROR: Hauria de rebutjar límit negatiu\n";
            testsFallats++;
        } catch (const exception& e) {
            cout << "? Correcte: " << e.what() << "\n";
            testsPasats++;
        }

        // ====================================================================
        // TEST 11: VERIFICAR QUE NOVETATS ESTÀ ORDENAT PER DATA
        // ====================================================================
        separador();
        titol("TEST 11: Verificar ordenació de novetats per data");

        try {
            vector<DTOExperiencia> novetats = CtrlConsultaNovetats::consultaNovetats(5);
            
            if (novetats.size() >= 2) {
                bool ordenades = true;
                for (size_t i = 1; i < novetats.size(); i++) {
                    if (novetats[i].dataAlta > novetats[i-1].dataAlta) {
                        ordenades = false;
                        break;
                    }
                }
                
                if (ordenades) {
                    cout << "? Novetats correctament ordenades per data (desc)\n";
                    testsPasats++;
                } else {
                    cout << "? ERROR: No estan ordenades per data\n";
                    testsFallats++;
                }
            } else {
                cout << "  ??  No hi ha prou experiències per verificar ordenació\n";
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
        titol("RESUM DEL JOC DE PROVA 05");

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
