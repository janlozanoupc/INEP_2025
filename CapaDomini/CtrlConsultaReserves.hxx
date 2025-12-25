#ifndef CTRLCONSULTARESERVES_HXX
#define CTRLCONSULTARESERVES_HXX

#include <string>
#include "DTOs/DTOLlistaReserves.hxx"

using namespace std;

class CtrlConsultaReserves {
public:
    // Consultar totes les reserves d'un usuari
    // PRE: sobrenom no buit
    // POST: retorna DTOLlistaReserves amb totes les reserves de l'usuari i el total pagat
    //       llança runtime_error si l'usuari no existeix
    static DTOLlistaReserves consultaReserves(const string& sobrenom);
};

#endif // CTRLCONSULTARESERVES_HXX
