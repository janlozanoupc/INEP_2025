#include "CapaPresentacio/CapaDePresentacio.hxx"
#include <iostream>
#include <locale>

using namespace std;

int main() {
    try {
        // Configurar locale per caràcters especials
        locale::global(locale(""));
        
        // Executar l'aplicació
        CapaDePresentacio::getInstance().executar();
        
    } catch (const exception& e) {
        cerr << "Error crític: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
