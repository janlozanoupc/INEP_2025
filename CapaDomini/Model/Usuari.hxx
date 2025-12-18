#ifndef USUARI_HXX
#define USUARI_HXX

#include <odb/core.hxx>
#include <string>
#include <vector>
#include <memory>
#include "Reserva.hxx"
#include "../DTOs/DTOUsuari.hxx"

using namespace std;

// Forward declaration
class Experiencia;

#pragma db object
class Usuari {
public:
    // Constructor per defecte (per ODB)
    Usuari();

    // Constructor amb paràmetres
    // PRE: edat >= 18
    // POST: Crea usuari amb les dades proporcionades
    Usuari(const string& sobrenom, const string& nom, const string& contrasenya, 
           const string& email, int edat);

    // Getters
    string getSobrenom() const;
    string getNom() const;
    string getContrasenya() const;
    string getCorreuElectronic() const;
    int getEdat() const;
    const vector<shared_ptr<Reserva>>& getReserves() const;

    // Setters
    void setNom(const string& n);
    void setContrasenya(const string& c);
    void setCorreuElectronic(const string& email);
    void setEdat(int e);

    // Afegir una nova reserva
    // PRE: exp != nullptr, numPlaces > 0
    // POST: Nova reserva afegida a _reserves, retorna preu final
    float afegirReserva(shared_ptr<Experiencia> exp, int numPlaces);

    // Obtenir informació de l'usuari
    // PRE: cert
    // POST: Retorna DTO amb informació de l'usuari
    DTOUsuari obteInfo() const;

private:
    friend class odb::access;

    #pragma db member(_sobrenom) id
    string _sobrenom;

    string _nom;
    string _contrasenya;

    #pragma db member(_correuElectronic) unique
    string _correuElectronic;

    #pragma db member(_edat) check("_edat >= 18")
    int _edat;

    #pragma db value_not_null inverse(_usuari)
    vector<shared_ptr<Reserva>> _reserves;
};

#endif // USUARI_HXX
