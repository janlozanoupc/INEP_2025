#ifndef EXPERIENCIA_HXX
#define EXPERIENCIA_HXX

#include <odb/core.hxx>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include "../DTOs/DTOExperiencia.hxx"

using namespace std;
using namespace boost::gregorian;

#pragma db object polymorphic
class Experiencia {
public:
    // Constructor per defecte (per ODB)
    Experiencia();

    // Constructor amb paràmetres
    // PRE: maximP > 0, pr > 0.0
    // POST: Crea experiència amb les dades proporcionades i dataAlta = avui
    Experiencia(const string& n, const string& desc, const string& c, 
                int maximP, float pr);

    // Destructor virtual
    virtual ~Experiencia() = default;

    // Getters
    string getNom() const;
    string getDescripcio() const;
    string getCiutat() const;
    int getMaximPlaces() const;
    float getPreu() const;
    date getDataAlta() const;
    int getNumReserves() const;

    // Setters
    void setDescripcio(const string& desc);
    void setCiutat(const string& c);
    void setMaximPlaces(int maxP);
    void setPreu(float pr);

    // Mètode abstracte per calcular preu
    // PRE: nPersones > 0
    // POST: Retorna preu total segons tipus d'experiència
    virtual float calculaPreu(int nPersones) const = 0;

    // Mètode per calcular preu amb descompte opcional
    // PRE: nPersones > 0
    // POST: Retorna preu amb/sense descompte segons primeraReserva
    float calculaPreu(int nPersones, bool primeraReserva) const;

    // Incrementar comptador de reserves
    // PRE: cert
    // POST: _numReserves++
    void incrementarReserves();

    // Obtenir informació completa (Template Method)
    // PRE: cert
    // POST: Retorna DTO amb tota la informació de l'experiència
    DTOExperiencia obteInfo() const;

protected:
    friend class odb::access;

    // Mètode virtual pur per omplir detalls específics al DTO
    virtual void ompleDetalls(DTOExperiencia& dto) const = 0;

    #pragma db member(_nom) id
    string _nom;

    string _descripcio;
    string _ciutat;

    #pragma db member(_maximPlaces) check("_maximPlaces > 0")
    int _maximPlaces;

    #pragma db member(_preu) check("_preu > 0.0")
    float _preu;

    date _dataAlta;

    #pragma db member(_numReserves) check("_numReserves >= 0")
    int _numReserves;
};

#endif // EXPERIENCIA_HXX
