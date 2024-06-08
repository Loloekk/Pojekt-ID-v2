create or replace function insert_deklaracja_wypakowan() returns trigger as
$$
begin
    if (select count (*) from kursy k where k.id_kursu = new.id_kursu and data_przyjazdu is not null) > 0 then return new; end if;
    raise exception 'Pojazd jeszcze nie dojechal';
    return null;
end;
$$
language plpgsql;

drop trigger if exists tr_insert_deklaracja_wypakowan on deklaracja_wypakowan;
create trigger tr_insert_deklaracja_wypakowan before insert on deklaracja_wypakowan for each row execute procedure insert_deklaracja_wypakowan();
