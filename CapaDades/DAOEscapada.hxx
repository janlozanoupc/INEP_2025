#ifndef DAOESCAPADA_HXX
#define DAOESCAPADA_HXX

#include <memory>
#include <vector>
#include <string>
#include "../CapaDomini/Model/Escapada.hxx"

using namespace std;

class DAOEscapada {
public:
    // Obtenir totes les escapades
    // PRE: cert
    // POST: retorna un vector amb totes les escapades de la BD
    static vector<shared_ptr<Escapada>> totes();

    // Obtenir escapades filtrades per ciutat i places mínimes
    // PRE: cert
    // POST: retorna un vector amb les escapades que compleixen els filtres
    static vector<shared_ptr<Escapada>> obtePerCiutatIPlaces(const string& ciutat, int placesMinimes);

    // Obtenir les N escapades més reservades
    // PRE: limit > 0
    // POST: retorna un vector amb les N escapades amb més reserves, ordenades descendentment
    static vector<shared_ptr<Escapada>> obteTopMesReservades(int limit);

    // Obtenir les últimes N escapades donades d'alta
    // PRE: limit > 0
    // POST: retorna un vector amb les N últimes escapades per data d'alta
    static vector<shared_ptr<Escapada>> obteUltimes(int limit);
};

#endif // DAOESCAPADA_HXX
