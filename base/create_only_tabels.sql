
DROP TABLE IF EXISTS osoby CASCADE;
DROP TABLE IF EXISTS stanowiska CASCADE;
DROP TABLE IF EXISTS stanowiska_osoby CASCADE;
DROP TABLE IF EXISTS uprawnienia CASCADE;
DROP TABLE IF EXISTS osoby_uprawnienia CASCADE;
DROP TABLE IF EXISTS rodzaje_pojazdow CASCADE;
DROP TABLE IF EXISTS pojazdy CASCADE;
DROP TABLE IF EXISTS usterki CASCADE;
DROP TABLE IF EXISTS rodzaje_przegladow CASCADE;
DROP TABLE IF EXISTS przeglady_rod_pojazdy CASCADE;
DROP TABLE IF EXISTS serwis CASCADE;
DROP TABLE IF EXISTS magazyny CASCADE;
DROP TABLE IF EXISTS praca_osoby CASCADE;
DROP TABLE IF EXISTS paczkomaty CASCADE;
DROP TABLE IF EXISTS zlecenia CASCADE;
DROP TABLE IF EXISTS kursy CASCADE;
DROP TABLE IF EXISTS zlecenia_kursy CASCADE;
DROP TABLE IF EXISTS nadania CASCADE;
DROP TABLE IF EXISTS odbiory CASCADE;
DROP TABLE IF EXISTS zlecenia_magazyny CASCADE;
DROP TABLE IF EXISTS kursy_paczkomaty CASCADE;
DROP TABLE IF EXISTS skrytki CASCADE;
DROP TABLE IF EXISTS deklaracja_wypakowan CASCADE;

CREATE TABLE osoby(
    id_osoby NUMERIC(9,0) PRIMARY KEY,
    pesel NUMERIC(15,0),
    imie VARCHAR(30) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    nr_tel VARCHAR(25) NOT NULL UNIQUE
);

CREATE TABLE stanowiska(
    id_stanowiska NUMERIC(6,0) PRIMARY KEY,
    nazwa VARCHAR(200) NOT NULL
);

CREATE TABLE stanowiska_osoby(
    id_osoby NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    id_stanowiska NUMERIC(6,0) NOT NULL REFERENCES stanowiska(id_stanowiska)
);

CREATE TABLE uprawnienia(
    id_uprawnienia NUMERIC(4,0) PRIMARY KEY,
    nazwa VARCHAR(200) NOT NULL
);

CREATE TABLE osoby_uprawnienia(
    id_osoby NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    id_uprawnienia NUMERIC(4,0) NOT NULL REFERENCES uprawnienia(id_uprawnienia)
);

CREATE TABLE rodzaje_pojazdow(
    id_rodzaju NUMERIC(9,0) PRIMARY KEY,
    nazwa VARCHAR(200) NOT NULL,
    pojemnosc NUMERIC(12,0) NOT NULL,
    id_uprawnienia NUMERIC(4,0) REFERENCES uprawnienia(id_uprawnienia)
);

CREATE TABLE pojazdy(
    id_pojazdu NUMERIC(9,0) PRIMARY KEY,
    nr_rejestracyjny VARCHAR(12) NOT NULL,
    id_rodzaju NUMERIC(9,0) NOT NULL REFERENCES rodzaje_pojazdow(id_rodzaju)
);

CREATE TABLE usterki(
    id_pojazdu NUMERIC(9,0) NOT NULL REFERENCES pojazdy(id_pojazdu),
    opis VARCHAR(300) NOT NULL,
    data_wystapienia TIMESTAMP NOT NULL,
    data_rozpoczecia_naprawy TIMESTAMP CHECK(data_wystapienia<=data_rozpoczecia_naprawy),
    data_zakonczenia_naprawy TIMESTAMP CHECK(data_rozpoczecia_naprawy<=data_zakonczenia_naprawy)
);

CREATE TABLE rodzaje_przegladow(
    id_przegladu NUMERIC(9,0) PRIMARY KEY,
    nazwa VARCHAR(200) NOT NULL
);

CREATE TABLE przeglady_rod_pojazdy(
    id_rodzaju NUMERIC(9,0) NOT NULL REFERENCES rodzaje_pojazdow(id_rodzaju),
    id_przegladu NUMERIC(9,0) NOT NULL REFERENCES rodzaje_przegladow(id_przegladu),
    czestotliwosc INT NOT NULL
);

