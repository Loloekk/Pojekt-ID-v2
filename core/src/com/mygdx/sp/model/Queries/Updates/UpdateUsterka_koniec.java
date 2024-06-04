package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class UpdateUsterka_koniec implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nr_rej = args.get(0).toString();
        String opis = args.get(1).toString();
        if(!check(args))
            return null;
        return "update usterki set data_zakonczenia_naprawy = now() " +
                "WHERE id_pojazdu = " + "(SELECT id_pojazdu FROM pojazdy WHERE nr_rejestracyjny='" + nr_rej + "') " +
                "AND opis='" + opis + "';";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Numer rejestracyjny", "Opis");
    }
    @Override
    public String toString() {
        return "Zakoncz naprawe usterki";
    }
}
