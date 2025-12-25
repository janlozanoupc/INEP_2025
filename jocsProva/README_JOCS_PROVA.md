# ?? JOCS DE PROVA DEL SISTEMA PLANGO

Aquest directori conté una suite completa de jocs de prova (casos de prova) per verificar totes les funcionalitats del sistema PlanGo.

## ?? Contingut

### Scripts SQL

1. **01_inicialitzar_bd.sql** - Inicialitzar base de dades amb dades de prova
   - 7 usuaris
   - 5 escapades
   - 8 activitats

2. **99_netejar_bd.sql** - Neteja completa de la base de dades

### Programes de Prova (C++)

3. **02_joc_usuaris.cxx** - Tests de gestió d'usuaris (10 tests)
4. **03_joc_experiencies.cxx** - Tests de gestió d'experiències (11 tests)
5. **04_joc_reserves.cxx** - Tests del sistema de reserves (10 tests)
6. **05_joc_consultes.cxx** - Tests de consultes avançades (11 tests)

**TOTAL: 42 tests automàtics**

---

## ?? Com Utilitzar els Jocs de Prova

### Pas 1: Preparar la Base de Dades

```bash
# Entrar a MySQL/MariaDB
mysql -u root -p

# Crear la base de dades si no existeix
CREATE DATABASE IF NOT EXISTS plango CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

# Sortir
exit
```

### Pas 2: Generar l'Esquema amb ODB

```bash
cd C:\Users\koros2\Source\Repos\INEP_2025

# Generar fitxers ODB
odb -d mysql --generate-query --generate-schema ^
  CapaDomini/Model/PlanGo.hxx ^
  CapaDomini/Model/Usuari.hxx ^
  CapaDomini/Model/Experiencia.hxx ^
  CapaDomini/Model/Escapada.hxx ^
  CapaDomini/Model/Activitat.hxx ^
  CapaDomini/Model/Reserva.hxx

# Crear les taules
odb -d mysql --generate-schema-only schema.sql CapaDomini/Model/*.hxx
mysql -u root -p plango < schema.sql
```

### Pas 3: Inicialitzar Dades de Prova

```bash
mysql -u root -p plango < jocsProva/01_inicialitzar_bd.sql
```

Això crearà:
- **7 usuaris**: admin, joan, maria, pere, anna, david, laura
- **5 escapades**: Barcelona, Pirineus, Costa Brava, Penedès, Madrid
- **8 activitats**: Parapent, Kayak, Escalada, Diving, BTT, Surf, Barranquisme, Espeleologia

### Pas 4: Compilar i Executar els Jocs de Prova

#### A) Amb MSVC (Visual Studio)

```bash
# Joc de prova d'usuaris
cl /EHsc /std:c++17 /I".." jocsProva/02_joc_usuaris.cxx ^
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx ^
  /link odb-mysql.lib odb.lib /Fe:joc_usuaris.exe

.\joc_usuaris.exe

# Joc de prova d'experiències
cl /EHsc /std:c++17 /I".." jocsProva/03_joc_experiencies.cxx ^
  CapaDomini/Model/*.cxx CapaDades/*.cxx ^
  /link odb-mysql.lib odb.lib /Fe:joc_experiencies.exe

.\joc_experiencies.exe

# Joc de prova de reserves
cl /EHsc /std:c++17 /I".." jocsProva/04_joc_reserves.cxx ^
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx ^
  /link odb-mysql.lib odb.lib /Fe:joc_reserves.exe

.\joc_reserves.exe

# Joc de prova de consultes
cl /EHsc /std:c++17 /I".." jocsProva/05_joc_consultes.cxx ^
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx ^
  /link odb-mysql.lib odb.lib /Fe:joc_consultes.exe

.\joc_consultes.exe
```

#### B) Amb g++ (Linux/MinGW)

