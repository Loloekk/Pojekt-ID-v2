create or replace function getMagazynZlecenia(id_zle int) returns int AS
$getMagazyn$
declare
data_magazyn timestamp;
data_kurs timestamp;
begin
    if id_zle is null then return null; end if; 
    data_magazyn := (select max(zm.data_rozpakowania) from zlecenia_magazyny zm where zm.id_zlecenia = id_zle);
    data_kurs := (select max(zk.data_zapakowania) from zlecenia_kursy zk where zk.id_zlecenia = id_zle);
    if data_kurs > data_magazyn then return null; end if;
    return (select zm.id_magazynu from zlecenia_magazyny zm where zm.data_rozpakowania = data_magazyn and zm.id_zlecenia = id_zle);
end;
$getMagazyn$
language plpgsql;

create or replace function getKursZlecenia(id_zle int) returns int AS
$getKurs$
declare
data_magazyn timestamp;
data_kurs timestamp;
begin
    if id_zle is null then return null; end if; 
    data_magazyn := (select max(zm.data_rozpakowania) from zlecenia_magazyny zm where zm.id_zlecenia = id_zle);
    data_kurs := (select max(zk.data_zapakowania) from zlecenia_kursy zk where zk.id_zlecenia = id_zle);
    if data_kurs < data_magazyn then return null; end if;
    return (select zm.id_kursu from zlecenia_kursy zk where zk.data_zapakowania = data_kurs and zk.id_zlecenia = id_zle);
end;
$getKurs$
language plpgsql;
