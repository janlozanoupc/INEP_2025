#ifndef RESERVA_HXX
#define RESERVA_HXX

#include <odb/core.hxx>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include "../DTOs/DTOReserva.hxx"

using namespace std;
using namespace boost::gregorian;

// Forward declarations
class Usuari;
class Experiencia;

#pragma db object
class Reserva {
public:
    // Factory Method per crear reserves
    // PRE: u != nullptr, e != nullptr, numP > 0
    // POST: Nova reserva creada amb data actual, preu calculat segons primeraR
    static shared_ptr<Reserva> create(shared_ptr<Usuari> u, shared_ptr<Experiencia> e, 
                                      int numP, bool primeraR);

    // Getters
    int getId() const;
    date getData() const;
    int getNumPlaces() const;
    float getPreuPagat() const;
    shared_ptr<Usuari> getUsuari() const;
    shared_ptr<Experiencia> getExperiencia() const;

    // Obtenir informació de la reserva
    // PRE: cert
    // POST: Retorna DTO amb tota la informació de la reserva
    DTOReserva obteInfo() const;

private:
    friend class odb::access;

    // Constructor per defecte (per ODB)
    Reserva();

    // Constructor privat (Factory Method)
    Reserva(shared_ptr<Usuari> u, shared_ptr<Experiencia> e, 
            int numP, float preu);

    #pragma db member(_id) id auto
    int _id;

    date _data;

    #pragma db member(_numPlaces) check("_numPlaces > 0")
    int _numPlaces;

    #pragma db member(_preuPagat) check("_preuPagat > 0.0")
    float _preuPagat;

    #pragma db member(_usuari) not_null on_delete(cascade)
    shared_ptr<Usuari> _usuari;

    #pragma db member(_experiencia) not_null
    shared_ptr<Experiencia> _experiencia;
};

#pragma db member(Reserva::_data) unique(Reserva::_usuari, Reserva::_experiencia)

#endif // RESERVA_HXX
