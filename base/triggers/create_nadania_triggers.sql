create or replace function insert_nadania() returns trigger AS
$insert_nadania$
begin
    if (select count(*) from nadania n where n.id_zlecenia = new.id_zlecenia) > 0 then 
        raise exception 'Ta przesyłka została już nadana.';
        return null;
    end if;
    if isEmptySkrytki(new.id_skrytki) is not null then
        raise exception 'Zajęta skrytka';
        return null;
    end if;
    insert into odbiory values (new.id_zlecenia,new.id_skrytki,null,null);
    return new;
end;
$insert_nadania$
language plpgsql;

drop trigger if exists tr_insert_nadania on nadania;
create trigger tr_insert_nadania before insert on nadania for each row execute procedure insert_nadania();
