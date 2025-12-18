#ifndef DTOLLISTARESERVES_HXX
#define DTOLLISTARESERVES_HXX

#include "DTOReserva.hxx"
#include <vector>

using namespace std;

class DTOLlistaReserves {
public:
    float totalPagat;
    vector<DTOReserva> reserves;

    // Constructor per defecte
    DTOLlistaReserves();

    // Constructor amb paràmetres
    DTOLlistaReserves(float total, const vector<DTOReserva>& res);
};

#endif // DTOLLISTARESERVES_HXX
