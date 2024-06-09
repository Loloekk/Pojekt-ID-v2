package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class UpdateSerwis_koniec implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nr_rej = args.get(0).toString();
        String id_przeg = args.get(1).toString();
        if(!check(args))
            return null;
        return "update serwis set data_zakonczenia = now() WHERE id_przegladu=" + id_przeg + " and id_pojazdu=" + "(SELECT id_pojazdu FROM pojazdy WHERE nr_rejestracyjny='" + nr_rej + "');";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Numer rejestracyjny");
        l.add("Id przegladu");
        return l;
    }
    @Override
    public String toString() {
        return "Zakoncz serwis pojazdu";
    }
}
