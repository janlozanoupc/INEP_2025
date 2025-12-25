#include "DAOActivitat.hxx"
#include "connexioBD.hxx"
#include "../CapaDomini/Model/Activitat-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

// PRE: cert
// POST: retorna un vector amb totes les activitats de la BD
vector<shared_ptr<Activitat>> DAOActivitat::totes() {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Activitat> query;
    typedef odb::result<Activitat> result;
    
    result r(db->query<Activitat>());
    vector<shared_ptr<Activitat>> activitats;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        activitats.push_back(i.load());
    }
    
    t.commit();
    return activitats;
}

// PRE: cert
// POST: retorna un vector amb les activitats que compleixen els filtres
vector<shared_ptr<Activitat>> DAOActivitat::obtePerCiutatIPlaces(const string& ciutat, int placesMinimes) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Activitat> query;
    typedef odb::result<Activitat> result;
    
    result r(db->query<Activitat>(query::_ciutat == ciutat && query::_maximPlaces >= placesMinimes));
    vector<shared_ptr<Activitat>> activitats;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        activitats.push_back(i.load());
    }
    
    t.commit();
    return activitats;
}

// PRE: limit > 0
// POST: retorna un vector amb les N activitats amb més reserves, ordenades descendentment
vector<shared_ptr<Activitat>> DAOActivitat::obteTopMesReservades(int limit) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Activitat> query;
    typedef odb::result<Activitat> result;
    
    result r(db->query<Activitat>(query::true_expr + "ORDER BY" + query::_numReserves + "DESC LIMIT" + 
                                  query::_ref(limit)));
    vector<shared_ptr<Activitat>> activitats;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        activitats.push_back(i.load());
    }
    
    t.commit();
    return activitats;
}

// PRE: limit > 0
// POST: retorna un vector amb les N últimes activitats per data d'alta
vector<shared_ptr<Activitat>> DAOActivitat::obteUltimes(int limit) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Activitat> query;
    typedef odb::result<Activitat> result;
    
    result r(db->query<Activitat>(query::true_expr + "ORDER BY" + query::_dataAlta + "DESC LIMIT" + 
                                  query::_ref(limit)));
    vector<shared_ptr<Activitat>> activitats;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        activitats.push_back(i.load());
    }
    
    t.commit();
    return activitats;
}
