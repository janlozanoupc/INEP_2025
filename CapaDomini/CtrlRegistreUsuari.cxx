#include "CtrlRegistreUsuari.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: tots els paràmetres són vàlids segons les regles de negoci
// POST: retorna DTOUsuari del nou usuari creat
//       llança runtime_error si l'usuari ja existeix o les dades no són vàlides
DTOUsuari CtrlRegistreUsuari::registraUsuari(const string& sobrenom, const string& nom, 
                                             const string& contrasenya, const string& correuElectronic, 
                                             int edat) {
    // Validar que els camps no estiguin buits
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }
    if (nom.empty()) {
        throw runtime_error("El nom no pot estar buit");
    }
    if (contrasenya.empty()) {
        throw runtime_error("La contrasenya no pot estar buida");
    }
    if (correuElectronic.empty()) {
        throw runtime_error("El correu electrònic no pot estar buit");
    }

    // Validar l'edat (>= 18 anys)
    if (edat < 18) {
        throw runtime_error("L'edat ha de ser igual o superior a 18 anys");
    }

    // Comprovar que l'usuari no existeix ja
    if (DAOUsuari::existeix(sobrenom)) {
        throw runtime_error("Ja existeix un usuari amb aquest sobrenom");
    }

    // Crear el nou usuari
    shared_ptr<Usuari> nouUsuari = make_shared<Usuari>(sobrenom, nom, contrasenya, correuElectronic, edat);

    // Insertar l'usuari a la base de dades
    DAOUsuari::inserta(nouUsuari);

    // Retornar les dades de l'usuari com a DTO
    return nouUsuari->obteInfo();
}
