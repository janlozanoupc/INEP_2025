#include "PlanGo.hxx"
#include <stdexcept>

using namespace std;

// Inicialització de la instància estàtica
PlanGo* PlanGo::_instancia = nullptr;

// Constructor per defecte
PlanGo::PlanGo() : _descompte(0.0f) {}

// PRE: cert
// POST: retorna la instància única de PlanGo
PlanGo& PlanGo::getInstance() {
    if (_instancia == nullptr) {
        _instancia = new PlanGo();
    }
    return *_instancia;
}

// PRE: cert
// POST: retorna el valor de _descompte
float PlanGo::getDescompte() const {
    return _descompte;
}

// PRE: 0.0 <= d <= 1.0
// POST: _descompte = d
void PlanGo::setDescompte(float d) {
    if (d < 0.0f || d > 1.0f) {
        throw invalid_argument("El descompte ha d'estar entre 0.0 i 1.0");
    }
    _descompte = d;
}
