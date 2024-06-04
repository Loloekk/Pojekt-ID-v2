create or replace function insert_zlecenia_magazyny() returns trigger as
$$
declare
kurs int;
begin
    kurs := getKursZlecenia(new.id_zlecenia);
    if kurs is null then return null; end if;
    if (select count(*) from kursy k where k.id_kursu = kurs and k.data_przyjazdu is not null and k.magazyn_docelowy = new.id_magazynu) > 0 then return new;end if;
    raise exception 'Zlecenie nie może zostać wypakowane';
    return null;
end;
$$
language plpgsql;

drop trigger if exists tr_insert_zlecenia_magazyny on zlecenia_magazyny;
create trigger tr_insert_zlecenia_magazyny before insert on zlecenia_magazyny for each row execute procedure insert_zlecenia_magazyny();
