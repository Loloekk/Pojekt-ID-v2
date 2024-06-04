create or replace function insert_kursy_paczkomaty() returns trigger as
$$
declare
wyjazd timestamp;
begin
    wyjazd := (select k.data_wyjazdu from kursy k where k.id_kursu = new.id_kursu);
    exception when others then return null;
    if (new.data_przyjazdu < wyjazd) then
        raise exception 'Pojazd jeszcze nie wyjechal.';
        return null;
    end if;
    if(select count(*) from kursy_paczkomaty kp where kp.data_odjazdu is null) > 0 then
        raise exception 'Pojazd stoi przy innym paczkomacie.';
        return null;
    end if;
    return new;
end;
$$
language plpgsql;

drop trigger if exists tr_insert_kursy_paczkomaty on kursy_paczkomaty;
create trigger tr_insert_kursy_paczkomaty before insert on kursy_paczkomaty for each row execute procedure insert_kursy_paczkomaty();

create or replace function update_kursy_paczkomaty() returns trigger as
$$
begin
    if(old.id_kursu != new.id_kursu) then
        raise exception 'Nie wolno zmieniac id_kursu.';
        return null;end if;
    if(old.id_paczkomatu != new.id_paczkomatu) then
        raise exception 'Nie wolno zmieniac id_paczkomatu.';
        return null;end if;
    if(old.data_przyjazdu != new.data_przyjazdu) then
        raise exception 'Nie wolno zmieniac data_przyjazdu.';
        return null;end if;
    if(new.data_odjazdu < new.data_przyjazdu) then
        raise exception 'Data odjazdu musi byc wieksza niz data przyajzdu.';
        return null;end if;
    return new;
end;
$$
language plpgsql;

drop trigger if exists tr_update_kursy_paczkomaty on kursy_paczkomaty;
create trigger tr_update_kursy_paczkomaty before update on kursy_paczkomaty for each row execute procedure update_kursy_paczkomaty();
