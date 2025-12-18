#include "Usuari.hxx"
#include "Experiencia.hxx"
#include <stdexcept>

using namespace std;

// Constructor per defecte
Usuari::Usuari() : _sobrenom(""), _nom(""), _contrasenya(""), _correuElectronic(""), _edat(18) {}

// PRE: edat >= 18
// POST: Crea usuari amb les dades proporcionades
Usuari::Usuari(const string& sobrenom, const string& nom, const string& contrasenya, 
               const string& email, int edat)
    : _sobrenom(sobrenom), _nom(nom), _contrasenya(contrasenya), 
      _correuElectronic(email), _edat(edat) {
    if (edat < 18) {
        throw invalid_argument("L'edat ha de ser igual o superior a 18 anys");
    }
}

// Getters
string Usuari::getSobrenom() const { return _sobrenom; }
string Usuari::getNom() const { return _nom; }
string Usuari::getContrasenya() const { return _contrasenya; }
string Usuari::getCorreuElectronic() const { return _correuElectronic; }
int Usuari::getEdat() const { return _edat; }
const vector<shared_ptr<Reserva>>& Usuari::getReserves() const { return _reserves; }

// Setters
void Usuari::setNom(const string& n) { _nom = n; }
void Usuari::setContrasenya(const string& c) { _contrasenya = c; }
void Usuari::setCorreuElectronic(const string& email) { _correuElectronic = email; }

void Usuari::setEdat(int e) {
    if (e < 18) {
        throw invalid_argument("L'edat ha de ser igual o superior a 18 anys");
    }
    _edat = e;
}

// PRE: exp != nullptr, numPlaces > 0
// POST: Nova reserva afegida a _reserves, retorna preu final
float Usuari::afegirReserva(shared_ptr<Experiencia> exp, int numPlaces) {
    if (exp == nullptr) {
        throw invalid_argument("L'experiència no pot ser nul·la");
    }
    if (numPlaces <= 0) {
        throw invalid_argument("El nombre de places ha de ser superior a 0");
    }

    // Comprovar si és la primera reserva de l'usuari
    bool primeraReserva = _reserves.empty();

    // Crear la reserva amb Factory Method
    // Nota: passem shared_from_this(), però com no estem heretant de enable_shared_from_this,
    // assumim que aquesta funció serà cridada des d'un context on l'usuari ja està en un shared_ptr
    // Per simplicitat, crearem la reserva i deixem que el Factory Method gestioni la lògica
    shared_ptr<Usuari> usuariPtr(this, [](Usuari*){});  // Shared ptr que no fa delete
    shared_ptr<Reserva> novaReserva = Reserva::create(usuariPtr, exp, numPlaces, primeraReserva);

    // Afegir la reserva al vector
    _reserves.push_back(novaReserva);

    // Retornar el preu pagat
    return novaReserva->getPreuPagat();
}

// PRE: cert
// POST: Retorna DTO amb informació de l'usuari
DTOUsuari Usuari::obteInfo() const {
    DTOUsuari dto;
    dto.sobrenom = _sobrenom;
    dto.nom = _nom;
    dto.correuElectronic = _correuElectronic;
    dto.edat = _edat;
    dto.numReserves = static_cast<int>(_reserves.size());
    return dto;
}
