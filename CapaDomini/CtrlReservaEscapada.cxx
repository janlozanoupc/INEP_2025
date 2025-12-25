#include "CtrlReservaEscapada.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "../CapaDades/DAOExperiencia.hxx"
#include "../CapaDades/DAOReserva.hxx"
#include "Model/Usuari.hxx"
#include "Model/Experiencia.hxx"
#include "Model/Reserva.hxx"
#include "Model/PlanGo.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: sobrenom i nomExperiencia no buits, numPlaces > 0
// POST: retorna DTOReserva amb la informació de la reserva creada
//       aplica descompte automàticament si és la primera reserva de l'usuari
//       llança runtime_error si l'usuari o l'experiència no existeixen
DTOReserva CtrlReservaEscapada::creaReserva(const string& sobrenom, const string& nomExperiencia, 
                                            int numPlaces) {
    // Validar paràmetres
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }
    if (nomExperiencia.empty()) {
        throw runtime_error("El nom de l'experiència no pot estar buit");
    }
    if (numPlaces <= 0) {
        throw runtime_error("El nombre de places ha de ser superior a 0");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Obtenir l'experiència de la base de dades
    shared_ptr<Experiencia> experiencia = DAOExperiencia::obte(nomExperiencia);
    if (experiencia == nullptr) {
        throw runtime_error("L'experiència no existeix");
    }

    // Obtenir les reserves actuals de l'usuari per comprovar si és la primera reserva
    vector<shared_ptr<Reserva>> reservesUsuari = DAOReserva::obteReservesUsuari(usuari);
    bool primeraReserva = reservesUsuari.empty();

    // Crear la reserva amb el Factory Method
    // El mètode create ja aplicarà el descompte si primeraReserva és true
    shared_ptr<Reserva> novaReserva = Reserva::create(usuari, experiencia, numPlaces, primeraReserva);

    // Insertar la reserva a la base de dades
    DAOReserva::inserta(novaReserva);

    // Actualitzar l'experiència amb el comptador de reserves incrementat
    DAOExperiencia::modifica(experiencia);

    // Retornar la informació de la reserva com a DTO
    return novaReserva->obteInfo();
}
