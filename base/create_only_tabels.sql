
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
    id_osoby INT PRIMARY KEY,
    pesel CHAR(11),
    imie VARCHAR(30) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    email VARCHAR(255) NOT NULL UNIQUE,
    nr_tel VARCHAR(25) NOT NULL UNIQUE
);

CREATE TABLE stanowiska(
    id_stanowiska NUMERIC(6,0) PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL
);

CREATE TABLE stanowiska_osoby(
    id_osoby INT NOT NULL REFERENCES osoby(id_osoby),
    id_stanowiska INT NOT NULL REFERENCES stanowiska(id_stanowiska),
    CONSTRAINT pk_stanowiska_osoby PRIMARY KEY(id_osoby,id_stanowiska)
);

CREATE TABLE uprawnienia(
    id_uprawnienia INT PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL
);

CREATE TABLE osoby_uprawnienia(
    id_osoby INT NOT NULL REFERENCES osoby(id_osoby),
    id_uprawnienia INT NOT NULL REFERENCES uprawnienia(id_uprawnienia),
    CONSTRAINT pk_osoby_uprawnienia PRIMARY KEY(id_osoby,id_uprawnienia)
);

CREATE TABLE rodzaje_pojazdow(
    id_rodzaju INT PRIMARY KEY,
    nazwa VARCHAR(50) NOT NULL,
    pojemnosc INT NOT NULL,
    id_uprawnienia INT REFERENCES uprawnienia(id_uprawnienia)
);

CREATE TABLE pojazdy(
    id_pojazdu INT PRIMARY KEY,
    nr_rejestracyjny VARCHAR(12) NOT NULL UNIQUE,
    id_rodzaju INT NOT NULL REFERENCES rodzaje_pojazdow(id_rodzaju)
);

CREATE TABLE usterki(
    id_pojazdu INT NOT NULL REFERENCES pojazdy(id_pojazdu),
    opis VARCHAR(300) NOT NULL,
    data_wystapienia TIMESTAMP NOT NULL,
    data_rozpoczecia_naprawy TIMESTAMP CHECK(data_wystapienia<=data_rozpoczecia_naprawy),
    data_zakonczenia_naprawy TIMESTAMP CHECK(data_rozpoczecia_naprawy<=data_zakonczenia_naprawy),
    CONSTRAINT roz_zak_usterki CHECK(data_zakonczenia_naprawy IS NULL OR data_rozpoczecia_naprawy IS NOT NULL),
    CONSTRAINT pk_usterki PRIMARY KEY(id_pojazdu,data_wystapienia,opis)
);

CREATE TABLE rodzaje_przegladow(
    id_przegladu INT PRIMARY KEY,
    nazwa VARCHAR(200) NOT NULL
);

CREATE TABLE przeglady_rod_pojazdy(
    id_rodzaju INT NOT NULL REFERENCES rodzaje_pojazdow(id_rodzaju),
    id_przegladu INT NOT NULL REFERENCES rodzaje_przegladow(id_przegladu),
    czestotliwosc INT NOT NULL,
    CONSTRAINT pk_przeglady_rod_pojazdy PRIMARY KEY(id_rodzaju,id_przegladu,czestotliwosc)
);

CREATE TABLE serwis(
    id_pojazdu INT NOT NULL REFERENCES pojazdy(id_pojazdu),
    id_przegladu INT NOT NULL REFERENCES rodzaje_przegladow(id_przegladu),
    data_rozpoczecia TIMESTAMP,
    data_zakonczenia TIMESTAMP, CHECK(data_rozpoczecia<data_zakonczenia),
    CONSTRAINT roz_zak_serwis CHECK(data_zakonczenia IS NULL OR data_rozpoczecia IS NOT NULL),
    CONSTRAINT ok_serwis PRIMARY KEY(id_pojazdu,id_przegladu,data_rozpoczecia)
);

CREATE TABLE magazyny(
    id_magazynu INT PRIMARY KEY,
    lokalizacja VARCHAR(200) NOT NULL
);

