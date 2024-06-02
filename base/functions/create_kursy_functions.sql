create or replace function getPaczkomatKursu(id_kurs int) returns int as 
$$
begin
    if id_kurs is null then return null; end if;
    if (select count(*) from kursy_paczkomaty kp where kp.id_kursu = id_kurs and kp.data_odjazdu is null) != 1 then return null; end if;
    return (select kp.id_paczkomatu from kursy_paczkomaty kp where kp.id_kursu = id_kurs and kp.data_odjazdu is null);
end;
$$
language plpgsql;
