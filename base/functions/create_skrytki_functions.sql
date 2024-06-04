create or replace function getPaczkomatSkrytki(id_skrytka int) returns int as 
$$
begin
    if id_skrytka is null then return null; end if;
    return (select s.id_paczkomatu from skrytki s where s.id_sktyrki = id_skrytka);
end;
$$
language plpgsql;

create or replace function isEmptySkrytki(id_skrytka int) returns numeric(12,0) as
$$
declare 
zlecenie numeric(12,0);
begin
    zlecenie := (select n.id_zlecenia from nadania n left join odbiory o on (n.id_zlecenia = o.id_zlecenia and n.id_skrytki = o.id_skrytki) left join zlecenia_kursy zk on n.id_zlecenia = zk.id_zlecenia where n.id_skrytki = id_skrytka and zk.id_kursu is null and o.data_odebrania is null limit 1);
    exception when others then zlecenie := null;

    if zlecenie is not null then return zlecenie; end if;

    zlecenie := (select count(*) from odbiory o where o.id_skrytki = id_skrytka and o.data_odebrania is null);
    exception when others then zlecenie := null;
    
    if zlecenie is not null then return zlecenie; end if;
    return null;
end;
$$
language plpgsql;
