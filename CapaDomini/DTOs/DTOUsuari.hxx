#ifndef DTOUSUARI_HXX
#define DTOUSUARI_HXX

#include <string>

using namespace std;

class DTOUsuari {
public:
    string sobrenom;
    string nom;
    string correuElectronic;
    int edat;
    int numReserves;

    // Constructor per defecte
    DTOUsuari();

    // Constructor amb paràmetres
    DTOUsuari(const string& sobr, const string& n, const string& email, int e, int numRes);
};

#endif // DTOUSUARI_HXX
