# ?? Sistema PlanGo

Sistema de gestió de reserves d'experiències turístiques desenvolupat amb C++17, ODB i MariaDB seguint una arquitectura en 3 capes.

## ?? Descripció del Projecte

PlanGo és un sistema complet de gestió que permet als usuaris reservar experiències (escapades i activitats), consultar disponibilitat, gestionar el seu perfil i visualitzar estadístiques de les experiències més populars.

## ??? Arquitectura

El sistema està organitzat en **3 capes**:

```
???????????????????????????????????????
?    Capa de Presentació              ?
?  (CapaDePresentacio - Singleton)    ?
?  - Interacció amb l'usuari          ?
?  - Menús i navegació                ?
???????????????????????????????????????
              ??
???????????????????????????????????????
?    Capa de Domini                   ?
?  - Controladors (Casos d'Ús)        ?
?  - Model de dades (ODB)             ?
?  - DTOs (Data Transfer Objects)     ?
???????????????????????????????????????
              ??
???????????????????????????????????????
?    Capa de Dades                    ?
?  - DAOs (Data Access Objects)       ?
?  - connexioBD (Singleton)           ?
?  - Transaccions ODB                 ?
???????????????????????????????????????
              ??
???????????????????????????????????????
?      Base de Dades MariaDB          ?
???????????????????????????????????????
```

## ?? Patrons de Disseny Implementats

- **Singleton**: PlanGo, connexioBD, CapaDePresentacio
- **DAO (Data Access Object)**: Separació de lògica de persistència
- **DTO (Data Transfer Object)**: Transferència de dades entre capes
- **Façana**: CapaDePresentacio com a punt d'entrada únic
- **Factory Method**: Reserva::create()
- **Template Method**: Experiencia::obteInfo()

## ?? Components Principals

### Model de Dades

#### Classes Principals
- **PlanGo** (Singleton): Configuració global del sistema (descompte)
- **Usuari**: Gestió d'usuaris amb validació d'edat >= 18
- **Experiencia** (abstracta): Classe base per experiències
  - **Escapada**: Experiències amb hotel i nits (preu fix)
  - **Activitat**: Experiències amb durada (preu per persona)
- **Reserva**: Gestió de reserves amb càlcul automàtic de preus

#### DTOs
- **DTOUsuari**: Informació bàsica d'usuari
- **DTOExperiencia**: Detalls d'experiència amb tipus específics
- **DTOReserva**: Informació completa de reserva
- **DTOLlistaReserves**: Llista de reserves amb total pagat

### Capa de Dades (DAOs)

- **DAOUsuari**: CRUD d'usuaris
- **DAOExperiencia**: CRUD d'experiències (polimòrfic)
- **DAOEscapada**: Consultes específiques d'escapades
- **DAOActivitat**: Consultes específiques d'activitats
- **DAOReserva**: CRUD de reserves amb filtres per usuari
- **connexioBD**: Gestió de connexió a MariaDB

### Controladors (Casos d'Ús)

#### Gestió d'Usuaris
- **CtrlRegistreUsuari**: Registre de nous usuaris
- **CtrlIniciSessio**: Autenticació d'usuaris
- **CtrlModificaUsuari**: Actualització de dades
- **CtrlEsborraUsuari**: Eliminació de compte

#### Gestió de Reserves
- **CtrlReservaEscapada**: Crear reserves d'escapades
- **CtrlReservaActivitat**: Crear reserves d'activitats
- **CtrlConsultaReserves**: Consultar reserves d'usuari

#### Consultes Avançades
- **CtrlConsultaExperiencies**: Filtrar per ciutat i places
- **CtrlConsultaNovetats**: Últimes experiències donades d'alta
- **CtrlConsultaMesReservades**: Top experiències més populars

## ?? Funcionalitats

### Per a Usuaris
? Registre i autenticació  
? Modificar dades del perfil  
? Esborrar compte (amb confirmació)  
? Reservar escapades (preu fix)  
? Reservar activitats (preu per persona)  
? Consultar les meves reserves  
? Veure totes les experiències  
? Filtrar experiències per ciutat i places  
? Veure novetats (últimes experiències)  
? Veure Top 5 més reservades  

### Per a Administradors
? Configurar descompte per primera reserva  

### Lògica de Negoci
? Descompte automàtic a la primera reserva  
? Validació d'edat >= 18 anys  
? Email únic per usuari  
? Validació de places disponibles  
? Càlcul automàtic de preus  
? ON DELETE CASCADE (esborrar usuari esborra reserves)  

## ??? Tecnologies Utilitzades

- **Llenguatge**: C++17
- **ORM**: ODB (Object-Relational Mapping)
- **Base de Dades**: MariaDB
- **Dates**: Boost.Date_Time (Gregorian Calendar)
- **IDE**: Visual Studio 2022
- **Control de Versions**: Git + GitHub

## ?? Requisits del Sistema

### Software Necessari
- Compilador C++ amb suport per C++17 (g++, MSVC)
- MariaDB Server 10.x o superior
- ODB Compiler i llibreries
- Boost Libraries (date_time)

