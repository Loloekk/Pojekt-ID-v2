package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertOsoba implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        TurboString imie = args.get(0);
        TurboString nazw = args.get(1);
        TurboString pesel = args.get(2);
        TurboString tel = args.get(3);
        TurboString mail = args.get(4);
        if(!check(args))
            return null;
        return "insert into osoby values (default, "
                + (!pesel.toString().isEmpty() ? "NULL" : "'" + pesel.toString() + "'") + ",'"
                + imie.toString() + "','"
                + nazw.toString() + "','"
                + tel.toString() + "','"
                + mail.toString() + "');";
    }
    @Override
    public Boolean check(List<TurboString> args) {
        TurboString imie = args.get(0);
        TurboString nazw = args.get(1);
        TurboString pesel = args.get(2);
        TurboString tel = args.get(3);
        TurboString mail = args.get(4);
        if(imie.toString().isEmpty() || nazw.toString().isEmpty() || tel.toString().isEmpty() || mail.toString().isEmpty())
            return false;
        if(!pesel.toString().isEmpty() && pesel.toString().length()!=11)
            return false;
        return true;
    }

    @Override
    public List<String> getFields() {
        return List.of("Imie","Nazwisko","PESEL","Numer telefonu","E-mail");
    }
    @Override
    public String toString()
    {
        return "Dodaj osobe";
    }
}
