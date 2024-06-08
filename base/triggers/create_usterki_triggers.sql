create or replace function update_usterki() returns trigger as 
$$
begin
    if old.id_pojazdu != new.id_pojazdu then
        raise exception 'Nie mozna edytowac id_pojazdu.';
        return null;
    end if;
    if old.data_wystapienia is not null and old.data_wystapienia != new.data_wystapienia then
        raise exception 'Nie mozna edytowac data_wystapienia.';
        return null;
    end if;
    if old.data_rozpoczecia_naprawy is not null and old.data_rozpoczecia_naprawy != new.data_rozpoczecia_naprawy then
        raise exception 'Nie mozna edytowac data_rozpoczecia_naprawy.';
        return null;
    end if;
    if new.data_rozpoczecia_naprawy is not null and data_rozpoczecia_naprawy < new.data_wystapienia then
        raise exception 'data_rozpoczecia_naprawy musi byc wieksza niz data_wystapienia.';
        return null;
    end if;
    if old.data_zakonczenia_naprawy is not null and old.data_zakonczenia_naprawy != new.data_zakonczenia_naprawy then
        raise exception 'Nie mozna edytowac data_zakonczenia_naprawy.';
        return null;
    end if;
    if new.data_zakonczenia_naprawy is not null and data_zakonczenia_naprawy < new.data_rozpoczecia_naprawy then
        raise exception 'data_zakonczenia_naprawy musi byc wieksza niz data_rozpoczecia_naprawy.';
        return null;
    end if;
    return new;
end;
$$
language plpgsql;


drop trigger if exists tr_update_usterki on usterki;
create trigger tr_update_usterki before update on usterki for each row execute procedure update_usterki();