#ifndef TESTPLANGO_HXX
#define TESTPLANGO_HXX

#include <string>
#include <vector>

using namespace std;

class TestPlanGo {
public:
    // Executar tots els tests
    static void executarTotsElsTests();

private:
    // Tests del model
    static bool test01_CrearPlanGoSingleton();
    static bool test02_ConfigurarDescompte();
    static bool test03_CrearUsuari();
    static bool test04_CrearEscapada();
    static bool test05_CrearActivitat();

    // Tests de DAOs
    static bool test06_DAOUsuariInsertarIObte();
    static bool test07_DAOExperienciaInsertarIObte();
    static bool test08_DAOReservaInsertarIObte();

    // Tests de controladors bàsics
    static bool test09_RegistreUsuari();
    static bool test10_IniciSessioCorrecte();
    static bool test11_IniciSessioIncorrecte();

    // Tests de reserves
    static bool test12_ReservaEscapadaAmbDescompte();
    static bool test13_ReservaEscapadaSenseDescompte();
    static bool test14_ReservaActivitat();
    static bool test15_ConsultaReserves();

    // Tests de gestió d'usuaris
    static bool test16_ModificarUsuari();
    static bool test17_EsborrarUsuari();

    // Tests de consultes avançades
    static bool test18_ConsultaExperienciesPerCiutat();
    static bool test19_ConsultaNovetats();
    static bool test20_ConsultaMesReservades();

    // Mètodes auxiliars
    static void mostrarResultat(const string& nomTest, bool resultat);
    static void netejaBD();
    static void inicialitzarDadesTest();
};

#endif // TESTPLANGO_HXX
