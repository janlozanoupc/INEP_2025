#ifndef CONNEXIOBD_HXX
#define CONNEXIOBD_HXX

#include <odb/mysql/database.hxx>
#include <memory>
#include <string>

using namespace std;

class connexioBD {
public:
    // Obtenir instància única del singleton
    // PRE: Arxiu configuracio.env existeix i conté les 4 variables
    // POST: Connexió establerta o llança runtime_error
    static connexioBD& getInstance();

    // Obtenir la base de dades
    // PRE: getInstance() ha estat cridat prèviament
    // POST: Retorna punter a la base de dades ODB
    shared_ptr<odb::mysql::database> getDB() const;

private:
    // Constructor privat (Singleton)
    connexioBD();

    // Llegir configuració des de fitxer .env
    // PRE: Arxiu configuracio.env existeix
    // POST: Retorna mapa amb les variables de configuració o llança runtime_error
    void llegirConfiguracio();

    // Crear connexió a la base de dades
    // PRE: _dbUser, _dbPass, _dbName, _dbHost han estat inicialitzats
    // POST: _db apunta a una connexió vàlida o llança runtime_error
    void crearConnexio();

    // Atributs de configuració
    string _dbUser;
    string _dbPass;
    string _dbName;
    string _dbHost;

    // Connexió a la base de dades
    shared_ptr<odb::mysql::database> _db;

    // Instància única del singleton
    static connexioBD* _instancia;
};

#endif // CONNEXIOBD_HXX
