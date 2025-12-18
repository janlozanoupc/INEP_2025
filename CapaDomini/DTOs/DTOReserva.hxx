#ifndef DTORESERVA_HXX
#define DTORESERVA_HXX

#include "DTOExperiencia.hxx"
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

class DTOReserva {
public:
    int id;
    int numPlaces;
    float preuPagat;
    date dataReserva;
    DTOExperiencia experiencia;

    // Constructor per defecte
    DTOReserva();

    // Constructor amb paràmetres
    DTOReserva(int i, int numP, float preu, const date& data, const DTOExperiencia& exp);
};

#endif // DTORESERVA_HXX
