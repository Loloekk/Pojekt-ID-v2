create or replace function insert_kursy() returns trigger as 
$$
begin
    if coalesce(getMagazynPojazdu(new.id_pojazdu),-1) != new.magazyn_start then return null; end if;
    if coalesce(getMagazynOsoby(new.id_osoby),-1) != new.magazyn_start then return null; end if;
    if hasUprawnienieOsoby(new.id_osoby,getWymaganeUprawnieniePojazdu(new.id_pojazdu)) then return new; end if;
    return null;
end;
$$
language plpgsql;


drop trigger if exists tr_insert_kursy on kursy;
create trigger tr_insert_kursy before insert on kursy for each row execute procedure insert_kursy();