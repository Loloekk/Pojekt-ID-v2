create or replace function getPaczkomatSkrytki(id_skrytka int) returns int as 
$$
begin
    if id_skrytka is null then return null; end if;
    return (select s.id_paczkomatu from skrytki s where s.id_sktyrki = id_skrytka);
end;
$$
language plpgsql;
