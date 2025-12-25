#ifndef CTRLMODIFICAUSUARI_HXX
#define CTRLMODIFICAUSUARI_HXX

#include <string>
#include "DTOs/DTOUsuari.hxx"

using namespace std;

class CtrlModificaUsuari {
public:
    // Modificar les dades d'un usuari existent
    // PRE: sobrenom no buit, edat >= 18
    // POST: retorna DTOUsuari amb les dades actualitzades
    //       llança runtime_error si l'usuari no existeix o el nou email ja està en ús per un altre usuari
    static DTOUsuari modificaUsuari(const string& sobrenom, const string& nouNom, 
                                    const string& nouCorreuElectronic, int novaEdat);
};

#endif // CTRLMODIFICAUSUARI_HXX
