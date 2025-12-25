#ifndef CTRLCONSULTANOVETATS_HXX
#define CTRLCONSULTANOVETATS_HXX

#include <vector>
#include "DTOs/DTOExperiencia.hxx"

using namespace std;

class CtrlConsultaNovetats {
public:
    // Consultar les últimes experiències donades d'alta
    // PRE: limit > 0
    // POST: retorna un vector amb les últimes 'limit' experiències (escapades i activitats) ordenades per data d'alta
    static vector<DTOExperiencia> consultaNovetats(int limit = 10);
};

#endif // CTRLCONSULTANOVETATS_HXX
