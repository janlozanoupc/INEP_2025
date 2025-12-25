#include "DAOEscapada.hxx"
#include "connexioBD.hxx"
#include "../CapaDomini/Model/Escapada-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

// PRE: cert
// POST: retorna un vector amb totes les escapades de la BD
vector<shared_ptr<Escapada>> DAOEscapada::totes() {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Escapada> query;
    typedef odb::result<Escapada> result;
    
    result r(db->query<Escapada>());
    vector<shared_ptr<Escapada>> escapades;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        escapades.push_back(i.load());
    }
    
    t.commit();
    return escapades;
}

// PRE: cert
// POST: retorna un vector amb les escapades que compleixen els filtres
vector<shared_ptr<Escapada>> DAOEscapada::obtePerCiutatIPlaces(const string& ciutat, int placesMinimes) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Escapada> query;
    typedef odb::result<Escapada> result;
    
    result r(db->query<Escapada>(query::_ciutat == ciutat && query::_maximPlaces >= placesMinimes));
    vector<shared_ptr<Escapada>> escapades;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        escapades.push_back(i.load());
    }
    
    t.commit();
    return escapades;
}

// PRE: limit > 0
// POST: retorna un vector amb les N escapades amb més reserves, ordenades descendentment
vector<shared_ptr<Escapada>> DAOEscapada::obteTopMesReservades(int limit) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Escapada> query;
    typedef odb::result<Escapada> result;
    
    result r(db->query<Escapada>(query::true_expr + "ORDER BY" + query::_numReserves + "DESC LIMIT" + 
                                 query::_ref(limit)));
    vector<shared_ptr<Escapada>> escapades;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        escapades.push_back(i.load());
    }
    
    t.commit();
    return escapades;
}

// PRE: limit > 0
// POST: retorna un vector amb les N últimes escapades per data d'alta
vector<shared_ptr<Escapada>> DAOEscapada::obteUltimes(int limit) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Escapada> query;
    typedef odb::result<Escapada> result;
    
    result r(db->query<Escapada>(query::true_expr + "ORDER BY" + query::_dataAlta + "DESC LIMIT" + 
                                 query::_ref(limit)));
    vector<shared_ptr<Escapada>> escapades;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        escapades.push_back(i.load());
    }
    
    t.commit();
    return escapades;
}
