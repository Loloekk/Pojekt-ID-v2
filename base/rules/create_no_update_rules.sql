--CREATE RULE no_update_osoby AS ON UPDATE TO osoby DO INSTEAD NOTHING; 
CREATE RULE no_update_stanowiska AS ON UPDATE TO stanowiska DO INSTEAD NOTHING; 
CREATE RULE no_update_stanowiska_osoby AS ON UPDATE TO stanowiska_osoby DO INSTEAD NOTHING; 
CREATE RULE no_update_uprawnienia AS ON UPDATE TO uprawnienia DO INSTEAD NOTHING; 
CREATE RULE no_update_osoby_uprawnienia AS ON UPDATE TO osoby_uprawnienia DO INSTEAD NOTHING; 
--CREATE RULE no_update_rodzaje_pojazdow AS ON UPDATE TO rodzaje_pojazdow DO INSTEAD NOTHING; 
CREATE RULE no_update_pojazdy AS ON UPDATE TO pojazdy DO INSTEAD NOTHING; 
CREATE RULE no_update_rodzaje_przegladow AS ON UPDATE TO rodzaje_przegladow DO INSTEAD NOTHING; 
--CREATE RULE no_update_przeglady_rod_pojazdy AS ON UPDATE TO przeglady_rod_pojazdy DO INSTEAD NOTHING; 
CREATE RULE no_update_magazyny AS ON UPDATE TO magazyny DO INSTEAD NOTHING; 
CREATE RULE no_update_paczkomaty AS ON UPDATE TO paczkomaty DO INSTEAD NOTHING; 
CREATE RULE no_update_zlecenia AS ON UPDATE TO zlecenia DO INSTEAD NOTHING; 
CREATE RULE no_update_zlecenia_kursy AS ON UPDATE TO zlecenia_kursy DO INSTEAD NOTHING; 
CREATE RULE no_update_zlecenia_magazyny AS ON UPDATE TO zlecenia_magazyny DO INSTEAD NOTHING; 
CREATE RULE no_update_skrytki AS ON UPDATE TO skrytki DO INSTEAD NOTHING; 
CREATE RULE no_update_nadania AS ON UPDATE TO nadania DO INSTEAD NOTHING; 
CREATE RULE no_update_deklaracja_wypakowan AS ON UPDATE TO deklaracja_wypakowan DO INSTEAD NOTHING; 

create or replace function tr_no_update_osoby()
returns trigger as
$$
begin
 if new.id_osoby != old.id_osoby then
  return null;
 end if;
 return new;
end;
$$ language plpgsql;

drop trigger if exists tr_no_update_osoby on osoby;
create trigger tr_no_update_osoby before update on osoby
for each row execute procedure tr_no_update_osoby();


create or replace function tr_no_update_rodzaje_pojazdow()
returns trigger as
$$
begin
 if new.id_rodzaju != old.id_rodzaju then
  return null;
 end if;
 return new;
end;
$$ language plpgsql;

drop trigger if exists tr_no_update_rodzaje_pojazdow on rodzaje_pojazdow;
create trigger tr_no_update_rodzaje_pojazdow before update on rodzaje_pojazdow
for each row execute procedure tr_no_update_rodzaje_pojazdow();


create or replace function tr_no_update_przeglady_rod_pojazdy()
returns trigger as
$$
begin
 if new.id_rodzaju != old.id_rodzaju or new.id_przegladu!=old.id_przegladu then
  return null;
 end if;
 return new;
end;
$$ language plpgsql;

drop trigger if exists tr_no_update_przeglady_rod_pojazdy on przeglady_rod_pojazdy;
create trigger tr_no_update_przeglady_rod_pojazdy before update on przeglady_rod_pojazdy
for each row execute procedure tr_no_update_przeglady_rod_pojazdy();
