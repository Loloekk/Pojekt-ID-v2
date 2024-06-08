create or replace function insert_kursy() returns trigger as 
$$
begin
    if coalesce(getMagazynPojazdu(new.id_pojazdu),-1) != new.magazyn_start then 
        raise exception 'Pojazd nie znajduje sie w tym magazynie.';
        return null; end if;
    if coalesce(getMagazynOsoby(new.id_kierowcy),-1) != new.magazyn_start then 
            raise exception 'Kierowca nie znajduje sie w tym magazynie.';
        return null; end if;
    if needSerwis(new.id_pojazdu) then 
            raise exception 'Pojazd wymaga serwisu.';
        return null; end if;
    if hasUprawnienieOsoby(new.id_kierowcy,getWymaganeUprawnieniePojazdu(new.id_pojazdu)) then return new; end if;
        raise exception 'Kierowca nie posiada wymaganych uprawnien.';
    return null;
end;
$$
language plpgsql;


drop trigger if exists tr_insert_kursy on kursy;
create trigger tr_insert_kursy before insert on kursy for each row execute procedure insert_kursy();

create or replace function update_kursy() returns trigger as 
$$
begin
    if old.id_kursu != new.id_kursu then
        raise exception 'Nie mozna edytowac id_kursu.';
        return null;
    end if;
    if old.id_pojazdu != new.id_pojazdu then
        raise exception 'Nie mozna edytowac id_pojazdu.';
        return null;
    end if;
    if old.id_kierowcy != new.id_kierowcy then
        raise exception 'Nie mozna edytowac id_kierowcy.';
        return null;
    end if;
    if old.magazyn_start != new.magazyn_start then
        raise exception 'Nie mozna edytowac magazyn_start.';
        return null;
    end if;
    if old.magazyn_docelowy != new.magazyn_docelowy then
        raise exception 'Nie mozna edytowac magazyn_docelowy.';
        return null;
    end if;
    if old.data_wyjazdu is not null and old.data_wyjazdu != new.data_wyjazdu then
        raise exception 'Nie mozna edytowac data_wyjazdu.';
        return null;
    end if;
    if old.data_przyjazdu is not null and old.data_przyjazdu != new.data_przyjazdu then
        raise exception 'Nie mozna edytowac data_przyjazdu.';
        return null;
    end if;
    if new.data_przyjazdu is not null and new.data_przyjazdu < new.data_wyjazdu then
        raise exception 'Data przyjazdu musi byc wieksza niz data wyjazdu.';
        return null;
    end if;
    return new;
end;
$$
language plpgsql;


drop trigger if exists tr_update_kursy on kursy;
create trigger tr_update_kursy before update on kursy for each row execute procedure update_kursy();
