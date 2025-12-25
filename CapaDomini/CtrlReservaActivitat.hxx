#ifndef CTRLRESERVAACTIVITAT_HXX
#define CTRLRESERVAACTIVITAT_HXX

#include <string>
#include "DTOs/DTOReserva.hxx"

using namespace std;

class CtrlReservaActivitat {
public:
    // Crear una nova reserva d'activitat per a un usuari
    // PRE: sobrenom i nomActivitat no buits, numPersones > 0, numPersones <= maximPlaces
    // POST: retorna DTOReserva amb la informació de la reserva creada
    //       aplica descompte automàticament si és la primera reserva de l'usuari
    //       llança runtime_error si l'usuari o l'activitat no existeixen o es supera el màxim de places
    static DTOReserva creaReserva(const string& sobrenom, const string& nomActivitat, 
                                  int numPersones);
};

#endif // CTRLRESERVAACTIVITAT_HXX
