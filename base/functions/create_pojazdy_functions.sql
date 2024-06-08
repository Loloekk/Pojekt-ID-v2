create or replace function getKursPojazdu(id_pojazd int) returns int as
$$
begin
    return (select k.id_kursu from kursy k where k.id_pojazdu = id_pojazd and data_przyjazdu is null);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function isSerwisedPojazdu(id_pojazd int) returns boolean as
$$
begin
    return case when (select count(*) from serwis s where s.id_pojazdu = id_pojazd and s.data_zakonczenia is null) > 0
        then true
        else false
    end;
    return false;
end;
$$
language plpgsql;

create or replace function isUsterkiPojazdu(id_pojazd int) returns boolean as
$$
begin
    return case when (select count(*) from usterki u where u.id_pojazdu = id_pojazd and u.data_zakonczenia_naprawy is null) > 0
        then true
        else false
    end;
    return false;
end;
$$
language plpgsql;

create or replace function getMagazynPojazdu(id_pojazd int) returns int as
$$
begin
    if getKursPojazdu(id_pojazd) is not null then return null; end if;
    if isSerwisedPojazdu(id_pojazd) then return null; end if;
    if isUsterkiPojazdu(id_pojazd) then return null; end if;
    return (select k.magazyn_docelowy from kursy k where k.id_pojazdu = id_pojazd order by data_wyjazdu desc limit 1);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function getWymaganeUprawnieniePojazdu(id_pojazd int) returns int as
$$
begin
    return (select rp.id_uprawnienia from pojazdy p join rodzaje_pojazdow rp using(id_rodzaju) where p.id_pojazdu = id_pojazd);
    exception when others then return null;

end;
$$
language plpgsql;

create or replace function needSerwis(id_pojazd int) returns boolean as
$$
declare  
r record;
begin
    for r in (select prp.id_przegladu, prp.czestotliwosc from pojazdy p join przeglady_rod_pojazdy prp on p.id_rodzaju = prp.id_rodzaju where p.id_pojazdu = id_pojazd) loop
        if (select max(s.data_zakonczenia) from serwis s where s.id_pojazdu = id_pojazd and s.id_przegladu = r.id_przegladu) < now() - (r.czestotliwosc * interval '1 month') then return true; end if;
    end loop;
    return false;
end;
$$
language plpgsql;

create or replace function lastSerwis(id_pojazd int, id_serwis int) returns timestamp as
$$
begin
    return (select max(s.data_zakonczenia) from serwis s where s.id_pojazdu = id_pojazd and s.id_przegladu = id_serwis);
end;
$$
language plpgsql;