```bash
# Joc de prova d'usuaris
g++ -std=c++17 -I.. jocsProva/02_joc_usuaris.cxx \
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx \
  -lodb-mysql -lodb -lboost_date_time -o joc_usuaris

./joc_usuaris

# Joc de prova d'experiències
g++ -std=c++17 -I.. jocsProva/03_joc_experiencies.cxx \
  CapaDomini/Model/*.cxx CapaDades/*.cxx \
  -lodb-mysql -lodb -lboost_date_time -o joc_experiencies

./joc_experiencies

# Joc de prova de reserves
g++ -std=c++17 -I.. jocsProva/04_joc_reserves.cxx \
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx \
  -lodb-mysql -lodb -lboost_date_time -o joc_reserves

./joc_reserves

# Joc de prova de consultes
g++ -std=c++17 -I.. jocsProva/05_joc_consultes.cxx \
  CapaDomini/Model/*.cxx CapaDades/*.cxx CapaDomini/Ctrl*.cxx \
  -lodb-mysql -lodb -lboost_date_time -o joc_consultes

./joc_consultes
```

### Pas 5: Netejar la Base de Dades

Quan vulguis esborrar totes les dades:

```bash
mysql -u root -p plango < jocsProva/99_netejar_bd.sql
```

---

## ?? Descripció dels Jocs de Prova

### 02_joc_usuaris.cxx (10 tests)

**Funcionalitats testejades:**
- ? Registre d'usuari nou
- ? Inici de sessió amb credencials correctes
- ? Inici de sessió amb contrasenya incorrecta
- ? Modificar dades d'usuari
- ? Intentar modificar amb email duplicat
- ? Registre amb edat inferior a 18
- ? Registre amb sobrenom duplicat
- ? Consultar tots els usuaris
- ? Esborrar usuari amb contrasenya incorrecta
- ? Esborrar usuari amb contrasenya correcta

**Validacions:**
- Email únic
- Edat >= 18
- Sobrenom únic
- Contrasenya correcta per esborrar

---

### 03_joc_experiencies.cxx (11 tests)

**Funcionalitats testejades:**
- ? Crear nova escapada
- ? Crear nova activitat
- ? Obtenir totes les experiències
- ? Filtrar escapades per ciutat i places
- ? Filtrar activitats per ciutat i places
- ? Obtenir últimes experiències
- ? Modificar escapada
- ? Modificar activitat
- ? Càlcul de preu per escapada (fix)
- ? Càlcul de preu per activitat (per persona)
- ? Esborrar experiències

**Conceptes verificats:**
- Polimorfisme (Experiencia ? Escapada/Activitat)
- Template Method (obteInfo)
- Filtres amb ODB
- Càlcul de preus diferenciat

---

### 04_joc_reserves.cxx (10 tests)

**Funcionalitats testejades:**
- ? Primera reserva amb descompte (escapada)
- ? Segona reserva sense descompte
- ? Reserva d'activitat (preu per persona)
- ? Consultar reserves d'usuari
- ? Primera reserva d'un altre usuari amb descompte
- ? Validació de places màximes
- ? Reserva amb experiència inexistent
- ? Reserva amb usuari inexistent
- ? Increment del comptador de reserves
- ? Esborrar reserves

**Lògica de negoci verificada:**
- Descompte només a primera reserva
- Càlcul correcte de preus
- Validacions de places
- Comptador de reserves
- Total pagat

---

### 05_joc_consultes.cxx (11 tests)

**Funcionalitats testejades:**
- ? Filtrar per ciutat i places (Barcelona)
- ? Filtrar per ciutat i places (Girona)
- ? Filtrar amb ciutat inexistent
- ? Consultar novetats (últimes 10)
- ? Consultar novetats amb límit reduït
- ? Top 5 experiències més reservades
- ? Top 3 més reservades
- ? Filtrar amb 0 persones (validació)
- ? Filtrar amb ciutat buida
- ? Novetats amb límit negatiu
- ? Verificar ordenació de novetats per data

**Consultes SQL testejades:**
- Filtres amb WHERE
- ORDER BY DESC
- LIMIT
- Validacions de paràmetres

