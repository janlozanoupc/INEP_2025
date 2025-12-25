#include "DAOReserva.hxx"
#include "connexioBD.hxx"
#include "../CapaDomini/Model/Reserva-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

// PRE: cert
// POST: retorna la reserva amb l'id especificat, o nullptr si no existeix
shared_ptr<Reserva> DAOReserva::obte(int id) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Reserva> reserva = db->find<Reserva>(id);
    
    t.commit();
    return reserva;
}

// PRE: cert
// POST: retorna true si existeix la reserva amb l'id especificat
bool DAOReserva::existeix(int id) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Reserva> reserva = db->find<Reserva>(id);
    bool existeix = (reserva != nullptr);
    
    t.commit();
    return existeix;
}

// PRE: cert
// POST: retorna un vector amb totes les reserves de la BD
vector<shared_ptr<Reserva>> DAOReserva::tots() {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Reserva> query;
    typedef odb::result<Reserva> result;
    
    result r(db->query<Reserva>());
    vector<shared_ptr<Reserva>> reserves;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        reserves.push_back(i.load());
    }
    
    t.commit();
    return reserves;
}

// PRE: r != nullptr
// POST: la reserva s'ha insertat a la BD
void DAOReserva::inserta(shared_ptr<Reserva> r) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->persist(r);
    
    t.commit();
}

// PRE: r != nullptr, existeix reserva amb el mateix id
// POST: les dades de la reserva s'han actualitzat a la BD
void DAOReserva::modifica(shared_ptr<Reserva> r) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->update(r);
    
    t.commit();
}

// PRE: existeix reserva amb l'id especificat
// POST: la reserva s'ha esborrat de la BD
void DAOReserva::esborra(int id) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->erase<Reserva>(id);
    
    t.commit();
}

// PRE: u != nullptr
// POST: retorna un vector amb totes les reserves de l'usuari especificat
vector<shared_ptr<Reserva>> DAOReserva::obteReservesUsuari(shared_ptr<Usuari> u) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Reserva> query;
    typedef odb::result<Reserva> result;
    
    // Consulta amb filtre per obtenir només les reserves de l'usuari especificat
    result r(db->query<Reserva>(query::_usuari == u->getSobrenom()));
    vector<shared_ptr<Reserva>> reserves;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        reserves.push_back(i.load());
    }
    
    t.commit();
    return reserves;
}
