create or replace function insert_nadania() returns trigger AS
$insert_nadania$
begin
    if (select count(*) from nadania n where n.id_zlecenia = new.id_zlecenia) > 0 then 
        raise exception 'Ta przesyłka została już nadana.';
        return null;
    end if;
    if (select count(*) from zlecenia z left join zlecenia_kursy zk on zk.id_zlecenia = z.id_zlecenia left join nadania n on n.id_zlecenia = z.id_zlecenia where n.id_skrytki = new.id_skrytki and zk.id_kursu is null) + (select count(*) from odbiory o where o.id_skrytki = new.id_skrytki and o.data_odebrania is null) > 0 then
        raise exception 'Zajęta skrytka';
        return null;
    end if;
    return new;
end;
$insert_nadania$
language plpgsql;

create or replace trigger tr_nadania before insert on nadania for each row execute procedure insert_nadania();
