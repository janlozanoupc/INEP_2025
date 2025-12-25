#include "CtrlConsultaNovetats.hxx"
#include "../CapaDades/DAOEscapada.hxx"
#include "../CapaDades/DAOActivitat.hxx"
#include <stdexcept>
#include <algorithm>

using namespace std;

// PRE: limit > 0
// POST: retorna un vector amb les últimes 'limit' experiències (escapades i activitats) ordenades per data d'alta
vector<DTOExperiencia> CtrlConsultaNovetats::consultaNovetats(int limit) {
    // Validar paràmetre
    if (limit <= 0) {
        throw runtime_error("El límit ha de ser superior a 0");
    }

    vector<DTOExperiencia> experiencies;

    // Obtenir últimes escapades
    vector<shared_ptr<Escapada>> escapades = DAOEscapada::obteUltimes(limit);
    for (const auto& escapada : escapades) {
        experiencies.push_back(escapada->obteInfo());
    }

    // Obtenir últimes activitats
    vector<shared_ptr<Activitat>> activitats = DAOActivitat::obteUltimes(limit);
    for (const auto& activitat : activitats) {
        experiencies.push_back(activitat->obteInfo());
    }

    // Ordenar totes les experiències per data d'alta (més recents primer)
    sort(experiencies.begin(), experiencies.end(), 
         [](const DTOExperiencia& a, const DTOExperiencia& b) {
             return a.dataAlta > b.dataAlta;
         });

    // Limitar al nombre màxim demanat
    if (experiencies.size() > static_cast<size_t>(limit)) {
        experiencies.resize(limit);
    }

    return experiencies;
}
