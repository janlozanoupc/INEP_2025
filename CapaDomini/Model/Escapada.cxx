#include "Escapada.hxx"
#include <stdexcept>

using namespace std;

// Constructor per defecte
Escapada::Escapada() : Experiencia(), _hotel(""), _numNits(1) {}

// PRE: maximP > 0, pr > 0.0, nNits > 0
// POST: Crea escapada amb les dades proporcionades
Escapada::Escapada(const string& n, const string& desc, const string& c, 
                   int maximP, float pr, const string& hot, int nNits)
    : Experiencia(n, desc, c, maximP, pr), _hotel(hot), _numNits(nNits) {
    if (nNits <= 0) {
        throw invalid_argument("El nombre de nits ha de ser superior a 0");
    }
}

// Getters
string Escapada::getHotel() const { return _hotel; }
int Escapada::getNumNits() const { return _numNits; }

// Setters
void Escapada::setHotel(const string& hot) { _hotel = hot; }

void Escapada::setNumNits(int nNits) {
    if (nNits <= 0) {
        throw invalid_argument("El nombre de nits ha de ser superior a 0");
    }
    _numNits = nNits;
}

// PRE: nPersones == _maximPlaces (per escapades)
// POST: Retorna _preu (preu total de l'escapada)
float Escapada::calculaPreu(int nPersones) const {
    // Per escapades, el preu és fix (preu total independentment del nombre de persones)
    return _preu;
}

// Omplir detalls específics d'escapada al DTO
void Escapada::ompleDetalls(DTOExperiencia& dto) const {
    dto.tipusExperiencia = "ESCAPADA";
    dto.hotel = _hotel;
    dto.numNits = _numNits;
}
