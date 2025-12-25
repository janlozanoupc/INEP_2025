#include "TestPlanGo.hxx"
#include <iostream>
#include <locale>

using namespace std;

int main() {
    try {
        // Configurar locale per caràcters especials
        locale::global(locale(""));
        
        // Executar tots els tests
        TestPlanGo::executarTotsElsTests();
        
    } catch (const exception& e) {
        cerr << "Error crític durant els tests: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
