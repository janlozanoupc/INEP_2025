#ifndef PLANGO_HXX
#define PLANGO_HXX

#include <odb/core.hxx>
#include <string>

using namespace std;

#pragma db object
class PlanGo {
public:
    // Obtenir instància única del singleton
    // PRE: cert
    // POST: retorna la instància única de PlanGo
    static PlanGo& getInstance();

    // Getter del descompte
    // PRE: cert
    // POST: retorna el valor de _descompte
    float getDescompte() const;

    // Setter del descompte
    // PRE: 0.0 <= d <= 1.0
    // POST: _descompte = d
    void setDescompte(float d);

private:
    friend class odb::access;

    // Constructor per defecte (privat per Singleton)
    PlanGo();

    // Descompte aplicat a la primera reserva (entre 0.0 i 1.0)
    #pragma db member(_descompte) check("_descompte >= 0.0 AND _descompte <= 1.0")
    float _descompte;

    // Instància única del singleton
    static PlanGo* _instancia;
};

#endif // PLANGO_HXX
