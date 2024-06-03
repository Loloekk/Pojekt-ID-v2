create or replace function startPracyOsoby(id_osoba int) returns timestamp as
$$
begin
    if (select count(*) from praca_osoby po where po.id_osoby = id_osoba and data_zakonczenia is null) = 0
    then return null; end if;
    return (select po.data_rozpoczecia from praca_osoby po where po.id_osoby = id_osoba and data_zakonczenia is null);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getMagazynStartOsoby(id_osoba int) returns int as
$$
begin
    if (select count(*) from praca_osoby po where po.id_osoby = id_osoba and data_zakonczenia is null) = 0
    then return null; end if;
    return (select po.id_magazynu from praca_osoby po where po.id_osoby = id_osoba and data_zakonczenia is null);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getKursOsoby(id_osoba int) returns int as
$$
begin
    return (select k.id_kursu from kursy k where k.id_osoby = id.osoba and data_przyjazdu is null);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getLeastMagazynKursOsoby(id_osoba int) returns int as
$$
begin
    return (select k.magazyn_docelowy from kursy k where k.id_osoby = id.osoba order by k.data_wyjazdu desc limit 1);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getLeastDateKursOsoby(id_osoba int) returns int as
$$
begin
    return (select k.id_wyjazdu from kursy k where k.id_osoby = id.osoba order by k.data_wyjazdu desc limit 1);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getMagazynOsoby(id_osoba int) returns int as
$$
begin
    if startPracyOsoby(id_osoba) is null then return null; end if;
    if getKursOsoby(id_osoba) is not null then return null; end if;
    if startPracyOsoby(id_osoba) > getLeastDateKursOsoby(id_osoba) 
        then return getMagazynStartOsoby(id_osoba); 
        else return getLeastMagazynKursOsoby(id_osoba);
    end if;
    exception when others then return null;
end;
$$
language plpgsql;