### Llibreries
```bash
# Ubuntu/Debian
sudo apt-get install libodb-dev libodb-mysql-dev libboost-date-time-dev

# Windows (amb vcpkg)
vcpkg install odb odb-mysql boost-date-time
```

## ?? Instal·lació i Configuració

### 1. Clonar el Repositori
```bash
git clone https://github.com/janlozanoupc/INEP_2025.git
cd INEP_2025
```

### 2. Configurar la Base de Dades

Edita el fitxer `configuracio.env`:
```
DB_USER=root
DB_PASS=la_teva_contrasenya
DB_NAME=plango
DB_HOST=127.0.0.1
```

Crea la base de dades:
```sql
CREATE DATABASE plango CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

### 3. Generar Fitxers ODB

```bash
odb -d mysql --generate-query --generate-schema \
  CapaDomini/Model/PlanGo.hxx \
  CapaDomini/Model/Usuari.hxx \
  CapaDomini/Model/Experiencia.hxx \
  CapaDomini/Model/Escapada.hxx \
  CapaDomini/Model/Activitat.hxx \
  CapaDomini/Model/Reserva.hxx
```

### 4. Crear l'Esquema de la BD

```bash
# Generar l'SQL
odb -d mysql --generate-schema-only schema.sql \
  CapaDomini/Model/*.hxx

# Executar l'SQL
mysql -u root -p plango < schema.sql
```

### 5. Compilar

```bash
# Linux/Mac
make

# Windows (Visual Studio)
# Obrir el .sln i compilar amb Visual Studio
```

## ?? Ús del Sistema

### Executar l'Aplicació Principal
```bash
./plango
```

### Executar els Tests
```bash
./test_plango
```

Consulta [README_TESTS.md](README_TESTS.md) per més informació sobre els tests.

## ?? Estructura del Projecte

```
INEP_2025/
??? CapaPresentacio/
?   ??? CapaDePresentacio.hxx
?   ??? CapaDePresentacio.cxx
??? CapaDomini/
?   ??? Model/
?   ?   ??? PlanGo.hxx/cxx
?   ?   ??? Usuari.hxx/cxx
?   ?   ??? Experiencia.hxx/cxx
?   ?   ??? Escapada.hxx/cxx
?   ?   ??? Activitat.hxx/cxx
?   ?   ??? Reserva.hxx/cxx
?   ??? DTOs/
?   ?   ??? DTOUsuari.hxx
?   ?   ??? DTOExperiencia.hxx
?   ?   ??? DTOReserva.hxx
?   ?   ??? DTOLlistaReserves.hxx
?   ??? Controladors (Ctrl*.hxx/cxx)
??? CapaDades/
?   ??? connexioBD.hxx/cxx
?   ??? DAO*.hxx/cxx
??? main.cxx
??? main_test.cxx
??? TestPlanGo.hxx/cxx
??? configuracio.env
??? README.md
??? README_TESTS.md
```

## ?? Testing

El projecte inclou **20 tests automàtics** que cobreixen:
- Model de dades
- DAOs i persistència
- Controladors i casos d'ús
- Lògica de negoci
- Consultes avançades

Executa:
```bash
./test_plango
```

Resultats esperats: **20/20 tests pasats** ?

## ?? Seguretat

- Contrasenya requerida per esborrar compte
- Validació de permisos per configuració d'admin
- Validacions de dades a totes les capes
- Transaccions ODB per mantenir integritat

## ?? Estadístiques del Projecte

- **Línies de codi**: ~3.000
- **Fitxers**: 46
- **Classes**: 23
- **Controladors**: 11
- **DAOs**: 5
- **DTOs**: 4
- **Tests**: 20

## ?? Contribucions

Aquest és un projecte acadèmic de l'assignatura INEP (UPC).

### Autor
- Jan Lozano
- GitHub: [@janlozanoupc](https://github.com/janlozanoupc)

## ?? Llicència

Projecte acadèmic - UPC 2025

## ?? Resolució de Problemes

### Error de connexió a la BD
```
? Error: No s'ha pogut obrir el fitxer configuracio.env
```
**Solució**: Crea el fitxer `configuracio.env` amb les credencials correctes.

### Error de compilació ODB
```
error: cannot find -lodb-mysql
```
**Solució**: Instal·la les llibreries ODB MySQL.

### Tests fallen
```
? FALLAT - Tests de DAOs
```
**Solució**: Verifica que l'esquema de la BD estigui creat i que el servei MariaDB estigui actiu.

## ?? Documentació Addicional

- [README_TESTS.md](README_TESTS.md) - Guia completa de tests
- Diagrames UML (si disponibles)
- Manual d'usuari (si disponible)

## ?? Funcionalitats Futures (Possibles Millores)

- [ ] API REST per accés extern
- [ ] Interfície web amb React/Vue
- [ ] Sistema de valoracions d'experiències
- [ ] Notificacions per email
- [ ] Sistema de pagaments integrat
- [ ] Geolocalització d'experiències
- [ ] Xat entre usuaris i proveïdors
- [ ] Sistema de cupons descompte
- [ ] Historial de reserves amb estat

## ?? Suport

Per problemes tècnics o preguntes:
- Obre un issue al GitHub
- Contacta amb l'autor

---

**Desenvolupat amb ?? per INEP 2025 - UPC**
