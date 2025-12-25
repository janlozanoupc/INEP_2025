#ifndef CTRLCONSULTAEXPERIENCIES_HXX
#define CTRLCONSULTAEXPERIENCIES_HXX

#include <string>
#include <vector>
#include "DTOs/DTOExperiencia.hxx"

using namespace std;

class CtrlConsultaExperiencies {
public:
    // Consultar experiències filtrades per ciutat i nombre de persones
    // PRE: ciutat no buida, numPersones > 0
    // POST: retorna un vector amb DTOExperiencia de totes les experiències que compleixen els filtres
    static vector<DTOExperiencia> consultaPerCiutatIPersones(const string& ciutat, int numPersones);
};

#endif // CTRLCONSULTAEXPERIENCIES_HXX
