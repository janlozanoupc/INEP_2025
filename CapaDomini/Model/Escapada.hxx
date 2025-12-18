#ifndef ESCAPADA_HXX
#define ESCAPADA_HXX

#include "Experiencia.hxx"

using namespace std;

#pragma db object
class Escapada : public Experiencia {
public:
    // Constructor per defecte (per ODB)
    Escapada();

    // Constructor amb paràmetres
    // PRE: maximP > 0, pr > 0.0, nNits > 0
    // POST: Crea escapada amb les dades proporcionades
    Escapada(const string& n, const string& desc, const string& c, 
             int maximP, float pr, const string& hot, int nNits);

    // Getters
    string getHotel() const;
    int getNumNits() const;

    // Setters
    void setHotel(const string& hot);
    void setNumNits(int nNits);

    // Implementació del càlcul de preu per escapades
    // PRE: nPersones == _maximPlaces (per escapades)
    // POST: Retorna _preu (preu total de l'escapada)
    float calculaPreu(int nPersones) const override;

protected:
    friend class odb::access;

    // Omplir detalls específics d'escapada al DTO
    void ompleDetalls(DTOExperiencia& dto) const override;

private:
    string _hotel;

    #pragma db member(_numNits) check("_numNits > 0")
    int _numNits;
};

#endif // ESCAPADA_HXX
