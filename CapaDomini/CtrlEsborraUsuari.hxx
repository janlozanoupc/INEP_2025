#ifndef CTRLESBARRAUSUARI_HXX
#define CTRLESBARRAUSUARI_HXX

#include <string>

using namespace std;

class CtrlEsborraUsuari {
public:
    // Esborrar un usuari del sistema amb confirmació de contrasenya
    // PRE: sobrenom i contrasenya no buits
    // POST: l'usuari ha estat esborrat de la BD (i les seves reserves per CASCADE)
    //       llança runtime_error si l'usuari no existeix o la contrasenya és incorrecta
    static void esborraUsuari(const string& sobrenom, const string& contrasenya);
};

#endif // CTRLESBARRAUSUARI_HXX
