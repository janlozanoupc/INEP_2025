#include "Activitat.hxx"
#include <stdexcept>

using namespace std;

// Constructor per defecte
Activitat::Activitat() : Experiencia(), _durada(60) {}

// PRE: maximP > 0, pr > 0.0, dur > 0
// POST: Crea activitat amb les dades proporcionades
Activitat::Activitat(const string& n, const string& desc, const string& c, 
                     int maximP, float pr, int dur)
    : Experiencia(n, desc, c, maximP, pr), _durada(dur) {
    if (dur <= 0) {
        throw invalid_argument("La durada ha de ser superior a 0 minuts");
    }
}

// Getter
int Activitat::getDurada() const { return _durada; }

// Setter
void Activitat::setDurada(int dur) {
    if (dur <= 0) {
        throw invalid_argument("La durada ha de ser superior a 0 minuts");
    }
    _durada = dur;
}

// PRE: nPersones > 0 AND nPersones <= _maximPlaces
// POST: Retorna _preu * nPersones (preu per persona)
float Activitat::calculaPreu(int nPersones) const {
    if (nPersones <= 0) {
        throw invalid_argument("El nombre de persones ha de ser superior a 0");
    }
    if (nPersones > _maximPlaces) {
        throw invalid_argument("El nombre de persones supera el màxim de places");
    }
    return _preu * nPersones;
}

// Omplir detalls específics d'activitat al DTO
void Activitat::ompleDetalls(DTOExperiencia& dto) const {
    dto.tipusExperiencia = "ACTIVITAT";
    dto.durada = _durada;
}
