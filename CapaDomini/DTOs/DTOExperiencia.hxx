#ifndef DTOEXPERIENCIA_HXX
#define DTOEXPERIENCIA_HXX

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

class DTOExperiencia {
public:
    // Atributs comuns
    string nom;
    string descripcio;
    string ciutat;
    string tipusExperiencia; // "ESCAPADA" o "ACTIVITAT"
    int maximPlaces;
    int numReserves;
    float preu;
    date dataAlta;

    // Atributs específics (opcionals)
    string hotel;         // Per Escapada
    int numNits;          // Per Escapada (0 si no aplica)
    int durada;           // Per Activitat (0 si no aplica)

    // Constructor per defecte
    DTOExperiencia();

    // Constructor amb paràmetres comuns
    DTOExperiencia(const string& n, const string& desc, const string& c, 
                   const string& tipus, int maxPlaces, int numRes, 
                   float pr, const date& data);
};

#endif // DTOEXPERIENCIA_HXX
