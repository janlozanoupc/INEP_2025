#ifndef DAOEXPERIENCIA_HXX
#define DAOEXPERIENCIA_HXX

#include <memory>
#include <vector>
#include <string>
#include "../CapaDomini/Model/Experiencia.hxx"

using namespace std;

class DAOExperiencia {
public:
    // Obtenir una experiència pel seu nom
    // PRE: cert
    // POST: retorna l'experiència amb el nom especificat, o nullptr si no existeix
    static shared_ptr<Experiencia> obte(const string& nom);

    // Comprovar si existeix una experiència
    // PRE: cert
    // POST: retorna true si existeix l'experiència amb el nom especificat
    static bool existeix(const string& nom);

    // Obtenir totes les experiències
    // PRE: cert
    // POST: retorna un vector amb totes les experiències de la BD
    static vector<shared_ptr<Experiencia>> tots();

    // Insertar una nova experiència
    // PRE: exp != nullptr, no existeix experiència amb el mateix nom
    // POST: l'experiència s'ha insertat a la BD
    static void inserta(shared_ptr<Experiencia> exp);

    // Modificar una experiència existent
    // PRE: exp != nullptr, existeix experiència amb el mateix nom
    // POST: les dades de l'experiència s'han actualitzat a la BD
    static void modifica(shared_ptr<Experiencia> exp);

    // Esborrar una experiència
    // PRE: existeix experiència amb el nom especificat
    // POST: l'experiència s'ha esborrat de la BD
    static void esborra(const string& nom);
};

#endif // DAOEXPERIENCIA_HXX
