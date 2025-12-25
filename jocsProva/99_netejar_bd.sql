-- ============================================================================
-- SCRIPT DE NETEJA DE LA BASE DE DADES
-- Sistema PlanGo - INEP 2025
-- ============================================================================
-- Aquest script esborra totes les dades de la base de dades mantenint
-- l'estructura de les taules intacta.
-- ============================================================================

USE plango;

SET FOREIGN_KEY_CHECKS = 0;

-- Esborrar totes les reserves
DELETE FROM Reserva;
ALTER TABLE Reserva AUTO_INCREMENT = 1;
SELECT 'Reserves esborrades' as Info;

-- Esborrar totes les escapades
DELETE FROM Escapada;
SELECT 'Escapades esborrades' as Info;

-- Esborrar totes les activitats
DELETE FROM Activitat;
SELECT 'Activitats esborrades' as Info;

-- Esborrar totes les experiències
DELETE FROM Experiencia;
SELECT 'Experiències esborrades' as Info;

-- Esborrar tots els usuaris
DELETE FROM Usuari;
SELECT 'Usuaris esborrats' as Info;

SET FOREIGN_KEY_CHECKS = 1;

-- Verificació final
SELECT '' as Separador;
SELECT 'VERIFICACIÓ DE NETEJA:' as Info;
SELECT 
    (SELECT COUNT(*) FROM Usuari) as Usuaris,
    (SELECT COUNT(*) FROM Experiencia) as Experiencies,
    (SELECT COUNT(*) FROM Escapada) as Escapades,
    (SELECT COUNT(*) FROM Activitat) as Activitats,
    (SELECT COUNT(*) FROM Reserva) as Reserves;

SELECT '' as Separador;
SELECT '? Base de dades netejada correctament' as Resultat;

-- ============================================================================
-- FI DE L'SCRIPT DE NETEJA
-- ============================================================================
