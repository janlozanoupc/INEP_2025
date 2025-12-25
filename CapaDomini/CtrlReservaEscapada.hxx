#ifndef CTRLRESERVAESCAPADA_HXX
#define CTRLRESERVAESCAPADA_HXX

#include <string>
#include "DTOs/DTOReserva.hxx"

using namespace std;

class CtrlReservaEscapada {
public:
    // Crear una nova reserva d'escapada per a un usuari
    // PRE: sobrenom i nomExperiencia no buits, numPlaces > 0
    // POST: retorna DTOReserva amb la informació de la reserva creada
    //       aplica descompte automàticament si és la primera reserva de l'usuari
    //       llança runtime_error si l'usuari o l'experiència no existeixen
    static DTOReserva creaReserva(const string& sobrenom, const string& nomExperiencia, 
                                  int numPlaces);
};

#endif // CTRLRESERVAESCAPADA_HXX
