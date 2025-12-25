#include "CtrlConsultaReserves.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "../CapaDades/DAOReserva.hxx"
#include "Model/Usuari.hxx"
#include "Model/Reserva.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: sobrenom no buit
// POST: retorna DTOLlistaReserves amb totes les reserves de l'usuari i el total pagat
//       llança runtime_error si l'usuari no existeix
DTOLlistaReserves CtrlConsultaReserves::consultaReserves(const string& sobrenom) {
    // Validar paràmetre
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Obtenir totes les reserves de l'usuari
    vector<shared_ptr<Reserva>> reserves = DAOReserva::obteReservesUsuari(usuari);

    // Crear el DTO de llista de reserves
    DTOLlistaReserves dto;
    dto.totalPagat = 0.0f;
    dto.reserves.clear();

    // Processar cada reserva
    for (const auto& reserva : reserves) {
        // Obtenir la informació de la reserva com a DTO
        DTOReserva dtoReserva = reserva->obteInfo();
        
        // Afegir al vector de reserves
        dto.reserves.push_back(dtoReserva);
        
        // Acumular el total pagat
        dto.totalPagat += reserva->getPreuPagat();
    }

    return dto;
}
