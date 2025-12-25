#ifndef CTRLINICISESSIO_HXX
#define CTRLINICISESSIO_HXX

#include <string>
#include "DTOs/DTOUsuari.hxx"

using namespace std;

class CtrlIniciSessio {
public:
    // Iniciar sessió d'un usuari
    // PRE: sobrenom i contrasenya no buits
    // POST: retorna DTOUsuari si les credencials són correctes
    //       llança runtime_error si l'usuari no existeix o la contrasenya és incorrecta
    static DTOUsuari iniciSessio(const string& sobrenom, const string& contrasenya);
};

#endif // CTRLINICISESSIO_HXX
