#include "CtrlConsultaMesReservades.hxx"
#include "../CapaDades/DAOEscapada.hxx"
#include "../CapaDades/DAOActivitat.hxx"
#include <stdexcept>
#include <algorithm>

using namespace std;

// PRE: limit > 0
// POST: retorna un vector amb les 'limit' experiències (escapades i activitats) amb més reserves
vector<DTOExperiencia> CtrlConsultaMesReservades::consultaMesReservades(int limit) {
    // Validar paràmetre
    if (limit <= 0) {
        throw runtime_error("El límit ha de ser superior a 0");
    }

    vector<DTOExperiencia> experiencies;

    // Obtenir top escapades
    vector<shared_ptr<Escapada>> escapades = DAOEscapada::obteTopMesReservades(limit);
    for (const auto& escapada : escapades) {
        experiencies.push_back(escapada->obteInfo());
    }

    // Obtenir top activitats
    vector<shared_ptr<Activitat>> activitats = DAOActivitat::obteTopMesReservades(limit);
    for (const auto& activitat : activitats) {
        experiencies.push_back(activitat->obteInfo());
    }

    // Ordenar totes les experiències per nombre de reserves (més reserves primer)
    sort(experiencies.begin(), experiencies.end(), 
         [](const DTOExperiencia& a, const DTOExperiencia& b) {
             return a.numReserves > b.numReserves;
         });

    // Limitar al nombre màxim demanat
    if (experiencies.size() > static_cast<size_t>(limit)) {
        experiencies.resize(limit);
    }

    return experiencies;
}
