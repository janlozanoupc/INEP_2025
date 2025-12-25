#include "DAOUsuari.hxx"
#include "connexioBD.hxx"
#include "../CapaDomini/Model/Usuari-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

// PRE: cert
// POST: retorna l'usuari amb el sobrenom especificat, o nullptr si no existeix
shared_ptr<Usuari> DAOUsuari::obte(const string& sobrenom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Usuari> usuari = db->find<Usuari>(sobrenom);
    
    t.commit();
    return usuari;
}

// PRE: cert
// POST: retorna true si existeix l'usuari amb el sobrenom especificat
bool DAOUsuari::existeix(const string& sobrenom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Usuari> usuari = db->find<Usuari>(sobrenom);
    bool existeix = (usuari != nullptr);
    
    t.commit();
    return existeix;
}

// PRE: cert
// POST: retorna un vector amb tots els usuaris de la BD
vector<shared_ptr<Usuari>> DAOUsuari::tots() {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Usuari> query;
    typedef odb::result<Usuari> result;
    
    result r(db->query<Usuari>());
    vector<shared_ptr<Usuari>> usuaris;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        usuaris.push_back(i.load());
    }
    
    t.commit();
    return usuaris;
}

// PRE: u != nullptr, no existeix usuari amb el mateix sobrenom
// POST: l'usuari s'ha insertat a la BD
void DAOUsuari::inserta(shared_ptr<Usuari> u) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->persist(u);
    
    t.commit();
}

// PRE: u != nullptr, existeix usuari amb el mateix sobrenom
// POST: les dades de l'usuari s'han actualitzat a la BD
void DAOUsuari::modifica(shared_ptr<Usuari> u) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->update(u);
    
    t.commit();
}

// PRE: existeix usuari amb el sobrenom especificat
// POST: l'usuari s'ha esborrat de la BD (i les seves reserves per CASCADE)
void DAOUsuari::esborra(const string& sobrenom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->erase<Usuari>(sobrenom);
    
    t.commit();
}
