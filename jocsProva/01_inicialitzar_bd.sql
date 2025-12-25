-- ============================================================================
-- SCRIPT D'INICIALITZACIÓ DE LA BASE DE DADES PER JOCS DE PROVA
-- Sistema PlanGo - INEP 2025
-- ============================================================================

USE plango;

-- Configurar el sistema amb un descompte inicial del 15%
-- (Aquest valor es pot modificar durant els tests)

-- Eliminar dades anteriors si existeixen (ordre important per FK)
DELETE FROM Reserva;
DELETE FROM Escapada;
DELETE FROM Activitat;
DELETE FROM Experiencia;
DELETE FROM Usuari;

-- Reiniciar auto_increment de Reserva
ALTER TABLE Reserva AUTO_INCREMENT = 1;

-- ============================================================================
-- INSERTAR USUARIS DE PROVA
-- ============================================================================

INSERT INTO Usuari (sobrenom, nom, contrasenya, correuElectronic, edat) VALUES
('admin', 'Administrador del Sistema', 'admin123', 'admin@plango.com', 35),
('joan', 'Joan García Martínez', 'pass123', 'joan@gmail.com', 28),
('maria', 'Maria López Sánchez', 'maria456', 'maria@yahoo.com', 32),
('pere', 'Pere Rodríguez Vila', 'pere789', 'pere@hotmail.com', 25),
('anna', 'Anna Fernández Costa', 'anna321', 'anna@outlook.com', 41),
('david', 'David Martí Pujol', 'david654', 'david@gmail.com', 22),
('laura', 'Laura Soler Ribas', 'laura987', 'laura@gmail.com', 30);

-- ============================================================================
-- INSERTAR ESCAPADES
-- ============================================================================

INSERT INTO Escapada (nom, descripcio, ciutat, maximPlaces, preu, dataAlta, numReserves, hotel, numNits) VALUES
('Weekend Barcelona', 
 'Escapada de cap de setmana a Barcelona amb visita als principals monuments i gastronomia catalana', 
 'Barcelona', 4, 450.00, '2024-12-01', 0, 'Hotel Arts Barcelona', 2),

('Escapada Pirineus', 
 'Escapada a la muntanya amb rutes de senderisme i gastronomia de muntanya', 
 'Vall d''Aran', 6, 380.00, '2024-12-05', 0, 'Hotel Parador d''Arties', 3),

('Costa Brava Luxury', 
 'Weekend de luxe a la Costa Brava amb spa i platja privada', 
 'Tossa de Mar', 2, 650.00, '2024-12-10', 0, 'Hotel Mar Menuda', 2),

('Ruta del Vi Penedès', 
 'Escapada enogastronòmica pel Penedès amb visita a cellers i tast de vins', 
 'Vilafranca del Penedès', 8, 320.00, '2024-12-12', 0, 'Hotel Finca Bell-lloc', 2),

('Madrid Cultural', 
 'Escapada cultural a Madrid amb entrades a museus i espectacles', 
 'Madrid', 4, 520.00, '2024-12-15', 0, 'Hotel Ritz Madrid', 3);

-- ============================================================================
-- INSERTAR ACTIVITATS
-- ============================================================================

INSERT INTO Activitat (nom, descripcio, ciutat, maximPlaces, preu, dataAlta, numReserves, durada) VALUES
('Parapent Costa Brava', 
 'Vol en parapent amb monitor qualificat i vistes espectaculars de la costa', 
 'Girona', 8, 85.00, '2024-12-01', 0, 120),

('Kayak Pirineus', 
 'Descens en kayak pel riu Noguera Pallaresa amb material inclòs', 
 'Lleida', 12, 55.00, '2024-12-03', 0, 180),

('Escalada Montserrat', 
 'Escalada a Montserrat amb guia professional per a tots els nivells', 
 'Montserrat', 6, 70.00, '2024-12-06', 0, 240),

('Diving Costa Brava', 
 'Immersió amb equip complet a les cales més boniques de la Costa Brava', 
 'L''Estartit', 8, 95.00, '2024-12-08', 0, 150),

('BTT Collserola', 
 'Ruta en bicicleta de muntanya pel Parc Natural de Collserola', 
 'Barcelona', 10, 40.00, '2024-12-10', 0, 180),

('Surf Tarragona', 
 'Classe de surf per a principiants amb monitor i taula inclosa', 
 'Tarragona', 8, 50.00, '2024-12-12', 0, 120),

('Barranquisme Pallars', 
 'Descens de barrancs amb tècniques de ràpel i salts d''aigua', 
 'Pallars Sobirà', 6, 80.00, '2024-12-14', 0, 300),

('Espeleologia Garrotxa', 
 'Exploració de coves volcàniques amb equip especialitzat', 
 'Olot', 10, 60.00, '2024-12-16', 0, 180);

-- ============================================================================
-- VERIFICACIÓ DE LES DADES INSERTADES
-- ============================================================================

-- Mostrar resum d'usuaris
SELECT 'USUARIS CREATS:' as Info;
SELECT sobrenom, nom, edat, correuElectronic FROM Usuari ORDER BY sobrenom;

-- Mostrar resum d'escapades
SELECT '' as Separador;
SELECT 'ESCAPADES CREADES:' as Info;
SELECT nom, ciutat, preu as 'Preu (€)', maximPlaces as Places, numNits as Nits 
FROM Escapada ORDER BY dataAlta;

-- Mostrar resum d'activitats
SELECT '' as Separador;
SELECT 'ACTIVITATS CREADES:' as Info;
SELECT nom, ciutat, preu as 'Preu (€)', maximPlaces as Places, durada as 'Durada (min)' 
FROM Activitat ORDER BY dataAlta;

-- Resum total
SELECT '' as Separador;
SELECT 'RESUM TOTAL:' as Info;
SELECT 
    (SELECT COUNT(*) FROM Usuari) as TotalUsuaris,
    (SELECT COUNT(*) FROM Escapada) as TotalEscapades,
    (SELECT COUNT(*) FROM Activitat) as TotalActivitats,
    (SELECT COUNT(*) FROM Reserva) as TotalReserves;

-- ============================================================================
-- FI DE L'SCRIPT D'INICIALITZACIÓ
-- ============================================================================
