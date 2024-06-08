create or replace function getPaczkomatSkrytki(id_skrytka int) returns int as 
$$
begin
    if id_skrytka is null then return null; end if;
    return (select s.id_paczkomatu from skrytki s where s.id_skrytki = id_skrytka);
end;
$$
language plpgsql;

create or replace function isEmptySkrytki(skrytkaId int) returns int as
$$
begin
    if (select count(*) from odbiory where data_odebrania is null and id_skrytki=skrytkaId)>0 then
        -- Skrytka jest zarezerwowana
        return (select id_zlecenia from odbiory where data_odebrania is null and id_skrytki=skrytkaId);
    end if;
    return null;
end;
$$
language plpgsql;
