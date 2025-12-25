#include "CtrlReservaActivitat.hxx"
#include "../CapaDades/DAOUsuari.hxx"
#include "../CapaDades/DAOExperiencia.hxx"
#include "../CapaDades/DAOReserva.hxx"
#include "Model/Usuari.hxx"
#include "Model/Experiencia.hxx"
#include "Model/Activitat.hxx"
#include "Model/Reserva.hxx"
#include <stdexcept>
#include <memory>

using namespace std;

// PRE: sobrenom i nomActivitat no buits, numPersones > 0, numPersones <= maximPlaces
// POST: retorna DTOReserva amb la informació de la reserva creada
//       aplica descompte automàticament si és la primera reserva de l'usuari
//       llança runtime_error si l'usuari o l'activitat no existeixen o es supera el màxim de places
DTOReserva CtrlReservaActivitat::creaReserva(const string& sobrenom, const string& nomActivitat, 
                                             int numPersones) {
    // Validar paràmetres
    if (sobrenom.empty()) {
        throw runtime_error("El sobrenom no pot estar buit");
    }
    if (nomActivitat.empty()) {
        throw runtime_error("El nom de l'activitat no pot estar buit");
    }
    if (numPersones <= 0) {
        throw runtime_error("El nombre de persones ha de ser superior a 0");
    }

    // Obtenir l'usuari de la base de dades
    shared_ptr<Usuari> usuari = DAOUsuari::obte(sobrenom);
    if (usuari == nullptr) {
        throw runtime_error("L'usuari no existeix");
    }

    // Obtenir l'experiència de la base de dades
    shared_ptr<Experiencia> experiencia = DAOExperiencia::obte(nomActivitat);
    if (experiencia == nullptr) {
        throw runtime_error("L'activitat no existeix");
    }

    // Verificar que és una activitat
    shared_ptr<Activitat> activitat = dynamic_pointer_cast<Activitat>(experiencia);
    if (activitat == nullptr) {
        throw runtime_error("L'experiència especificada no és una activitat");
    }

    // Validar que el nombre de persones no superi el màxim de places
    if (numPersones > activitat->getMaximPlaces()) {
        throw runtime_error("El nombre de persones supera el màxim de places disponibles");
    }

    // Obtenir les reserves actuals de l'usuari per comprovar si és la primera reserva
    vector<shared_ptr<Reserva>> reservesUsuari = DAOReserva::obteReservesUsuari(usuari);
    bool primeraReserva = reservesUsuari.empty();

    // Crear la reserva amb el Factory Method
    // El mètode create ja aplicarà el descompte si primeraReserva és true
    // Per activitats, el càlcul del preu serà: preu * numPersones
    shared_ptr<Reserva> novaReserva = Reserva::create(usuari, experiencia, numPersones, primeraReserva);

    // Insertar la reserva a la base de dades
    DAOReserva::inserta(novaReserva);

    // Actualitzar l'experiència amb el comptador de reserves incrementat
    DAOExperiencia::modifica(experiencia);

    // Retornar la informació de la reserva com a DTO
    return novaReserva->obteInfo();
}