CREATE TABLE serwis(
    id_pojazdu NUMERIC(9,0) NOT NULL REFERENCES pojazdy(id_pojazdu),
    id_przegladu NUMERIC(9,0) NOT NULL REFERENCES rodzaje_przegladow(id_przegladu),
    data_rozpoczecia TIMESTAMP,
    data_zakonczenia TIMESTAMP, CHECK(data_rozpoczecia<data_zakonczenia)
);

CREATE TABLE magazyny(
    id_magazynu NUMERIC(6,0) PRIMARY KEY,
    lokalizacja VARCHAR(200) NOT NULL
);

CREATE TABLE praca_osoby(
    id_osoby NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    id_magazynu NUMERIC(6,0) NOT NULL REFERENCES magazyny(id_magazynu),
    id_stanowiska NUMERIC(6,0) NOT NULL REFERENCES stanowiska(id_stanowiska),
    data_rozpoczecia TIMESTAMP NOT NULL,
    data_zakonczenia TIMESTAMP CHECK(data_rozpoczecia<data_zakonczenia)
);

CREATE TABLE paczkomaty(
    id_paczkomatu NUMERIC(9,0) PRIMARY KEY,
    lokalizacja VARCHAR(200) NOT NULL,
    magazyn NUMERIC(6,0) NOT NULL REFERENCES magazyny(id_magazynu)
);

CREATE TABLE zlecenia(
    id_zlecenia NUMERIC(12,0) PRIMARY KEY,
    id_nadawcy NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    id_odbiorcy NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    id_pacz_odb NUMERIC(9,0) NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    data_zlozenia TIMESTAMP NOT NULL,
    rozmiar NUMERIC(1,0),
    CONSTRAINT rozmiary_przesylek CHECK (rozmiar IN(1,2,3))
);

CREATE TABLE kursy(
    id_kursu NUMERIC(12,0) PRIMARY KEY,
    id_pojazdu NUMERIC(9,0) NOT NULL REFERENCES pojazdy(id_pojazdu),
    id_kierowcy NUMERIC(9,0) NOT NULL REFERENCES osoby(id_osoby),
    magazyn_start NUMERIC(6,0) NOT NULL REFERENCES magazyny(id_magazynu),
    magazyn_docelowy NUMERIC(6,0) NOT NULL REFERENCES magazyny(id_magazynu),
    data_wyjazdu TIMESTAMP,
    data_przyjazdu TIMESTAMP CHECK (data_wyjazdu<=data_przyjazdu)
);

CREATE TABLE zlecenia_kursy(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_kursu NUMERIC(12,0) NOT NULL REFERENCES kursy(id_kursu),
    "data" TIMESTAMP NOT NULL
);

CREATE TABLE zlecenia_magazyny(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_magazynu NUMERIC(6,0) NOT NULL REFERENCES magazyny(id_magazynu),
    "data" TIMESTAMP NOT NULL
);

CREATE TABLE kursy_paczkomaty(
    id_kursu NUMERIC(12,0) NOT NULL REFERENCES kursy(id_kursu),
    id_paczkomatu NUMERIC(9,0) NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    data_przyjazdu TIMESTAMP NOT NULL,
    data_odjazdu TIMESTAMP CHECK (data_przyjazdu<=data_odjazdu)
);

CREATE TABLE skrytki(
    id_skrytki NUMERIC(12,0) PRIMARY KEY,
    id_paczkomatu NUMERIC(9,0) NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    rozmiar NUMERIC(1,0) NOT NULL,
    CONSTRAINT rozmiary_skrytek CHECK (rozmiar IN(1,2,3))
);

CREATE TABLE odbiory(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_skrytki NUMERIC(12,0) NOT NULL REFERENCES skrytki(id_skrytki),
    data_dostarczenia TIMESTAMP,
    data_odebrania TIMESTAMP
);

CREATE TABLE nadania(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_skrytki NUMERIC(12,0) NOT NULL REFERENCES skrytki(id_skrytki),
    "data" TIMESTAMP NOT NULL
);

CREATE TABLE deklaracja_wypakowan(
    id_kursu NUMERIC(12,0) NOT NULL REFERENCES kursy(id_kursu),
    "data" TIMESTAMP NOT NULL
);
