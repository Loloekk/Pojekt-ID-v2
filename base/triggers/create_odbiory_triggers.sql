create or replace function insert_odbiory() returns trigger as
$insert_odbiory$
begin
    if (select count(*) from odbiory o where i.id_zlecenia = new.id_zlecenia) > 0 then 
        raise exception 'Ta przesyłka już ma zarejestrowaną skrytkę.';
        return null;
    end if;
    if (select count(*) from zlecenia z left join zlecenia_kursy zk on zk.id_zlecenia = z.id_zlecenia left join odbiory o on o.id_zlecenia = z.id_zlecenia where o.id_skrytki = new.id_skrytki and zk.id_kursu is null) + (select count(*) from odbiory o where o.id_skrytki = new.id_skrytki and o.data_odebrania is null) > 0 then
        raise exception 'Zajęta skrytka';
        return null;
    end if;
    if new.data_dostarczenia is not null then
        if getPaczkomatKursu(getKursZlecenia(new.id_zlecenia)) is null or getPaczkomatSkrytki(new.id_skrytki) or getPaczkomatKursu(getKursZlecenia(new.id_zlecenia)) != getPaczkomatSkrytki(new.id_skrytki) then 
            raise exception 'Żaden kierowca nie jest przy tym paczkomacie';
            return null;
        end if;
    end if;
    if new.data_odebrania is not null and (new.data_dostarczenia is null or new.data_dostarczenia > new.data_odebrania) then
        raise exception 'Błąd w datach';
        return null;
    end if; 
    return new;
end;
$insert_odbiory$
language plpgsql;

create or replace trigger tr_insert_odbiory before insert on odbiory for each row execute procedure insert_odbiory();


create or replace function update_odbiory() returns trigger as
$update_odbiory$
begin
    if old.id_zlecenia != new.id_zlecenia or old.id_skrytki != new.id_skrytki then 
        raise exception 'Nie można edytować pól id_zlecenia oraz id_skrytki';
        return null;
    end if;
    if new.data_dostarczenia is not null and old.data_dostarczenia is null then
        if getPaczkomatKursu(getKursZlecenia(new.id_zlecenia)) is null or getPaczkomatSkrytki(new.id_skrytki) or getPaczkomatKursu(getKursZlecenia(new.id_zlecenia)) != getPaczkomatSkrytki(new.id_skrytki) then 
            raise exception 'Żaden kierowca nie jest przy tym paczkomacie';
            return null;
        end if;
    end if;
    if new.data_dostarczenia is not null and old.data_dostarczenia is not null and new.data_dostarczenia != old.data_dostarczenia then
        raise exception 'Nie można edytować pola data_dostarczenia';
        return null;
    end if;
    if new.data_odebrania is not null and odl.data_odebrania is null and (new.data_dostarczenia is null or new.data_dostarczenia > new.data_odebrania) then
        raise exception 'Błąd w datach';
        return null;
    end if; 
    if new.data_odebrania is not null and old.data_odebrania is not null and new.data_odebrania != old.data_odebrania then
        raise exception 'Nie można edytować pola data_odebrania';
        return null;
    end if;
    return new;
end;
$update_odbiory$
language plpgsql;

create or replace trigger tr_update_odbiory before update on odbiory for each row execute procedure update_odbiory();
