#ifndef CAPADEPRESENTACIO_HXX
#define CAPADEPRESENTACIO_HXX

#include <string>

using namespace std;

class CapaDePresentacio {
public:
    // Obtenir instància única del singleton
    // PRE: cert
    // POST: retorna la instància única de CapaDePresentacio
    static CapaDePresentacio& getInstance();

    // Executar el menú principal de l'aplicació
    // PRE: cert
    // POST: mostra el menú i gestiona les opcions de l'usuari
    void executar();

private:
    // Constructor privat (Singleton)
    CapaDePresentacio();

    // Mètodes per a cada cas d'ús
    void iniciarSessio();
    void registrarUsuari();
    void reservarEscapada();
    void consultarReserves();
    void configurarDescompte();
    void mostrarTotesExperiencies();

    // Mètodes auxiliars
    void mostrarMenuPrincipal();
    void mostrarMenuUsuari(const string& sobrenom);
    void pausar();
    void netejaPantalla();

    // Atribut per guardar l'usuari actual (si ha iniciat sessió)
    string _usuariActual;

    // Instància única del singleton
    static CapaDePresentacio* _instancia;
};

#endif // CAPADEPRESENTACIO_HXX
