-- Nadaj paczke, zbierz ja z paczkomatu do magazynu, przewiez do innego magazynu, przewiez z magazynu do paczkomatu, odbierz paczke

-- Kurs z mag11 do mag11
select pg_sleep(0.3);
insert INTO zlecenia VALUES (default, 1, 2, 1, now(), 1); --rejestracja zlecenia
select pg_sleep(0.3);
insert into nadania values (11382, 23459, now()); -- nadanie paczki
select pg_sleep(0.3);
insert into praca_osoby values (30003, 11, 2, now(), null); -- kierowca przyszedl do pracy
select pg_sleep(0.3);
insert into kursy values ( default, 25, 30003, 11, 11, now(), null); -- start kursu z mag11 do mag11
select pg_sleep(0.3);
insert into kursy_paczkomaty values (6671, 139, now(), null); -- przyjazd do paczkomatu 139
select pg_sleep(0.3);
insert into zlecenia_kursy values (11382, 6671, now()); -- zapakowanie paczki do pojazdu, przypisanie jej do kursu
select pg_sleep(0.3);
update kursy_paczkomaty SET data_odjazdu = now() where id_kursu=6671 and id_paczkomatu=139; -- odjazd spod paczkomatu 139
select pg_sleep(0.3);
update kursy SET data_przyjazdu = now() where id_kursu=6671; -- zakonczenie kursu, dojechalismy do celu
select pg_sleep(0.3);
insert into zlecenia_magazyny values (6671, 11, now()); -- wypakowujemy paczke do magazynu
select pg_sleep(0.3);
insert into deklaracja_wypakowan values (6671, now()); -- deklarujemy ze wypakowalismy wszystkie paczki
select pg_sleep(0.3);

-- Kurs z mag11 do mag1
select pg_sleep(0.3);
insert into kursy values (default, 25, 30003, 11, 1, now(), null); -- start kursu z mag11 do mag1
select pg_sleep(0.3);
insert into zlecenia_kursy values (11382, 6672, now()); -- zapakowanie paczki do pojazdu, przypisanie jej do kursu
select pg_sleep(0.3);
update kursy SET data_przyjazdu = now() where id_kursu=6672; -- koniec kursu z mag11 do mag1
select pg_sleep(0.3);
insert into zlecenia_magazyny values (11382, 1, now()); -- przeniesienie paczki do mag1
select pg_sleep(0.3);
insert into deklaracja_wypakowan values (6672, now()); -- deklaracja wypakowania wszystkiego
select pg_sleep(0.3);

-- Kurs z mag1 do mag1
select pg_sleep(0.3);
insert into kursy values (default, 25, 30003, 1, 1, now(), null); -- start kursu z mag1 do mag1
select pg_sleep(0.3);
insert into zlecenia_kursy values (11382, 6673, now()); -- zapakowanie paczki do pojazdu, przypisanie jej do kursu
select pg_sleep(0.3);
insert into kursy_paczkomaty values (6673, 1, now(), null); -- przyjazd do paczkomatu 1
select pg_sleep(0.3);
update odbiory SET data_dostarczenia = now() where id_zlecenia=11382 and id_skrytki=23459; -- wlozenie paczki do paczkomatu
select pg_sleep(0.3);
update kursy_paczkomaty SET data_odjazdu = now() where id_kursu=6673 and id_paczkomatu=1; -- odjazd spod paczkomatu 1
select pg_sleep(0.3);
update kursy SET data_przyjazdu = now() where id_kursu=6673; -- zakonczenie kursu, rozwiezlismy wszystkie paczki
select pg_sleep(0.3);
insert into deklaracja_wypakowan values (6673, now()); -- deklarujemy ze wypakowalismy wszystkie paczki
