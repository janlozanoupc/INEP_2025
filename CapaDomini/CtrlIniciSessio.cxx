#include "CtrlIniciSessio.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>

using namespace std;

// PRE: sobrenom i contrasenya no buits
// POST: retorna DTOUsuari si les credencials són correctes
//       llança runtime_error si l'usuari no existeix o la contrasenya és incorrecta
DTOUsuari CtrlIniciSessio::iniciSessio(const string& sobrenom, const string& contrasenya) {
    // Verificar que els paràmetres no siguin buits
    if (sobrenom.empty() || contrasenya.empty()) {
        throw runtime_error("El sobrenom i la contrasenya no poden estar buits");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);

    // Verificar que l'usuari existeix
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Verificar que la contrasenya és correcta
    if (usuari->getContrasenya() != contrasenya) {
        throw runtime_error("La contrasenya és incorrecta");
    }

    // Retornar les dades de l'usuari com a DTO
    return usuari->obteInfo();
}