CREATE TABLE praca_osoby(
    id_osoby INT NOT NULL REFERENCES osoby(id_osoby),
    id_magazynu INT NOT NULL REFERENCES magazyny(id_magazynu),
    id_stanowiska INT NOT NULL REFERENCES stanowiska(id_stanowiska),
    data_rozpoczecia TIMESTAMP NOT NULL,
    data_zakonczenia TIMESTAMP CHECK(data_rozpoczecia<data_zakonczenia),
    CONSTRAINT pk_praca_osoby PRIMARY KEY (id_osoby,id_magazynu,id_stanowiska,data_rozpoczecia)
);

CREATE TABLE paczkomaty(
    id_paczkomatu INT PRIMARY KEY,
    lokalizacja VARCHAR(200) NOT NULL,
    magazyn INT NOT NULL REFERENCES magazyny(id_magazynu)
);

CREATE TABLE zlecenia(
    id_zlecenia NUMERIC(12,0) PRIMARY KEY,
    id_nadawcy INT NOT NULL REFERENCES osoby(id_osoby),
    id_odbiorcy INT NOT NULL REFERENCES osoby(id_osoby),
    id_pacz_odb INT NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    data_zlozenia TIMESTAMP NOT NULL,
    rozmiar INT NOT NULL,
    CONSTRAINT rozmiary_przesylek CHECK (rozmiar IN(1,2,3))
);

CREATE TABLE kursy(
    id_kursu INT PRIMARY KEY,
    id_pojazdu INT NOT NULL REFERENCES pojazdy(id_pojazdu),
    id_kierowcy INT NOT NULL REFERENCES osoby(id_osoby),
    magazyn_start INT NOT NULL REFERENCES magazyny(id_magazynu),
    magazyn_docelowy INT NOT NULL REFERENCES magazyny(id_magazynu),
    data_wyjazdu TIMESTAMP,
    data_przyjazdu TIMESTAMP CHECK (data_wyjazdu<=data_przyjazdu)
);

CREATE TABLE zlecenia_kursy(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_kursu INT NOT NULL REFERENCES kursy(id_kursu),
    "data_zapakowania" TIMESTAMP NOT NULL,
    CONSTRAINT pk_zlecenia_kursy PRIMARY KEY(id_zlecenia,id_kursu)

);

CREATE TABLE zlecenia_magazyny(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_magazynu INT NOT NULL REFERENCES magazyny(id_magazynu),
    "data_rozpakowania" TIMESTAMP NOT NULL,
    CONSTRAINT pk_zlecenia_magazyny PRIMARY KEY (id_zlecenia,id_magazynu)
);

CREATE TABLE kursy_paczkomaty(
    id_kursu INT NOT NULL REFERENCES kursy(id_kursu),
    id_paczkomatu INT NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    data_przyjazdu TIMESTAMP NOT NULL,
    data_odjazdu TIMESTAMP CHECK (data_przyjazdu<=data_odjazdu),
    CONSTRAINT pk_kursy_paczkomaty PRIMARY KEY (id_kursu,id_paczkomatu,data_przyjazdu)
);

CREATE TABLE skrytki(
    id_skrytki NUMERIC(12,0) PRIMARY KEY,
    id_paczkomatu INT NOT NULL REFERENCES paczkomaty(id_paczkomatu),
    rozmiar INT NOT NULL,
    CONSTRAINT rozmiary_skrytek CHECK (rozmiar IN(1,2,3))
);

CREATE TABLE odbiory(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_skrytki NUMERIC(12,0) NOT NULL REFERENCES skrytki(id_skrytki),
    data_dostarczenia TIMESTAMP,
    data_odebrania TIMESTAMP,
    CONSTRAINT pk_odbiory PRIMARY KEY (id_zlecenia)
);

CREATE TABLE nadania(
    id_zlecenia NUMERIC(12,0) NOT NULL REFERENCES zlecenia(id_zlecenia),
    id_skrytki NUMERIC(12,0) NOT NULL REFERENCES skrytki(id_skrytki),
    "data_nadania" TIMESTAMP NOT NULL,
    CONSTRAINT pk_nadania PRIMARY KEY(id_zlecenia)
);

CREATE TABLE deklaracja_wypakowan(
    id_kursu INT NOT NULL REFERENCES kursy(id_kursu),
    "data_wypakowania" TIMESTAMP NOT NULL,
    CONSTRAINT pk_deklaracja_wypakowan PRIMARY KEY(id_kursu)
);
