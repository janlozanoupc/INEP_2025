#ifndef DAOUSUARI_HXX
#define DAOUSUARI_HXX

#include <memory>
#include <vector>
#include <string>
#include "../CapaDomini/Model/Usuari.hxx"

using namespace std;

class DAOUsuari {
public:
    // Obtenir un usuari pel seu sobrenom
    // PRE: cert
    // POST: retorna l'usuari amb el sobrenom especificat, o nullptr si no existeix
    static shared_ptr<Usuari> obte(const string& sobrenom);

    // Comprovar si existeix un usuari
    // PRE: cert
    // POST: retorna true si existeix l'usuari amb el sobrenom especificat
    static bool existeix(const string& sobrenom);

    // Obtenir tots els usuaris
    // PRE: cert
    // POST: retorna un vector amb tots els usuaris de la BD
    static vector<shared_ptr<Usuari>> tots();

    // Insertar un nou usuari
    // PRE: u != nullptr, no existeix usuari amb el mateix sobrenom
    // POST: l'usuari s'ha insertat a la BD
    static void inserta(shared_ptr<Usuari> u);

    // Modificar un usuari existent
    // PRE: u != nullptr, existeix usuari amb el mateix sobrenom
    // POST: les dades de l'usuari s'han actualitzat a la BD
    static void modifica(shared_ptr<Usuari> u);

    // Esborrar un usuari
    // PRE: existeix usuari amb el sobrenom especificat
    // POST: l'usuari s'ha esborrat de la BD (i les seves reserves per CASCADE)
    static void esborra(const string& sobrenom);
};

#endif // DAOUSUARI_HXX
