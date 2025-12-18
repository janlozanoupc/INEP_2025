#ifndef ACTIVITAT_HXX
#define ACTIVITAT_HXX

#include "Experiencia.hxx"

using namespace std;

#pragma db object
class Activitat : public Experiencia {
public:
    // Constructor per defecte (per ODB)
    Activitat();

    // Constructor amb paràmetres
    // PRE: maximP > 0, pr > 0.0, dur > 0
    // POST: Crea activitat amb les dades proporcionades
    Activitat(const string& n, const string& desc, const string& c, 
              int maximP, float pr, int dur);

    // Getter
    int getDurada() const;

    // Setter
    void setDurada(int dur);

    // Implementació del càlcul de preu per activitats
    // PRE: nPersones > 0 AND nPersones <= _maximPlaces
    // POST: Retorna _preu * nPersones (preu per persona)
    float calculaPreu(int nPersones) const override;

protected:
    friend class odb::access;

    // Omplir detalls específics d'activitat al DTO
    void ompleDetalls(DTOExperiencia& dto) const override;

private:
    #pragma db member(_durada) check("_durada > 0")
    int _durada; // Durada en minuts
};

#endif // ACTIVITAT_HXX
