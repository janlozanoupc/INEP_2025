#ifndef CTRLCONSULTAMESRESERVADES_HXX
#define CTRLCONSULTAMESRESERVADES_HXX

#include <vector>
#include "DTOs/DTOExperiencia.hxx"

using namespace std;

class CtrlConsultaMesReservades {
public:
    // Consultar les experiències més reservades
    // PRE: limit > 0
    // POST: retorna un vector amb les 'limit' experiències (escapades i activitats) amb més reserves
    static vector<DTOExperiencia> consultaMesReservades(int limit = 5);
};

#endif // CTRLCONSULTAMESRESERVADES_HXX
