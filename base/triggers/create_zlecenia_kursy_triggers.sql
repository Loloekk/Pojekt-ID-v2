create or replace function insert_zlecenia_kursy() returns trigger as
$$
begin
    if (select count(*) from nadania n where n.id_zlecenia = new.id_zlecenia) = 0 then
        raise exception 'Przesyłka nie została jeszcze nadana';
        return null;
    end if;
    return new;
    /*if (select count(*) from zlecenia_kursy zk where zk.id_zlecenia = new.id_zlecenia) = 0 then
        if (select count (*) from kursy_paczkomaty kp join zlecenia z on kp.id_paczkomatu = z.id_zlecenia where z.id_zlecenia = new.id_zlecenia and kp.id_kursu = new.id_kursu and kp.data_odjazdu is null) > 0 then return new; end if;
      	raise exception 'Pojazd nie stoi przy odpowiednim paczkomacie';
        return null;
    else
        if (select count(*) from kursy k where k.id_kursu = new.id_kursu and k.data_wyjazdu is null and k.magazyn_start = getMagazynZlecenia(new.id_zlecenia)) > 0 then return new;end if;
        raise exception 'Nie ma takiego kursu';
        return null;
    end if;*/
end;
$$
language plpgsql;

drop trigger if exists tr_insert_zlecenia_kursy on zlecenia_kursy;
create trigger tr_insert_zlecenia_kursy before insert on zlecenia_kursy for each row execute procedure insert_zlecenia_kursy();
