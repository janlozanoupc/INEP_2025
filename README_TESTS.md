# Sistema PlanGo - Tests Automàtics

## ?? Descripció

Aquest fitxer conté 20 tests automàtics per verificar totes les funcionalitats del sistema PlanGo.

## ?? Tests Implementats

### Tests del Model (5)
1. **Test 01**: Crear PlanGo Singleton - Verifica que el patró Singleton funciona correctament
2. **Test 02**: Configurar descompte - Valida la configuració del descompte de PlanGo
3. **Test 03**: Crear usuari - Comprova la creació d'objectes Usuari
4. **Test 04**: Crear escapada - Valida la creació d'objectes Escapada
5. **Test 05**: Crear activitat - Comprova la creació d'objectes Activitat

### Tests de DAOs (3)
6. **Test 06**: DAO Usuari - Insertar i obtenir usuaris de la BD
7. **Test 07**: DAO Experiència - Insertar i obtenir experiències de la BD
8. **Test 08**: DAO Reserva - Insertar i obtenir reserves de la BD

### Tests de Controladors Bàsics (3)
9. **Test 09**: Registre d'usuari - Valida el cas d'ús de registre
10. **Test 10**: Inici de sessió correcte - Comprova l'autenticació amb credencials vàlides
11. **Test 11**: Inici de sessió incorrecte - Valida que es rebutgen credencials errònies

### Tests de Reserves (4)
12. **Test 12**: Reserva escapada amb descompte - Verifica l'aplicació del descompte a la primera reserva
13. **Test 13**: Reserva escapada sense descompte - Comprova que no s'aplica descompte a reserves posteriors
14. **Test 14**: Reserva activitat - Valida el càlcul de preu per persona
15. **Test 15**: Consulta reserves - Comprova la consulta de reserves d'un usuari

### Tests de Gestió d'Usuaris (2)
16. **Test 16**: Modificar usuari - Valida l'actualització de dades d'usuari
17. **Test 17**: Esborrar usuari - Comprova l'esborrat d'usuari i CASCADE

### Tests de Consultes Avançades (3)
18. **Test 18**: Consulta experiències per ciutat - Valida els filtres de ciutat i places
19. **Test 19**: Consulta novetats - Comprova la consulta d'últimes experiències
20. **Test 20**: Consulta més reservades - Valida el Top 5 d'experiències populars

## ?? Com executar els tests

### Requisits previs
1. Base de dades MariaDB configurada
2. Fitxer `configuracio.env` amb les credencials correctes
3. Compilador C++ amb suport per C++17
4. Llibreries ODB i Boost instal·lades

### Compilació

```bash
# Generar fitxers ODB (si encara no s'ha fet)
odb -d mysql --generate-query --generate-schema \
  CapaDomini/Model/PlanGo.hxx \
  CapaDomini/Model/Usuari.hxx \
  CapaDomini/Model/Experiencia.hxx \
  CapaDomini/Model/Escapada.hxx \
  CapaDomini/Model/Activitat.hxx \
  CapaDomini/Model/Reserva.hxx

# Compilar programa de tests
g++ -std=c++17 -o test_plango main_test.cxx TestPlanGo.cxx \
  CapaDomini/Model/*.cxx \
  CapaDomini/DTOs/*.cxx \
  CapaDades/*.cxx \
  CapaDomini/*.cxx \
  -lodb-mysql -lodb -lboost_date_time
```

### Execució

```bash
./test_plango
```

## ?? Sortida esperada

