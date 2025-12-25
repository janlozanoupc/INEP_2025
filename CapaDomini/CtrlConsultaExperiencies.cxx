#include "CtrlConsultaExperiencies.hxx"
#include "../CapaDades/DAOEscapada.hxx"
#include "../CapaDades/DAOActivitat.hxx"
#include <stdexcept>

using namespace std;

// PRE: ciutat no buida, numPersones > 0
// POST: retorna un vector amb DTOExperiencia de totes les experiències que compleixen els filtres
vector<DTOExperiencia> CtrlConsultaExperiencies::consultaPerCiutatIPersones(const string& ciutat, int numPersones) {
    // Validar paràmetres
    if (ciutat.empty()) {
        throw runtime_error("La ciutat no pot estar buida");
    }
    if (numPersones <= 0) {
        throw runtime_error("El nombre de persones ha de ser superior a 0");
    }

    vector<DTOExperiencia> experiencies;

    // Obtenir escapades que compleixen els filtres
    vector<shared_ptr<Escapada>> escapades = DAOEscapada::obtePerCiutatIPlaces(ciutat, numPersones);
    for (const auto& escapada : escapades) {
        experiencies.push_back(escapada->obteInfo());
    }

    // Obtenir activitats que compleixen els filtres
    vector<shared_ptr<Activitat>> activitats = DAOActivitat::obtePerCiutatIPlaces(ciutat, numPersones);
    for (const auto& activitat : activitats) {
        experiencies.push_back(activitat->obteInfo());
    }

    return experiencies;
}
