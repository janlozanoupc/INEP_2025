#ifndef DAOACTIVITAT_HXX
#define DAOACTIVITAT_HXX

#include <memory>
#include <vector>
#include <string>
#include "../CapaDomini/Model/Activitat.hxx"

using namespace std;

class DAOActivitat {
public:
    // Obtenir totes les activitats
    // PRE: cert
    // POST: retorna un vector amb totes les activitats de la BD
    static vector<shared_ptr<Activitat>> totes();

    // Obtenir activitats filtrades per ciutat i places mínimes
    // PRE: cert
    // POST: retorna un vector amb les activitats que compleixen els filtres
    static vector<shared_ptr<Activitat>> obtePerCiutatIPlaces(const string& ciutat, int placesMinimes);

    // Obtenir les N activitats més reservades
    // PRE: limit > 0
    // POST: retorna un vector amb les N activitats amb més reserves, ordenades descendentment
    static vector<shared_ptr<Activitat>> obteTopMesReservades(int limit);

    // Obtenir les últimes N activitats donades d'alta
    // PRE: limit > 0
    // POST: retorna un vector amb les N últimes activitats per data d'alta
    static vector<shared_ptr<Activitat>> obteUltimes(int limit);
};

#endif // DAOACTIVITAT_HXX
