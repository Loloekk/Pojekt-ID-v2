create or replace function insert_praca_osoby() returns trigger AS
$insert_praca_osoby$
begin
    if (select count(*) from praca_osoby po where po.id_osoby = new.id_osoby and (po.data_zakonczenia is null or po.data_zakonczenia > new.data_rozpoczecia)) > 0 then
        raise exception' Ta osoba już pracuje.';
        return null;
    end if; 
    if (select count(*) from praca_osoby po where po.id_osoby = new.id_osoby and po.data_rozpoczecia > new.data_rozpoczecia) > 0 then
        raise exception 'Błędna data.';
        return null;
    end if; 
    if (select count(*) from stanowiska_osoby so where so.id_osoby = new.id_osoby and so.id_stanowiska = new.id_stanowiska) = 0 then
        raise exception 'Niepoprawne stanowisko';
        return null;
    end if;
    return new;
end;
$insert_praca_osoby$
language plpgsql;

drop trigger if exists tr_insert_praca_osoby on praca_osoby;
create trigger tr_insert_praca_osoby before insert on praca_osoby for each row execute procedure insert_praca_osoby();

create or replace function update_praca_osoby() returns trigger AS
$update_praca_osoby$
begin
    if old.id_osoby != new.id_osoby then
        raise exception 'Nie można edytować osoby';
        return null;
    end if;
    if old.id_magazynu != new.id_magazynu then
        raise exception 'Nie można edytować magazynu';
        return null;
    end if;
    if old.id_stanowiska != new.id_stanowiska then
        raise exception 'Nie można edytować stanowiska';
        return null;
    end if;
    if old.data_rozpoczecia != new.data_rozpoczecia then
        raise exception 'Nie można edytować daty rozpoczecia';
        return null;
    end if;
    if new.data_zakonczenia < odl.data_rozpoczecia then
        raise exception 'Błędna data';
        return null;
    end if;
    return new;
end;
$update_praca_osoby$
language plpgsql;

drop trigger if exists tr_update_praca_osoby on praca_osoby;
create trigger tr_update_praca_osoby before update on praca_osoby for each row execute procedure update_praca_osoby();
