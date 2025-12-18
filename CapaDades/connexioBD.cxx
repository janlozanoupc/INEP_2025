#include "connexioBD.hxx"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

using namespace std;

// Inicialització de la instància estàtica
connexioBD* connexioBD::_instancia = nullptr;

// Constructor privat
connexioBD::connexioBD() : _dbUser(""), _dbPass(""), _dbName(""), _dbHost("") {
    llegirConfiguracio();
    crearConnexio();
}

// PRE: Arxiu configuracio.env existeix i conté les 4 variables
// POST: Connexió establerta o llança runtime_error
connexioBD& connexioBD::getInstance() {
    if (_instancia == nullptr) {
        _instancia = new connexioBD();
    }
    return *_instancia;
}

// PRE: getInstance() ha estat cridat prèviament
// POST: Retorna punter a la base de dades ODB
shared_ptr<odb::mysql::database> connexioBD::getDB() const {
    return _db;
}

// PRE: Arxiu configuracio.env existeix
// POST: Retorna mapa amb les variables de configuració o llança runtime_error
void connexioBD::llegirConfiguracio() {
    ifstream fitxer("configuracio.env");
    
    if (!fitxer.is_open()) {
        throw runtime_error("No s'ha pogut obrir el fitxer configuracio.env");
    }

    map<string, string> config;
    string linia;

    while (getline(fitxer, linia)) {
        // Saltar línies buides i comentaris
        if (linia.empty() || linia[0] == '#') {
            continue;
        }

        // Buscar el separador '='
        size_t pos = linia.find('=');
        if (pos == string::npos) {
            continue;
        }

        string clau = linia.substr(0, pos);
        string valor = linia.substr(pos + 1);

        // Eliminar espais en blanc
        clau.erase(0, clau.find_first_not_of(" \t\r\n"));
        clau.erase(clau.find_last_not_of(" \t\r\n") + 1);
        valor.erase(0, valor.find_first_not_of(" \t\r\n"));
        valor.erase(valor.find_last_not_of(" \t\r\n") + 1);

        config[clau] = valor;
    }

    fitxer.close();

    // Comprovar que existeixen totes les variables necessàries
    if (config.find("DB_USER") == config.end() ||
        config.find("DB_PASS") == config.end() ||
        config.find("DB_NAME") == config.end() ||
        config.find("DB_HOST") == config.end()) {
        throw runtime_error("El fitxer configuracio.env no conté totes les variables necessàries (DB_USER, DB_PASS, DB_NAME, DB_HOST)");
    }

    _dbUser = config["DB_USER"];
    _dbPass = config["DB_PASS"];
    _dbName = config["DB_NAME"];
    _dbHost = config["DB_HOST"];
}

// PRE: _dbUser, _dbPass, _dbName, _dbHost han estat inicialitzats
// POST: _db apunta a una connexió vàlida o llança runtime_error
void connexioBD::crearConnexio() {
    try {
        _db = make_shared<odb::mysql::database>(
            _dbUser,
            _dbPass,
            _dbName,
            _dbHost
        );
    } catch (const exception& e) {
        throw runtime_error(string("Error en crear la connexió a la base de dades: ") + e.what());
    }
}
