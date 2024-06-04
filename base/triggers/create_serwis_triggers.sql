create or replace function insert_serwis() returns trigger as 
$$
begin
    if getKursPojazdu(new.id_pojazdu) is not null then raise exception 'Pojazd jest w trasie.'; return null; end if;
    return new;
end;
$$
language plpgsql;


drop trigger if exists tr_insert_serwis on serwis;
create trigger tr_insert_serwis before insert on serwis for each row execute procedure insert_serwis();


create or replace function update_serwis() returns trigger as 
$$
begin
    if old.id_pojazdu != new.id_pojazdu then 
        raise exception 'Nie mozna edytować id_pojazdu.';
        return null;
    end if;
    if old.id_przegladu != new.id_przegladu then 
        raise exception 'Nie mozna edytować id_przegladu.';
        return null;
    end if;if old.data_rozpoczecia != new.data_rozpoczecia then 
        raise exception 'Nie mozna edytować data_rozpoczecia.';
        return null;
    end if;
    if new.data_zakonczenia is not null and new.data_zakonczenia < new.data_rozpoczecia then
        raise exception 'data_zakonczenia musi byc pozniej niż data_rozpoczecia.';
        return null;
    end if;
    return new;
end;
$$
language plpgsql;


drop trigger if exists tr_update_serwis on serwis;
create trigger tr_update_serwis before update on serwis for each row execute procedure update_serwis();