---

## ?? Resultats Esperats

Tots els jocs de prova han de mostrar:

```
????????????????????????????????????????????????????????????
?                  RESUM DEL JOC DE PROVA XX               ?
????????????????????????????????????????????????????????????

Tests executats: N
Tests pasats:    N ?
Tests fallats:   0 ?

??? TOTS ELS TESTS HAN PASSAT CORRECTAMENT! ???
```

---

## ?? Verificació Manual amb SQL

També pots verificar manualment les dades:

```sql
USE plango;

-- Veure tots els usuaris
SELECT * FROM Usuari ORDER BY sobrenom;

-- Veure totes les experiències
SELECT e.nom, e.ciutat, e.preu, e.maximPlaces, 
       CASE 
         WHEN esc.nom IS NOT NULL THEN 'ESCAPADA'
         WHEN act.nom IS NOT NULL THEN 'ACTIVITAT'
       END as tipus
FROM Experiencia e
LEFT JOIN Escapada esc ON e.nom = esc.nom
LEFT JOIN Activitat act ON e.nom = act.nom
ORDER BY e.dataAlta DESC;

-- Veure totes les reserves amb detalls
SELECT r.id, u.sobrenom, e.nom as experiencia, 
       r.numPlaces, r.preuPagat, r.data
FROM Reserva r
JOIN Usuari u ON r.usuari = u.sobrenom
JOIN Experiencia e ON r.experiencia = e.nom
ORDER BY r.data DESC;

-- Resum de reserves per usuari
SELECT u.sobrenom, u.nom, 
       COUNT(r.id) as numReserves,
       SUM(r.preuPagat) as totalPagat
FROM Usuari u
LEFT JOIN Reserva r ON u.sobrenom = r.usuari
GROUP BY u.sobrenom, u.nom
ORDER BY numReserves DESC;

-- Top experiències més reservades
SELECT e.nom, e.ciutat, e.numReserves,
       CASE 
         WHEN esc.nom IS NOT NULL THEN 'ESCAPADA'
         WHEN act.nom IS NOT NULL THEN 'ACTIVITAT'
       END as tipus
FROM Experiencia e
LEFT JOIN Escapada esc ON e.nom = esc.nom
LEFT JOIN Activitat act ON e.nom = act.nom
ORDER BY e.numReserves DESC
LIMIT 5;
```

---

## ?? Notes Importants

1. **Ordre d'Execució**: Executa sempre en aquest ordre:
   - `01_inicialitzar_bd.sql` primer
   - Després els programes de prova
   - `99_netejar_bd.sql` al final

2. **Dades de Test**: Els jocs de prova creen i esborren les seves pròpies dades, però utilitzen també les dades de l'script d'inicialització.

3. **Transaccions**: Tots els DAOs utilitzen transaccions ODB per mantenir la integritat.

4. **CASCADE DELETE**: En esborrar un usuari, s'esborren automàticament les seves reserves.

5. **Descompte**: El descompte es configura a 15% en els tests de reserves.

---

## ?? Suport

Si algun test falla:
1. Verifica que la BD està ben inicialitzada
2. Comprova que el fitxer `configuracio.env` és correcte
3. Revisa que tots els fitxers ODB s'han generat
4. Assegura't que MariaDB està actiu

---

## ? Checklist de Verificació

Abans d'executar els tests:
- [ ] Base de dades `plango` creada
- [ ] Fitxers ODB generats
- [ ] Esquema creat (taules)
- [ ] Dades inicials carregades
- [ ] Fitxer `configuracio.env` configurat
- [ ] Llibreries ODB i Boost instal·lades

Després d'executar els tests:
- [ ] 10 tests d'usuaris passat
- [ ] 11 tests d'experiències passat
- [ ] 10 tests de reserves passat
- [ ] 11 tests de consultes passat
- [ ] **TOTAL: 42/42 tests passat** ?

---

**Desenvolupat per INEP 2025 - UPC**
