#include "CtrlModificaUsuari.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: sobrenom no buit, edat >= 18
// POST: retorna DTOUsuari amb les dades actualitzades
//       llança runtime_error si l'usuari no existeix o el nou email ja està en ús per un altre usuari
DTOUsuari CtrlModificaUsuari::modificaUsuari(const string& sobrenom, const string& nouNom, 
                                             const string& nouCorreuElectronic, int novaEdat) {
    // Validar paràmetres
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }
    if (nouNom.empty()) {
        throw runtime_error("El nom no pot estar buit");
    }
    if (nouCorreuElectronic.empty()) {
        throw runtime_error("El correu electrònic no pot estar buit");
    }
    if (novaEdat < 18) {
        throw runtime_error("L'edat ha de ser igual o superior a 18 anys");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Comprovar si el nou email és diferent de l'actual
    if (nouCorreuElectronic != usuari->getCorreuElectronic()) {
        // Verificar que el nou email no estigui en ús per un altre usuari
        vector<shared_ptr<Usuari>> totsUsuaris = DAOUsuari::tots();
        for (const auto& u : totsUsuaris) {
            if (u->getCorreuElectronic() == nouCorreuElectronic && u->getSobrenom() != sobrenom) {
                throw runtime_error("El correu electrònic ja està en ús per un altre usuari");
            }
        }
    }

    // Actualitzar les dades de l'usuari
    usuari->setNom(nouNom);
    usuari->setCorreuElectronic(nouCorreuElectronic);
    usuari->setEdat(novaEdat);

    // Guardar els canvis a la base de dades
    DAOUsuari::modifica(usuari);

    // Retornar les dades actualitzades com a DTO
    return usuari->obteInfo();
}
