#include "Experiencia.hxx"
#include "PlanGo.hxx"
#include <stdexcept>

using namespace std;
using namespace boost::gregorian;

// Constructor per defecte
Experiencia::Experiencia() 
    : _nom(""), _descripcio(""), _ciutat(""), _maximPlaces(1), 
      _preu(0.0f), _dataAlta(day_clock::local_day()), _numReserves(0) {}

// PRE: maximP > 0, pr > 0.0
// POST: Crea experiència amb les dades proporcionades i dataAlta = avui
Experiencia::Experiencia(const string& n, const string& desc, const string& c, 
                         int maximP, float pr)
    : _nom(n), _descripcio(desc), _ciutat(c), _maximPlaces(maximP), 
      _preu(pr), _dataAlta(day_clock::local_day()), _numReserves(0) {
    if (maximP <= 0) {
        throw invalid_argument("El màxim de places ha de ser superior a 0");
    }
    if (pr <= 0.0f) {
        throw invalid_argument("El preu ha de ser superior a 0.0");
    }
}

// Getters
string Experiencia::getNom() const { return _nom; }
string Experiencia::getDescripcio() const { return _descripcio; }
string Experiencia::getCiutat() const { return _ciutat; }
int Experiencia::getMaximPlaces() const { return _maximPlaces; }
float Experiencia::getPreu() const { return _preu; }
date Experiencia::getDataAlta() const { return _dataAlta; }
int Experiencia::getNumReserves() const { return _numReserves; }

// Setters
void Experiencia::setDescripcio(const string& desc) { _descripcio = desc; }
void Experiencia::setCiutat(const string& c) { _ciutat = c; }

void Experiencia::setMaximPlaces(int maxP) {
    if (maxP <= 0) {
        throw invalid_argument("El màxim de places ha de ser superior a 0");
    }
    _maximPlaces = maxP;
}

void Experiencia::setPreu(float pr) {
    if (pr <= 0.0f) {
        throw invalid_argument("El preu ha de ser superior a 0.0");
    }
    _preu = pr;
}

// PRE: nPersones > 0
// POST: Retorna preu amb/sense descompte segons primeraReserva
float Experiencia::calculaPreu(int nPersones, bool primeraReserva) const {
    if (nPersones <= 0) {
        throw invalid_argument("El nombre de persones ha de ser superior a 0");
    }
    
    float preuTotal = calculaPreu(nPersones);
    
    if (primeraReserva) {
        float descompte = PlanGo::getInstance().getDescompte();
        preuTotal = preuTotal * (1.0f - descompte);
    }
    
    return preuTotal;
}

// PRE: cert
// POST: _numReserves++
void Experiencia::incrementarReserves() {
    _numReserves++;
}

// PRE: cert
// POST: Retorna DTO amb tota la informació de l'experiència
DTOExperiencia Experiencia::obteInfo() const {
    DTOExperiencia dto;
    dto.nom = _nom;
    dto.descripcio = _descripcio;
    dto.ciutat = _ciutat;
    dto.maximPlaces = _maximPlaces;
    dto.numReserves = _numReserves;
    dto.preu = _preu;
    dto.dataAlta = _dataAlta;
    
    // Inicialitzar camps específics amb valors per defecte
    dto.hotel = "";
    dto.numNits = 0;
    dto.durada = 0;
    
    // Cridar mètode template per omplir detalls específics
    ompleDetalls(dto);
    
    return dto;
}
