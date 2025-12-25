#include "CtrlEsborraUsuari.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: sobrenom i contrasenya no buits
// POST: l'usuari ha estat esborrat de la BD (i les seves reserves per CASCADE)
//       llança runtime_error si l'usuari no existeix o la contrasenya és incorrecta
void CtrlEsborraUsuari::esborraUsuari(const string& sobrenom, const string& contrasenya) {
    // Validar paràmetres
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }
    if (contrasenya.empty()) {
        throw runtime_error("La contrasenya no pot estar buida");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Verificar que la contrasenya és correcta
    if (usuari->getContrasenya() != contrasenya) {
        throw runtime_error("La contrasenya és incorrecta");
    }

    // Esborrar l'usuari de la base de dades
    // Les reserves s'esborraran automàticament per CASCADE
    DAOUsuari::esborra(sobrenom);
}
