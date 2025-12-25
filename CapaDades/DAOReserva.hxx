#ifndef DAORESERVA_HXX
#define DAORESERVA_HXX

#include <memory>
#include <vector>
#include "../CapaDomini/Model/Reserva.hxx"
#include "../CapaDomini/Model/Usuari.hxx"

using namespace std;

class DAOReserva {
public:
    // Obtenir una reserva pel seu id
    // PRE: cert
    // POST: retorna la reserva amb l'id especificat, o nullptr si no existeix
    static shared_ptr<Reserva> obte(int id);

    // Comprovar si existeix una reserva
    // PRE: cert
    // POST: retorna true si existeix la reserva amb l'id especificat
    static bool existeix(int id);

    // Obtenir totes les reserves
    // PRE: cert
    // POST: retorna un vector amb totes les reserves de la BD
    static vector<shared_ptr<Reserva>> tots();

    // Insertar una nova reserva
    // PRE: r != nullptr
    // POST: la reserva s'ha insertat a la BD
    static void inserta(shared_ptr<Reserva> r);

    // Modificar una reserva existent
    // PRE: r != nullptr, existeix reserva amb el mateix id
    // POST: les dades de la reserva s'han actualitzat a la BD
    static void modifica(shared_ptr<Reserva> r);

    // Esborrar una reserva
    // PRE: existeix reserva amb l'id especificat
    // POST: la reserva s'ha esborrat de la BD
    static void esborra(int id);

    // Obtenir les reserves d'un usuari concret
    // PRE: u != nullptr
    // POST: retorna un vector amb totes les reserves de l'usuari especificat
    static vector<shared_ptr<Reserva>> obteReservesUsuari(shared_ptr<Usuari> u);
};

#endif // DAORESERVA_HXX