```
?????????????????????????????????????????????????????????????
?         TESTS DEL SISTEMA PLANGO                          ?
?????????????????????????????????????????????????????????????

Inicialitzant base de dades per als tests...
? Dades de test inicialitzades correctament

??? TESTS DEL MODEL ???
Test 01: Crear PlanGo Singleton                    : ? PASSAT
Test 02: Configurar descompte                      : ? PASSAT
Test 03: Crear usuari                              : ? PASSAT
Test 04: Crear escapada                            : ? PASSAT
Test 05: Crear activitat                           : ? PASSAT

??? TESTS DE DAOs ???
Test 06: DAO Usuari - Insertar i obtenir          : ? PASSAT
Test 07: DAO Experiència - Insertar i obtenir     : ? PASSAT
Test 08: DAO Reserva - Insertar i obtenir         : ? PASSAT

??? TESTS DE CONTROLADORS BÀSICS ???
Test 09: Registre d'usuari                         : ? PASSAT
Test 10: Inici de sessió correcte                  : ? PASSAT
Test 11: Inici de sessió incorrecte                : ? PASSAT

??? TESTS DE RESERVES ???
Test 12: Reserva escapada amb descompte            : ? PASSAT
Test 13: Reserva escapada sense descompte          : ? PASSAT
Test 14: Reserva activitat                         : ? PASSAT
Test 15: Consulta reserves                         : ? PASSAT

??? TESTS DE GESTIÓ D'USUARIS ???
Test 16: Modificar usuari                          : ? PASSAT
Test 17: Esborrar usuari                           : ? PASSAT

??? TESTS DE CONSULTES AVANÇADES ???
Test 18: Consulta experiències per ciutat          : ? PASSAT
Test 19: Consulta novetats                         : ? PASSAT
Test 20: Consulta més reservades                   : ? PASSAT

?????????????????????????????????????????????????????????????
?                    RESUM DELS TESTS                       ?
?????????????????????????????????????????????????????????????
Tests pasats:  20 / 20
Tests fallats: 0 / 20

??? TOTS ELS TESTS HAN PASSAT CORRECTAMENT! ???
```

## ?? Detalls dels Tests

### Cobertura de Funcionalitats
- ? Patró Singleton (PlanGo, connexioBD, CapaDePresentacio)
- ? Patró DAO amb transaccions ODB
- ? Patró DTO per transferència de dades
- ? Factory Method (Reserva::create)
- ? Template Method (Experiencia::obteInfo)
- ? Polimorfisme (Escapada i Activitat)
- ? Herència amb ODB
- ? Relacions bidireccionals (Usuari ? Reserva)
- ? ON DELETE CASCADE
- ? Validacions de negoci
- ? Càlcul de preus amb descompte
- ? Consultes amb filtres i ordenació
- ? Gestió d'errors amb excepcions

### Estratègia de Testing
1. **Aïllament**: Cada test crea i neteja les seves pròpies dades
2. **Independència**: Els tests no depenen uns dels altres
3. **Verificació**: Cada test comprova un aspecte específic
4. **Neteja**: S'eliminen les dades de test després de cada prova

## ?? Resolució de Problemes

### Error de connexió a la BD
Comprova que:
- El servei MariaDB està actiu
- Les credencials al fitxer `configuracio.env` són correctes
- La base de dades `plango` existeix

### Tests fallen
1. Verifica que les taules estiguin creades (executar l'esquema ODB)
2. Comprova que no hi hagi dades conflictives a la BD
3. Revisa els logs d'error específics

### Problemes de compilació
- Assegura't que ODB i Boost estan instal·lats
- Verifica les rutes d'inclusió
- Comprova que tots els fitxers `-odb.hxx` i `-odb.cxx` s'hagin generat

## ?? Notes Addicionals

- Els tests modifiquen la base de dades, però netegen les dades de test
- Es recomana executar els tests en una base de dades de desenvolupament
- Alguns tests depenen de l'ordre d'execució per simular escenaris realistes
- El descompte es configura al 10% per defecte en els tests

## ?? Integració Contínua

Aquest conjunt de tests es pot integrar en un pipeline de CI/CD per:
- Validar canvis abans de fer commit
- Executar automàticament en pull requests
- Verificar la integritat del sistema després de desplegaments

## ?? Suport

Si els tests fallen i no pots resoldre el problema, comprova:
1. Els logs d'error detallats
2. L'estat de la base de dades
3. Les versions de les llibreries
4. La configuració de connexió
