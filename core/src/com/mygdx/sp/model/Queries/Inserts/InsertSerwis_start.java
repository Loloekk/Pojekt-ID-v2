package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertSerwis_start implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nr_rej = args.get(0).toString();
        String id_rodz = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into serwis values ("
                + "(SELECT id_pojazdu FROM pojazdy WHERE nr_rejestracyjny='" + nr_rej + "')"
                + "'," + id_rodz + ")";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Nr rejestracyjny", "Id przegladu");
    }
    @Override
    public String toString() {
        return "Oddaj pojazd do serwisu";
    }
}
