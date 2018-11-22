--
-- File generated with SQLiteStudio v3.2.1 on mar. nov. 20 03:24:17 2018
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: tpedi
CREATE TABLE tpedi (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, nombre VARCHAR NOT NULL, apellido VARCHAR NOT NULL, fecha DATE NOT NULL, asistencia VARCHAR NOT NULL);
INSERT INTO tpedi (id, nombre, apellido, fecha, asistencia) VALUES (1, 'juany', 'zaya', '12/12/12', 'presente');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
