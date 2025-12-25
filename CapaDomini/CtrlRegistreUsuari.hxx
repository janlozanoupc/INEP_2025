#ifndef CTRLREGISTREUSUARI_HXX
#define CTRLREGISTREUSUARI_HXX

#include <string>
#include "DTOs/DTOUsuari.hxx"

using namespace std;

class CtrlRegistreUsuari {
public:
    // Registrar un nou usuari al sistema
    // PRE: tots els paràmetres són vàlids segons les regles de negoci
    // POST: retorna DTOUsuari del nou usuari creat
    //       llança runtime_error si l'usuari ja existeix o les dades no són vàlides
    static DTOUsuari registraUsuari(const string& sobrenom, const string& nom, 
                                    const string& contrasenya, const string& correuElectronic, 
                                    int edat);
};

#endif // CTRLREGISTREUSUARI_HXX
