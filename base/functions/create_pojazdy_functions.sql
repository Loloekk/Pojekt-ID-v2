create or replace function getKursPojazdu(id_pojazd int) returns int as
$$
begin
    return (select k.id_kursu from kursy k where k.id_pojazdu = id.pojazd and data_przyjazdu is null);
    exception when others then return null;
end;
$$
language plpgsql;

create or replace function isSerwisedPojazdu(id_pojazd int) returns boolean as
$$
begin
    return case when (select count(*) from serwis s where s.id_pojazdu = id.pojazd and s.data_zakonczenia is null) > 0
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
    return case when (select count(*) from usterki u where u.id_pojazdu = id.pojazd and u.data_zakonczenia_naprawy is null) > 0
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
    return (select up.id_uprawnienia from pojazdy p join rodzaje_pojazdow rp using(id_rodzaju) where p.id_pojazdu = id_pojazd);
    exception when others then return null;

end;
$$
language plpgsql;