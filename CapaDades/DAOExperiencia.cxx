#include "DAOExperiencia.hxx"
#include "connexioBD.hxx"
#include "../CapaDomini/Model/Experiencia-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

// PRE: cert
// POST: retorna l'experiència amb el nom especificat, o nullptr si no existeix
shared_ptr<Experiencia> DAOExperiencia::obte(const string& nom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Experiencia> experiencia = db->find<Experiencia>(nom);
    
    t.commit();
    return experiencia;
}

// PRE: cert
// POST: retorna true si existeix l'experiència amb el nom especificat
bool DAOExperiencia::existeix(const string& nom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    shared_ptr<Experiencia> experiencia = db->find<Experiencia>(nom);
    bool existeix = (experiencia != nullptr);
    
    t.commit();
    return existeix;
}

// PRE: cert
// POST: retorna un vector amb totes les experiències de la BD
vector<shared_ptr<Experiencia>> DAOExperiencia::tots() {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    typedef odb::query<Experiencia> query;
    typedef odb::result<Experiencia> result;
    
    result r(db->query<Experiencia>());
    vector<shared_ptr<Experiencia>> experiencies;
    
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        experiencies.push_back(i.load());
    }
    
    t.commit();
    return experiencies;
}

// PRE: exp != nullptr, no existeix experiència amb el mateix nom
// POST: l'experiència s'ha insertat a la BD
void DAOExperiencia::inserta(shared_ptr<Experiencia> exp) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->persist(exp);
    
    t.commit();
}

// PRE: exp != nullptr, existeix experiència amb el mateix nom
// POST: les dades de l'experiència s'han actualitzat a la BD
void DAOExperiencia::modifica(shared_ptr<Experiencia> exp) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->update(exp);
    
    t.commit();
}

// PRE: existeix experiència amb el nom especificat
// POST: l'experiència s'ha esborrat de la BD
void DAOExperiencia::esborra(const string& nom) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    
    db->erase<Experiencia>(nom);
    
    t.commit();
}
