#include "Reserva.hxx"
#include "Usuari.hxx"
#include "Experiencia.hxx"
#include <stdexcept>

using namespace std;
using namespace boost::gregorian;

// Constructor per defecte
Reserva::Reserva() : _id(0), _data(day_clock::local_day()), _numPlaces(1), _preuPagat(0.0f) {}

// Constructor privat
Reserva::Reserva(shared_ptr<Usuari> u, shared_ptr<Experiencia> e, 
                 int numP, float preu)
    : _id(0), _data(day_clock::local_day()), _numPlaces(numP), 
      _preuPagat(preu), _usuari(u), _experiencia(e) {
    if (numP <= 0) {
        throw invalid_argument("El nombre de places ha de ser superior a 0");
    }
    if (preu <= 0.0f) {
        throw invalid_argument("El preu pagat ha de ser superior a 0.0");
    }
}

// PRE: u != nullptr, e != nullptr, numP > 0
// POST: Nova reserva creada amb data actual, preu calculat segons primeraR
shared_ptr<Reserva> Reserva::create(shared_ptr<Usuari> u, shared_ptr<Experiencia> e, 
                                    int numP, bool primeraR) {
    if (u == nullptr) {
        throw invalid_argument("L'usuari no pot ser nul");
    }
    if (e == nullptr) {
        throw invalid_argument("L'experiència no pot ser nul·la");
    }
    if (numP <= 0) {
        throw invalid_argument("El nombre de places ha de ser superior a 0");
    }

    // Calcular preu amb o sense descompte
    float preu = e->calculaPreu(numP, primeraR);

    // Crear reserva
    shared_ptr<Reserva> reserva(new Reserva(u, e, numP, preu));

    // Incrementar comptador de reserves de l'experiència
    e->incrementarReserves();

    return reserva;
}

// Getters
int Reserva::getId() const { return _id; }
date Reserva::getData() const { return _data; }
int Reserva::getNumPlaces() const { return _numPlaces; }
float Reserva::getPreuPagat() const { return _preuPagat; }
shared_ptr<Usuari> Reserva::getUsuari() const { return _usuari; }
shared_ptr<Experiencia> Reserva::getExperiencia() const { return _experiencia; }

// PRE: cert
// POST: Retorna DTO amb tota la informació de la reserva
DTOReserva Reserva::obteInfo() const {
    DTOReserva dto;
    dto.id = _id;
    dto.numPlaces = _numPlaces;
    dto.preuPagat = _preuPagat;
    dto.dataReserva = _data;
    
    if (_experiencia != nullptr) {
        dto.experiencia = _experiencia->obteInfo();
    }
    
    return dto;
}
